#if __has_include(<samd51.h>)
/* newer cmsis-atmel from upstream */
#include <samd51.h>
#else
/* older cmsis-atmel from adafruit */
#include <samd.h>
#endif

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
    OSC32KCTRL->XOSC32K.reg |= OSC32KCTRL_XOSC32K_EN32K | OSC32KCTRL_XOSC32K_RUNSTDBY;
    while (!OSC32KCTRL->STATUS.bit.XOSC32KRDY);
#endif

    /* make sure the APB is enabled for TC3 */
    MCLK->APBBMASK.reg |= MCLK_APBBMASK_TC3;
    
    /* use the 32 kHz clock peripheral as the source for TC3 */
    GCLK->PCHCTRL[TC3_GCLK_ID].reg = GCLK_PCHCTRL_GEN_GCLK3_Val | (1U << GCLK_PCHCTRL_CHEN_Pos);
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
    TC3->COUNT16.WAVE.reg = TC_WAVE_WAVEGEN_MFRQ;
    TC3->COUNT16.CC[0].reg = 16383;
    
    /* fire an interrupt whenever counter equals that value */
    TC3->COUNT16.INTENSET.bit.MC0 = 1;
    NVIC_EnableIRQ(TC3_IRQn);
    
    /* enable the timer */
    while (TC3->COUNT16.SYNCBUSY.reg);
    TC3->COUNT16.CTRLA.bit.ENABLE = 1;
    while (TC3->COUNT16.SYNCBUSY.bit.ENABLE);
}

static unsigned long wakes = 0;

void TC3_Handler(void) {
    if (!TC3->COUNT16.INTFLAG.bit.MC0) return;
    TC3->COUNT16.INTFLAG.reg = (TC_INTFLAG_Type){ .bit.MC0 = 1 }.reg;
    
    wakes++;
}

void sleep_until_next_timer_interval(void) {
    static unsigned long wakes_acknowledged = 0;
    while (*(volatile unsigned long *)&wakes == wakes_acknowledged) __WFI();
    wakes_acknowledged++;
}

int main(void) {
    led_init();
    timer_init();
    
    while (1) {
        sleep_until_next_timer_interval();
        led_on();
        sleep_until_next_timer_interval();
        led_off();
    }
}
