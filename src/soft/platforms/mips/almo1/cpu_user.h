/*------------------------------------------------------------------------------------------------*\
   _     ___    __
  | |__ /'v'\  / /      \date       2022-07-03
  | / /(     )/ _ \     \copyright  2021-2022 Sorbonne University
  |_\_\ x___x \___/                 https://opensource.org/licenses/MIT

  \file     platform/mips/almo1/hcpu_user.h
  \author   Franck Wajsburt
  \brief    CPU specific user functions 
            - This file contains cpu-dependant functions used by user applications. 
            - This functions could be static inline functions because or even macros,
              instead this is real code in .h file that is not very clean, 
              but I don't want theses functions inlined in order to see them in the trace execution
            - system calls 
            - FIXME spinlock or atomic add should be appeared.

\*------------------------------------------------------------------------------------------------*/

#ifndef _HCPU_USER_H_
#define _HCPU_USER_H_

//int syscall_fct (int a0, int a1, int a2, int a3, int syscall_code)
__asm__ (
".globl syscall_fct \n"         // it is an external function, it must be declared globl
"syscall_fct:       \n"         // syscall_fct function label
"   lw  $2,16($29)  \n"         // since syscall has 5 parameters, the fifth is in the stack
"   syscall         \n"         // EPC=addr_of_syscall; j 0x80000180; c0_sr.EXL=1; c0_cause.XCODE=8
"   jr  $31         \n"         // $31 must not have changed
);

#endif//_HCPU_USER_H_

