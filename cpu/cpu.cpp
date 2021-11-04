//
// Created by User on 04.11.2021.
//

#include <cstring>
#include "../include/cpu.h"
#include "stack/include/stack.h"

static double DARK_REGISTERS[DARK_REGISTERS_NUMBER] = {0};
static double REGISTERS[REGISTERS_NUMBER]           = {0};
static double RAM[RAM_SIZE]                         = {0};
static Stack  STACK                                 = {0};

static void process_commands(const Command *const commands, const size_t commands_number)
{
   const Command *p_currentCommand = commands;
   
   while (p_currentCommand < commands + commands_number)
   {
      if (p_currentCommand->key == 1)
      {
         if (p_currentCommand->is_ram)
         {
            if (p_currentCommand->is_register)
               stack_push(&STACK, RAM[ (size_t)REGISTERS[ (size_t)p_currentCommand->argument ] ]);
            else
               stack_push(&STACK, RAM[ (size_t)p_currentCommand->argument ]);
         }
         else
         {
            if (p_currentCommand->is_register)
               stack_push(&STACK, REGISTERS[ (size_t)p_currentCommand->argument ]);
            else
               stack_push(&STACK, p_currentCommand->argument);
         }
      }
      else if (p_currentCommand->key == 2)
      {
         if (p_currentCommand->is_ram)
         {
            if (p_currentCommand->is_register)
               stack_pop(&STACK, RAM + (size_t)REGISTERS[ (size_t)p_currentCommand->argument ]);
            else
               stack_pop(&STACK, RAM + (size_t)p_currentCommand->argument);
         }
         else
         {
            if (p_currentCommand->is_register)
               stack_pop(&STACK, REGISTERS + (size_t)p_currentCommand->argument);
            else
               kill
         }
      }
      else if (p_currentCommand->key == 3)
      {
         stack_pop(&STACK, DARK_REGISTERS);
         stack_pop(&STACK, DARK_REGISTERS + 1);
         
         stack_push(&STACK, DARK_REGISTERS[0] + DARK_REGISTERS[1]);
      }
      else if (p_currentCommand->key == 4)
      {
         stack_pop(&STACK, DARK_REGISTERS);
         stack_pop(&STACK, DARK_REGISTERS + 1);
         
         stack_push(&STACK, DARK_REGISTERS[0] * DARK_REGISTERS[1]);
      }
      
      p_currentCommand += 1;
   }
}

static const Command* get_commands(const char *const binaryFile_path, size_t *const p_commands_number)
{
   dead(binaryFile_path);
   dead(p_commands_number);
   
   FILE          *binaryFile      = nullptr;
   size_t         commands_number =  0;
   const Command *commands        = nullptr;
   
   binaryFile = fopen(binaryFile_path, "rb");
   
   dead(binaryFile);
   
   fread(&commands_number, sizeof(size_t), 1, binaryFile);
   
   commands = (Command *)calloc(commands_number, sizeof(Command));
   fread((void *)commands, sizeof(Command), commands_number, binaryFile);
   
   fclose(binaryFile);
   
   *p_commands_number = commands_number;
   
   return commands;
}

void cpu(const char *const binaryFile_path)
{
   size_t               commands_number  = 0;
   const Command *const commands         = get_commands(binaryFile_path, &commands_number);
   
   stack_debug(&STACK);
   stack_init(&STACK, 2);
   
   process_commands(commands, commands_number);
   
   stack_info(&STACK);
   
   stack_destroy(&STACK);
}