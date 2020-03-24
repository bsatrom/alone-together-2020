/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/bsatrom/Development/particle/alone-together-2020/src/alone-together-2020.ino"
/*
 * Project alone-together-2020
 * Description:
 * Author:
 * Date:
 */
#include <Grove_ChainableLED.h>
#include <Debounce.h>

void breatheLED();
void handleMessage(const char *event, const char *data);
void setup();
void loop();
#line 10 "/Users/bsatrom/Development/particle/alone-together-2020/src/alone-together-2020.ino"
ChainableLED led(A4, A5, 1);
Debounce debouncer = Debounce();

#define BUTTON_PIN D4

bool sent_message = false;

void breatheLED() {
    int ledNum = 0;
    float hue = 0.0;
    float saturation = 0.0;
    float brightness = 0.0;

    // Ramp up slowly to our final color
    for (int i = 0; i < 10; i++) {
        hue += 0.075;
        saturation += 0.07;
        brightness += 0.04;

        led.setColorHSB(ledNum, hue, saturation, brightness);

        delay(100);
    }

    // Ramp down slowly to turn the LED off
    for (int i = 10; i > 0; i--) {
        hue -= 0.075;
        saturation -= 0.07;
        brightness -= 0.04;

        led.setColorHSB(ledNum, hue, saturation, brightness);

        delay(100);
    }
}

void handleMessage(const char *event, const char *data) {
    for (int i = 0; i < 3; i++) {
        breatheLED();
    }
}

void setup() {
    led.init();

    led.setColorHSB(0, 0.0, 0.0, 0.0);

    debouncer.attach(BUTTON_PIN, INPUT_PULLUP);
    debouncer.interval(30);

    Particle.subscribe("alonetogether2020", handleMessage, ALL_DEVICES);
}

void loop() {
    debouncer.update();

    if (debouncer.read() == HIGH) {
       if (!sent_message) {
            sent_message = true;

            Particle.publish("alonetogether2020", NULL, PUBLIC);
        }
    } else {
        sent_message = false;
    }
}