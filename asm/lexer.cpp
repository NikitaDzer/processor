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
   return isalnum(ch) || ch == '$' || ch == '_';
}

static inline bool is_command_argument_char(const char ch)
{
   return isalnum(ch) ||  ch == ' '  || ch == '[' || ch == ']';
}

static inline bool is_argument_register(const char *const start, const size_t size)
{
   for (const char *iterator = start; iterator < start + size; iterator++)
   {
      if (isalpha(*iterator))
         return true;
   }
   
   return false;
}

static inline const char* skip_gap(const char *const start)
{
   const char *iterator = start;
   
   while (*iterator != '\0')
   {
      if (*iterator == ' ')
         iterator += 1;
      else
         return iterator;
   }
   
   return iterator;
}

static const char* write_command_name(const char *const start, LineLexemes *const p_line_lexemes)
{
   dead(start);
   dead(p_line_lexemes);
   
   const char *iterator = start;
   while (is_command_name_char(*iterator))
   {
      p_line_lexemes->command_name[iterator - start] = *iterator;
      iterator += 1;
   }
   
   return iterator;
}

static const char* write_command_argument(const char *const start, LineLexemes *const p_line_lexemes)
{
   dead(start);
   dead(p_line_lexemes);
   
   const char *iterator = start;
   while (is_command_argument_char(*iterator))
      iterator += 1;
   
   size_t shift = 0;
   size_t argument_size = 0;
   
   while (*(iterator - shift) == ' ')
      shift += 1;
   
   argument_size = iterator - start - argument_size + 1;
   p_line_lexemes->argument_string = (char *)calloc(argument_size, sizeof(char));
   
   dead(p_line_lexemes->argument_string);
   
   memcpy(p_line_lexemes->argument_string, start, (argument_size - 1) * sizeof(char));
   p_line_lexemes->argument_string[argument_size - 1] = '\0';
   
   return iterator;
}

static const char* write_command_header(const char *const start, LineLexemes *const p_line_lexemes)
{
   dead(start);
   dead(p_line_lexemes);
   
   const char *iterator = start;
   
   iterator = write_command_name(iterator, p_line_lexemes);
   iterator = skip_gap(iterator);
   
   if (is_command_argument_char(*iterator))
      iterator = write_command_argument(iterator, p_line_lexemes);
   
   return iterator;
}

size_t lexer(const char *const source, const size_t file_size, LineLexemes **p_lines_lexemes)
{
   dead(source);
   dead(p_lines_lexemes);
   
   LineLexemes  *lines_lexemes          = (LineLexemes *)calloc(file_size / 2, sizeof(LineLexemes));
   LineLexemes  *lines_lexemes_iterator = lines_lexemes;
   size_t lines_lexemes_counter         = 0;
   
   dead(lines_lexemes);
   
   char const *source_iterator = source;
   
   while (true)
   {
      if (*source_iterator == '\0')
         break;
      
      if (is_command_name_char(*source_iterator))
      {
         source_iterator = write_command_header(source_iterator, lines_lexemes_iterator);
   
         lines_lexemes_iterator += 1;
         lines_lexemes_counter  += 1;
      }
      else
         source_iterator += 1;
   }
   
   *p_lines_lexemes = lines_lexemes;
   
   
   return lines_lexemes_counter;
}