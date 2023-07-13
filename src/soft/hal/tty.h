/*------------------------------------------------------------------------------------------------*\
   _     ___    __
  | |__ /'v'\  / /      \date       2023-07-10
  | / /(     )/ _ \     \copyright  2021-2022 Sorbonne University
  |_\_\ x___x \___/                 https://opensource.org/licenses/MIT

  \file     hal/tty.h
  \author   Franck Wajsburt, Nolan Bled
  \brief    Generic TTY functions prototypes

\*------------------------------------------------------------------------------------------------*/

#ifndef _HAL_TTY_H_
#define _HAL_TTY_H_

#include <common/errno.h>
#include <common/list.h>
#include <hal/dev.h>

#define TTY_FIFO_DEPTH 20

struct tty_s;

struct tty_ops_s {
    void (*tty_init)(struct tty_s *tty, unsigned address, unsigned baudrate);

    /**
     * \brief   Generic function that write to the tty device
     * \param   tty     the tty device
     * \param   buf     the buffer to write to the tty
     * \param   count   the number of bytes to write
     * \return  number of bytes actually written
    */
    int (*tty_write)(struct tty_s *tty, char *buf, unsigned count);

    /**
     * \brief   Generic function that reads from the tty device
     * \param   tty     the tty device
     * \param   buf     the buffer that will receive the data from the tty
     * \param   count   the number of bytes that should be written into the buffer
     * \return  number of bytes actually read
    */
    int (*tty_read)(struct tty_s *tty, char *buf, unsigned count);
};

/**
 * Simple fifo (1 writer - 1 reader)
 *   - data      buffer of data
 *   - pt_write  write pointer for L fifos (0 at the beginning)
 *   - pt_read   read pointer for L fifos (0 at the beginning)
 *
 * data[] is used as a circular array. At the beginning (pt_read == pt_write) means an empty fifo
 * then when we push a data, we write it at pt_write, the we increment pt_write % fifo_size.
 * The fifo is full when it remains only one free cell, then when (pt_write + 1)%size == pt_read
 */
struct tty_fifo_s {
    char data [TTY_FIFO_DEPTH];
    unsigned pt_read;
    unsigned pt_write;
};

struct tty_s {
    unsigned address;           // memory-mapped register addresses
    unsigned baudrate;          // tty baudrate
    list_t list;                // linked-list entry into the tty's list
    unsigned no;                // number of the tty entry in the tty's list
    struct tty_fifo_s fifo;
    struct tty_ops_s *ops;      // driver specific operations linked to the tty
};

#define tty_alloc() (struct tty_s*) (dev_alloc(TTY_DEV, sizeof(struct tty_s))->data)
#define tty_get(no) (struct tty_s*) (dev_get(TTY_DEV, no)->data)

/* Helper functions for TTY's FIFOs */

/**
 * \brief   push a character into the tty's FIFO
 * \param   fifo    structure of fifo to store data
 * \param   c       char to write
 * \return  SUCCESS or FAILURE
 */
int tty_fifo_push (struct tty_fifo_s *fifo, char c);

/**
 * \brief   pop a character from the tty's FIFO
 * \param   fifo    structure of fifo to store data
 * \param   c       pointer on char to put the read char 
 * \return  SUCCESS or FAILURE
 */
int tty_fifo_pull (struct tty_fifo_s *fifo, int *c);

#endif