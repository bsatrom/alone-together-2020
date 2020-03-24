/*
 * Project alone-together-2020
 * Description:
 * Author:
 * Date:
 */
#include <Grove_ChainableLED.h>
#include <Debounce.h>

ChainableLED led(A4, A5, 1);
Debounce debouncer = Debounce();

#define BUTTON_PIN D4

bool sent_message = false;

void handleMessage(const char *event, const char *data) {
    led.setColorHSB(0, 0.0, 0.5, 0.5);

    delay(3000);

    led.setColorHSB(0, 0.0, 0.0, 0.0);
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