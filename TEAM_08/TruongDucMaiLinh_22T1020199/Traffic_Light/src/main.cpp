#include <Arduino.h>


#define RED_LED    25
#define YELLOW_LED 33
#define GREEN_LED  32


unsigned long redTime    = 5000;
unsigned long yellowTime = 3000;
unsigned long greenTime  = 7000;

unsigned long previousMillis = 0;
int currentState = 0; 

void setup() {
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  Serial.begin(115200);
  previousMillis = millis();
  digitalWrite(RED_LED, HIGH); 
  Serial.println("RED ON");
}

void loop() {
  unsigned long now = millis();

  if (currentState == 0 && now - previousMillis >= redTime) {
    previousMillis = now;
    currentState = 1;
    digitalWrite(RED_LED, LOW);
    digitalWrite(YELLOW_LED, HIGH);
    Serial.println("YELLOW ON");
  }
  else if (currentState == 1 && now - previousMillis >= yellowTime) {
    previousMillis = now;
    currentState = 2;
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
    Serial.println("GREEN ON");
  }
  else if (currentState == 2 && now - previousMillis >= greenTime) {
    previousMillis = now;
    currentState = 0;
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);
    Serial.println("RED ON");
  }
}
