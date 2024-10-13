// Script basado en ChepeCarlos de ALSW, Tutorial Completo en https://nocheprogramacion.com

//Librerias para ESP32
#if defined(ESP32)
#include <WiFi.h>
#include <WiFiMulti.h>
WiFiMulti wifiMulti;
#endif

#include "data.h"

int pinLed = 2;
boolean Estado = false;

//Variables de control de espera del cliente wifi
const uint32_t TiempoEsperaWifi = 5000;
unsigned long TiempoActual = 0;
unsigned long TiempoAnterior = 0;
const long TiempoCancelacion = 500;

//Inicializar el servidor en el puerto 80
WiFiServer servidor(80);


void setup() {
  Serial.begin(115200);
  Serial.println("\nIniciando multi Wifi");

  pinMode(pinLed, OUTPUT);
  digitalWrite(pinLed, 0);

  //Puedes tratar de conectarte hasta a dos conexiones
  wifiMulti.addAP(ssid_1, password_1);
  wifiMulti.addAP(ssid_2, password_2);

  //Muestra mensaje sobre estado de la conexión
  WiFi.mode(WIFI_STA);
  Serial.print("Conectando a Wifi ..");
  while (wifiMulti.run(TiempoEsperaWifi) != WL_CONNECTED) {
    Serial.print(".");
  }
  Serial.println(".. Conectado");
  Serial.print("SSID:");
  Serial.print(WiFi.SSID());
  Serial.print(" IP:");
  Serial.println(WiFi.localIP());

  //Inicia el servidor que hemos definido más arriba
  servidor.begin();

}

void loop() {
  //Escucha la disponibilidad de clientes
  WiFiClient cliente = servidor.available();

  //Si hay un cliente disponible, muestralo
  if (cliente) {
    Serial.println("Nuevo Cliente");
    TiempoActual = millis();
    TiempoAnterior = TiempoActual;
    String LineaActual = "";

    //Manten la conexión activa mientras sea posible y no tarde mucho en responder
    while (cliente.connected() && TiempoActual - TiempoAnterior <= TiempoCancelacion) {
      
      //Si hay información en bytes del cliente, muestralo
      if (cliente.available()) {
        TiempoActual = millis();
        char Letra = cliente.read();
        
        //Lee letra por letra y añadelas para ir formando las queries
        if (Letra == '\n') {
          if (LineaActual.length() == 0) {
            digitalWrite(pinLed, Estado);
            ResponderCliente(cliente);
            break;
          } else {
            Serial.println(LineaActual);
            VerificarMensaje(LineaActual);
            LineaActual = "";
          }
        }  else if (Letra != '\r') {
          LineaActual += Letra;
        }
      }
    }

    //Desconecta si el cliente interrumpe la conexión
    cliente.stop();
    Serial.println("Cliente Desconectado");
    Serial.println();
  }
}


void VerificarMensaje(String Mensaje) {
  if (Mensaje.indexOf("GET /encender") >= 0) {
    Serial.println("Encender Led");
    Estado = true;
  } else if (Mensaje.indexOf("GET /apagar") >= 0) {
    Serial.println("Apagar Led");
    Estado = false;
  }
}

void ResponderCliente(WiFiClient& cliente) {
  cliente.print(Pagina);
  cliente.print("Hola ");
  cliente.print(cliente.remoteIP());
  cliente.print("<br>Estado del led: ");
  cliente.print(Estado ? "Encendida" : "Apagada");
  cliente.print("<br>Cambia el Led: ");
  cliente.print("<a href = '/");
  cliente.print(Estado ? "apagar" : "encender");
  cliente.print("'>Cambiar </a><br>");
  cliente.print("</html>");
}