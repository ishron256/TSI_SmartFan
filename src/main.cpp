#include <Arduino.h>

#define LED_PIN_3 2  // Built-in LED on most ESP32DevKit boards
#define LED_PIN_1 5  // GPIO 4 for first LED
#define LED_PIN_2 3  // GPIO 6 for second LED


void setup() {
    pinMode(LED_PIN_3, OUTPUT);
    pinMode(LED_PIN_1, OUTPUT);
    pinMode(LED_PIN_2, OUTPUT);
}

void loop() {
// Turn both LEDs on
    digitalWrite(LED_PIN_3, LOW);
    digitalWrite(LED_PIN_1, HIGH);
    digitalWrite(LED_PIN_2, HIGH);
    delay(1000);  // Wait 1 second

// Turn both LEDs off
    digitalWrite(LED_PIN_3, HIGH);
    digitalWrite(LED_PIN_1, LOW);
    digitalWrite(LED_PIN_2, LOW);
    delay(1000);  // Wait 1 second
}