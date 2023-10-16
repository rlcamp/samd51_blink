/* derived from adafruit samd core, in turn derived from cmsis. significant deviations should be noted

 ideally, this file should be able to be used in the following scenarios:
 - with a standalone build script using upstream cmsis/atmel/gcc/bossac
 - with the same build script using older cmsis/atmel/gcc/bossac as packaged by adafruit
 - within a sketch in the arduino ide using the adafruit samd core
 */

#ifdef __SAMD51__

#if __has_include(<samd51.h>)
/* newer cmsis-atmel from upstream */
#include <samd51.h>
#else
/* older cmsis-atmel from adafruit */
#include <samd.h>
#endif

/* Default empty handlers */
void Dummy_Handler(void) { while (1); }
void Empty_Handler(void) { }

/* Cortex-M4 processor handlers */
void Reset_Handler               (void);
void NMI_Handler                 (void) __attribute__ ((weak, alias("Dummy_Handler")));
void HardFault_Handler           (void) __attribute__ ((weak, alias("Dummy_Handler")));
void MemManage_Handler           (void) __attribute__ ((weak, alias("Dummy_Handler")));
void BusFault_Handler            (void) __attribute__ ((weak, alias("Dummy_Handler")));
void UsageFault_Handler          (void) __attribute__ ((weak, alias("Dummy_Handler")));
void SVC_Handler                 (void) __attribute__ ((weak, alias("Dummy_Handler")));
void DebugMon_Handler            (void) __attribute__ ((weak, alias("Dummy_Handler")));
void PendSV_Handler              (void) __attribute__ ((weak, alias("Dummy_Handler")));
void SysTick_Handler               (void) __attribute__ ((weak, alias("Empty_Handler")));

