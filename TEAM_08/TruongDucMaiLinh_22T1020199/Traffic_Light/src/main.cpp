#include <Arduino.h>

/* ===== LED PINS ===== */
#define RED_LED     25
#define YELLOW_LED  33
#define GREEN_LED   32

/* ===== LDR ===== */
#define LDR_PIN 4   // ADC

/* ===== TIME (ms) ===== */
unsigned long redTime    = 5000;
unsigned long yellowTime = 3000;
unsigned long greenTime  = 7000;

unsigned long previousMillis = 0;
int currentState = 0;

void setup() {
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(LDR_PIN, INPUT);

  Serial.begin(115200);
  delay(1000);

  digitalWrite(RED_LED, HIGH);
  Serial.println("SYSTEM START");
}

void loop() {
  unsigned long now = millis();

  /* ===== READ LDR ===== */
  int ldrValue = analogRead(LDR_PIN);
  Serial.print("LDR = ");
  Serial.println(ldrValue);

  /* ===== NIGHT MODE ===== */
  if (ldrValue < 1500) {  
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, LOW);

    digitalWrite(YELLOW_LED, HIGH);
    delay(500);
    digitalWrite(YELLOW_LED, LOW);
    delay(500);
    return;
  }

  /* ===== NORMAL TRAFFIC LIGHT ===== */
  if (currentState == 0 && now - previousMillis >= redTime) {
    previousMillis = now;
    currentState = 1;

    digitalWrite(RED_LED, LOW);
    digitalWrite(YELLOW_LED, HIGH);
  }
  else if (currentState == 1 && now - previousMillis >= yellowTime) {
    previousMillis = now;
    currentState = 2;

    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
  }
  else if (currentState == 2 && now - previousMillis >= greenTime) {
    previousMillis = now;
    currentState = 0;

    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);
  }
}
