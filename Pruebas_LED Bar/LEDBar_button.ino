byte ledPins[] = { 14, 27, 13, 5, 15, 4, 2, 19, 18, 21 };
int buttonPin = 12;
int contador = 0;
const int maxContador = 10;

void setup() {
  // activa todos los LEDs y pines:
  for (int i = 0; i < maxContador; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }
  pinMode(buttonPin, INPUT);
  //activa el serial para las pruebas
  //Serial.begin(115200);
}

void loop() {
  // Si lee que el botón tiene energia:
  if (digitalRead(buttonPin) == LOW) {
    //Controlar la variable "contador" 
    //Serial.println("Ha entrado, contador: " + String(contador) + "\n");

    //Incrementaamos el valor de contador que valdrá un rango entre 1 y 11 asegurandonos que nunca exceda el valor de maxContador, haciendo que el contador se reinicie a 0 cuando llega a ese valor.
    contador = (contador + 1) % (maxContador + 1);

    //Llamamos a la función de activar pines
    updateLEDBar();
    delay(200);
  }
}

void updateLEDBar() {
  //Encendemos o apagamos los pines por orden en función del contador
  for (int i = 0; i < maxContador; i++) {
    if (i < contador) {
      digitalWrite(ledPins[i], HIGH);
    } else {
      digitalWrite(ledPins[i], LOW);
    }
  }
}

