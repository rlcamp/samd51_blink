#if __has_include(<samd51.h>)
/* as invoked by Makefile, regardless of cmsis-atmel version */
#include <samd51.h>
#else
/* as invoked by arduino ide */
#include <samd51/include/samd51.h>
#endif

/* assume itsybitsy m4 pinout if this is defined */
#ifdef CRYSTALLESS
#define PORT0_LED_PIN 22U
#else
#define PORT0_LED_PIN 23U
#endif

void led_init(void) {
    /* pad PA23 on samd51 (pin 13 on the adafruit feather m4 express) */
    PORT->Group[0].OUTCLR.reg = 1U << PORT0_LED_PIN;
    PORT->Group[0].DIRSET.reg = 1U << PORT0_LED_PIN;
    PORT->Group[0].PINCFG[PORT0_LED_PIN].reg = 0;
}

void led_on(void) { PORT->Group[0].OUTSET.reg = 1U << PORT0_LED_PIN; }
void led_off(void) { PORT->Group[0].OUTCLR.reg = 1U << PORT0_LED_PIN; }

void timer_init(void) {
    /* assume GCLK3 is one or the other 32 kHz reference, and we need to make sure it is
     enabled and allowed to run in stdby */
#ifdef CRYSTALLESS
    OSC32KCTRL->OSCULP32K.bit.EN32K = 1;
#else
    OSC32KCTRL->XOSC32K.bit.EN32K = 1;
    OSC32KCTRL->XOSC32K.bit.RUNSTDBY = 1;
    while (!OSC32KCTRL->STATUS.bit.XOSC32KRDY);
#endif

    /* make sure the APB is enabled for TC3 */
    MCLK->APBBMASK.bit.TC3_ = 1;

    /* use the 32 kHz clock peripheral as the source for TC3 */
    GCLK->PCHCTRL[TC3_GCLK_ID].reg = (GCLK_PCHCTRL_Type) { .bit = {
        .GEN = GCLK_PCHCTRL_GEN_GCLK3_Val,
        .CHEN = 1
    }}.reg;
    while (GCLK->SYNCBUSY.reg);
    
    /* reset the TC3 peripheral */
    TC3->COUNT16.CTRLA.bit.SWRST = 1;
    while (TC3->COUNT16.SYNCBUSY.bit.SWRST);
    
    TC3->COUNT16.CTRLA.reg = (TC_CTRLA_Type) { .bit = {
        .MODE = TC_CTRLA_MODE_COUNT16_Val, /* use 16 bit counter mode */
        .PRESCALER = TC_CTRLA_PRESCALER_DIV1_Val, /* no prescaler */
        .RUNSTDBY = 1 /* run in stdby */
    }}.reg;

    /* counter resets after the value in cc[0], i.e. its period is that number plus one */
    TC3->COUNT16.WAVE.reg = (TC_WAVE_Type) { .bit.WAVEGEN = TC_WAVE_WAVEGEN_MFRQ_Val }.reg;
    TC3->COUNT16.CC[0].reg = 16383;
    while (TC3->COUNT16.SYNCBUSY.bit.COUNT);

    /* fire an interrupt at lowest priority whenever counter equals that value */
    TC3->COUNT16.INTENSET.bit.MC0 = 1;
    NVIC_EnableIRQ(TC3_IRQn);

    /* enable the timer */
    while (TC3->COUNT16.SYNCBUSY.reg);
    TC3->COUNT16.CTRLA.bit.ENABLE = 1;
    while (TC3->COUNT16.SYNCBUSY.bit.ENABLE);
}

static unsigned wakes = 0;

void TC3_Handler(void) {
    /* clear flag so that interrupt doesn't re-fire */
    TC3->COUNT16.INTFLAG.reg = (TC_INTFLAG_Type){ .bit.MC0 = 1 }.reg;

    wakes++;

    /* arm an321 page 22 fairly strongly suggests this is necessary prior to exception
     return (or will be on future processors) when the first thing the processor wants
     to do afterward depends on state changed in the handler */
    __DSB();
}

int main(void) {
    PM->SLEEPCFG.bit.SLEEPMODE = PM_SLEEPCFG_SLEEPMODE_STANDBY_Val;

    led_init();
    timer_init();

    unsigned wakes_acknowledged = 0;

    while (1) {
        if (*(volatile unsigned *)&wakes != wakes_acknowledged) {
            wakes_acknowledged++;

            /* toggle the led */
            if (wakes_acknowledged % 2) led_on();
            else led_off();
        }

        /* sleep until next event (in this case the tc3 interrupt), unless the event register
         is already set, in which case it is cleared and no sleep occurs. note since no other
         code calls WFE, there will be at least two passes through the main loop for every
         interrupt, where on the final pass, no state is changed, ER is already cleared, and
         the processor sleeps. in exchange for these redundant passes before sleeping, we get
         a guarantee that we will never spuriously sleep when we should have stayed awake to
         handle an already-pending interrupt, as is possible with WFI if not disabling
         interrupts during sleep (which adds latency in handling them on wake) */
        __DSB();
        __WFE();
    }
}