/* Peripherals handlers */
void PM_Handler                  (void) __attribute__ ((weak, alias("Dummy_Handler")));
void MCLK_Handler                (void) __attribute__ ((weak, alias("Dummy_Handler")));
void OSCCTRL_0_Handler           (void) __attribute__ ((weak, alias("Dummy_Handler")));
void OSCCTRL_1_Handler           (void) __attribute__ ((weak, alias("Dummy_Handler")));
void OSCCTRL_2_Handler           (void) __attribute__ ((weak, alias("Dummy_Handler")));
void OSCCTRL_3_Handler           (void) __attribute__ ((weak, alias("Dummy_Handler")));
void OSCCTRL_4_Handler           (void) __attribute__ ((weak, alias("Dummy_Handler")));
void OSC32KCTRL_Handler          (void) __attribute__ ((weak, alias("Dummy_Handler")));
void SUPC_0_Handler              (void) __attribute__ ((weak, alias("Dummy_Handler")));
void SUPC_1_Handler              (void) __attribute__ ((weak, alias("Dummy_Handler")));
void WDT_Handler                 (void) __attribute__ ((weak, alias("Dummy_Handler")));
void RTC_Handler                 (void) __attribute__ ((weak, alias("Dummy_Handler")));
void EIC_0_Handler               (void) __attribute__ ((weak, alias("Dummy_Handler")));
void EIC_1_Handler               (void) __attribute__ ((weak, alias("Dummy_Handler")));
void EIC_2_Handler               (void) __attribute__ ((weak, alias("Dummy_Handler")));
void EIC_3_Handler               (void) __attribute__ ((weak, alias("Dummy_Handler")));
void EIC_4_Handler               (void) __attribute__ ((weak, alias("Dummy_Handler")));
void EIC_5_Handler               (void) __attribute__ ((weak, alias("Dummy_Handler")));
void EIC_6_Handler               (void) __attribute__ ((weak, alias("Dummy_Handler")));
void EIC_7_Handler               (void) __attribute__ ((weak, alias("Dummy_Handler")));
void EIC_8_Handler               (void) __attribute__ ((weak, alias("Dummy_Handler")));
void EIC_9_Handler               (void) __attribute__ ((weak, alias("Dummy_Handler")));
void EIC_10_Handler              (void) __attribute__ ((weak, alias("Dummy_Handler")));
void EIC_11_Handler              (void) __attribute__ ((weak, alias("Dummy_Handler")));
void EIC_12_Handler              (void) __attribute__ ((weak, alias("Dummy_Handler")));
void EIC_13_Handler              (void) __attribute__ ((weak, alias("Dummy_Handler")));
void EIC_14_Handler              (void) __attribute__ ((weak, alias("Dummy_Handler")));
void EIC_15_Handler              (void) __attribute__ ((weak, alias("Dummy_Handler")));
void FREQM_Handler               (void) __attribute__ ((weak, alias("Dummy_Handler")));
void NVMCTRL_0_Handler           (void) __attribute__ ((weak, alias("Dummy_Handler")));
void NVMCTRL_1_Handler           (void) __attribute__ ((weak, alias("Dummy_Handler")));
void DMAC_0_Handler              (void) __attribute__ ((weak, alias("Dummy_Handler")));
void DMAC_1_Handler              (void) __attribute__ ((weak, alias("Dummy_Handler")));
void DMAC_2_Handler              (void) __attribute__ ((weak, alias("Dummy_Handler")));
void DMAC_3_Handler              (void) __attribute__ ((weak, alias("Dummy_Handler")));
void DMAC_4_Handler              (void) __attribute__ ((weak, alias("Dummy_Handler")));
void EVSYS_0_Handler             (void) __attribute__ ((weak, alias("Dummy_Handler")));
void EVSYS_1_Handler             (void) __attribute__ ((weak, alias("Dummy_Handler")));
void EVSYS_2_Handler             (void) __attribute__ ((weak, alias("Dummy_Handler")));
void EVSYS_3_Handler             (void) __attribute__ ((weak, alias("Dummy_Handler")));
void EVSYS_4_Handler             (void) __attribute__ ((weak, alias("Dummy_Handler")));
void PAC_Handler                 (void) __attribute__ ((weak, alias("Dummy_Handler")));
void TAL_0_Handler               (void) __attribute__ ((weak, alias("Dummy_Handler")));
void TAL_1_Handler               (void) __attribute__ ((weak, alias("Dummy_Handler")));
void RAMECC_Handler              (void) __attribute__ ((weak, alias("Dummy_Handler")));
void SERCOM0_0_Handler           (void) __attribute__ ((weak, alias("Dummy_Handler")));
void SERCOM0_1_Handler           (void) __attribute__ ((weak, alias("Dummy_Handler")));
void SERCOM0_2_Handler           (void) __attribute__ ((weak, alias("Dummy_Handler")));
void SERCOM0_3_Handler           (void) __attribute__ ((weak, alias("Dummy_Handler")));
void SERCOM1_0_Handler           (void) __attribute__ ((weak, alias("Dummy_Handler")));
void SERCOM1_1_Handler           (void) __attribute__ ((weak, alias("Dummy_Handler")));
void SERCOM1_2_Handler           (void) __attribute__ ((weak, alias("Dummy_Handler")));
void SERCOM1_3_Handler           (void) __attribute__ ((weak, alias("Dummy_Handler")));
void SERCOM2_0_Handler           (void) __attribute__ ((weak, alias("Dummy_Handler")));
void SERCOM2_1_Handler           (void) __attribute__ ((weak, alias("Dummy_Handler")));
void SERCOM2_2_Handler           (void) __attribute__ ((weak, alias("Dummy_Handler")));
void SERCOM2_3_Handler           (void) __attribute__ ((weak, alias("Dummy_Handler")));
void SERCOM3_0_Handler           (void) __attribute__ ((weak, alias("Dummy_Handler")));
void SERCOM3_1_Handler           (void) __attribute__ ((weak, alias("Dummy_Handler")));
void SERCOM3_2_Handler           (void) __attribute__ ((weak, alias("Dummy_Handler")));
void SERCOM3_3_Handler           (void) __attribute__ ((weak, alias("Dummy_Handler")));
void SERCOM4_0_Handler           (void) __attribute__ ((weak, alias("Dummy_Handler")));
void SERCOM4_1_Handler           (void) __attribute__ ((weak, alias("Dummy_Handler")));
void SERCOM4_2_Handler           (void) __attribute__ ((weak, alias("Dummy_Handler")));
void SERCOM4_3_Handler           (void) __attribute__ ((weak, alias("Dummy_Handler")));
void SERCOM5_0_Handler           (void) __attribute__ ((weak, alias("Dummy_Handler")));
void SERCOM5_1_Handler           (void) __attribute__ ((weak, alias("Dummy_Handler")));
void SERCOM5_2_Handler           (void) __attribute__ ((weak, alias("Dummy_Handler")));
void SERCOM5_3_Handler           (void) __attribute__ ((weak, alias("Dummy_Handler")));
void SERCOM6_0_Handler           (void) __attribute__ ((weak, alias("Dummy_Handler")));
void SERCOM6_1_Handler           (void) __attribute__ ((weak, alias("Dummy_Handler")));
void SERCOM6_2_Handler           (void) __attribute__ ((weak, alias("Dummy_Handler")));
void SERCOM6_3_Handler           (void) __attribute__ ((weak, alias("Dummy_Handler")));
void SERCOM7_0_Handler           (void) __attribute__ ((weak, alias("Dummy_Handler")));
void SERCOM7_1_Handler           (void) __attribute__ ((weak, alias("Dummy_Handler")));
void SERCOM7_2_Handler           (void) __attribute__ ((weak, alias("Dummy_Handler")));
void SERCOM7_3_Handler           (void) __attribute__ ((weak, alias("Dummy_Handler")));
void CAN0_Handler                (void) __attribute__ ((weak, alias("Dummy_Handler")));
void CAN1_Handler                (void) __attribute__ ((weak, alias("Dummy_Handler")));
void USB_0_Handler               (void) __attribute__ ((weak, alias("Empty_Handler")));
void USB_1_Handler               (void) __attribute__ ((weak, alias("Empty_Handler")));
void USB_2_Handler               (void) __attribute__ ((weak, alias("Empty_Handler")));
void USB_3_Handler               (void) __attribute__ ((weak, alias("Empty_Handler")));
void TCC0_0_Handler              (void) __attribute__ ((weak, alias("Dummy_Handler")));
void TCC0_1_Handler              (void) __attribute__ ((weak, alias("Dummy_Handler")));
void TCC0_2_Handler              (void) __attribute__ ((weak, alias("Dummy_Handler")));
void TCC0_3_Handler              (void) __attribute__ ((weak, alias("Dummy_Handler")));
void TCC0_4_Handler              (void) __attribute__ ((weak, alias("Dummy_Handler")));
void TCC0_5_Handler              (void) __attribute__ ((weak, alias("Dummy_Handler")));
void TCC0_6_Handler              (void) __attribute__ ((weak, alias("Dummy_Handler")));
void TCC1_0_Handler              (void) __attribute__ ((weak, alias("Dummy_Handler")));
void TCC1_1_Handler              (void) __attribute__ ((weak, alias("Dummy_Handler")));
void TCC1_2_Handler              (void) __attribute__ ((weak, alias("Dummy_Handler")));
void TCC1_3_Handler              (void) __attribute__ ((weak, alias("Dummy_Handler")));
void TCC1_4_Handler              (void) __attribute__ ((weak, alias("Dummy_Handler")));
void TCC2_0_Handler              (void) __attribute__ ((weak, alias("Dummy_Handler")));
void TCC2_1_Handler              (void) __attribute__ ((weak, alias("Dummy_Handler")));
void TCC2_2_Handler              (void) __attribute__ ((weak, alias("Dummy_Handler")));
void TCC2_3_Handler              (void) __attribute__ ((weak, alias("Dummy_Handler")));
void TCC3_0_Handler              (void) __attribute__ ((weak, alias("Dummy_Handler")));
void TCC3_1_Handler              (void) __attribute__ ((weak, alias("Dummy_Handler")));
void TCC3_2_Handler              (void) __attribute__ ((weak, alias("Dummy_Handler")));
void TCC4_0_Handler              (void) __attribute__ ((weak, alias("Dummy_Handler")));
void TCC4_1_Handler              (void) __attribute__ ((weak, alias("Dummy_Handler")));
void TCC4_2_Handler              (void) __attribute__ ((weak, alias("Dummy_Handler")));
void TC0_Handler                 (void) __attribute__ ((weak, alias("Dummy_Handler")));
void TC1_Handler                 (void) __attribute__ ((weak, alias("Dummy_Handler")));
void TC2_Handler                 (void) __attribute__ ((weak, alias("Dummy_Handler")));
void TC3_Handler                 (void) __attribute__ ((weak, alias("Dummy_Handler")));
void TC4_Handler                 (void) __attribute__ ((weak, alias("Dummy_Handler")));
void TC5_Handler                 (void) __attribute__ ((weak, alias("Dummy_Handler")));
void TC6_Handler                 (void) __attribute__ ((weak, alias("Dummy_Handler")));
void TC7_Handler                 (void) __attribute__ ((weak, alias("Dummy_Handler")));
void PDEC_0_Handler              (void) __attribute__ ((weak, alias("Dummy_Handler")));
void PDEC_1_Handler              (void) __attribute__ ((weak, alias("Dummy_Handler")));
void PDEC_2_Handler              (void) __attribute__ ((weak, alias("Dummy_Handler")));
void ADC0_0_Handler              (void) __attribute__ ((weak, alias("Dummy_Handler")));
void ADC0_1_Handler              (void) __attribute__ ((weak, alias("Dummy_Handler")));
void ADC1_0_Handler              (void) __attribute__ ((weak, alias("Dummy_Handler")));
void ADC1_1_Handler              (void) __attribute__ ((weak, alias("Dummy_Handler")));
void AC_Handler                  (void) __attribute__ ((weak, alias("Dummy_Handler")));
void DAC_0_Handler               (void) __attribute__ ((weak, alias("Dummy_Handler")));
void DAC_1_Handler               (void) __attribute__ ((weak, alias("Dummy_Handler")));
void DAC_2_Handler               (void) __attribute__ ((weak, alias("Dummy_Handler")));
void DAC_3_Handler               (void) __attribute__ ((weak, alias("Dummy_Handler")));
void DAC_4_Handler               (void) __attribute__ ((weak, alias("Dummy_Handler")));
void I2S_Handler                 (void) __attribute__ ((weak, alias("Dummy_Handler")));
void PCC_Handler                 (void) __attribute__ ((weak, alias("Dummy_Handler")));
void AES_Handler                 (void) __attribute__ ((weak, alias("Dummy_Handler")));
void TRNG_Handler                (void) __attribute__ ((weak, alias("Dummy_Handler")));
void ICM_Handler                 (void) __attribute__ ((weak, alias("Dummy_Handler")));
void PUKCC_Handler               (void) __attribute__ ((weak, alias("Dummy_Handler")));
void QSPI_Handler                (void) __attribute__ ((weak, alias("Dummy_Handler")));
void SDHC0_Handler               (void) __attribute__ ((weak, alias("Dummy_Handler")));
void SDHC1_Handler               (void) __attribute__ ((weak, alias("Dummy_Handler")));

