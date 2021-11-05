//
// Created by User on 04.11.2021.
//

#include <cstring>
#include "../include/cpu.h"
#include "stack/include/stack.h"

#define DEFINE_COMMAND(cmd_name, cmd_key, arguments_number, code)         \
            case cmd_key:                                                 \
            {                                                             \
               code                                                       \
               break;                                                     \
            }


static double DARK_REGISTERS[DARK_REGISTERS_NUMBER] = {0};
static double REGISTERS[REGISTERS_NUMBER]           = {0};
static double RAM[RAM_SIZE]                         = {0};
static Stack  STACK                                 = {0};

static void process_commands(const Command *const commands, const size_t commands_number)
{
   const Command *p_currentCommand = commands;
   
   while (p_currentCommand < commands + commands_number)
   {
//      printf("key:%d ", p_currentCommand->key);
      
      switch ((size_t)p_currentCommand->key)
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
}

static const Command* get_commands(const char *const binaryFile_path, size_t *const p_commands_number)
{
   dead(binaryFile_path);
   dead(p_commands_number);
   
   FILE          *binaryFile      = nullptr;
   size_t         commands_number = 0;
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
   
   free((void *)commands);
   stack_destroy(&STACK);
}