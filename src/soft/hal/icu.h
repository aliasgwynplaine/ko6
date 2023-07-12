/*------------------------------------------------------------------------------------------------*\
   _     ___    __
  | |__ /'v'\  / /      \date       2023-07-10
  | / /(     )/ _ \     \copyright  2021-2022 Sorbonne University
  |_\_\ x___x \___/                 https://opensource.org/licenses/MIT

  \file     hal/icu.h
  \author   Franck Wajsburt, Nolan Bled
  \brief    Generic ICU functions prototypes

\*------------------------------------------------------------------------------------------------*/

#ifndef _HAL_ICU_H_
#define _HAL_ICU_H_

struct icu_s;

struct icu_ops_s {
    void        (*icu_init)(struct icu_s *icu, unsigned address);

    /**
     * \brief   Generic function that fetch the highest priority IRQ from the ICU device
     * \param   icu the icu device
     * \return  highest priority IRQ
    */
    unsigned    (*icu_get_highest)(struct icu_s *icu);

    /**
     * \brief   Generic function that sets the priority of a given IRQ
     * \param   icu the icu device
     * \param   irq the irq
     * \param   pri the new priority of the IRQ
     * \return  nothing
    */
    void        (*icu_set_priority)(struct icu_s *icu, unsigned irq, unsigned pri);

    /**
     * \brief   Generic function that should aknowledge an IRQ
     * \param   icu the icu device
     * \param   irq the irq to acknowledge
     * \return  nothing
    */
    void        (*icu_acknowledge)(struct icu_s *icu, unsigned irq);

    /**
     * \brief   Generic function that mask (disable) an IRQ
     * \param   icu the icu device
     * \param   irq the irq to mask
     * \return  nothing
    */
    void        (*icu_mask)(struct icu_s *icu, unsigned irq);

    /**
     * \brief   Generic function that unmask (enable) an IRQ
     * \param   icu the icu device
     * \param   irq the irq to unmask
     * \return  nothing
    */   
    void        (*icu_unmask)(struct icu_s *icu, unsigned irq);
};

struct icu_s {
    unsigned address;           // ICU's address
    struct icu_ops_s *ops;      // driver-specific operations
};

/* ICU must be defined once somewhere */
extern struct icu_s icu;

#endif