/* Initialize segments */
extern uint32_t __etext;
extern uint32_t __data_start__;
extern uint32_t __data_end__;
extern uint32_t __bss_start__;
extern uint32_t __bss_end__;
extern uint32_t __StackTop;

/* Exception Table */
__attribute__((used))
__attribute__((section(".isr_vector"))) const DeviceVectors exception_table = {
    /* Configure Initial Stack Pointer, using linker-generated symbols */
    (void *)(&__StackTop),

    /* Cortex-M handlers */
    (void *)Reset_Handler,
    (void *)NMI_Handler,
    (void *)HardFault_Handler,
    (void *)MemManage_Handler,
    (void *)BusFault_Handler,
    (void *)UsageFault_Handler,
    (void *)(0UL), /* Reserved */
    (void *)(0UL), /* Reserved */
    (void *)(0UL), /* Reserved */
    (void *)(0UL), /* Reserved */
    (void *)SVC_Handler,
    (void *)DebugMon_Handler,
    (void *)(0UL), /* Reserved */
    (void *)PendSV_Handler,
    (void *)SysTick_Handler,

    /* Peripheral handlers */
    (void *)PM_Handler,                    /*  0 Power Manager */
    (void *)MCLK_Handler,                  /*  1 Main Clock */
    (void *)OSCCTRL_0_Handler,             /*  2 Oscillators Control IRQ 0 */
    (void *)OSCCTRL_1_Handler,             /*  3 Oscillators Control IRQ 1 */
    (void *)OSCCTRL_2_Handler,             /*  4 Oscillators Control IRQ 2 */
    (void *)OSCCTRL_3_Handler,             /*  5 Oscillators Control IRQ 3 */
    (void *)OSCCTRL_4_Handler,             /*  6 Oscillators Control IRQ 4 */
    (void *)OSC32KCTRL_Handler,            /*  7 32kHz Oscillators Control */
    (void *)SUPC_0_Handler,                /*  8 Supply Controller IRQ 0 */
    (void *)SUPC_1_Handler,                /*  9 Supply Controller IRQ 1 */
    (void *)WDT_Handler,                   /* 10 Watchdog Timer */
    (void *)RTC_Handler,                   /* 11 Real-Time Counter */
    (void *)EIC_0_Handler,                 /* 12 External Interrupt Controller IRQ 0 */
    (void *)EIC_1_Handler,                 /* 13 External Interrupt Controller IRQ 1 */
    (void *)EIC_2_Handler,                 /* 14 External Interrupt Controller IRQ 2 */
    (void *)EIC_3_Handler,                 /* 15 External Interrupt Controller IRQ 3 */
    (void *)EIC_4_Handler,                 /* 16 External Interrupt Controller IRQ 4 */
    (void *)EIC_5_Handler,                 /* 17 External Interrupt Controller IRQ 5 */
    (void *)EIC_6_Handler,                 /* 18 External Interrupt Controller IRQ 6 */
    (void *)EIC_7_Handler,                 /* 19 External Interrupt Controller IRQ 7 */
    (void *)EIC_8_Handler,                 /* 20 External Interrupt Controller IRQ 8 */
    (void *)EIC_9_Handler,                 /* 21 External Interrupt Controller IRQ 9 */
    (void *)EIC_10_Handler,                /* 22 External Interrupt Controller IRQ 10 */
    (void *)EIC_11_Handler,                /* 23 External Interrupt Controller IRQ 11 */
    (void *)EIC_12_Handler,                /* 24 External Interrupt Controller IRQ 12 */
    (void *)EIC_13_Handler,                /* 25 External Interrupt Controller IRQ 13 */
    (void *)EIC_14_Handler,                /* 26 External Interrupt Controller IRQ 14 */
    (void *)EIC_15_Handler,                /* 27 External Interrupt Controller IRQ 15 */
    (void *)FREQM_Handler,                 /* 28 Frequency Meter */
    (void *)NVMCTRL_0_Handler,             /* 29 Non-Volatile Memory Controller IRQ 0 */
    (void *)NVMCTRL_1_Handler,             /* 30 Non-Volatile Memory Controller IRQ 1 */
    (void *)DMAC_0_Handler,                /* 31 Direct Memory Access Controller IRQ 0 */
    (void *)DMAC_1_Handler,                /* 32 Direct Memory Access Controller IRQ 1 */
    (void *)DMAC_2_Handler,                /* 33 Direct Memory Access Controller IRQ 2 */
    (void *)DMAC_3_Handler,                /* 34 Direct Memory Access Controller IRQ 3 */
    (void *)DMAC_4_Handler,                /* 35 Direct Memory Access Controller IRQ 4 */
    (void *)EVSYS_0_Handler,               /* 36 Event System Interface IRQ 0 */
    (void *)EVSYS_1_Handler,               /* 37 Event System Interface IRQ 1 */
    (void *)EVSYS_2_Handler,               /* 38 Event System Interface IRQ 2 */
    (void *)EVSYS_3_Handler,               /* 39 Event System Interface IRQ 3 */
    (void *)EVSYS_4_Handler,               /* 40 Event System Interface IRQ 4 */
    (void *)PAC_Handler,                   /* 41 Peripheral Access Controller */
    (void *)TAL_0_Handler,                 /* 42 Trigger Allocator IRQ 0 */
    (void *)TAL_1_Handler,                 /* 43 Trigger Allocator IRQ 1 */
    (void *)(0UL),
    (void *)RAMECC_Handler,                /* 45 RAM ECC */
    (void *)SERCOM0_0_Handler,             /* 46 Serial Communication Interface 0 IRQ 0 */
    (void *)SERCOM0_1_Handler,             /* 47 Serial Communication Interface 0 IRQ 1 */
    (void *)SERCOM0_2_Handler,             /* 48 Serial Communication Interface 0 IRQ 2 */
    (void *)SERCOM0_3_Handler,             /* 49 Serial Communication Interface 0 IRQ 3 */
    (void *)SERCOM1_0_Handler,             /* 50 Serial Communication Interface 1 IRQ 0 */
    (void *)SERCOM1_1_Handler,             /* 51 Serial Communication Interface 1 IRQ 1 */
    (void *)SERCOM1_2_Handler,             /* 52 Serial Communication Interface 1 IRQ 2 */
    (void *)SERCOM1_3_Handler,             /* 53 Serial Communication Interface 1 IRQ 3 */
    (void *)SERCOM2_0_Handler,             /* 54 Serial Communication Interface 2 IRQ 0 */
    (void *)SERCOM2_1_Handler,             /* 55 Serial Communication Interface 2 IRQ 1 */
    (void *)SERCOM2_2_Handler,             /* 56 Serial Communication Interface 2 IRQ 2 */
    (void *)SERCOM2_3_Handler,             /* 57 Serial Communication Interface 2 IRQ 3 */
    (void *)SERCOM3_0_Handler,             /* 58 Serial Communication Interface 3 IRQ 0 */
    (void *)SERCOM3_1_Handler,             /* 59 Serial Communication Interface 3 IRQ 1 */
    (void *)SERCOM3_2_Handler,             /* 60 Serial Communication Interface 3 IRQ 2 */
    (void *)SERCOM3_3_Handler,             /* 61 Serial Communication Interface 3 IRQ 3 */
    (void *)SERCOM4_0_Handler,             /* 62 Serial Communication Interface 4 IRQ 0 */
    (void *)SERCOM4_1_Handler,             /* 63 Serial Communication Interface 4 IRQ 1 */
    (void *)SERCOM4_2_Handler,             /* 64 Serial Communication Interface 4 IRQ 2 */
    (void *)SERCOM4_3_Handler,             /* 65 Serial Communication Interface 4 IRQ 3 */
    (void *)SERCOM5_0_Handler,             /* 66 Serial Communication Interface 5 IRQ 0 */
    (void *)SERCOM5_1_Handler,             /* 67 Serial Communication Interface 5 IRQ 1 */
    (void *)SERCOM5_2_Handler,             /* 68 Serial Communication Interface 5 IRQ 2 */
    (void *)SERCOM5_3_Handler,             /* 69 Serial Communication Interface 5 IRQ 3 */
    (void *)SERCOM6_0_Handler,             /* 70 Serial Communication Interface 6 IRQ 0 */
    (void *)SERCOM6_1_Handler,             /* 71 Serial Communication Interface 6 IRQ 1 */
    (void *)SERCOM6_2_Handler,             /* 72 Serial Communication Interface 6 IRQ 2 */
    (void *)SERCOM6_3_Handler,             /* 73 Serial Communication Interface 6 IRQ 3 */
    (void *)SERCOM7_0_Handler,             /* 74 Serial Communication Interface 7 IRQ 0 */
    (void *)SERCOM7_1_Handler,             /* 75 Serial Communication Interface 7 IRQ 1 */
    (void *)SERCOM7_2_Handler,             /* 76 Serial Communication Interface 7 IRQ 2 */
    (void *)SERCOM7_3_Handler,             /* 77 Serial Communication Interface 7 IRQ 3 */
    (void *)CAN0_Handler,                  /* 78 Control Area Network 0 (SAM E5x) */
    (void *)CAN1_Handler,                  /* 79 Control Area Network 0 (SAM E5x) */
    (void *)USB_0_Handler,                 /* 80 Universal Serial Bus IRQ 0 */
    (void *)USB_1_Handler,                 /* 81 Universal Serial Bus IRQ 1 */
    (void *)USB_2_Handler,                 /* 82 Universal Serial Bus IRQ 2 */
    (void *)USB_3_Handler,                 /* 83 Universal Serial Bus IRQ 3 */
    (void *)(0UL),
    (void *)TCC0_0_Handler,                /* 85 Timer Counter Control 0 IRQ 0 */
    (void *)TCC0_1_Handler,                /* 86 Timer Counter Control 0 IRQ 1 */
    (void *)TCC0_2_Handler,                /* 87 Timer Counter Control 0 IRQ 2 */
    (void *)TCC0_3_Handler,                /* 88 Timer Counter Control 0 IRQ 3 */
    (void *)TCC0_4_Handler,                /* 89 Timer Counter Control 0 IRQ 4 */
    (void *)TCC0_5_Handler,                /* 90 Timer Counter Control 0 IRQ 5 */
    (void *)TCC0_6_Handler,                /* 91 Timer Counter Control 0 IRQ 6 */
    (void *)TCC1_0_Handler,                /* 92 Timer Counter Control 1 IRQ 0 */
    (void *)TCC1_1_Handler,                /* 93 Timer Counter Control 1 IRQ 1 */
    (void *)TCC1_2_Handler,                /* 94 Timer Counter Control 1 IRQ 2 */
    (void *)TCC1_3_Handler,                /* 95 Timer Counter Control 1 IRQ 3 */
    (void *)TCC1_4_Handler,                /* 96 Timer Counter Control 1 IRQ 4 */
    (void *)TCC2_0_Handler,                /* 97 Timer Counter Control 2 IRQ 0 */
    (void *)TCC2_1_Handler,                /* 98 Timer Counter Control 2 IRQ 1 */
    (void *)TCC2_2_Handler,                /* 99 Timer Counter Control 2 IRQ 2 */
    (void *)TCC2_3_Handler,                /* 100 Timer Counter Control 2 IRQ 3 */
    (void *)TCC3_0_Handler,                /* 101 Timer Counter Control 3 IRQ 0 */
    (void *)TCC3_1_Handler,                /* 102 Timer Counter Control 3 IRQ 1 */
    (void *)TCC3_2_Handler,                /* 103 Timer Counter Control 3 IRQ 2 */
    (void *)TCC4_0_Handler,                /* 104 Timer Counter Control 4 IRQ 0 */
    (void *)TCC4_1_Handler,                /* 105 Timer Counter Control 4 IRQ 1 */
    (void *)TCC4_2_Handler,                /* 106 Timer Counter Control 4 IRQ 2 */
    (void *)TC0_Handler,                   /* 107 Basic Timer Counter 0 */
    (void *)TC1_Handler,                   /* 108 Basic Timer Counter 1 */
    (void *)TC2_Handler,                   /* 109 Basic Timer Counter 2 */
    (void *)TC3_Handler,                   /* 110 Basic Timer Counter 3 */
    (void *)TC4_Handler,                   /* 111 Basic Timer Counter 4 */
    (void *)TC5_Handler,                   /* 112 Basic Timer Counter 5 */
    (void *)TC6_Handler,                   /* 113 Basic Timer Counter 6 */
    (void *)TC7_Handler,                   /* 114 Basic Timer Counter 7 */
    (void *)PDEC_0_Handler,                /* 115 Quadrature Decodeur IRQ 0 */
    (void *)PDEC_1_Handler,                /* 116 Quadrature Decodeur IRQ 1 */
    (void *)PDEC_2_Handler,                /* 117 Quadrature Decodeur IRQ 2 */
    (void *)ADC0_0_Handler,                /* 118 Analog Digital Converter 0 IRQ 0 */
    (void *)ADC0_1_Handler,                /* 119 Analog Digital Converter 0 IRQ 1 */
    (void *)ADC1_0_Handler,                /* 120 Analog Digital Converter 1 IRQ 0 */
    (void *)ADC1_1_Handler,                /* 121 Analog Digital Converter 1 IRQ 1 */
    (void *)AC_Handler,                    /* 122 Analog Comparators */
    (void *)DAC_0_Handler,                 /* 123 Digital-to-Analog Converter IRQ 0 */
    (void *)DAC_1_Handler,                 /* 124 Digital-to-Analog Converter IRQ 1 */
    (void *)DAC_2_Handler,                 /* 125 Digital-to-Analog Converter IRQ 2 */
    (void *)DAC_3_Handler,                 /* 126 Digital-to-Analog Converter IRQ 3 */
    (void *)DAC_4_Handler,                 /* 127 Digital-to-Analog Converter IRQ 4 */
    (void *)I2S_Handler,                   /* 128 Inter-IC Sound Interface */
    (void *)PCC_Handler,                   /* 129 Parallel Capture Controller */
    (void *)AES_Handler,                   /* 130 Advanced Encryption Standard */
    (void *)TRNG_Handler,                  /* 131 True Random Generator */
    (void *)ICM_Handler,                   /* 132 Integrity Check Monitor */
    (void *)PUKCC_Handler,                 /* 133 PUblic-Key Cryptography Controller */
    (void *)QSPI_Handler,                  /* 134 Quad SPI interface */
    (void *)SDHC0_Handler,                 /* 135 SD/MMC Host Controller 0 */
    (void *)SDHC1_Handler,                 /* 136 SD/MMC Host Controller 1 */
};

