/*
   Ejercicio05 – Mover Servo
   Web: https://www.aprendiendoarduino.com/cursos/programacion-arduino-2019/
   Montaje: https://github.com/jecrespo/aprendiendoarduino-Curso_Programacion_Arduino_2019/blob/master/Esquemas%20Montajes%20Pr%C3%A1cticas%20Fritzing/Curso_Programacion-Montaje%20Arduino_bb.png
*/

//Librerías pantalla LCD
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//Objeto pantalla
LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

//Librería Servo
#include <Servo.h>

//Objeto servo
Servo miservo;

//Definición pines
#define PIN_SERVO 9
#define PIN_POT A0

//Variables globales
int pos;

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

  //Inicializo Servo
  Serial.println(F("Inicializando servo..."));
  miservo.attach(PIN_SERVO);

}

void loop() {

  lcd.clear();
  
  pos = int (10 + ((float (analogRead(PIN_POT)) / 1024) * 160));
  miservo.write(pos);
    
  lcd.setCursor(0, 0);
  lcd.print("Posicion=");
  lcd.setCursor(9, 0);
  lcd.print(pos);

  Serial.println("Posicion= "  + (String)pos);
  delay(100);

}
