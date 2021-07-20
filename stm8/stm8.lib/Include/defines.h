/* Written by Oleg Terentiev (Hoksmur)
 * dec 2020 
 */
#ifndef __DEFINES_H__
#define __DEFINES_H__

#if defined( __SDCC_stm8 )
  #define ISR(VECT)   void vector_##VECT (void) __interrupt ( VECT )
  #define ISR_TRAP()  void handler (void) __trap
  
  // RESET
  // TRAP 
  #define ISR_TLI          0
  #define ISR_AWU          1
  #define ISR_CLK          2
  #define ISR_EXTI0_PORTA  3
  #define ISR_EXTI1_PORTB  4
  #define ISR_EXTI2_PORTC  5
  #define ISR_EXTI3_PORTD  6
  #define ISR_EXTI4_PORTE  7
  // --
  // --
  #define ISR_SPI          10
  #define ISR_TIM1_Upd_Ovf 11
  #define ISR_TIM1_Cap_Com 12
  #define ISR_TIM2_Upd_Ovf 13
  #define ISR_TIM2_Cap_Com 14
  // --
  // --
  #define ISR_UART1_TXC    17
  #define ISR_UART1_RXF    18
  #define ISR_I2C          19
  // --
  // --
  #define ISR_ADC_Conv_End 22
  #define ISR_TIM4_Upd_Ovf 23
  #define ISR_FLASH_EOP_WR_PG_DIS 24
  
#else
  #warning "Not SDCC?"
#endif

#define PAIS(X) (X<<0)
#define PBIS(X) (X<<2)
#define PCIS(X) (X<<4)
#define PDIS(X) (X<<6)
#define PEIS(X) (X<<0)


#ifdef __AVMACRO_H__

#define PA0  GPIOA, 0
#define PA1  GPIOA, 1
#define PA2  GPIOA, 2
#define PA3  GPIOA, 3
#define PA4  GPIOA, 4
#define PA5  GPIOA, 5
#define PA6  GPIOA, 6
#define PA7  GPIOA, 7

#define PB0  GPIOB, 0
#define PB1  GPIOB, 1
#define PB2  GPIOB, 2
#define PB3  GPIOB, 3
#define PB4  GPIOB, 4
#define PB5  GPIOB, 5
#define PB6  GPIOB, 6
#define PB7  GPIOB, 7

#define PC0  GPIOC, 0
#define PC1  GPIOC, 1
#define PC2  GPIOC, 2
#define PC3  GPIOC, 3
#define PC4  GPIOC, 4
#define PC5  GPIOC, 5
#define PC6  GPIOC, 6
#define PC7  GPIOC, 7

#define PD0  GPIOD, 0
#define PD1  GPIOD, 1
#define PD2  GPIOD, 2
#define PD3  GPIOD, 3
#define PD4  GPIOD, 4
#define PD5  GPIOD, 5
#define PD6  GPIOD, 6
#define PD7  GPIOD, 7

#define PE0  GPIOE, 0
#define PE1  GPIOE, 1
#define PE2  GPIOE, 2
#define PE3  GPIOE, 3
#define PE4  GPIOE, 4
#define PE5  GPIOE, 5
#define PE6  GPIOE, 6
#define PE7  GPIOE, 7

#define PF0  GPIOF, 0
#define PF1  GPIOF, 1
#define PF2  GPIOF, 2
#define PF3  GPIOF, 3
#define PF4  GPIOF, 4
#define PF5  GPIOF, 5
#define PF6  GPIOF, 6
#define PF7  GPIOF, 7

#else 
  #warning "Use this file with avmacro.h"
#endif /* __AVMACRO_H__ */



#endif /* __DEFINES_H__ */