extern int main(void);
extern void __libc_init_array();

/* This is called on processor reset to initialize the device and call main() */
void Reset_Handler(void) {
    /* Initialize the initialized data section */
    if (&__data_start__ != &__data_end__ && &__etext != &__data_start__)
        for (uint32_t * src = &__etext, * dest = &__data_start__; dest < &__data_end__; dest++, src++)
            *dest = *src;

    /* Clear the zero section */
    for (uint32_t * dest = &__bss_start__; dest < &__bss_end__; dest++)
        *dest = 0UL;

    /* Enable FPU */
    SCB->CPACR |= (0xFu << 20);
    __DSB();
    __ISB();

    /* deviation from upstream cmsis: we start all the clocks before any C or C++ constructors are run */
    SystemInit();

    /* deviation from adafruit/arduino samd core: we run the constructors before main(), rather than doing both clock init and constructors in main() */
    __libc_init_array();

    main();
    while (1);
}

/* everything below is derived from adafruit's startup.c. TODO: lots of cargo cult */

#define GENERIC_CLOCK_GENERATOR_MAIN (0u)
#define GENERIC_CLOCK_GENERATOR_48M (1u)
#define GENERIC_CLOCK_GENERATOR_XOSC32K (3u)
#define GENERIC_CLOCK_GENERATOR_1M (5u)
/* deviation from adafruit/arduino: note that the adafruit core uses GCLKs 2 and 4 for 100
 and 1 MHz respectively, we don't, but we should probably not reuse those two GCLKs for
 other clock frequencies */

