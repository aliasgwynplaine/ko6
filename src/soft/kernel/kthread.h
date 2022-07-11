/*------------------------------------------------------------------------------------------------*\
   _     ___    __
  | |__ /'v'\  / /      \date       2022-07-03
  | / /(     )/ _ \     \copyright  2021-2022 Sorbonne University
  |_\_\ x___x \___/                 https://opensource.org/licenses/MIT

  \file     kernel/kthread.h
  \author   Franck Wajsburt
  \brief    scheduler & thread functions API

\*------------------------------------------------------------------------------------------------*/


#ifndef _KTHREAD_H_
#define _KTHREAD_H_


//--------------------------------------------------------------------------------------------------
// Maximum number of thread it can be changed
//--------------------------------------------------------------------------------------------------


#define THREAD_MAX          4


//--------------------------------------------------------------------------------------------------
// Thread states
//-------------------------------------------------------------------------------------------------


#define TH_STATE_RUNNING    0       /* there is at most one thread per processor */
#define TH_STATE_READY      1       /* threads that need the processor */
#define TH_STATE_DEAD       2       /* threads that have exited and whose retval has been read */
#define TH_STATE_WAIT       3       /* threads that is waiting for something to run again */
#define TH_STATE_ZOMBIE     4       /* threads that are exited but their retval is not yet read */


//--------------------------------------------------------------------------------------------------
// Thread & scheduler API
//--------------------------------------------------------------------------------------------------


/**
 * \brief   Hidden definition of thread_t, other C files don't know what is in the struct thread_s
 */
typedef struct thread_s * thread_t;

/**
 * \brief   Pointeur to the current RUNNING thread (only one per processor)
 *          TODO should be an array if there are several processor
 *          TODO add a variable to count the number of threads and check it when tbread_create
 */
extern thread_t ThreadCurrent;  

extern void thread_addlast (list_t * root, thread_t thread);

extern thread_t thread_item (list_t * item);


/**
 * \brief   Displays on the console (tty0) all active threads, it is for debugging.
 */
extern void sched_dump (void);

/**
 * \brief   Calls by the kernel in order to implement the user thread_create() syscall
 *          This function has the same arguments as thread_create(), plus one which is
 *          the pointer to the function that will start the thread, there are two of those:
 *          one for the main thread (nammed _start defined in crt0.c)
 *          and one for the standard thread (nammed thread_start defined in thread.c).
 *          These two functions do not have the same type but it does not matter because
 *          we are converting to int.
 * \param   thread  pointer to the thread structure
 * \param   fun     pointer to the function of the thread (cast to int)
 * \param   arg     the argument given to fun() (cast to int)
 * \param   start   pointer to the function which will start the thread (cast to int)
 *                  This function is defined in the same address space as the thread.
 *                  If it is a user thread the start function is in user space
 * \return  0 on success, an error code on fealure
 */
extern int thread_create (thread_t * thread, int fun, int arg, int start);

/**
 * \brief   load the context of the main() thread, only used by kinit
 * \return  nothing but the thread is launched and never come back
 */
extern void thread_main_load (thread_t thread);

/**
 * \brief   Causes the current thread to give up the CPU in order to give it to another
 * \return  0 in any cases
 */
extern int thread_yield (void);

/**
 * \brief   Terminates the current thread, it never returns (see details in kthread.c)
 * \param   retval the value can be retrieved by calling the thread_join function by another thread
 * \return  return the value retval 
 */
extern void thread_exit (void *retval);

/**
 * \brief   Wait for a thread termination (see details in kthread.c)
 * \param   thread  pointer to the awaited thread structure
 * \param   retval  pointer to the return value of the awaited thread
 * \return  0 on success, an error code on fealure (not yet implemented)
 */
extern int thread_join (thread_t thread, void ** retval);

/**
 * \brief   Ask the current RUNNING thread to WAIT
 *          the current thread must become READY again after the call to thread_notify().
 *          In some cases, when thread_notify() is called just before thread_wait() has had time 
 *          to put the current thread in the WAIT state (this is possible, since thread_notify() 
 *          is called by another thread running on another processor) then the current thread 
 *          is already READY but thread_wait() yields the processor anyway, so the current thread
 *          should lose the processor for a while, until the scheduler chooses it again.
 * \return  nothing but there is a state changement
 */
extern void thread_wait (void);

/**
 * \brief   Ask the current RUNNING thread to WAIT
 *          the current thread must become READY again after the call to thread_notify().
 *          In some cases, when thread_notify() is called just before thread_wait() has had time 
 *          to put the current thread in the WAIT state (this is possible, since thread_notify() 
 *          is called by another thread running on another processor) then the current thread 
 *          is already READY but thread_wait() yields the processor anyway, so the current thread
 *          should lose the processor for a while, until the scheduler chooses it again.
 */
extern void thread_notify (thread_t thread);

/**
 * \brief   return address of errno for the current thread
 *          this function is defined here, because it needs to access at the hidden thread struct
 * \return  an address in user space where the last syscall error is put
 */
extern int * __errno_location (void);

#endif//_KTHREAD_H_
