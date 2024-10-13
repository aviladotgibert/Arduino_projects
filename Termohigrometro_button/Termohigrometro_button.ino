#include "DHTesp.h"
DHTesp dht; //Creamos el objeto del sensor DHT

const int PIN_LED = 2;
const int  PIN_BUTTON = 12;
const int dhtPin = 25;//Definimos el pin del dht
int lastSwitchValue = -1;  // Último valor conocido del switch

// the setup function runs once when you press reset or power the board
void setup() {
 // inicializamos el PIN_LED como output y el botón como input.
 pinMode(PIN_LED, OUTPUT);
 pinMode(PIN_BUTTON, INPUT);
 dht.setup(dhtPin, DHTesp::DHT11); //Inicializamos el pin dht y el objecto
 Serial.begin(115200); //Para la conexión serial iniciamos el baud rate en 115200
}

// the loop function runs over and over again forever
void loop() {
  int switchValue = digitalRead(PIN_BUTTON);

 if (switchValue == 1) {
    //Si el pin esta en la posicion 1 entonces enciende el LED en el pin 2
  digitalWrite(PIN_LED,HIGH);
  leerTempHum();
  //Serial.println("Ahora deberia estar encendido");


    // Actualizar el último valor conocido del switch
    lastSwitchValue = switchValue;

 }else{
  if (lastSwitchValue != switchValue) {
    //Serial.println("Ahora deberia estar apagado");
    lastSwitchValue = switchValue;
  }
  digitalWrite(PIN_LED,LOW);
 }

 // Pequeña demora para evitar lecturas rápidas consecutivas
  delay(100);

}

//Creamos una función para ejecutar la lectura del sensor
void leerTempHum () {
  

  //Sacar la información del sensor a partir del dht
  flag:TempAndHumidity newValues = dht.getTempAndHumidity();

  //Juzga si el valor es correcto, que sea diferente a 0
  if (dht.getStatus() != 0) {
    goto flag;               //If there is an error, go back to the flag and re-read the data
  }
 
  //Muestra la temperatura y humedad por pantalla
  //Normal: Serial.println(" Temperature:" + String(newValues.temperature) +  " Humidity:" + String(newValues.humidity));
  //CSV: 
  Serial.println(String(newValues.temperature) +  "," + String(newValues.humidity));

  delay(600000); //que saque los valores cada 10 minutos
}