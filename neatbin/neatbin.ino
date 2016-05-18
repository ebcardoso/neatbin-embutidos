//Programa: Conectando Sensor Ultrassonico HC-SR04 ao Arduino
//Autor: FILIPEFLOP

//Carrega a biblioteca do sensor ultrassonico
#include "Ultrasonic.h"

//carrega a biblioteca da telinha
#include <Wire.h>
#include "LiquidCrystal_I2C.h"
// Inicializa o display no endereco 0x27
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);

//Define os pinos para o trigger e echo
#define pino_trigger 4
#define pino_echo 5

//Inicializa o sensor nos pinos definidos acima
Ultrasonic ultrasonic(pino_trigger, pino_echo);

void setup()
{
  lcd.begin (16,2);
  lcd.setBacklight(HIGH);

  lcd.setCursor(0,0);
    lcd.print("Sensor Distancia");
  lcd.setCursor(0,1);
    lcd.print("Lendo dados do sensor...");
}

void loop()
{
  //Le as informacoes do sensor, em cm e pol
  float cmMsec, inMsec;
  long microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  inMsec = ultrasonic.convert(microsec, Ultrasonic::IN);
  //Exibe informacoes no serial monitor
  lcd.setCursor(0,1);
    lcd.print("Dist: ");
    lcd.print(cmMsec);
    lcd.print("cm      ");
    //lcd.println(inMsec);
  delay(1000);
}
