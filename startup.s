.syntax unified
.cpu cortex-m3
.fpu softvfp
.thumb

.global .g_pfnVectors
.global Default_Handler

.word sidata
.word sdata
.word edata
.word sbss
.word ebss


    .section .text.ResetHandler
    .weak ResetHandler
    .type ResetHandler, %function

ResetHandler:
    movs r0, #0
    ldr r2, =sdata
    b dataInit

dataLoop:
    ldr r1, =sidata
    ldr r1, [r1, r0]
    str r1, [r2, r0]
    add r0, r0, #4
dataInit:
    ldr r1, =edata
    add r3, r2, r0
    cmp r3, r1
    bcc dataLoop
    
    ldr r1, =sbss
    ldr r2, =ebss
    b bssInit
bssLoop:
    mov r0, #0
    str r0, [r1], #4
bssInit:
    cmp r1, r2
    bcc bssLoop

    bl __libc_init_array
    bl main
    bx lr
.size ResetHandler, .-ResetHandler

    .section .text.Default_Handler, "ax", %progbits
    .weak Default_Handler
Default_Handler:
Loop:
    MRS r0, IPSR
    ldr r1, =interrupt
    str r0, [r1]
    b Loop
.size Default_Handler, .-Default_Handler


    .section .isr_vector,"a",%progbits
    .type g_pfnVectors, %object
    .size g_pfnVectors, .-g_pfnVectors


