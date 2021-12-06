//
// Created by User on 04.11.2021.
//

#include "../include/assembler.h"
#include "../include/global.h"
#include "../include/lexer.h"
#include "../include/parser.h"
#include <ctime>

static CommandLexemes *commands_lexemes        = nullptr;
static Command        *commands                = nullptr;
static size_t          commands_lexemes_number = 0;
static size_t          commands_number         = 0;

static long get_file_size(FILE* const file)
{
   long initialPosition = ftell(file);
   long file_size       = 0;
   
   fseek(file, 0, SEEK_END);
   file_size = ftell(file);
   fseek(file, initialPosition, SEEK_SET);
   
   return file_size - 1;
}

static void assembler_log()
{
   const time_t        seconds           = time(nullptr);
   const tm     *const date              = localtime(&seconds);
   FILE         *const assembler_logfile = fopen(assembler_logfile_path, "w");
   
   fprintf(assembler_logfile,
           "Time: %d:%d:%d\n"
           "========================================\n",
           date->tm_hour, date->tm_min, date->tm_sec);
   
   for (size_t i = 0, j = 0; i < commands_number; i++, j++)
   {
      while (commands_lexemes[j].command_name[0] == '\0')
         j += 1;
      
      fprintf(assembler_logfile,
              "%-10s %s\n"
              "%-10d %-10lg ram: %-d register: %-d\n"
              "----------------------------------------\n",
              commands_lexemes[j].command_name, commands_lexemes[j].argument_string,
              commands[i].key, commands[i].argument, commands[i].is_ram, commands[i].is_register);
   }
   
   fclose(assembler_logfile);
}

static char* get_asmcode(const char asmfile_path[], long *const p_asmcode_size)
{
   dead(asmfile_path);
   dead(p_asmcode_size);
   
   FILE *asmfile = nullptr;
   char *asmcode = nullptr;
   
   asmfile        = fopen(asmfile_path, "r");
   dead(asmfile);
   
  *p_asmcode_size = get_file_size(asmfile);
   asmcode        = (char *)calloc(*p_asmcode_size, sizeof(char));
   dead(asmcode);
   
   fread(asmcode, sizeof(char), *p_asmcode_size, asmfile);
   fclose(asmfile);
   
   return asmcode;
}

static void write_binfile(const char binfile_path[])
{
   FILE *const binfile = fopen(binfile_path, "wb");
   
   fwrite(&commands_number, sizeof(size_t), 1, binfile);
   fwrite(commands, sizeof(Command), commands_number, binfile);
   
   fclose(binfile);
}

void assembler(const char *const asmfile_path, const char *const binfile_path)
{
   dead(asmfile_path);
   dead(binfile_path);
   
   long        asmcode_size = 0;
   char *const asmcode      = get_asmcode(asmfile_path, &asmcode_size);
   
   commands_lexemes_number = lex(asmcode, asmcode_size, &commands_lexemes);
   commands_number         = parse(commands_lexemes, commands_lexemes_number, &commands);
   
   write_binfile(binfile_path);
   assembler_log();
   
   for (size_t i = 0; i < commands_number; i++)
      free(commands_lexemes[i].argument_string);
   
   free(commands_lexemes);
   free(commands);
   free(asmcode);
}