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
static Stack  CALLSTACK                             = {0};
static Stack  STACK                                 = {0};

static int process_commands(const Command *const commands, const size_t commands_number)
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
   
   return 0;
}

static const Command* get_commands(const char *const binfile_path, size_t *const p_commands_number)
{
   dead(binfile_path);
   dead(p_commands_number);
   
   FILE          *binfile         = nullptr;
   size_t         commands_number = 0;
   const Command *commands        = nullptr;
   
   binfile = fopen(binfile_path, "rb");
   
   dead(binfile);
   
   fread(&commands_number, sizeof(size_t), 1, binfile);
   
   commands = (Command *)calloc(commands_number, sizeof(Command));
   
   fread((void *)commands, sizeof(Command), commands_number, binfile);
   fclose(binfile);
   
   *p_commands_number = commands_number;
   
   return commands;
}

void cpu(const char *const binfile_path)
{
   size_t               commands_number  = 0;
   const Command *const commands         = get_commands(binfile_path, &commands_number);
   
   stack_debug(&STACK);
   stack_debug(&CALLSTACK);
   
   stack_init(&STACK, 2);
   stack_init(&CALLSTACK, 2);
   
   process_commands(commands, commands_number);
   
//   stack_info(&STACK);
//   stack_info(&CALLSTACK);
   
   free((void *)commands);
   stack_destroy(&STACK);
   stack_destroy(&CALLSTACK);
}