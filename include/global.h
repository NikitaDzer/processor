//
// Created by User on 03.11.2021.
//

#ifndef PROCESSOR_GLOBAL_H
#define PROCESSOR_GLOBAL_H

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstdio>

typedef int_fast8_t error_t;

const size_t DARK_REGISTERS_NUMBER = 2;
const size_t REGISTERS_NUMBER      = 16;
const size_t RAM_SIZE              = 2048;

#define dead(pointer)                        \
        if ((pointer) == nullptr)            \
            do {                             \
               printf("#######\n"            \
                      "DEAD AT %ld %s\n",    \
                      __LINE__, __FILE__);   \
               exit(0xDEAD);                 \
            }   while (0)


#define notice(pointer)                       \
        if ((pointer) == nullptr)             \
            do {                              \
                printf("!!!!!!\n"             \
                       "NOTICE AT %ld %s",    \
                       __LINE__, __FILE__);   \
            } while (0)

#define kill                              \
         {                                \
            printf("@@@@@@\n"             \
                   "KILL AT %ld %s\n",    \
                   __LINE__, __FILE__);   \
            exit(0x4111);                 \
         }

#endif //PROCESSOR_GLOBAL_H
