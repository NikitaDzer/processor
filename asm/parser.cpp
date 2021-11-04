//
// Created by User on 04.11.2021.
//


#include "../include/parser.h"
#include <cstring>


void parse(const LineLexemes *const lines_lexemes, const size_t lines_lexemes_number, Command **p_commands)
{
   dead(lines_lexemes);
   dead(p_commands);
   
   Command *const commands                        = (Command *)calloc(lines_lexemes_number, sizeof(Command));
   Command       *commands_iterator               = commands;
   const LineLexemes *commands_headers_iterator = lines_lexemes;
   
   dead(commands);
   
   for (size_t i = 0; i < lines_lexemes_number; i++)
   {
      if (strcmp(commands_headers_iterator->command_name, "PUSH") == 0)
      {
         commands_iterator->key = 1;
         
         if (commands_headers_iterator->argument_string)
         {
            sscanf(commands_headers_iterator->argument_string, "%lf", &commands_iterator->argument);
            commands_iterator->has_argument = true;
         }
         else
         {
            commands_iterator->has_argument = false;
            kill
         }
      }
      else if (strcmp(commands_headers_iterator->command_name, "POP") == 0)
      {
         commands_iterator->key = 2;
         
         if (commands_headers_iterator->argument_string)
         {
            sscanf(commands_headers_iterator->argument_string, "%lf", &commands_iterator->argument);
            commands_iterator->has_argument = true;
         }
         else
         {
            commands_iterator->has_argument = false;
            kill
         }
      }
      else
      {
         kill
      }
      
      commands_iterator         += 1;
      commands_headers_iterator += 1;
   }
   
   *p_commands = commands;
}