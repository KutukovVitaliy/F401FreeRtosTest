/*
 * usart.c
 *
 *  Created on: Jul 2, 2021
 *      Author: kutuk
 */
#include "usart.h"
#include "string.h"
#include "stdio.h"

extern uint8_t receive_buff[BUFFER_SIZE];
extern DMA_HandleTypeDef hdma_usart1_rx;
extern UART_HandleTypeDef huart1;

void USER_UART_IRQHandler(UART_HandleTypeDef *huart)
{
    if(USART1 == huart1.Instance)                                   //Determine whether it is serial port 1
    {
        if(RESET != __HAL_UART_GET_FLAG(&huart1, UART_FLAG_IDLE))   //Judging whether it is idle interruption
        {
            __HAL_UART_CLEAR_IDLEFLAG(&huart1);                     //Clear idle interrupt sign (otherwise it will continue to enter interrupt)
            printf("\r\nUART1 Idle IQR Detected\r\n");
            USAR_UART_IDLECallback(huart);                          //Call interrupt handler
        }
    }
}


void USAR_UART_IDLECallback(UART_HandleTypeDef *huart)
{
	//Stop this DMA transmission
    HAL_UART_DMAStop(&huart1);

    //Calculate the length of the received data
    uint8_t data_length  = BUFFER_SIZE - __HAL_DMA_GET_COUNTER(&hdma_usart1_rx);

	//Test function: Print out the received data
    printf("Receive Data(length = %d): ",data_length);
    HAL_UART_Transmit(&huart1,receive_buff,data_length,0x200);
    printf("\r\n");
    for(int i = 0; i < data_length; ++i)
    {
    	printf("%2X ", receive_buff[i]);
    }

    printf("\r\n");
	//Zero Receiving Buffer
    memset(receive_buff,0,data_length);
    data_length = 0;

    //Restart to start DMA transmission of 255 bytes of data at a time
    HAL_UART_Receive_DMA(&huart1, (uint8_t*)receive_buff, 255);
}

