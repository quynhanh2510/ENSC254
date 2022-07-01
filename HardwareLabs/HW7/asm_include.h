
/******************************************************************************
*                   Peripherals' Base addresses
******************************************************************************/

#define APB                 0xFFFF8000     
#define FLASHR_BASE         0x80100000
#define FLASHPR_BASE        0x8010DFB0     
#define CFG_BASE            0x40000000
#define PRCCU_BASE          0x60000000
#define ARB_BASE            0x20000000

#define APB_BASE        APB
#define I2C0_BASE       (APB + 0x400)
#define I2C1_BASE       (APB + 0x800)
#define TB0_BASE        (APB + 0x1800)
#define TB1_BASE        (APB + 0x1900)
#define TB2_BASE        (APB + 0x1A00)
#define UART0_BASE      (APB + 0x1C00)
#define UART1_BASE      (APB + 0x2000)
#define UART2_BASE      (APB + 0x1E00)
#define UART3_BASE      (APB + 0x2200)
#define WDG_BASE        (APB + 0x2400)
#define WUT_BASE        (APB + 0x2600)
#define TIM0_BASE       (APB + 0x2800)
#define TIM1_BASE       (APB + 0x2C00)
#define TIM5_BASE       (APB + 0x3000)
#define TIM6_BASE       (APB + 0x3080)
#define TIM7_BASE       (APB + 0x3100)
#define TIM8_BASE       (APB + 0x3180)
#define TIM9_BASE       (APB + 0x3200)
#define WIU_BASE        (APB + 0x3800)
#define CAN0_BASE       (APB + 0x4400)
#define CAN1_BASE       (APB + 0x4800)
#define CAN2_BASE       (APB + 0x4C00)
#define PWM0_BASE       (APB + 0x5000)
#define PWM1_BASE       (APB + 0x5040)
#define PWM2_BASE       (APB + 0x5080)
#define PWM3_BASE       (APB + 0x50C0)
#define PWM4_BASE       (APB + 0x5100)
#define PWM5_BASE       (APB + 0x5140)
#define GPIO0_BASE      (APB + 0x5400)
#define GPIO1_BASE      (APB + 0x5410)
#define GPIO2_BASE      (APB + 0x5420)
#define GPIO3_BASE      (APB + 0x5430)
#define GPIO4_BASE      (APB + 0x5440)
#define GPIO5_BASE      (APB + 0x5450)
#define GPIO6_BASE      (APB + 0x5460)
#define BSPI0_BASE      (APB + 0x5800)
#define BSPI1_BASE      (APB + 0x5C00)
#define BSPI2_BASE      (APB + 0x6000)
#define TIM2_BASE       (APB + 0x6400)
#define TIM3_BASE       (APB + 0x6800)
#define TIM4_BASE       (APB + 0x6C00)
#define DMA0_BASE       (APB + 0x7000)
#define DMA1_BASE       (APB + 0x7100)
#define DMA2_BASE       (APB + 0x7200)
#define DMA3_BASE       (APB + 0x7300)
#define RTC_BASE        (APB + 0x7400)
#define CMU_BASE        (APB + 0x7600)
#define ADC_BASE        (APB + 0x7800)
#define EIC_BASE        (APB + 0x7C00)



/* Exported constants --------------------------------------------------------*/
/* GPIO Pins define */
#define GPIO_PIN_NONE   0x0000
#define GPIO_PIN_0      0x0001
#define GPIO_PIN_1      0x0002
#define GPIO_PIN_2      0x0004
#define GPIO_PIN_3      0x0008
#define GPIO_PIN_4      0x0010
#define GPIO_PIN_5      0x0020
#define GPIO_PIN_6      0x0040
#define GPIO_PIN_7      0x0080
#define GPIO_PIN_8      0x0100
#define GPIO_PIN_9      0x0200
#define GPIO_PIN_10     0x0400
#define GPIO_PIN_11     0x0800
#define GPIO_PIN_12     0x1000
#define GPIO_PIN_13     0x2000
#define GPIO_PIN_14     0x4000
#define GPIO_PIN_15     0x8000
#define GPIO_PIN_ALL    0xFFFF

/* GPIO Modes define */
#define GPIO_Mode_HI_AIN_TRI    0x0001
#define GPIO_Mode_IN_TRI_TTL    0x0002
#define GPIO_Mode_INOUT_WP      0x0003
#define GPIO_Mode_OUT_OD        0x0004
#define GPIO_Mode_OUT_PP        0x0005
#define GPIO_Mode_AF_OD         0x0006
#define GPIO_Mode_AF_PP         0x0007

/* GPIO MSB and LSB Bytes define */
#define GPIO_LSB   0x0000
#define GPIO_MSB   0x0008

// GPIO register offsets 
#define GPIO_PC0_OFS	0x0
#define GPIO_PC1_OFS	0x4
#define GPIO_PC2_OFS	0x8
#define GPIO_PD_OFS		0xC

// Timer register offsets 
#define TIMn_ICAR 0x00   /* Input Capture A Register*/
#define TIMn_ICBR 0x04   /* Input Capture B Register*/
#define TIMn_OCAR 0x08   /* Output Compare A Register*/
#define TIMn_OCBR 0x0C   /* Input Capture B Register*/
#define TIMn_CNTR 0x10   /* Counter Register */
#define TIMn_CR1 0x14    /* Control Register 1 */
#define TIMn_CR2 0x18    /* Control Register 2 */
#define TIMn_SR 0x1C     /* Status Register */

// EIC
// EIC register offsets 
#define EIC_ICR       0x00   /*  Interrupt Control Register*/
#define EIC_CICR      0x04   /*  Current Interrupt Channel Register*/
#define EIC_CIPR      0x08   /*  Current Interrupt Priority Register*/

#define EIC_FIER      0x10   /*  Fast Interrupt Enable Register*/
#define EIC_FIPR      0x14   /*  Fast Interrupt Pending Register*/
#define EIC_IVR       0x18   /*  Interrupt Vector Register*/
#define EIC_FIR       0x1C   /*  Fast Interrupt Register*/
#define EIC_IER0      0x20   /*  Interrupt Enable Register0*/
#define EIC_IER1      0x24   /*  Interrupt Enable Register1*/

#define EIC_IPR0      0x40   /*  Interrupt Pending Register0*/
#define EIC_IPR1      0x44   /*  Interrupt Pending Register1*/

#define EIC_SIRn      0x60   /*  64 Source Interrupt registers- Channel n*/

/*----------------   System Configuration Registers ----------------------------*/
#define CFG_R0     0x00    /*Configuration Register 0*/
#define CFG_EITE0  0x04    /*External Interrupt Trigger Event Register 0*/
#define PCGR0  0x08    /*Peripheral Clock Gating Register 0*/
#define PCGR1  0x0C    /*Peripheral Clock Gating Register 1*/
#define PECGR0 0x10    /*Peripheral Emulation Clock Gating Register 0*/
#define PECGR1 0x14    /*Peripheral Emulation Clock Gating Register 1*/
#define PCGRB0 0x18    /*Peripheral Clock Gating Register B0*/
#define PCGRB1 0x1C    /*Peripheral Clock Gating Register B1*/
#define TIMSR  0x20    /*TIM External Clock Select Register*/
#define CFG_EITE1  0x24    /*External Interrupt Trigger Event Register 1*/
#define CFG_EITE2  0x28    /*External Interrupt Trigger Event Register 2*/
#define ESPR   0x2C    /*Emulation Serial Protection Register*/
#define CFG_R1     0x30    /*Configuration Register 1*/
#define DIDR   0x34    /*Device Identification Register*/
