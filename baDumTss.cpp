// A forceResistor
int force = A4;

// A Potentiometer pin
int pot = A1;

// Three LED pins
int red = D6;
int yellow = D5;
int green = D4;

// Create a variable to hold the analogue input
int potReading;
int forceReading;
int ledBrightness;

void setup() {
    // Set up the LED for output
    pinMode(red, OUTPUT);
    pinMode(yellow, OUTPUT);
    pinMode(green, OUTPUT);
    
    // Create a cloud variable of type integer
    // called 'light' mapped to photoCellReading
    Particle.variable("Your finger power is:", &forceReading, INT);
    }

void loop() {
    // Use analogRead to read the pot value
    potReading = analogRead(pot);    
    // Use analogRead to read the force value
    forceReading = analogRead(force);
    
    // Map this value into the PWM range (0-255)
    // and store as the led brightness
    ledBrightness = map(potReading, 0, 4095, 0, 255);
    
    // Based on the force
    // change numbers of LED to light up
    if (forceReading >= 1000 and forceReading < 2000) {
        analogWrite(green, ledBrightness);
    } else if (forceReading >= 2000 and forceReading < 3000) {
        analogWrite(green, ledBrightness);
        analogWrite(yellow, ledBrightness);
    } else if (forceReading >= 3000 and forceReading < 4000) {
        analogWrite(green, ledBrightness);
        analogWrite(yellow, ledBrightness);
        analogWrite(red, ledBrightness);
    }

    delay(100);
    
    digitalWrite(green, LOW);
    digitalWrite(yellow, LOW);
    digitalWrite(red, LOW);
}