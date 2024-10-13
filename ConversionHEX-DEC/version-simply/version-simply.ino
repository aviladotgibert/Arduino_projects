#include "Freenove_WS2812_Lib_for_ESP32.h"

#define LEDS_COUNT 8
#define LEDS_PIN 2
#define CHANNEL 0

String inputString = "";      //a String to hold incoming data
bool stringComplete = false;  // whether the string is complete

Freenove_ESP32_WS2812 strip = Freenove_ESP32_WS2812(LEDS_COUNT, LEDS_PIN, CHANNEL, TYPE_GRB);
int m_color[5][3] = { { 255, 0, 0 }, { 0, 255, 0 }, { 0, 0, 255 }, { 255, 255, 255 }, { 0, 0, 0 } };
int delayval = 100;

void setup() {
  Serial.begin(115200);
  strip.begin();
  //strip.setBrightness(10);
  Serial.println("Introduce el color en formato hexadecimal (ej: FF0000 para rojo): ");
}


void loop() {
  if (Serial.available()) {       // judge whether data has been received
    char inChar = Serial.read();  // read one character
    inputString += inChar;

    //long numero = strtol(hexColor.c_str(), NULL, 16);

    // Convertir cada componente (R, G, B) de hexadecimal a decimal
    long r = strtol(hexColor.substring(0, 2).c_str(), NULL, 16);
    long g = strtol(hexColor.substring(2, 4).c_str(), NULL, 16);
    long b = strtol(hexColor.substring(4, 6).c_str(), NULL, 16);

    u8 m_color[5][3] = { { r, g, b } };

    // Mostrar los valores RGB en la consola
    Serial.print("Rojo: ");
    Serial.print(r);
    Serial.print(", Verde: ");
    Serial.print(g);
    Serial.print(", Azul: ");
    Serial.println(b);

    for (int j = 0; j < 5; j++) {
      for (int i = 0; i < LEDS_COUNT; i++) {
        strip.setLedColorData(i, m_color[j][0], m_color[j][1], m_color[j][2]);  // Set color data.
        strip.show();                                                           // Send color data to LED, and display.
        delay(delayval);                                                        // Interval time of each LED.
      }
      delay(500);  // Interval time of each group of colors.
    }



    if (inChar == '\n') {
      stringComplete = true;
    }
  }
  if (stringComplete) {
    Serial.printf("inputString: %s \n", inputString);
    inputString = "";
    stringComplete = false;
  }








  /*
    hexColor.trim();  // Elimina espacios o saltos de línea innecesarios

    // Verificar que el color sea de 6 caracteres (formato RRGGBB)
    
      //long numero = strtol(hexColor.c_str(), NULL, 16);

      // Convertir cada componente (R, G, B) de hexadecimal a decimal
      long r = strtol(hexColor.substring(0, 2).c_str(), NULL, 16);
      long g = strtol(hexColor.substring(2, 4).c_str(), NULL, 16);
      long b = strtol(hexColor.substring(4, 6).c_str(), NULL, 16);

      // Split them up into r, g, b values
       r = 255 - (hexColor >> 16);
       g = 255 - (hexColor >> 8 & 0xFF);
       b = 255 - (hexColor & 0xFF);

      // Si el LED es de ánodo común, invertir los valores
      u8 m_color[5][3] = {{ r, g, b }};

      // Mostrar los valores RGB en la consola
      Serial.print("Rojo: ");
      Serial.print(r);
      Serial.print(", Verde: ");
      Serial.print(g);
      Serial.print(", Azul: ");
      Serial.println(b);

*/
}