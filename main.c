/*
 * main.c
 *
 *  Created on: 5. apr. 2015
 *      Author: Urban Zrim
 */

#include "dboardsetup.h"

int esc_fl;
int esc_fr;
int esc_bl;	//TIM4_CH2_PIN
int esc_br;

int main(void)
{

	gpio_init();
	tim_init();
	uart_init();

    while(1)
    {

    }
}
