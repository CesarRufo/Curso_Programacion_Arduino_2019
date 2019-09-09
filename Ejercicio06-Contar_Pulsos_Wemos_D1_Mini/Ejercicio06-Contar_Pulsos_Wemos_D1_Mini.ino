/*
   Ejercicio06 - Contar Pulsos Wemos D1 Mini
   Web: https://www.aprendiendoarduino.com/cursos/programacion-arduino-2019/
   Montaje: https://github.com/jecrespo/aprendiendoarduino-Curso_Programacion_Arduino_2019/blob/master/Esquemas%20Montajes%20Pr%C3%A1cticas%20Fritzing/Curso_Programacion-Montaje%20Arduino_bb.png
*/
//Librería Pantalla
#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define PIN_BOTON_B D3

//Define pantalla
#define OLED_RESET 0  // GPIO0

//Objeto Pantalla
Adafruit_SSD1306 display(OLED_RESET);

static boolean anterior_b;
int pulsos_b = 0;

unsigned long tiempo_pulsos = 0;

void setup() {
  Serial.begin(115200);

  //Configure pulsador
  pinMode(PIN_BOTON_B, INPUT);

  anterior_b = digitalRead(PIN_BOTON_B);

  //Pantalla
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 64x48)
}

void loop() {
  boolean estado_b = digitalRead(PIN_BOTON_B);

  if (anterior_b != estado_b) {
    if (estado_b == HIGH) {  //flanco ascendente pull-down
      Serial.println(F("Pulsado boton B"));
      pulsos_b++;
      Serial.println("Numero pulsaciones boton B: " + (String)pulsos_b);
      int tiempo = (millis()-tiempo_pulsos)/1000;
      tiempo_pulsos = millis();
      Serial.println("Tiempo entre pulsos: " + (String)tiempo + " segundos");

      //Imprimir en pantalla oled
      display.clearDisplay();
      display.setTextSize(1);
      display.setCursor(0, 0);
      display.setTextColor(WHITE);
      display.print("Pulsado B");
      display.setCursor(0, 15);
      display.print("Num.: " + String(pulsos_b));
      display.setCursor(0, 30);
      display.print("Time: " + String(tiempo) + "s");
      display.display();
    }
  }
  anterior_b = estado_b;
  delay(50); //Evitar rebotes
}
