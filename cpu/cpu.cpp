//
// Created by User on 04.11.2021.
//

#include <cstring>
#include <cmath>
#include "../include/cpu.h"
#include "stack/include/stack.h"

#define DEFINE_COMMAND(cmd_name, cmd_key, arguments_number, code)         \
            case COMMAND_##cmd_name:                                      \
            {                                                             \
               code                                                       \
               break;                                                     \
            }

struct CPU
{
   double *DARK_REGISTERS;
   double *REGISTERS;
   double *RAM;
   char   *VRAM;
   Stack   STACK;
   Stack   CALLSTACK;
};

static void get_commands(const char *const binfile_path,
                         Command **const p_commands, size_t *const p_commands_number)
{
   dead(binfile_path);
   dead(p_commands);
   dead(p_commands_number);
   
   FILE *binfile = fopen(binfile_path, "rb");
   dead(binfile);
   
   control_fread(p_commands_number, sizeof(size_t), 1, binfile);
   
   *p_commands = (Command *)calloc(*p_commands_number, sizeof(Command));
   dead(*p_commands);
   
   control_fread(*p_commands, sizeof(Command), *p_commands_number, binfile);
   
   if (fclose(binfile) == EOF)
      kill
}

static int process_commands(CPU *const p_cpu, const Command *const commands, const size_t commands_number)
{
   dead(commands);
   
   const Command *p_currentCommand = commands;
   
   while (p_currentCommand < commands + commands_number)
   {
//      printf("key:%d ", p_currentCommand->key);
      
      switch (p_currentCommand->key)
      {
         #include "./commands_system"
         #include "./commands"
   
         default:
         {
            kill
         }
      }
      
      p_currentCommand += 1;
   }
   
   return 0;
}

static void destruct_cpu(CPU *const p_CPU)
{
   dead(p_CPU);
   
   stack_destroy(&p_CPU->CALLSTACK);
   stack_destroy(&p_CPU->STACK);
   
   free(p_CPU->VRAM);
   free(p_CPU->RAM);
   free(p_CPU->REGISTERS);
   free(p_CPU->DARK_REGISTERS);
}

static void construct_cpu(CPU *const p_CPU)
{
   dead(p_CPU);
   
   p_CPU->DARK_REGISTERS = (double *)calloc(DARK_REGISTERS_NUMBER, sizeof(double));
   p_CPU->REGISTERS      = (double *)calloc(REGISTERS_NUMBER,      sizeof(double));
   p_CPU->RAM            = (double *)calloc(RAM_SIZE,              sizeof(double));
   p_CPU->VRAM           = (char   *)calloc(VRAM_SIZE,             sizeof(char));
   
   dead(p_CPU->DARK_REGISTERS);
   dead(p_CPU->REGISTERS);
   dead(p_CPU->RAM);
   dead(p_CPU->VRAM);
   
//   stack_debug(&p_CPU->STACK);
//   stack_debug(&p_CPU->CALLSTACK);
   
   stack_init(&p_CPU->STACK,     2);
   stack_init(&p_CPU->CALLSTACK, 2);
}

void processor(const char *const binfile_path)
{
   CPU      cpu             = {};
   size_t   commands_number = 0;
   Command *commands        = nullptr;
   
   construct_cpu(&cpu);
   
   get_commands(binfile_path, &commands, &commands_number);
   process_commands(&cpu, commands, commands_number);
   
   free((void *)commands);
   destruct_cpu(&cpu);
}