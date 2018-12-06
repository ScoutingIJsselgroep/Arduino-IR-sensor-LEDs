#include <IRremote.h>

//set D2 as input signal pin
int input_pin = 2;

// 6 PWM port: D3, D5, D6, D9, D10, D11
int r_pin = 9;
int g_pin = 10;
int b_pin = 5;
int y_pin = 6;

// status voor het programma
int state;

// duur voor faden
int duration = 333;

IRrecv irrecv(input_pin);
decode_results signals;

// signaal van de afstandsbediening dat we gaan gebruiken kan hier in
unsigned long firstValue;

void setup() {
  Serial.begin(4800);
  
  irrecv.enableIRIn();

  // zet de LED pins als output, en de LEDs uit
  pinMode(r_pin, OUTPUT);
  pinMode(g_pin, OUTPUT);
  pinMode(b_pin, OUTPUT);
  pinMode(y_pin, OUTPUT);
  digitalWrite(r_pin, 0);
  digitalWrite(g_pin, 0);
  digitalWrite(b_pin, 0);
  digitalWrite(y_pin, 0);

  state = -1;
}


void loop() {
  if(state == -1) {
    if (irrecv.decode(&signals)) {
      Serial.print(signals.value, HEX);
      Serial.println(" <- Assigned");

      // eerst herkende waarde gaan we gebruiken 
      firstValue = signals.value;

      // volgende signaal ontvangen
      irrecv.resume();

      state = 0;
    }
  } else {
    if (irrecv.decode(&signals)) {
      if(firstValue != signals.value) {
        Serial.print(signals.value, HEX);
        Serial.println(" <- Ignored");
        
        // volgende signaal ontvangen
        irrecv.resume();
      } else {
        Serial.print(signals.value, HEX);
        Serial.println(" <- Used");
        
        // volgende signaal ontvangen
        irrecv.resume();

        // naar de volgende stand
        state++;
        
        // alle LEDs laten knipperen
        digitalWrite(r_pin, HIGH);
        digitalWrite(g_pin, HIGH);
        digitalWrite(b_pin, HIGH);
        digitalWrite(y_pin, HIGH);
        delay (300);
        digitalWrite(r_pin, 0);
        digitalWrite(g_pin, 0);
        digitalWrite(b_pin, 0);
        digitalWrite(y_pin, 0);
        delay (300);
        digitalWrite(r_pin, HIGH);
        digitalWrite(g_pin, HIGH);
        digitalWrite(b_pin, HIGH);
        digitalWrite(y_pin, HIGH);
        delay (300);
        digitalWrite(r_pin, 0);
        digitalWrite(g_pin, 0);
        digitalWrite(b_pin, 0);
        digitalWrite(y_pin, 0);
      
        if (state == 1) {
          digitalWrite(r_pin, HIGH);
        } else if (state == 2) {
          digitalWrite(g_pin, HIGH);
        } else if (state == 3) {
          digitalWrite(b_pin, HIGH);
        } else if (state == 4) {
          digitalWrite(y_pin, HIGH);
        } else if (state == 5) {
          digitalWrite(r_pin, HIGH);
          digitalWrite(g_pin, HIGH);
          digitalWrite(b_pin, HIGH);
          digitalWrite(y_pin, HIGH);
        } else {
          // 0 is faden, dit gebeurt hieronder
          state = 0;
        }
      }
    }

    // faden
    if(state == 0) {
      long val = (millis() / 25) % duration;
      int part = duration / 4;
      long fase = ((val % part) * 255) / part;
      
      if(val < part) {
        analogWrite(r_pin, fase);
        analogWrite(g_pin, 0);
        analogWrite(b_pin, 0);
        analogWrite(y_pin, 255 - fase);
      } else if(val < part * 2) {
        analogWrite(r_pin, 255 - fase);
        analogWrite(g_pin, fase);
        analogWrite(b_pin, 0);
        analogWrite(y_pin, 0);
      } else if(val < part * 3) {
        analogWrite(r_pin, 0);
        analogWrite(g_pin, 255 - fase);
        analogWrite(b_pin, fase);
        analogWrite(y_pin, 0);
      } else {
        analogWrite(r_pin, 0);
        analogWrite(g_pin, 0);
        analogWrite(b_pin, 255 - fase);
        analogWrite(y_pin, fase);
      }
    }
  }
}
