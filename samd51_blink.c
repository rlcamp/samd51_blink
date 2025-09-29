#if __has_include(<samd51.h>)
/* as invoked by Makefile, regardless of cmsis-atmel version */
#include <samd51.h>
#else
/* as invoked by arduino ide */
#include <samd51/include/samd51.h>
#endif

#ifndef PORT0_LED_PIN
/* for itsybitsy m4, define this to 22 */
#define PORT0_LED_PIN 23U
#endif

static void led_init(void) {
    /* pad PA23 on samd51 (pin 13 on the adafruit feather m4 express) */
    PORT->Group[0].OUTCLR.reg = 1U << PORT0_LED_PIN;
    PORT->Group[0].DIRSET.reg = 1U << PORT0_LED_PIN;
    PORT->Group[0].PINCFG[PORT0_LED_PIN].reg = 0;
}

static void led_on(void) { PORT->Group[0].OUTSET.reg = 1U << PORT0_LED_PIN; }
static void led_off(void) { PORT->Group[0].OUTCLR.reg = 1U << PORT0_LED_PIN; }

static void timer_init(void) {
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

    /* fire an interrupt at lowest priority, but do NOT enable the ISR in the NVIC */
    TC3->COUNT16.INTENSET.bit.MC0 = 1;
    NVIC_DisableIRQ(TC3_IRQn);

    /* enable the timer */
    while (TC3->COUNT16.SYNCBUSY.reg);
    TC3->COUNT16.CTRLA.bit.ENABLE = 1;
    while (TC3->COUNT16.SYNCBUSY.bit.ENABLE);
}

int main(void) {
    /* processor will wake up and return from wfe even if interrupt is disabled in nvic */
    SCB->SCR |= SCB_SCR_SEVONPEND_Msk;

    PM->SLEEPCFG.bit.SLEEPMODE = PM_SLEEPCFG_SLEEPMODE_STANDBY_Val;

    led_init();
    timer_init();
    led_on();

    for (unsigned ipass = 0;; ipass++) {
        /* sleep until next event (in this case the tc3 interrupt) */
        while (!TC3->COUNT16.INTFLAG.bit.MC0)
            __WFE();

        /* clear interrupt in peripheral, and clear pending irq in nvic */
        TC3->COUNT16.INTFLAG.reg = (TC_INTFLAG_Type){ .bit.MC0 = 1 }.reg;
        NVIC_ClearPendingIRQ(TC3_IRQn);

        /* toggle the led */
        if (ipass % 2) led_on();
        else led_off();
    }
}