static void switch_cpu_to_32kHz(void) {
#ifdef CRYSTALLESS
    OSC32KCTRL->OSCULP32K.bit.EN32K = 1;
#else
    /* enable 32 kHz xtal oscillator */
    OSC32KCTRL->XOSC32K.reg = OSC32KCTRL_XOSC32K_ENABLE | OSC32KCTRL_XOSC32K_EN1K | OSC32KCTRL_XOSC32K_EN32K | OSC32KCTRL_XOSC32K_CGM_XT | OSC32KCTRL_XOSC32K_XTALEN;
    while ((OSC32KCTRL->STATUS.reg & OSC32KCTRL_STATUS_XOSC32KRDY) == 0);
#endif

    /* reset gclk peripheral */
    GCLK->CTRLA.bit.SWRST = 1;
    while (GCLK->SYNCBUSY.reg & GCLK_SYNCBUSY_SWRST);

    /* one or the other of the 32 kHz oscillators will be generic clock generator 3 */
#ifndef CRYSTALLESS
    GCLK->GENCTRL[GENERIC_CLOCK_GENERATOR_XOSC32K].reg = GCLK_GENCTRL_SRC(GCLK_GENCTRL_SRC_XOSC32K) | GCLK_GENCTRL_GENEN;
#else
    GCLK->GENCTRL[GENERIC_CLOCK_GENERATOR_XOSC32K].reg = GCLK_GENCTRL_SRC(GCLK_GENCTRL_SRC_OSCULP32K) | GCLK_GENCTRL_GENEN;
#endif

    while (GCLK->SYNCBUSY.reg & GCLK_SYNCBUSY_GENCTRL3);

    /* temporarily use the ulp oscillator for generic clock 0 */
    GCLK->GENCTRL[0].reg = GCLK_GENCTRL_SRC(GCLK_GENCTRL_SRC_OSCULP32K) | GCLK_GENCTRL_GENEN;
    while (GCLK->SYNCBUSY.reg & GCLK_SYNCBUSY_GENCTRL0);
}

