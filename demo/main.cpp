#include "mbed.h"

DigitalOut led(LED3);

void blink_led()
{
    led = !led;
}

int main()
{
    Ticker blink;
    blink.attach(&blink_led, 0.5);

    while (1);
}