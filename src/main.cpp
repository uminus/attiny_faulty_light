#include <Arduino.h>

#define BUZ0    PB3 // *** Pin 2
#define PWM0    PB4 // *** Pin 3

/*
pin 1: PB5 Reset
pin 2: PB3 buzzer
pin 3: PB4 pwm
pin 4: GND
pin 5: PB0 x
pin 6: PB1 x
pin 7: PB2 x
pin 8: VCC
 */

void setup() {
    pinMode(BUZ0, OUTPUT);
    pinMode(PWM0, OUTPUT);

    randomSeed(analogRead(A1));
}

int blinkLevel = 0;
static unsigned long nextBlinkStepMillis = 0;

bool isBuzzHigh = false;
static unsigned long buzzHighAtMillis = 0;
static unsigned long nextBuzzStepMillis = 0;

void loop() {
    const unsigned long now = millis();

    if (isBuzzHigh && buzzHighAtMillis + 1 < now) {
        digitalWrite(BUZ0, LOW);
        isBuzzHigh = false;
        blinkLevel -= 127;
    }
    if (nextBuzzStepMillis < now) {
        if (random(100) < 50) {
            digitalWrite(BUZ0, HIGH);
            isBuzzHigh = true;
            buzzHighAtMillis = now;
        }
        nextBuzzStepMillis = now + random(67, 1213);
    }

    if (nextBlinkStepMillis < now) {
        nextBlinkStepMillis = now + 37;

        blinkLevel += static_cast<int>(random(-5, 13));
        if (blinkLevel > 255) blinkLevel = 255;
        if (blinkLevel < 0) blinkLevel = 0;

        analogWrite(PWM0, blinkLevel);
    }
}