static void switch_cpu_from_32kHz_to_fast(void) {
    /* bring up dfll in open loop mode */

    OSCCTRL->DFLLCTRLA.reg = 0;
    //GCLK->PCHCTRL[OSCCTRL_GCLK_ID_DFLL48].reg = (1 << GCLK_PCHCTRL_CHEN_Pos) | GCLK_PCHCTRL_GEN(GCLK_PCHCTRL_GEN_GCLK3_Val);

    OSCCTRL->DFLLMUL.reg = OSCCTRL_DFLLMUL_CSTEP(0x1) | OSCCTRL_DFLLMUL_FSTEP(0x1) | OSCCTRL_DFLLMUL_MUL(0);
    while (OSCCTRL->DFLLSYNC.reg & OSCCTRL_DFLLSYNC_DFLLMUL);

    OSCCTRL->DFLLCTRLB.reg = 0;
    while (OSCCTRL->DFLLSYNC.reg & OSCCTRL_DFLLSYNC_DFLLCTRLB);

    OSCCTRL->DFLLCTRLA.reg |= OSCCTRL_DFLLCTRLA_ENABLE;
    while (OSCCTRL->DFLLSYNC.reg & OSCCTRL_DFLLSYNC_ENABLE);

    /* chip errata 2.8.3 workaround says to set dfllmul, then clear ctrlb to select open loop, then
     enable the dfll, then do this weird dfllval reload thing, then set dfllctrlb to final value */
    OSCCTRL->DFLLVAL.reg = OSCCTRL->DFLLVAL.reg;
    while (OSCCTRL->DFLLSYNC.bit.DFLLVAL);

    OSCCTRL->DFLLCTRLB.reg = OSCCTRL_DFLLCTRLB_WAITLOCK | OSCCTRL_DFLLCTRLB_CCDIS | OSCCTRL_DFLLCTRLB_USBCRM;
    while (!OSCCTRL->STATUS.bit.DFLLRDY);

    if (48000000 == F_CPU)
    /* use the 48 MHz clock for the cpu */
        GCLK->GENCTRL[GENERIC_CLOCK_GENERATOR_MAIN].reg = GCLK_GENCTRL_SRC(GCLK_GENCTRL_SRC_DFLL) | GCLK_GENCTRL_IDC | GCLK_GENCTRL_GENEN;
    else {
        /* divide by 48 to get a 1 MHz clock for generic clock generator 5 */
        GCLK->GENCTRL[GENERIC_CLOCK_GENERATOR_1M].reg = GCLK_GENCTRL_SRC(GCLK_GENCTRL_SRC_DFLL_Val) | GCLK_GENCTRL_GENEN | GCLK_GENCTRL_DIV(48u);
        while (GCLK->SYNCBUSY.bit.GENCTRL5);

        /* set up fdpll0 at F_CPU (120 MHz) */
        GCLK->PCHCTRL[OSCCTRL_GCLK_ID_FDPLL0].reg = (1 << GCLK_PCHCTRL_CHEN_Pos) | GCLK_PCHCTRL_GEN(GCLK_PCHCTRL_GEN_GCLK5_Val);

        OSCCTRL->Dpll[0].DPLLRATIO.reg = OSCCTRL_DPLLRATIO_LDRFRAC(0x00) | OSCCTRL_DPLLRATIO_LDR((F_CPU - 500000) / 1000000);
        while (OSCCTRL->Dpll[0].DPLLSYNCBUSY.bit.DPLLRATIO);

        //MUST USE LBYPASS DUE TO BUG IN REV A OF SAMD51
        OSCCTRL->Dpll[0].DPLLCTRLB.reg = OSCCTRL_DPLLCTRLB_REFCLK_GCLK | OSCCTRL_DPLLCTRLB_LBYPASS;

        OSCCTRL->Dpll[0].DPLLCTRLA.reg = OSCCTRL_DPLLCTRLA_ENABLE;
        while (OSCCTRL->Dpll[0].DPLLSTATUS.bit.CLKRDY == 0 || OSCCTRL->Dpll[0].DPLLSTATUS.bit.LOCK == 0);

        /* 48 MHz clock, required for usb and many other things */
        GCLK->GENCTRL[GENERIC_CLOCK_GENERATOR_48M].reg = GCLK_GENCTRL_SRC(GCLK_GENCTRL_SRC_DFLL_Val) | GCLK_GENCTRL_IDC | GCLK_GENCTRL_GENEN;
        while (GCLK->SYNCBUSY.reg & GCLK_SYNCBUSY_GENCTRL1);

        /* use the 120 MHz clock for the cpu */
        GCLK->GENCTRL[GENERIC_CLOCK_GENERATOR_MAIN].reg = GCLK_GENCTRL_SRC(GCLK_GENCTRL_SRC_DPLL0) | GCLK_GENCTRL_IDC | GCLK_GENCTRL_GENEN;
    }

    while (GCLK->SYNCBUSY.reg & GCLK_SYNCBUSY_GENCTRL0);

    /* with no divider */
    MCLK->CPUDIV.reg = MCLK_CPUDIV_DIV_DIV1;
}

