#include <stdint.h>
const int leds [4] = {0, 0, 0, 1};
//uint8_t leds = 0b0001;
const int miVector[4] = {13, 12, 11, 10};
int contador=0;
int simbolo=-1;
//const int verde = 13; // Pin del LED en Arduino Uno
void setup() {
  for (int pin = 10; pin <= 13; pin++) {
    pinMode(pin, OUTPUT);
  }
  Serial.begin(9600);
  //Apagado de interrupciones
  cli();
  TCCR1A = 0; //Resetea el registro TCCR1A a 0
  TCCR1B = 0;

  //Seteado de preescaler
  TCCR1B |= 0b00000100;

  //Permitimos la comparación entre registros
  TIMSK1 |= B00000010;

  OCR1A = 12500;
  sei();
}

void loop() {
  Serial.println(leds[(contador)%4]);
    Serial.println(leds[(contador+simbolo)%4]);
        Serial.println(leds[(contador+2*simbolo)%4]);
            Serial.println();
            delay(777);
}

ISR(TIMER1_COMPA_vect) {
  TCNT1 = 0;

  contador++;
  digitalWrite(miVector[0], leds[(contador)%4] ); // Enciende o apaga el LED según el estado del bit menos significativo de leds
  digitalWrite(miVector[1], leds[(contador+simbolo)%4]); // Enciende o apaga el LED según el estado del segundo bit menos significativo de leds
  digitalWrite(miVector[2], leds[(contador+2*simbolo)%4]); // Enciende o apaga el LED según el estado del tercer bit menos significativo de leds
  digitalWrite(miVector[3], leds[(contador+3*simbolo)%4]); // Enciende o apaga el LED según el estado del bit más significativo de leds
}