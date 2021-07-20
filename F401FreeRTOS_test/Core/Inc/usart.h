/*
 * usart.h
 *
 *  Created on: Jul 2, 2021
 *      Author: kutuk
 */

#ifndef INC_USART_H_
#define INC_USART_H_

#include "stm32f4xx_hal.h"
#define BUFFER_SIZE	255

void USER_UART_IRQHandler(UART_HandleTypeDef *huart);
void USAR_UART_IDLECallback(UART_HandleTypeDef *huart);


#endif /* INC_USART_H_ */
