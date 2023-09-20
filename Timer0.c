/*
 * Timer0.c
 *
 *  Created on: Jul 27, 2023
 *      Author: My Laptop
 */

#include "Timer0.h"

bool Timer0_OF = false;

void Timer0_Init(void){
  TIMER_Init_TypeDef timerInit = TIMER_INIT_DEFAULT;

  timerInit.enable = false;

  CMU_ClockEnable(cmuClock_TIMER0, true);

  TIMER_Init(TIMER0, &timerInit);

  uint32_t timerfreq = CMU_ClockFreqGet(cmuClock_TIMER0) / (timerInit.prescale+1);
  uint32_t timerTopval = timerfreq / TIMER0_FREQUENCY;

  TIMER_TopSet(TIMER0, timerTopval);


  //interrupt enable
  TIMER_IntEnable(TIMER0, TIMER_IEN_OF);
  NVIC_EnableIRQ(TIMER0_IRQn);



}

void Timer0_Enable(void){
  uint32_t flags = TIMER_IntGet(TIMER0);
  TIMER_IntClear(TIMER0, flags);
  TIMER_Enable(TIMER0, true);
}

void Timer0_disable(void){
  uint32_t flags = TIMER_IntGet(TIMER0);
  TIMER_IntClear(TIMER0, flags);
  TIMER_Enable(TIMER0, false);
}

void TIMER0_IRQHandler(void){
  uint32_t flags = TIMER_IntGet(TIMER0);
  TIMER_IntClear(TIMER0, flags);
  Timer0_OF = true;

}
