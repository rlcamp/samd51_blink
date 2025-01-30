/* this roughly follows the linker scripts in cmsis 4, cmsis 5, and atmel dfp, all of which
 are apache licensed, but with some deviations as documented below */
MEMORY
{
    FLASH (rx) : ORIGIN = 0x00004000, LENGTH = 0x80000 - 0x4000 /* uf2 uses first 16 kB */
    RAM (rwx)  : ORIGIN = 0x20000000, LENGTH = 0x30000 /* length is ignored, see below */
}

/* NOTE: rather than pointing directly to the first C function, this points at a bit of asm
 which reads chip registers to determine how much SRAM there is, sets the stack pointer,
 and then jumps to the rest of the reset handler in C as usual. this allows us to run on
 samd51 variants with either 192 or 256 kB of sram w/o limiting heap+stack on the latter */
ENTRY(Reset_Handler)

SECTIONS
{
    .text :
    {
        . = ALIGN(0x4000);
        /* handle a bunch of different possible conventions for the isr vector symbol */
        KEEP(*(.vectors .vectors.* .isr_vector))
        *(.text*)

        KEEP(*(.init))
        /* similar to atmel linker script, deviation from cmsis: leave this stuff in rom */
        . = ALIGN(4);
        PROVIDE_HIDDEN (__preinit_array_start = .);
        KEEP(*(.preinit_array))
        PROVIDE_HIDDEN (__preinit_array_end = .);

        . = ALIGN(4);
        PROVIDE_HIDDEN (__init_array_start = .);
        KEEP(*(SORT(.init_array.*)))
        KEEP(*(.init_array))
        PROVIDE_HIDDEN (__init_array_end = .);

        /* note destructor stuff is omitted because no call site */

        *crtbegin.o(.ctors)
        *crtbegin?.o(.ctors)
        *(EXCLUDE_FILE(*crtend?.o *crtend.o) .ctors)
        *(SORT(.ctors.*))
        *(.ctors)

        *(.rodata*)

        KEEP(*(.eh_frame*))
    } > FLASH

    .ARM.extab :
    {
      *(.ARM.extab* .gnu.linkonce.armextab.*)
    } > FLASH

    __exidx_start = .;
    .ARM.exidx :
    {
      *(.ARM.exidx* .gnu.linkonce.armexidx.*)
    } > FLASH
    __exidx_end = .;

    . = ALIGN(4);
    __etext = .;

    .data : AT (__etext)
    {
        __data_start__ = .;
        *(vtable)
        *(.data)
        *(.data*)

        . = ALIGN(4);
        KEEP(*(.ramfunc))

        /* NOTE: someone (arduino/ArduinoCore-samd/pull/186) apparently once saw that this
         should be 16-byte aligned when using i2s on samd21. the symptom occurred at build
         time, but we are not seeing it, so continue to do what upstream cmsis+atmel do */
        . = ALIGN(4);
        __data_end__ = .;
    } > RAM

    .bss :
    {
        . = ALIGN(4);
        __bss_start__ = .;
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        __bss_end__ = .;
    } > RAM

    /* if heap is used, make sure it is 8-byte aligned */
    . = ALIGN(8);
    __end__ = .;

    /* newlib sbrk needs this */
    PROVIDE(end = .);

    /* note we don't do any of the cmsis 4 or cmsis 5 dummy stack stuff because we are
     going to set the initial stack pointer in asm before jumping to the first C code */
    ASSERT(. <= 0x20020000, "less than 64 kB remaining for heap+stack on samd51j19")
}
