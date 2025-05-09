#include <Arduino.h>
#include <DHT.h>

// Define LED pins
#define LED_PIN_1 5   // GPIO 5 for LED 1
#define LED_PIN_2 18  // GPIO 18 for LED 2

// Define DHT11 pins and types
#define DHT_PIN_A 4   // GPIO 4 for DHT11A (OUTSIDE)
#define DHT_PIN_B 6   // GPIO 6 for DHT11B (INSIDE)
#define DHT_TYPE DHT11

// Initialize DHT sensors
DHT dhtA(DHT_PIN_A, DHT_TYPE);
DHT dhtB(DHT_PIN_B, DHT_TYPE);

// Variables to store humidity readings
float OUTSIDE = 0.0;  // Humidity from DHT11A
float INSIDE = 0.0;   // Humidity from DHT11B

// Function to strobe LEDs and read DHT11A humidity
void strobeAndReadDHT11A() {
    unsigned long startTime = millis();
    unsigned long duration = 15000;  // 15 seconds
    bool ledState = true;

    while (millis() - startTime < duration) {
        // Read humidity from DHT11A
        float humidity = dhtA.readHumidity();
        if (!isnan(humidity)) {
            OUTSIDE = humidity;  // Store valid reading
        }

        // Strobe LEDs
        digitalWrite(LED_PIN_1, ledState ? HIGH : LOW);
        digitalWrite(LED_PIN_2, ledState ? LOW : HIGH);
        ledState = !ledState;  // Toggle state
        delay(500);  // 0.5 seconds
    }
}

// Function to strobe LEDs and read DHT11B humidity
void strobeAndReadDHT11B() {
    unsigned long startTime = millis();
    unsigned long duration = 15000;  // 15 seconds
    bool ledState = true;

    while (millis() - startTime < duration) {
        // Read humidity from DHT11B
        float humidity = dhtB.readHumidity();
        if (!isnan(humidity)) {
            INSIDE = humidity;  // Store valid reading
        }

        // Strobe LEDs
        digitalWrite(LED_PIN_1, ledState ? HIGH : LOW);
        digitalWrite(LED_PIN_2, ledState ? LOW : HIGH);
        ledState = !ledState;  // Toggle state
        delay(2000);  // 2 seconds
    }
}

// Function to calculate humidity difference and control LEDs
void processHumidityAndTemperature() {
    // Calculate humidity difference
    float humidityDiff = OUTSIDE - INSIDE;

    // Read temperature from DHT11A (convert Celsius to Fahrenheit)
    float tempC = dhtA.readTemperature();
    float tempF = (tempC * 9.0 / 5.0) + 32.0;

    // Check conditions
    if (!isnan(tempF) && tempF > 35.0 && humidityDiff > 10.0) {
        // Turn both LEDs on for 20 minutes
        digitalWrite(LED_PIN_1, HIGH);
        digitalWrite(LED_PIN_2, HIGH);
        delay(20 * 60 * 1000UL);  // 20 minutes
    } else {
        // Flash LEDs in unison for 5 minutes
        unsigned long startTime = millis();
        unsigned long duration = 5 * 60 * 1000UL;  // 5 minutes
        bool ledState = true;

        while (millis() - startTime < duration) {
            digitalWrite(LED_PIN_1, ledState ? HIGH : LOW);
            digitalWrite(LED_PIN_2, ledState ? HIGH : LOW);
            ledState = !ledState;
            delay(500);  // Flash every 0.5 seconds
        }
    }
}

void setup() {
    // Initialize LED pins
    pinMode(LED_PIN_1, OUTPUT);
    pinMode(LED_PIN_2, OUTPUT);

    // Initialize DHT sensors
    dhtA.begin();
    dhtB.begin();

    // Ensure LEDs are off initially
    digitalWrite(LED_PIN_1, LOW);
    digitalWrite(LED_PIN_2, LOW);
}

void loop() {
    // Strobe LEDs and read DHT11A
    strobeAndReadDHT11A();

    // Strobe LEDs and read DHT11B
    strobeAndReadDHT11B();

    // Process humidity and temperature
    processHumidityAndTemperature();
}