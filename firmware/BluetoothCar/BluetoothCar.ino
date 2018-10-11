/*
  Скетч к проекту "Bluetooth машинка на Arduino"
  Страница проекта (схемы, описания): https://alexgyver.ru/bluetooth-car/
  Исходники на GitHub: https://github.com/AlexGyver/BluetoothCar
  Нравится, как написан и закомментирован код? Поддержи автора! https://alexgyver.ru/support_alex/
  Автор: AlexGyver Technologies, 2018
  http://AlexGyver.ru/
*/

#define MOTOR_MAX 255	// максимальный сигнал на мотор (max 255)
#define JOY_MAX 40   	// рабочий ход джойстика (из приложения)

#define IN1 2
#define IN2 3         // IN2 обязательно должен быть ШИМ пином!!!
#define IN3 10
#define IN4 11        // IN4 обязательно должен быть ШИМ пином!!!

#define BT_TX 13
#define BT_RX 12

/*
	Bluetooth шлёт пакет вида $valueX valueY;
	моя функция parsing разбивает этот пакет в массив intData
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
GMotor motorL(IN1, IN2);
GMotor motorR(IN3, IN4);

#include <SoftwareSerial.h>
SoftwareSerial btSerial(12, 13); // TX, RX

void setup() {
  Serial.begin(9600);
  btSerial.begin(9600);
  //PWMfrequency(IN2, 1);   // 31 кГц
}

void loop() {
  parsing();       				// функция парсинга
  if (recievedFlag) {			// если получены данные
    recievedFlag = false;
    dataX = intData[0];
    dataY = intData[1];
    /*for (byte i = 0; i < PARSE_AMOUNT; i++) { // выводим элементы массива
      Serial.print(intData[i]); Serial.print(" ");
      } Serial.println();*/
    Serial.print(dutyR);
    Serial.print(" ");
    Serial.println(dutyL);
  }

  if (dataX == 0 && dataY == 0) {   // если мы в "мёртвой" зоне
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

boolean getStarted;
byte index;
String string_convert = "";
void parsing() {
  if (btSerial.available() > 0) {
    char incomingByte = btSerial.read();        // обязательно ЧИТАЕМ входящий символ
    if (getStarted) {                         // если приняли начальный символ (парсинг разрешён)
      if (incomingByte != ' ' && incomingByte != ';') {   // если это не пробел И не конец
        string_convert += incomingByte;       // складываем в строку
      } else {                                // если это пробел или ; конец пакета
        intData[index] = string_convert.toInt();  // преобразуем строку в int и кладём в массив
        string_convert = "";                  // очищаем строку
        index++;                              // переходим к парсингу следующего элемента массива
      }
    }
    if (incomingByte == '$') {                // если это $
      getStarted = true;                      // поднимаем флаг, что можно парсить
      index = 0;                              // сбрасываем индекс
      string_convert = "";                    // очищаем строку
    }
    if (incomingByte == ';') {                // если таки приняли ; - конец парсинга
      getStarted = false;                     // сброс
      recievedFlag = true;                    // флаг на принятие
    }
  }
}
