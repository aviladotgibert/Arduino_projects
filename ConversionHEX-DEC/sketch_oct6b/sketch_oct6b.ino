#include "Freenove_WS2812_Lib_for_ESP32.h"

#define LEDS_COUNT 8
#define LEDS_PIN 2
#define CHANNEL 0
#define hexColor

Freenove_ESP32_WS2812 strip = Freenove_ESP32_WS2812(LEDS_COUNT, LEDS_PIN, CHANNEL, TYPE_GRB);

void setup() {
  Serial.begin(115200);
  strip.begin();
  strip.setBrightness(10);
  Serial.println("Introduce el color en formato hexadecimal (ej: FF0000 para rojo): ");
}

//u8_t m_color[5][3] = { {255, 0, 0}, {0, 255, 0}, {0, 0, 255}, {255, 255, 255}, {0, 0, 0} };

void loop() {
  //if (Serial.available()) {
    //Pasar codigo hex a rgb
    //Este no funciona: Byte hexColor = Serial.readStringUntil('\n');
    char inChar = Serial.read();  // lee los caracteres uno a uno
    hexColor += inChar;
    Serial.print(hexColor);  //muestra los caracteres

    hexColor.trim();  // Elimina espacios o saltos de línea innecesarios

    // Verificar que el color sea de 6 caracteres (formato RRGGBB)
    if (hexColor.length() == 6) {
      // Convertir cada componente (R, G, B) de hexadecimal a decimal
      //int red = strtol(hexColor.substring(0, 2).c_str(), NULL, 16);
      //int green = strtol(hexColor.substring(2, 4).c_str(), NULL, 16);
      //int blue = strtol(hexColor.substring(4, 6).c_str(), NULL, 16);

      // Split them up into r, g, b values
      long long r = hexColor >> 16;
      long long g = hexColor >> 8 & 0xFF;
      long long b = hexColor & 0xFF;

      // Si el LED es de ánodo común, invertir los valores
      r = 255 - r;
      g = 255 - g;
      b = 255 - b;

      // Mostrar los valores RGB en la consola
      Serial.print("Rojo: ");
      Serial.print(r);
      Serial.print(", Verde: ");
      Serial.print(g);
      Serial.print(", Azul: ");
      Serial.println(b);

      // Ajustar los valores PWM en los pines del LED RGB
      u8_t m_color[5][3] = { r, g, b };

    } else {
      Serial.println("Error: Introduce un valor hexadecimal de 6 dígitos.");
    }
  //}

  //Codigo para arcoiris
  /* for (int j = 0; j < 255; j += 2) {
  for (int i = 0; i < LEDS_COUNT; i++) {
    strip.setLedColorData(i, strip.Wheel((i * 256 / LEDS_COUNT + j) & 255));
  }
  strip.show();
  delay(2);
}
*/

  //Codigo cambio color rojo, verde, azul, blanco, apagado
  /*int delayval = 100;
  for (int j = 0; j < 5; j++) {
    for (int i = 0; i < LEDS_COUNT; i++) {
      strip.setLedColorData(i, m_color[j][0], m_color[j][1], m_color[j][2]);
      strip.show();
      delay(delayval);
    }
    delay(500);
  }
  */
}