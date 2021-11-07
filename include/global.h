//
// Created by User on 03.11.2021.
//

#ifndef PROCESSOR_GLOBAL_H
#define PROCESSOR_GLOBAL_H

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstdio>

#define DEFINE_COMMAND(cmd_name, cmd_key, arguments_number, code)  \
            COMMAND_##cmd_name = cmd_key,

typedef int_fast8_t error_t;

const size_t WINDOW_HEIGHT         = 30;
const size_t WINDOW_WIDTH          = 30;

const size_t DARK_REGISTERS_NUMBER = 4;
const size_t REGISTERS_NUMBER      = 16;
const size_t VRAM_SIZE             = WINDOW_WIDTH * WINDOW_HEIGHT; // == 900
const size_t RAM_SIZE              = 2048;

const size_t COMMAND_NAME_MAX_SIZE = 64;
const size_t LABEL_NAME_MAX_SIZE   = 64;

struct Command
{
   char key;
   bool is_register;
   bool is_ram;
   double argument;
};

enum CommandKey
{
   #include "../cpu/commands_system"
   #include "../cpu/commands"
};

#define dead(pointer)                                                           \
        if ((pointer) == nullptr)                                               \
            do {                                                                \
               printf("#######\n"                                               \
                      "DEAD AT %ld %s\n",                                       \
                      __LINE__, __FILE__);                                      \
               exit(0xDEAD);                                                    \
            } while (0)


#define notice(pointer)                                                         \
        if ((pointer) == nullptr)                                               \
            do {                                                                \
                printf("!!!!!!\n"                                               \
                       "NOTICE AT %ld %s",                                      \
                       __LINE__, __FILE__);                                     \
            } while (0)

#define kill                                                                    \
         {                                                                      \
            printf("@@@@@@\n"                                                   \
                   "KILL AT %ld %s\n",                                          \
                   __LINE__, __FILE__);                                         \
            exit(0x4111);                                                       \
         }

#define control_fread(dist, element_size, n_elements, file)                     \
            do {                                                                \
               dead(dist);                                                      \
               dead(file);                                                      \
                                                                                \
               if (fread((void *)(dist), (element_size), (n_elements), (file))  \
                   != (n_elements))                                             \
                   kill;                                                        \
                                                                                \
            } while (0)


#endif //PROCESSOR_GLOBAL_H
