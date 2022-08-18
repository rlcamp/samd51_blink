#include <stdatomic.h>
#include <math.h>

#ifdef NON_ANCIENT_HEADER_PATHS
/* newer cmsis-atmel from upstream */
#include <samd51j19a.h>
#else
/* older cmsis-atmel from adafruit */
#include <samd.h>
#endif

void led_init(void) {
    /* pad PA23 on samd51 (pin 13 on the adafruit feather m4 express) */
    PORT->Group[0].OUTCLR.reg = 1U << 23;
    PORT->Group[0].DIRSET.reg = 1U << 23;
    PORT->Group[0].PINCFG[23].reg = 0;
}

void led_on(void) { PORT->Group[0].OUTSET.reg = 1U << 23; }
void led_off(void) { PORT->Group[0].OUTCLR.reg = 1U << 23; }

void timer4_init(void) {
    /* make sure the APB is enabled for TC4 */
    MCLK->APBCMASK.reg |= MCLK_APBCMASK_TC4;
    
    /* use the 32 kHz clock peripheral as the source for TC4 */
    GCLK->PCHCTRL[TC4_GCLK_ID].reg = GCLK_PCHCTRL_GEN_GCLK3_Val | (1U << GCLK_PCHCTRL_CHEN_Pos);
    while (GCLK->SYNCBUSY.reg);
    
    /* reset the TC4 peripheral */
    TC4->COUNT16.CTRLA.bit.SWRST = 1;
    while (TC4->COUNT16.SYNCBUSY.bit.SWRST);
    
    /* put it in 16 bit mode */
    TC4->COUNT16.CTRLA.bit.MODE = TC_CTRLA_MODE_COUNT16_Val;
    
    /* timer ticks will be 32 kHz clock ticks divided by this prescaler value */
    TC4->COUNT16.CTRLA.bit.PRESCALER = TC_CTRLA_PRESCALER_DIV1_Val;
    
    /* counter resets after the value in cc[0], i.e. its period is that number plus one */
    TC4->COUNT16.WAVE.reg = TC_WAVE_WAVEGEN_MFRQ;
    TC4->COUNT16.CC[0].reg = 16383;
    
    /* fire an interrupt whenever counter equals that value */
    TC4->COUNT16.INTENSET.reg = 0;
    TC4->COUNT16.INTENSET.bit.MC0 = 1;
    NVIC_EnableIRQ(TC4_IRQn);
    
    /* enable the timer */
    while (TC4->COUNT16.SYNCBUSY.reg);
    TC4->COUNT16.CTRLA.bit.ENABLE = 1;
    while (TC4->COUNT16.SYNCBUSY.bit.ENABLE);
}

static volatile _Atomic unsigned long wakes = 0;

void TC4_Handler(void) {
    if (!TC4->COUNT16.INTFLAG.bit.MC0) return;
    TC4->COUNT16.INTFLAG.reg = (TC_INTFLAG_Type){ .bit.MC0 = 1 }.reg;
    
    wakes++;
}

void sleep_until_next_timer_interval(void) {
    static unsigned long wakes_prev = 0;
    while (wakes - wakes_prev < 1) __WFI();
    wakes_prev++;
}

int main(void) {
    led_init();
    timer4_init();
    
    while (1) {
        sleep_until_next_timer_interval();
        led_on();
        sleep_until_next_timer_interval();
        led_off();
    }
}
