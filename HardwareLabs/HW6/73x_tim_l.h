/* Exported constants --------------------------------------------------------*/

/*TIM MODE*/
#define TIM_PWMI      	    0x4000 /* PWM INPUT Mode */
#define TIM_OCM_CHANNELA    0x0100 /* OUTPUT COMPARE CHANNEL A Mode */
#define TIM_OCM_CHANNELB    0x0200 /* OUTPUT COMPARE CHANNEL B Mode */
#define TIM_OCM_CHANNELAB   0x0300 /* OUTPUT COMPARE CHANNEL A & CHANNEL B  Mode */
#define TIM_PWM             0x0010 /* PWM Mode */
#define TIM_OPM             0x0020 /* ONE PULSE Mode */
#define TIM_ICAP_CHANNELA   0x0400 /* INPUT CAPTURE A Mode */
#define TIM_ICAP_CHANNELB   0x0500 /* INPUT CAPTURE B Mode */
#define TIM_ICAP_CHANNELAB  0x0600 /* INPUT CAPTURE A & B Mode */

/*OUTPUT COMPARE MODE*/
#define TIM_Wave       0x0080
#define TIM_Timing     0x0800

/*CLOCK SOURCE*/
#define TIM_CLK_INTERNAL     0x8002
#define TIM_CLK_EXTERNAL     0x8001
#define TIM_ICAP_NONE        0x0000 
#define TIM_ICAP_0           0x0001
#define TIM_ICAP_1           0x0002
#define TIM_ICAP_2           0x0004
#define TIM_ICAP_3           0x0008
#define TIM_ICAP_4           0x0010
#define TIM_ICAP_5           0x0020
#define TIM_ICAP_6           0x0040
#define TIM_ICAP_7           0x0080
#define TIM_ICAP_8           0x0100
#define TIM_ICAP_9           0x0200

/*CLOCK EDGE*/
#define TIM_CLKEDGE_Falling  0x0004
#define TIM_CLKEDGE_Rising   0x0002

/*OUTPUT LEVEL*/
#define TIM_High       0x0200
#define TIM_Low        0x0300

/*OUTPUT EDGE*/
#define TIM_Rising     0x8000
#define TIM_Falling    0x0800

/*DMA SOURCE*/
#define TIM_DMA_ICA        0x0000 /* Input Capture Channel A DMA Source */
#define TIM_DMA_OCA        0x1000 /* OUTPUT Compare Channel A DMA Source */
#define TIM_DMA_ICB        0x2000 /* Input Capture Channel B DMA Source */
#define TIM_DMA_OCB        0x3000 /* OUTPUT Compare Channel A DMA Source */

/*DMA ENABLE/DISABLE*/
#define TIM_DMA_Enable      0x0400 /* DMA Enable */
#define TIM_DMA_Disable     0xFBFF /* DMA Disable */

/* Bits Masks */
#define TIM_ECK_ENABLE_Mask   0x0001
#define TIM_ECK_DISABLE_Mask  0xFFFE

#define TIM_EXEDG_ENABLE_Mask  0x0002
#define TIM_EXEDG_DISABLE_Mask 0xFFFD

#define TIM_IEDGA_ENABLE_Mask   0x0004
#define TIM_IEDGA_DISABLE_Mask  0xFFFB

#define TIM_IEDGB_ENABLE_Mask   0x0008
#define TIM_IEDGB_DISABLE_Mask  0xFFF7

#define TIM_PWM_Mask    0x0010
#define TIM_OMP_Mask    0x0020
#define TIM_OCA_ENABLE_Mask   0x0040
#define TIM_OCA_DISABLE_Mask  0xFFBF
#define TIM_OCB_ENABLE_Mask   0x0080
#define TIM_OCB_DISABLE_Mask  0xFF7F
#define TIM_PWMI_Mask   0x4000

#define TIM_OLVLA_Set_Mask    0x0100
#define TIM_OLVLA_Reset_Mask  0xFEFF

#define TIM_OLVLB_Set_Mask    0x0200
#define TIM_OLVLB_Reset_Mask  0xFDFF

#define TIM_ENABLE_Mask     0x8000
#define TIM_DISABLE_Mask    0x7FFF

/* TIM Interruption Sources*/
#define TIM_IT_ICA   0x8000 /* Input Capture Channel A Interrupt Source */ 
#define TIM_IT_OCA   0x4000 /* Output Compare Channel A Interrupt Source */
#define TIM_IT_TO    0x2000 /* Timer OverFlow Interrupt Source*/
#define TIM_IT_ICB   0x1000 /* Input Capture Channel B Interrupt Source */
#define TIM_IT_OCB   0x0800 /* Output Compare Channel B Interrupt Source */

/* TIM Flags */
#define TIM_FLAG_ICA     0x8000 /* Input Capture Channel A Flag */ 
#define TIM_FLAG_OCA     0x4000 /* Output Compare Channel A Flag */ 
#define TIM_FLAG_TO      0x2000 /* Timer OverFlow Flag */ 
#define TIM_FLAG_ICB     0x1000 /* Input Capture Channel B Flag */ 
#define TIM_FLAG_OCB     0x0800 /* Output Compare Channel B Flag */ 
