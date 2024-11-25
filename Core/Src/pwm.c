/*
 * pwm.c
 *
 *  Created on: Nov 25, 2024
 *      Author: Elias Nacif, Everson Elias, Vincent
 */

// ============= INCLUDES ============
#include "main.h"
#include <stdint.h>
// ===================================

/**
  * @brief Função responsável pelo settar do sinal PWM especificando período e pulso
  * @param1 timer (TIM_HandleTypeDef) : Aponta para o Timer que gerará o PWM
  * @param2 channel (uint32_t) : Canal de Saída do PWM
  * @param3 period (uint16_t) : Período do sinal
  * @param4 pulse (uint16_t) : Pulso do PWM
  * @retval None
  */
void setPWM(TIM_HandleTypeDef timer, uint32_t channel, uint16_t period, uint16_t pulse)
{
	 HAL_TIM_PWM_Stop(&timer, channel);
	 TIM_OC_InitTypeDef sConfigOC;
	 timer.Init.Period = period;
	 HAL_TIM_PWM_Init(&timer);
	 sConfigOC.OCMode = TIM_OCMODE_PWM1;
	 sConfigOC.Pulse = pulse;
	 sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	 sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	 HAL_TIM_PWM_ConfigChannel(&timer, &sConfigOC, channel);
	 HAL_TIM_PWM_Start(&timer, channel);
}
