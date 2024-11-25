/*
 * MOTOReLEME.h
 *
 *  Created on: Nov 23, 2024
 *      Author: Elias Nacif, Vincent, Everson Elias
 */

#ifndef INC_MOTORELEME_H_
#define INC_MOTORELEME_H_

#include <stdbool.h>

// ==== VARIAVEIS ====
extern uint16_t currentPosition;
// ===================


// ===== FUNCOES =====

void Rudder_Control(TIM_HandleTypeDef timer, uint32_t channel, uint16_t newPosition, uint8_t speed);

void Motor_Control(TIM_HandleTypeDef timer, uint32_t channel, bool enable, bool direction, uint16_t speed);

// ===================

#endif /* INC_MOTORELEME_H_ */
