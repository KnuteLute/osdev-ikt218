//
// Created by per on 1/1/23.
//

#ifndef UIAOS_CPU_H
#define UIAOS_CPU_H

#if (ARCH_TARGET == x86)
#include "interrupts.h" // TODO
#include "hardware.h"
#include "timer.h"
#else
    #error "Selected ARCH target is not supported for the CPU "
#endif
#endif //UIAOS_CPU_H