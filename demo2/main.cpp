#include "mbed.h"
#include "mbed_events.h"

DigitalOut redLED(LED1);
DigitalOut blueLED(LED3);
InterruptIn sw2(SW2);

EventQueue blinkQueue;
EventQueue printQueue;

void blink_blueLED()
{
    blueLED = !blueLED;
}

void print_toggle_led()
{
    printf("Toggle red LED!\r\n");
}

void btn_fall()
{
    redLED = !redLED;
    printQueue.call(&print_toggle_led);
}

int main()
{
    Thread printThread(osPriorityLow);
    printThread.start(callback(&printQueue, &EventQueue::dispatch_forever));

    Thread blinkThread(osPriorityHigh);
    blinkThread.start(callback(&blinkQueue, &EventQueue::dispatch_forever));

    Ticker ledTicker;
    ledTicker.attach(blinkQueue.event(&blink_blueLED), 0.5f);

    sw2.fall(&btn_fall);

    while(1) {
        wait(1);
    }
}