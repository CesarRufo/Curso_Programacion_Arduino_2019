/*
   Ejercicio03 – Leer LDR y mostrar Gráfica
   Web: https://www.aprendiendoarduino.com/cursos/programacion-arduino-2019/
   Montaje: https://github.com/jecrespo/aprendiendoarduino-Curso_Programacion_Arduino_2019/blob/master/Esquemas%20Montajes%20Pr%C3%A1cticas%20Fritzing/Curso_Programacion-Montaje%20Arduino_bb.png
*/

//Librerías pantalla LCD
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//Objeto pantalla
LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

//Definición pines
#define PIN_LDR A1

//Variables globales
int maximo = 0;
int minimo = 1023;
int sensorValue;

void setup() {
  //Inicializo puerto serie
  Serial.begin(9600);

  //Inicializo pantalla
  Serial.println(F("Inicializando pantalla..."));
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Inicializando...");
  delay(2000);
  lcd.clear();

}

void loop() {

  sensorValue = analogRead(PIN_LDR);
  maximo = max(maximo, sensorValue);
  minimo = min(minimo, sensorValue);

  lcd.setCursor(0, 0);
  lcd.print("Luz actual=");
  lcd.setCursor(11, 0);
  lcd.print(sensorValue);
  lcd.setCursor(0, 1);
  lcd.print("Max=");
  lcd.setCursor(4, 1);
  lcd.print(maximo);
  lcd.setCursor(8, 1);
  lcd.print("min=");
  lcd.setCursor(12, 1);
  lcd.print(minimo);

  Serial.println("Luz actual= "  + (String)sensorValue);
  Serial.println("Máximo= " + (String)maximo + "  Mínimo= " + (String)minimo);
  Serial.println("------------------------");

  delay(500);
 
}
