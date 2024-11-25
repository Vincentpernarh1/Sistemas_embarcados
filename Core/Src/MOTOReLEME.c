/*
 * MOTOReLEME.c
 *
 *  Created on: Nov 23, 2024
 *      Author: Elias Nacif, Vincent, Everson Elias
*/


// ============= INCLUDES ============
#include <stdint.h>
#include <stdbool.h>

#include "main.h"
#include "MOTOReLEME.h"
#include "pwm.h"
// ===================================


// =========== VARIAVEIS =============
uint16_t currentPosition = 94;
// ==================================


// ============= FUNCOES ============

/**
  * @brief Função de mudança de posicionamento do leme
  * @param1 timer (TIM_HandleTypeDef) : Aponta para o timer usado no leme
  * @param2 channel (uint32_t) : Equivale para o canal de saída do timer
  * @param3 newPosition (uint16_t) : Posição angular nova do leme que varia de 44 (-90°) até 144 (90°)
  *        com ponto neutro sendo 100 (0°)
  * @param4 speed (uint8_t) : Velocidade de giro do Leme [1 a 10]
  * @retval None
  */
void Rudder_Control(TIM_HandleTypeDef timer, uint32_t channel, uint16_t newPosition, uint8_t speed){
	int i = 0;

	if(newPosition <= currentPosition){
		for(i=0;i<(currentPosition-newPosition)+1; i+=1){
			setPWM(timer, channel, 1250, currentPosition-i);
			HAL_Delay(30);
		}
		currentPosition = newPosition;
	}
	else if(newPosition > currentPosition){
		for(i=0; i<(newPosition-currentPosition)+1; i+=1){
			setPWM(timer, channel, 1250, currentPosition+i);
			HAL_Delay(30);
		}
		currentPosition = newPosition;
	}
}


/**
  * @brief Função de Controle do Motor
  * @param1 timer (TIM_HandleTypeDef) : Aponta para o timer usado no leme
  * @param2 channel (uint32_t) : Equivale para o canal de saída do timer
  * @param3 enable (bool) : Ativação ou não do motor
  * @param4 direction (bool) : Aponta para a direção do motor [Adiante ou ré]
  * @param5 speed (uint16_t) : Velocidade de giro do Motor
  * @retval None
  */
void Motor_Control(TIM_HandleTypeDef timer, uint32_t channel, bool enable, bool direction, uint16_t speed){
	if (enable) {
		// Set motor direction
	    HAL_GPIO_WritePin(L293D_C_LK_GPIO_Port, L293D_C_LK_Pin, direction ? GPIO_PIN_SET : GPIO_PIN_RESET);
	    // Set PWM duty cycle for speed control (PA7)
	    __HAL_TIM_SET_COMPARE(&timer, channel, speed);
	    // Start PWM
	    HAL_TIM_PWM_Start(&timer, channel);
	} else {
	    // Stop motor by disabling PWM
	    HAL_TIM_PWM_Stop(&timer, channel);
	}
}
