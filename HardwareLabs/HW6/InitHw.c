
#include <73x_lib.h>                    /* STR730 library functions           */

GPIO_InitTypeDef  GPIO_InitStruct;      /* Declare GPIO  structure            */
UART_InitTypeDef  UART_InitStruct;      /* Declare UART  structure            */
TIM_InitTypeDef   TIM_InitStructure;    /* Declare TIM   structure            */
CMU_InitTypeDef   CMU_InitStruct;       /* Declare CMU   structure            */
//ADC_InitTypeDef   ADC_InitStruct;       /* Declare ADC   structure            */
PRCCU_InitTypeDef PRCCU_InitStruct;     /* Declare PRCCU structure            */


int InitHwC (void) {
	/* Setup GPIO0 - Strobing LEDs																							*/
	CFG_PeripheralClockConfig(CFG_CLK_GPIO0, ENABLE);

  /* Setup GPIO6 - UART0 Tx pin setup (P6.9)                                  */
  CFG_PeripheralClockConfig(CFG_CLK_GPIO6 , ENABLE);


  /* Enable Enhanced Interrupt Controller (EIC)                               */
  CFG_PeripheralClockConfig(CFG_CLK_EIC, ENABLE);

  /* Enable clocks for Timer 0                                    */
  CFG_PeripheralClockConfig(CFG_CLK_TIM0 , ENABLE);

  /* Clock Monitor Unit (CMU) Setup                                           */
  /* Setup CMU to use oscillator                                              */
  CMU_DeInit();
  CMU_StructInit(&CMU_InitStruct);
  CMU_InitStruct.CMU_CKSEL0             = CMU_CKSEL0_CKOSC;
  CMU_Init(&CMU_InitStruct);

  /* Power, Reset and Clock Control Unit (PRCCU) Setup                        */
  /* Setup clock to frequency of oscillator                                   */
  PRCCU_DeInit();
  PRCCU_StructInit(&PRCCU_InitStruct);  
  PRCCU_InitStruct.PRCCU_DIV2           = DISABLE;
  PRCCU_Init(&PRCCU_InitStruct);

  /* Setup UART0 configuration                                                */
  /* UART0 = 9600 bps, 8 data bits, no parity, 1 stop bit; Loopback off       */
  CFG_PeripheralClockConfig(CFG_CLK_UART0 , ENABLE);
  UART_StructInit(&UART_InitStruct);
  UART_InitStruct.UART_BaudRate         = 9600;
  UART_InitStruct.UART_Mode             = UART_Mode_8D;
  UART_InitStruct.UART_Loop_Standard    = UART_Standard;
  UART_InitStruct.UART_StopBits         = UART_StopBits_1;
  UART_Cmd(UART0, ENABLE);
  UART_Init(UART0, &UART_InitStruct);

	return 0;
}
