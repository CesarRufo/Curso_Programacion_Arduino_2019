/*
   Ejercicio10 - Alarma
   Web: https://www.aprendiendoarduino.com/cursos/programacion-arduino-2019/
   Montaje: https://github.com/jecrespo/aprendiendoarduino-Curso_Programacion_Arduino_2019/blob/master/Esquemas%20Montajes%20Pr%C3%A1cticas%20Fritzing/Curso_Programacion-Montaje%20Arduino_bb.png
*/

//Librerías pantalla LCD
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//Objeto pantalla
LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

//Librería DHT11
#include <SimpleDHT.h>

//Definición pines
#define PIN_BUZZER 8
#define PIN_DHT 11
#define UMBRAL 24
#define NOTE_C5  523  //Frecuencia de sonido del buzzer
#define PIN_LED_1 4
#define PIN_LED_2 5 //PWM
#define PIN_LED_3 6 //PWM
#define PIN_LED_4 7

//Objeto DHT11
SimpleDHT11 dht11(PIN_DHT);

//Variables globales
boolean alarma_temperatura;

void setup() {
  //Inicializo puerto serie
  Serial.begin(9600);

  //Inicializo Pines
  pinMode(PIN_LED_1, OUTPUT);
  pinMode(PIN_LED_2, OUTPUT);
  pinMode(PIN_LED_3, OUTPUT);
  pinMode(PIN_LED_4, OUTPUT);

  //Inicializo pantalla
  Serial.println(F("Inicializando pantalla..."));
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Inicializando...");
  delay(2000);
  lcd.clear();

  if (lee_temperatura () > UMBRAL) {
    alarma_temperatura = true;
    tone(PIN_BUZZER, NOTE_C5);
    Serial.println("ALARMA!!");
    lcd.setCursor(0, 1);
    lcd.print("ALARMA!!        ");

  }
  else {
    alarma_temperatura = false;
    noTone(PIN_BUZZER);
    Serial.println("TEMPERAT. NORMAL");
    lcd.setCursor(0, 1);
    lcd.print("TEMPERAT. NORMAL");
  }
}

void loop() {
  int temp = lee_temperatura ();
  if (temp > UMBRAL) {
    if (!alarma_temperatura) {
      alarma_temperatura = true;
      tone(PIN_BUZZER, NOTE_C5);
      Serial.println("ALARMA!!");
      lcd.setCursor(0, 1);
      lcd.print("ALARMA!!        ");
    }
  }
  else {
    if (alarma_temperatura) {
      alarma_temperatura = false;
      noTone(PIN_BUZZER);
      Serial.println("TEMPERAT. NORMAL");
      lcd.setCursor(0, 1);
      lcd.print("TEMPERAT. NORMAL");
    }
  }
    //Actualizar LEDs
    switch (temp) {
      case UMBRAL + 4:
        digitalWrite(PIN_LED_1, HIGH);
        digitalWrite(PIN_LED_2, HIGH);
        digitalWrite(PIN_LED_3, HIGH);
        digitalWrite(PIN_LED_4, HIGH);
        break;
      case UMBRAL + 3:
        digitalWrite(PIN_LED_1, HIGH);
        digitalWrite(PIN_LED_2, HIGH);
        digitalWrite(PIN_LED_3, HIGH);
        digitalWrite(PIN_LED_4, LOW);
        break;
      case UMBRAL + 2:
        digitalWrite(PIN_LED_1, HIGH);
        digitalWrite(PIN_LED_2, HIGH);
        digitalWrite(PIN_LED_3, LOW);
        digitalWrite(PIN_LED_4, LOW);
        break;
      case UMBRAL + 1:
        digitalWrite(PIN_LED_1, HIGH);
        digitalWrite(PIN_LED_2, LOW);
        digitalWrite(PIN_LED_3, LOW);
        digitalWrite(PIN_LED_4, LOW);
        break;
      default:
        digitalWrite(PIN_LED_1, LOW);
        digitalWrite(PIN_LED_2, LOW);
        digitalWrite(PIN_LED_3, LOW);
        digitalWrite(PIN_LED_4, LOW);
       break;
    }
  }


float lee_temperatura () {

  byte temperature = 0;
  byte humidity = 0;
  int err = dht11.read(&temperature, &humidity, NULL);

  if (err != SimpleDHTErrSuccess) {
    Serial.println("Read DHT11 failed, err= " + String(err));
    Serial.println("---------------------");

    temperature = 0;
    delay(1500);
  }
  else {
    Serial.println("Temperatura: " + String(temperature));
    Serial.println("Humedad: " + String(humidity));
    Serial.println("---------------------");
    lcd.setCursor(0, 0);
    lcd.print("Tem=");
    lcd.setCursor(4, 0);
    lcd.print(temperature);
    lcd.setCursor(8, 0);
    lcd.print("Hum=");
    lcd.setCursor(12, 0);
    lcd.print(humidity);
    delay(1500);
  }
  return temperature;
}
