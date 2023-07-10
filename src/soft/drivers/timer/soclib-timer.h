/*------------------------------------------------------------------------------------------------*\
   _     ___    __
  | |__ /'v'\  / /      \date       2023-07-10
  | / /(     )/ _ \     \copyright  2021-2022 Sorbonne University
  |_\_\ x___x \___/                 https://opensource.org/licenses/MIT

  \file     drivers/timer/soclib-timer.h
  \author   Franck Wajsburt, Nolan Bled
  \brief    Soclib timer driver

\*------------------------------------------------------------------------------------------------*/

#ifndef _SOCLIB_TIMER_H_
#define _SOCLIB_TIMER_H_

#include <hal/timer.h>

struct soclib_timer_regs_s {
    int value;          // timer's counter : +1 each cycle, can be written
    int mode;           // timer's mode : bit 0 = ON/OFF ; bit 1 = IRQ enable
    int period;         // timer's period between two IRQ
    int resetirq;       // address to acknowledge the timer's IRQ
};

void soclib_timer_isr(unsigned irq, struct timer_s *timer);

extern struct tty_ops_s soclib_tty_ops;

#endif