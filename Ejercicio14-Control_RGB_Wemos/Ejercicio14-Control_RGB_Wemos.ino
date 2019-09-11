/*
   Ejercicio14 - Control RGB Wemos
   Web: https://www.aprendiendoarduino.com/cursos/programacion-arduino-2019/
   Montaje: https://github.com/jecrespo/aprendiendoarduino-Curso_Programacion_Arduino_2019/blob/master/Esquemas%20Montajes%20Pr%C3%A1cticas%20Fritzing/Curso_Programacion-Montaje%20Arduino_bb.png
*/
//Librería LEDs RGB
#include <Adafruit_NeoPixel.h>

//Definición pines
#define PIN_BOTON_B D3
#define PIN   D4
#define LED_NUM 7

//Objeto Leds
Adafruit_NeoPixel leds = Adafruit_NeoPixel(LED_NUM, PIN, NEO_GRB + NEO_KHZ800);

//Variables globales
int velocidad = 200;
int color;
int colores[3] = {0, 0, 0};
boolean encendido = 0;  //Sistema encendido/apagado
int led = 1; //Led que enciendo para efecto
boolean anterior_b;
unsigned long tiempo_pulsacion;
unsigned long tiempo_led;

void setup() {
  //Inicializo puerto serie
  Serial.begin(9600);
  // This initializes the NeoPixel library.
  leds.begin();
  //Inicializo Pines
  pinMode(PIN_BOTON_B, INPUT);

  anterior_b = digitalRead(PIN_BOTON_B);

  for (int i = 0; i < LED_NUM ; i++){
    leds.setPixelColor (i, leds.Color (0,0,0));
    leds.show();
    delay (500);
  }
}

void loop() {

  boolean estado_b = digitalRead(PIN_BOTON_B);

  if (anterior_b != estado_b) {
    if (estado_b == LOW) {  //flanco ascendente pull-up
      tiempo_pulsacion = millis();  //tomo timepo al pulsar
      Serial.println(F("Pulsado boton B"));
    }
    else {  //flanco descendente
      unsigned long duracion_pulso = millis() - tiempo_pulsacion; //Aqui hay un bug por el millis overflow
      Serial.println("La pulsacion ha durado: " + String(duracion_pulso) + " ms.");
      if (duracion_pulso < 2000) {  //corta
        if (encendido) {  //Solo si esta encendido el sistema
          colores[color] = 0;
          color++;

          if (color > 2)
            color = 0;

          colores[color] = 10;
        }
      }
      else if (duracion_pulso < 10000) {  //larga
        if (encendido) {
          encendido = 0;
          //apago leds
          for (int i = 0; i < LED_NUM; i++) {
            leds.setPixelColor(i, leds.Color(0, 0, 0));
          }
          leds.show();
        }
        else {
          encendido = 1;
          leds.setPixelColor(0, leds.Color(10, 10, 10));  //Enciendo led central
          leds.show();
          tiempo_led = millis();
          led = 1;  //empiezo el efecto en el led 1
        }
      }
      else {
        Serial.println("pulsación demasiado larga");
      }
    }
  }
  anterior_b = estado_b;

  //actualizo led cuando toca (200 ms)
  if (encendido) {
    if ((millis() - tiempo_led) > 200) {
      tiempo_led = millis();
      if (led == 1)
        leds.setPixelColor(LED_NUM-1,leds.Color(0, 0, 0));
      else
        leds.setPixelColor(led - 1, leds.Color(0, 0, 0));
      leds.setPixelColor(led, leds.Color(colores[0], colores[1], colores[2]));
      leds.show();
      led++;
      if (led == LED_NUM)
        led = 1;
    }
  }
}  
