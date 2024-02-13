// Testing Mr. Java

// Libraries
#include <spark-dallas-temperature.h>
#include <OneWire.h>
#include "neopixel.h"

// NeoPixel Config
#define PIXEL_PIN D2
#define PIXEL_COUNT 16
#define PIXEL_TYPE WS2812
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

// Dallas Temperature Sensor Config
OneWire oneWire( D3 ); 
DallasTemperature dallas(&oneWire);
double temperatureF = 0.0;

// Moisture Sensor & Button Setup
int moisture_pin = A5; // Moisture sensor pin
int pushBtn = D4; // Pushbutton pin

void setup() {
    strip.begin();
    strip.show();
    Particle.variable("temperatureF", &temperatureF, DOUBLE);
    dallas.begin();

    Serial.begin(9600);
    pinMode(moisture_pin, INPUT);
    pinMode(pushBtn, INPUT_PULLUP);
}

void loop() {
    // Temperature reading & LED update
    dallas.requestTemperatures();
    float tempC = dallas.getTempCByIndex(0);
    temperatureF = (double)DallasTemperature::toFahrenheit(tempC);
    updateLedColor(temperatureF);
    Particle.publish("here", String(temperatureF) + "F");
    

    // Moisture reading and event triggering
    int moisture_analog = analogRead(moisture_pin);
    float moisture_percentage = (moisture_analog / 4095.00) * 100;
    if (moisture_percentage >= 50) {
        Particle.publish("coffeeTrigger");
        delay(500);
    }

    // Button state reading & event triggering
    int switchState = digitalRead(pushBtn);
    if (switchState == LOW) {
        Particle.publish("coffeeTrigger");
        delay(500);
    }
}

void updateLedColor(double tempF) {
    if (tempF <= 70.0) {
        setStripColor(strip.Color(0, 0, 255));
    } else {
        uint8_t redIntensity = map((int)tempF, 50, 120, 0, 255);
        setStripColor(strip.Color(redIntensity, 0, 0));
    }
}

void setStripColor(uint32_t color) {
    for (int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, color);
    }
    strip.show();
}