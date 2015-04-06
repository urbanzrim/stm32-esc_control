/*
 * main.c
 *
 *  Created on: 5. apr. 2015
 *      Author: Urban Zrim
 */

#include "dboardsetup.h"


int main(void)
{

	gpio_init();
	tim_init();
	uart_init();

    while(1)
    {

    }
}
