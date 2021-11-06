//
// Created by User on 03.11.2021.
//

#include <cctype>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include "../include/lexer.h"

static inline bool is_command_name_char(const char ch)
{
   return isalnum(ch) || ch == ':' || ch == '$' || ch == '_';
}

static inline bool is_command_argument_char(const char ch)
{
   return isalnum(ch) || ch == '-' ||  ch == ' ' || ch == '.' || ch == '_' || ch == '[' || ch == ']';
}

static inline const char* skip_gap(const char *const start)
{
   const char *iterator = start;
   
   while (*iterator == ' ')
      iterator += 1;
   
   return iterator;
}

static const char* write_command_name(const char *const start, CommandLexemes *const p_command_lexemes)
{
   dead(start);
   dead(p_command_lexemes);
   
   const char *iterator = start;
   while (is_command_name_char(*iterator))
   {
      p_command_lexemes->command_name[iterator - start] = *iterator;
      iterator += 1;
   }
   
   
   return iterator;
}

static const char* write_command_argument(const char *const start, CommandLexemes *const p_command_lexemes)
{
   dead(start);
   dead(p_command_lexemes);
   
   const char *iterator = start;
   while (is_command_argument_char(*iterator))
   {
      iterator += 1;
   }
   
   size_t shift = 0;
   size_t argument_size = 0;
   
   while (*(iterator - shift) == ' ')
      shift += 1;
   
   argument_size = iterator - start - argument_size + 1;
   p_command_lexemes->argument_string = (char *)calloc(argument_size, sizeof(char));
   
   dead(p_command_lexemes->argument_string);
   
   memcpy(p_command_lexemes->argument_string, start, (argument_size - 1) * sizeof(char));
   p_command_lexemes->argument_string[argument_size - 1] = '\0';
   
   return iterator;
}

static const char* write_command_lexemes(const char *const start, CommandLexemes *const p_command_lexemes)
{
   dead(start);
   dead(p_command_lexemes);
   
   const char *iterator = start;
   
   iterator = write_command_name(iterator, p_command_lexemes);
   iterator = skip_gap(iterator);

   if (is_command_argument_char(*iterator))
      iterator = write_command_argument(iterator, p_command_lexemes);
   
   return iterator;
}

size_t lex(const char *const source, const size_t file_size, CommandLexemes **p_commands_lexemes)
{
   dead(source);
   dead(p_commands_lexemes);
   
   CommandLexemes  *commands_lexemes          = (CommandLexemes *)calloc(file_size / 2, sizeof(CommandLexemes));
   CommandLexemes  *commands_lexemes_iterator = commands_lexemes;
   
   dead(commands_lexemes);
   
   char const *asmcode_iterator = source;
   
   while (true)
   {
      if (*asmcode_iterator == '\0')
         break;
      
      if (is_command_name_char(*asmcode_iterator))
      {
         asmcode_iterator = write_command_lexemes(asmcode_iterator, commands_lexemes_iterator);
         commands_lexemes_iterator += 1;
      }
      else
         asmcode_iterator += 1;
   }
   
   *p_commands_lexemes = commands_lexemes;
   
   return commands_lexemes_iterator - commands_lexemes;
}