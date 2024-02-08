/*
  Скетч к проекту "Bluetooth машинка на Arduino"
  Страница проекта (схемы, описания): https://alexgyver.ru/bluetooth-car/
  Исходники на GitHub: https://github.com/AlexGyver/BluetoothCar
  Переделано: Abdulhayev Muhammadrasul
*/

#define MOTOR_MAX 255	// максимальный сигнал на мотор (max 255)
#define JOY_MAX 40   	// рабочий ход джойстика (из приложения)

#define MOTOR_A_CLK 2
#define MOTOR_A_CCLK 3         // MOTOR_A_CCLK обязательно должен быть ШИМ пином!!!
#define MOTOR_B_CLK 10
#define MOTOR_B_CCLK 11        // MOTOR_B_CCLK обязательно должен быть ШИМ пином!!!

/*
	Bluetooth шлёт пакет вида $valueX valueY;
	моя функция parse разбивает этот пакет в массив intData
	Парсинг полностью прозрачный, не блокирующий и с защитой от битого пакета,
	так как присутствует строгий синтаксис посылки. Без хешсуммы конечно, но и так норм
*/

#define PARSE_AMOUNT 2         // число значений в массиве, который хотим получить

int intData[PARSE_AMOUNT];     // массив численных значений после парсинга
boolean recievedFlag;
int dutyR, dutyL;
int signalX, signalY;
int dataX, dataY;

#include "GyverMotor.h"
GMotor motorL(MOTOR_A_CLK, MOTOR_A_CCLK);
GMotor motorR(MOTOR_B_CLK, MOTOR_B_CCLK);

void setup() {
  Serial.begin(9600);
  PWMfrequency(MOTOR_A_CCLK, 1);   // 31 кГц
}

void loop() {
  parse();       				// функция парсинга
  if (recievedFlag) {			// если получены данные
    recievedFlag = false;
    dataX = intData[0];
    dataY = intData[1];
  }

  if (!dataX && !dataY) {   // если мы в "мёртвой" зоне
    motorR.setMode(STOP);           // не двигаемся
    motorL.setMode(STOP);
    dutyR = 0;
    dutyL = dutyR;
  } else {
    signalY = map((dataY), -JOY_MAX, JOY_MAX, -MOTOR_MAX, MOTOR_MAX);         // сигнал по У
    signalX = map((dataX), -JOY_MAX, JOY_MAX, -MOTOR_MAX / 2, MOTOR_MAX / 2); // сигнал по Х

    dutyR = signalY + signalX;
    dutyL = signalY - signalX;

    if (dutyR > 0) motorR.setMode(FORWARD);
    else motorR.setMode(BACKWARD);

    if (dutyL > 0) motorL.setMode(FORWARD);
    else motorL.setMode(BACKWARD);

    dutyR = constrain(abs(dutyR), 0, MOTOR_MAX);
    dutyL = constrain(abs(dutyL), 0, MOTOR_MAX);
  }
  motorR.setSpeed(dutyR);
  motorL.setSpeed(dutyL);
}

bool started;
int8_t index;
String string_merge = "";

void parse() {
  if (Serial.available() > 0) {
    char receivedByte = Serial.read();        // обязательно ЧИТАЕМ входящий символ
    if (started) {                         // если приняли начальный символ (парсинг разрешён)
      if (receivedByte != ' ' && receivedByte != ';') {   // если это не пробел И не конец
        string_merge += receivedByte;       // складываем в строку
      } else {                                // если это пробел или ; конец пакета
        intData[index] = string_merge.toInt();  // преобразуем строку в int и кладём в массив
        string_merge = "";                  // очищаем строку
        index++;                              // переходим к парсингу следующего элемента массива
      }
    }
    if (receivedByte == '$') {                // если это $
      started = true;                      // поднимаем флаг, что можно парсить
      index = 0;                              // сбрасываем индекс
      string_merge = "";                    // очищаем строку
    }
    if (receivedByte == ';') {                // если таки приняли ; - конец парсинга
      started = false;                     // сброс
      recievedFlag = true;                    // флаг на принятие
    }
  }
}