g_pfnVectors:

  .word estack
  .word ResetHandler
  .word NMI_Handler
  .word HardFault_Handler
  .word MemManage_Handler
  .word BusFault_Handler
  .word UsageFault_Handler
  .word 0
  .word 0
  .word 0
  .word 0
  .word SVC_Handler
  .word DebugMon_Handler
  .word 0
  .word PendSV_Handler
  .word SysTick_Handler

  .word WWDGT_ISR
  .word LVD_ISR
  .word TAMPER_ISR
  .word RTC_ISR
  .word FMC_ISR
  .word RCU_CTC_ISR
  .word EXTI0_ISR
  .word EXTI1_ISR
  .word EXTI2_ISR
  .word EXTI3_ISR
  .word EXTI4_ISR
  .word DMA0_Channel0_ISR
  .word DMA0_Channel1_ISR
  .word DMA0_Channel2_ISR
  .word DMA0_Channel3_ISR
  .word DMA0_Channel4_ISR
  .word DMA0_Channel5_ISR
  .word DMA0_Channel6_ISR
  .word ADC0_1_ISR
  .word USBD_HP_CAN0_TX_ISR
  .word USBD_LP_CAN0_RX0_ISR
  .word CAN0_RX1_ISR
  .word CAN0_EWMC_ISR
  .word EXTI5_9_ISR
  .word TIMER0_BRK_TIMER8_ISR
  .word TIMER0_UP_TIMER9_ISR
  .word TIMER0_TRG_CMT_TIMER10_ISR
  .word TIMER0_Channel_ISR
  .word TIMER1_ISR
  .word TIMER2_ISR
  .word TIMER3_ISR
  .word I2C0_EV_ISR
  .word I2C0_ER_ISR
  .word I2C1_EV_ISR
  .word I2C1_ER_ISR
  .word SPI0_ISR
  .word SPI1_ISR
  .word USART0_ISR
  .word USART1_ISR
  .word USART2_ISR
  .word EXTI10_15_ISR
  .word RTC_Alarm_ISR
  .word USBD_WKUP_ISR
  .word TIMER7_BRK_TIMER11_ISR
  .word TIMER7_UP_TIMER12_ISR
  .word TIMER7_TRG_CMT_TIMER13_ISR
  .word TIMER7_Channel_ISR
  .word ADC2_ISR
  .word EXMC_ISR
  .word SDIO_ISR
  .word TIMER4_ISR
  .word SPI2_ISR
  .word UART3_ISR
  .word UART4_ISR
  .word TIMER5_ISR
  .word TIMER6_ISR
  .word DMA1_Channel0_ISR
  .word DMA1_Channel1_ISR
  .word DMA1_Channel2_ISR
  .word DMA1_Channel3_4_ISR
  
  .weak NMI_Handler
  .weak HardFault_Handler
  .weak MemManage_Handler
  .weak BusFault_Handler
  .weak UsageFault_Handler
  .weak SVC_Handler
  .weak DebugMon_Handler
  .weak PendSV_Handler
  .weak SysTick_Handler
  .weak WWDGT_ISR
  .weak LVD_ISR
  .weak TAMPER_ISR
  .weak RTC_ISR
  .weak FMC_ISR
  .weak RCU_CTC_ISR
  .weak EXTI0_ISR
  .weak EXTI1_ISR
  .weak EXTI2_ISR
  .weak EXTI3_ISR
  .weak EXTI4_ISR
  .weak DMA0_Channel0_ISR
  .weak DMA0_Channel1_ISR
  .weak DMA0_Channel2_ISR
  .weak DMA0_Channel3_ISR
  .weak DMA0_Channel4_ISR
  .weak DMA0_Channel5_ISR
  .weak DMA0_Channel6_ISR
  .weak ADC0_1_ISR
  .weak USBD_HP_CAN0_TX_ISR
  .weak CAN0_TX_ISR
  .weak USBD_LP_CAN0_RX0_ISR
  .weak CAN0_RX0_ISR
  .weak CAN0_RX1_ISR
  .weak CAN0_EWMC_ISR
  .weak EXTI5_9_ISR
  .weak TIMER0_BRK_ISR
  .weak TIMER0_UP_ISR
  .weak TIMER0_TRG_CMT_ISR
  .weak TIMER0_Channel_ISR
  .weak TIMER0_BRK_TIMER8_ISR
  .weak TIMER0_UP_TIMER9_ISR
  .weak TIMER0_TRG_CMT_TIMER10_ISR
  .weak TIMER1_ISR
  .weak TIMER2_ISR
  .weak TIMER3_ISR
  .weak I2C0_EV_ISR
  .weak I2C0_ER_ISR
  .weak I2C1_EV_ISR
  .weak I2C1_ER_ISR
  .weak SPI0_ISR
  .weak SPI1_ISR
  .weak USART0_ISR
  .weak USART1_ISR
  .weak USART2_ISR
  .weak EXTI10_15_ISR
  .weak RTC_Alarm_ISR
  .weak USBD_WKUP_ISR
  .weak TIMER7_BRK_TIMER11_ISR
  .weak TIMER7_UP_TIMER12_ISR
  .weak TIMER7_TRG_CMT_TIMER13_ISR
  .weak TIMER7_Channel_ISR
  .weak ADC2_ISR
  .weak EXMC_ISR
  .weak SDIO_ISR
  .weak TIMER4_ISR
  .weak SPI2_ISR
  .weak UART3_ISR
  .weak UART4_ISR
  .weak TIMER5_ISR
  .weak TIMER6_ISR
  .weak DMA1_Channel0_ISR
  .weak DMA1_Channel1_ISR
  .weak DMA1_Channel2_ISR
  .weak DMA1_Channel3_4_ISR
  
  .thumb_set NMI_Handler, Default_Handler
  .thumb_set HardFault_Handler, Default_Handler
  .thumb_set MemManage_Handler, Default_Handler
  .thumb_set BusFault_Handler, Default_Handler
  .thumb_set UsageFault_Handler, Default_Handler
  .thumb_set SVC_Handler, Default_Handler
  .thumb_set DebugMon_Handler, Default_Handler
  .thumb_set PendSV_Handler, Default_Handler
  .thumb_set SysTick_Handler, Default_Handler
  .thumb_set WWDGT_ISR, Default_Handler
  .thumb_set LVD_ISR, Default_Handler
  .thumb_set TAMPER_ISR, Default_Handler
  .thumb_set RTC_ISR, Default_Handler
  .thumb_set FMC_ISR, Default_Handler
  .thumb_set RCU_CTC_ISR, Default_Handler
  .thumb_set EXTI0_ISR, Default_Handler
  .thumb_set EXTI1_ISR, Default_Handler
  .thumb_set EXTI2_ISR, Default_Handler
  .thumb_set EXTI3_ISR, Default_Handler
  .thumb_set EXTI4_ISR, Default_Handler
  .thumb_set DMA0_Channel0_ISR, Default_Handler
  .thumb_set DMA0_Channel1_ISR, Default_Handler
  .thumb_set DMA0_Channel2_ISR, Default_Handler
  .thumb_set DMA0_Channel3_ISR, Default_Handler
  .thumb_set DMA0_Channel4_ISR, Default_Handler
  .thumb_set DMA0_Channel5_ISR, Default_Handler
  .thumb_set DMA0_Channel6_ISR, Default_Handler
  .thumb_set ADC0_1_ISR, Default_Handler
  .thumb_set USBD_HP_CAN0_TX_ISR, Default_Handler
  .thumb_set CAN0_TX_ISR, Default_Handler
  .thumb_set USBD_LP_CAN0_RX0_ISR, Default_Handler
  .thumb_set CAN0_RX0_ISR, Default_Handler
  .thumb_set CAN0_RX1_ISR, Default_Handler
  .thumb_set CAN0_EWMC_ISR, Default_Handler
  .thumb_set EXTI5_9_ISR, Default_Handler
  .thumb_set TIMER0_BRK_ISR, Default_Handler
  .thumb_set TIMER0_UP_ISR, Default_Handler
  .thumb_set TIMER0_TRG_CMT_ISR, Default_Handler
  .thumb_set TIMER0_Channel_ISR, Default_Handler
  .thumb_set TIMER0_BRK_TIMER8_ISR, Default_Handler
  .thumb_set TIMER0_UP_TIMER9_ISR, Default_Handler
  .thumb_set TIMER0_TRG_CMT_TIMER10_ISR, Default_Handler
  .thumb_set TIMER1_ISR, Default_Handler
  .thumb_set TIMER2_ISR, Default_Handler
  .thumb_set TIMER3_ISR, Default_Handler
  .thumb_set I2C0_EV_ISR, Default_Handler
  .thumb_set I2C0_ER_ISR, Default_Handler
  .thumb_set I2C1_EV_ISR, Default_Handler
  .thumb_set I2C1_ER_ISR, Default_Handler
  .thumb_set SPI0_ISR, Default_Handler
  .thumb_set SPI1_ISR, Default_Handler
  .thumb_set USART0_ISR, Default_Handler
  .thumb_set USART1_ISR, Default_Handler
  .thumb_set USART2_ISR, Default_Handler
  .thumb_set EXTI10_15_ISR, Default_Handler
  .thumb_set RTC_Alarm_ISR, Default_Handler
  .thumb_set USBD_WKUP_ISR, Default_Handler
  .thumb_set TIMER7_BRK_TIMER11_ISR, Default_Handler
  .thumb_set TIMER7_UP_TIMER12_ISR, Default_Handler
  .thumb_set TIMER7_TRG_CMT_TIMER13_ISR, Default_Handler
  .thumb_set TIMER7_Channel_ISR, Default_Handler
  .thumb_set ADC2_ISR, Default_Handler
  .thumb_set EXMC_ISR, Default_Handler
  .thumb_set SDIO_ISR, Default_Handler
  .thumb_set TIMER4_ISR, Default_Handler
  .thumb_set SPI2_ISR, Default_Handler
  .thumb_set UART3_ISR, Default_Handler
  .thumb_set UART4_ISR, Default_Handler
  .thumb_set TIMER5_ISR, Default_Handler
  .thumb_set TIMER6_ISR, Default_Handler
  .thumb_set DMA1_Channel0_ISR, Default_Handler
  .thumb_set DMA1_Channel1_ISR, Default_Handler
  .thumb_set DMA1_Channel2_ISR, Default_Handler
  .thumb_set DMA1_Channel3_4_ISR, Default_Handler
