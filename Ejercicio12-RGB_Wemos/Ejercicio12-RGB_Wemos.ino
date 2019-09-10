/*
   Ejercicio12 - RGB Wemos
   Web: https://www.aprendiendoarduino.com/cursos/programacion-arduino-2019/
   Montaje: https://github.com/jecrespo/aprendiendoarduino-Curso_Programacion_Arduino_2019/blob/master/Esquemas%20Montajes%20Pr%C3%A1cticas%20Fritzing/Curso_Programacion-Montaje%20Arduino_bb.png
*/
//Librería LEDs RGB
#include <Adafruit_NeoPixel.h>

//Definición pines
#define PIN   D4
#define LED_NUM 7

//Objeto Leds
Adafruit_NeoPixel leds = Adafruit_NeoPixel(LED_NUM, PIN, NEO_GRB + NEO_KHZ800);

//Variables globales
int velocidad = 200;

void setup() {
  leds.begin(); // This initializes the NeoPixel library.
  Serial.begin(9600);
}

void loop() {
  for (int j = 1; j < 5; j++) {
    for (int i = 1; i < LED_NUM; i++) {
      leds.setPixelColor(i, leds.Color(0,10,0));
      leds.show();
      delay(velocidad);
      leds.setPixelColor(i, leds.Color(0,0,0));
    }
  }
  Serial.println(velocidad);
  velocidad -= 20;
  if (velocidad < 20)
    velocidad = 200;
}
