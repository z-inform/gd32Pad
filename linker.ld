ENTRY(ResetHandler)

estack = 0x20017FFF;
minHeapSize = 0x400;
minStackSize = 0x400;


MEMORY{
    RAM (xrw) : ORIGIN = 0x20000000, LENGTH = 96K
    FLASH (RX) : ORIGIN = 0X08000000, LENGTH = 1M
}

SECTIONS{

    .isr_vector : {
        . = ALIGN(4);
        KEEP(*( .isr_vector ))
        . = ALIGN(4);
    } >FLASH

    .text : {
        . = ALIGN(4);
        *(.text)          
        *(.text*)         
        *(.glue_7)        
        *(.glue_7t)       
        *(.eh_frame)

        KEEP (*(.init))
        KEEP (*(.fini))

        . = ALIGN(4);
        etext = .;      
    } >FLASH

            
      .rodata :
      {
        . = ALIGN(4);
        *(.rodata)         
        *(.rodata*)        
        . = ALIGN(4);
      } >FLASH

      .ARM.extab   : { *(.ARM.extab* .gnu.linkonce.armextab.*) } >FLASH
      .ARM : {
        __exidx_start = .;
        *(.ARM.exidx*)
        __exidx_end = .;
      } >FLASH

      .preinit_array     :
      {
        PROVIDE_HIDDEN (__preinit_array_start = .);
        KEEP (*(.preinit_array*))
        PROVIDE_HIDDEN (__preinit_array_end = .);
      } >FLASH
      .init_array :
      {
        PROVIDE_HIDDEN (__init_array_start = .);
        KEEP (*(SORT(.init_array.*)))
        KEEP (*(.init_array*))
        PROVIDE_HIDDEN (__init_array_end = .);
      } >FLASH
      .fini_array :
      {
        PROVIDE_HIDDEN (__fini_array_start = .);
        KEEP (*(SORT(.fini_array.*)))
        KEEP (*(.fini_array*))
        PROVIDE_HIDDEN (__fini_array_end = .);
      } >FLASH

      sidata = LOADADDR(.data);

      .data : 
      {
        . = ALIGN(4);
        sdata = .;        
        *(.data)           
        *(.data*)          

        . = ALIGN(4);
        edata = .;        
      } >RAM AT> FLASH

      
      . = ALIGN(4);
      .bss :
      {
        sbss = .;         
        __bss_start__ = sbss;
        *(.bss)
        *(.bss*)
        *(COMMON)

        . = ALIGN(4);
        ebss = .;         
        __bss_end__ = ebss;
      } >RAM

      ._user_heap_stack :
      {
        . = ALIGN(8);
        PROVIDE ( end = . );
        PROVIDE ( _end = . );
        . = . + minHeapSize;
        . = . + minStackSize;
        . = ALIGN(8);
      } >RAM

      

      /DISCARD/ :
      {
        libc.a ( * )
        libm.a ( * )
        libgcc.a ( * )
      }

      .ARM.attributes 0 : { *(.ARM.attributes) }
    }