void SystemInit(void) {
    /* zero wait states */
    NVMCTRL->CTRLA.reg |= NVMCTRL_CTRLA_RWS(0);

    switch_cpu_to_32kHz();
    switch_cpu_from_32kHz_to_fast();

    /* use ldo regulator */
    SUPC->VREG.bit.SEL = 0;

    /* enable cache */
    __disable_irq();
    CMCC->CTRL.reg = 1;
    __enable_irq();

    /* shut off 32 kHz oscillators we're not using */
#ifdef CRYSTALLESS
    OSC32KCTRL->XOSC32K.reg = 0;
#else
    OSC32KCTRL->OSCULP32K.reg &= ~(OSC32KCTRL_OSCULP32K_EN32K | OSC32KCTRL_OSCULP32K_EN1K);
#endif

    /* deviation from adafruit/arduino: removed debugging stuff */

    /* load adc calibration bias stuff */
    uint32_t bias0 = (*((uint32_t *)AC_FUSES_BIAS0_ADDR) & AC_FUSES_BIAS0_Msk) >> AC_FUSES_BIAS0_Pos;
    AC->CALIB.reg = AC_CALIB_BIAS0(bias0);

    uint32_t biascomp = (*((uint32_t *)ADC0_FUSES_BIASCOMP_ADDR) & ADC0_FUSES_BIASCOMP_Msk) >> ADC0_FUSES_BIASCOMP_Pos;
    uint32_t biasr2r = (*((uint32_t *)ADC0_FUSES_BIASR2R_ADDR) & ADC0_FUSES_BIASR2R_Msk) >> ADC0_FUSES_BIASR2R_Pos;
    uint32_t biasref = (*((uint32_t *)ADC0_FUSES_BIASREFBUF_ADDR) & ADC0_FUSES_BIASREFBUF_Msk) >> ADC0_FUSES_BIASREFBUF_Pos;

    ADC0->CALIB.reg = ADC_CALIB_BIASREFBUF(biasref) | ADC_CALIB_BIASR2R(biasr2r) | ADC_CALIB_BIASCOMP(biascomp);

    biascomp = (*((uint32_t *)ADC1_FUSES_BIASCOMP_ADDR) & ADC1_FUSES_BIASCOMP_Msk) >> ADC1_FUSES_BIASCOMP_Pos;
    biasr2r = (*((uint32_t *)ADC1_FUSES_BIASR2R_ADDR) & ADC1_FUSES_BIASR2R_Msk) >> ADC1_FUSES_BIASR2R_Pos;
    biasref = (*((uint32_t *)ADC1_FUSES_BIASREFBUF_ADDR) & ADC1_FUSES_BIASREFBUF_Msk) >> ADC1_FUSES_BIASREFBUF_Pos;

    ADC1->CALIB.reg = ADC_CALIB_BIASREFBUF(biasref) | ADC_CALIB_BIASR2R(biasr2r) | ADC_CALIB_BIASCOMP(biascomp);

    /* load usb calibration stuff */
    uint32_t usbtransn = (*((uint32_t *)USB_FUSES_TRANSN_ADDR) & USB_FUSES_TRANSN_Msk) >> USB_FUSES_TRANSN_Pos;
    uint32_t usbtransp = (*((uint32_t *)USB_FUSES_TRANSP_ADDR) & USB_FUSES_TRANSP_Msk) >> USB_FUSES_TRANSP_Pos;
    uint32_t usbtrim = (*((uint32_t *)USB_FUSES_TRIM_ADDR) & USB_FUSES_TRIM_Msk) >> USB_FUSES_TRIM_Pos;
    USB->DEVICE.PADCAL.reg = USB_PADCAL_TRIM(usbtrim) | USB_PADCAL_TRANSN(usbtransn) | USB_PADCAL_TRANSP(usbtransp);
}

__attribute((weak)) void _init(void) { }

#else
#warning lol todo
#endif
