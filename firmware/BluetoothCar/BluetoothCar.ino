/*
  Скетч к проекту "Bluetooth машинка на Arduino"
  Страница проекта (схемы, описания): https://alexgyver.ru/bluetooth-car/
  Исходники на GitHub: https://github.com/AlexGyver/BluetoothCar
  Нравится, как написан и закомментирован код? Поддержи автора! https://alexgyver.ru/support_alex/
  Автор: AlexGyver Technologies, 2018
  http://AlexGyver.ru/
*/

#define MOTOR_MAX 255     // максимальный сигнал на мотор (max 255)
#define JOY_MAX 40        // рабочий ход джойстика (из приложения)
#define minDuty 0         // скорость, при которой мотор должен начинать крутится
#define RIGHT_MOTOR_DIRECTION NORMAL//смени, если мотор крутится не в ту сторону (NORMAL или REVERSE)
#define LEFT_MOTOR_DIRECTION NORMAL//смени, если мотор крутится не в ту сторону (NORMAL или REVERSE)

#define LEFT_MOTOR_D 2
#define LEFT_MOTOR_PWM 3  //обязательно должен быть ШИМ пином!!!
#define RIGHT_MOTOR_D 10
#define RIGHT_MOTOR_PWM 11//обязательно должен быть ШИМ пином!!!

#define BT_TX 13
#define BT_RX 12

/*
  Bluetooth шлёт пакет вида $valueX valueY;
  моя функция parsing разбивает этот пакет в массив intData
  Парсинг полностью прозрачный, не блокирующий и с защитой от битого пакета,
  так как присутствует строгий синтаксис посылки. Без хешсуммы конечно, но и так норм
*/

#include "GyverMotor.h"
GMotor motorR(DRIVER2WIRE, RIGHT_MOTOR_D, RIGHT_MOTOR_PWM, HIGH);//смени HIGH на LOW, если мотор работает неправильно
GMotor motorL(DRIVER2WIRE, LEFT_MOTOR_D, LEFT_MOTOR_PWM, HIGH);//смени HIGH на LOW, если мотор работает неправильно

#include <SoftwareSerial.h>
SoftwareSerial BTserial(BT_TX, BT_RX); // TX, RX

boolean doneParsing, startParsing;
int dataX, dataY;
String string_convert;

void setup(){
  BTserial.begin(9600);
  motorR.setMinDuty(minDuty);
  motorL.setMinDuty(minDuty);
  motorR.setDirection(RIGHT_MOTOR_DIRECTION);
  motorL.setDirection(LEFT_MOTOR_DIRECTION);
  //PWMfrequency(RIGHT_MOTOR_PWM, 1);   // 31 кГц
  //PWMfrequency(LEFT_MOTOR_PWM, 1);    // 31 кГц
}

void loop(){
  parsing();             // функция парсинга
  if (doneParsing){      // если получены данные
    doneParsing = false;
    byte dutyR, dutyL;
    if (dataX == 0 && dataY == 0){   // если мы в "мёртвой" зоне
      motorR.setMode(STOP);           // не двигаемся
      motorL.setMode(STOP);
      dutyR = 0;
      dutyL = 0;
    } 
    else{
      byte signalX, signalY;
      signalY = map((dataY), -JOY_MAX, JOY_MAX, -MOTOR_MAX, MOTOR_MAX);         // сигнал по Y
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
}

void parsing(){
  if (BTserial.available() > 0) {
    char incomingChar = BTserial.read();//читаем из буфера
    if (startParsing){//начать принятие пакета
      if (incomingChar == ' '){//принят dataX
        dataX = string_convert.toInt();
        string_convert = "";
      }
      else if (incomingChar == ';'){//передача пакета завершена
        dataY = string_convert.toInt();
        string_convert = "";
        startParsing = false;
        doneParsing = true;//парсинг окончен, можно переходить к движению
      }
      else{
        string_convert += incomingChar;
      }
    }
    if (incomingChar == '$'){//начало парсинга
      startParsing = true;
    }
  }
}
