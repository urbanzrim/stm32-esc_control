/*
 * dboardsetup.h
 *
 *  Created on: 5. apr. 2015
 *      Author: Urban Zrim
 */

#include "stm32f30x.h"
#include "stm32f30x_usart.h"
#include "stm32f30x_gpio.h"
#include "stm32f30x_i2c.h"
#include "stm32f30x_rcc.h"
#include "stm32f30x_spi.h"
#include "stm32f30x_tim.h"
#include "stm32f30x_misc.h"
#include <stdio.h>

#define USART_RX_PIN	GPIO_Pin_5
#define USART_TX_PIN	GPIO_Pin_4

#define TIM2_CH2_PIN	GPIO_Pin_1	// PORTA
#define TIM2_CH4_PIN	GPIO_Pin_3	// PORTA
#define TIM2_CH3_PIN	GPIO_Pin_2	// PORTA
#define TIM3_CH2_PIN	GPIO_Pin_4	// PORTA
#define TIM3_CH1_PIN	GPIO_Pin_6	// PORTC
#define TIM4_CH3_PIN	GPIO_Pin_14	// PORTD
#define TIM4_CH2_PIN	GPIO_Pin_13	// PORTD
#define TIM4_CH4_PIN	GPIO_Pin_15	// PORTD

/* Initialization functions prototypes */
void gpio_init(void);
void tim_init(void);
void uart_init(void);
void int_init(void);

/* Initializes GPIO ports and pins for F3 breakout board */
void gpio_init(){

	GPIO_InitTypeDef GPIO_InitStructure;

	/* Enable GPIO peripheral clock for ports B and C */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);

	/* Set up Alternate function for pin 9 and 10 on port A to USART */
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource5, GPIO_AF_7);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource4, GPIO_AF_7);

	/* Set up Alternate functions for TIM pins */
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_2);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_2);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_2);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_2);

	/* Configuration of pin 9 and 10 */
	GPIO_InitStructure.GPIO_Pin = USART_RX_PIN | USART_TX_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	/* Configuration of pin 9 and 10 */
	GPIO_InitStructure.GPIO_Pin = TIM4_CH2_PIN | TIM4_CH4_PIN | TIM4_CH3_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	/* Configuration of pin 9 and 10 */
	GPIO_InitStructure.GPIO_Pin = TIM3_CH1_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

}

/* Initializes UART */
void uart_init(){

	USART_InitTypeDef USART_InitStructure;

	/* USART clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	/* USART structure init*/
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);

	USART_Cmd(USART1, ENABLE);

}

/* Initializes Timers */
void tim_init(){

	TIM_TimeBaseInitTypeDef TimerInitStructure;
    TIM_OCInitTypeDef OutputChannelInit;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

    TimerInitStructure.TIM_Prescaler = 71;
    TimerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TimerInitStructure.TIM_Period = 20000-1;
    TimerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TimerInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM4, &TimerInitStructure);
    TIM_TimeBaseInit(TIM3, &TimerInitStructure);

    OutputChannelInit.TIM_OCMode = TIM_OCMode_PWM1;
    OutputChannelInit.TIM_Pulse = 1000;
    OutputChannelInit.TIM_OutputState = TIM_OutputState_Enable;
    OutputChannelInit.TIM_OCPolarity = TIM_OCPolarity_High;

    TIM_OC2Init(TIM4, &OutputChannelInit);
    TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Disable);

    TIM_OC4Init(TIM4, &OutputChannelInit);
    TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Disable);

    TIM_OC3Init(TIM4, &OutputChannelInit);
    TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Disable);

    TIM_OC1Init(TIM3, &OutputChannelInit);
    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Disable);

   /* Enable timers */
    TIM_Cmd(TIM3, ENABLE);
    TIM_Cmd(TIM4, ENABLE);
}
