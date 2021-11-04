//
// Created by User on 04.11.2021.
//

#include "../include/assembler.h"
#include "../include/global.h"
#include "../include/lexer.h"
#include "../include/parser.h"
#include <ctime>

static CommandLexemes *commands_lexemes = nullptr;
static Command        *commands         = nullptr;
static size_t          commands_number  = 0;

static size_t get_file_size(FILE* const file)
{
   long initialPosition = ftell(file);
   size_t file_size = 0;
   
   fseek(file, 0, SEEK_END);
   file_size = ftell(file);
   fseek(file, initialPosition, SEEK_SET);
   
   return file_size;
}

static void free_mem()
{
   for (size_t i = 0; i < commands_number; i++)
   {
      free(commands_lexemes[i].argument_string);
   }
   
   free(commands_lexemes);
   free(commands);
}

static void assembler_log()
{
   FILE *assembler_logfile = fopen(assembler_logfile_path, "w");
   
   const time_t    seconds = time(nullptr);
   const tm *const date    = localtime(&seconds);
   
   fprintf(assembler_logfile,
           "Time: %d:%d:%d\n"
           "========================================\n",
           date->tm_hour, date->tm_min, date->tm_sec);
   
   for (size_t i = 0; i < commands_number; i++)
   {
      fprintf(assembler_logfile, "%-10s %s\n"
                                 "%-10lg %-10lg ram: %-lg register: %-lg\n"
                                 "----------------------------------------\n",
              commands_lexemes[i].command_name, commands_lexemes[i].argument_string,
              commands[i].key, commands[i].argument, commands[i].is_ram, commands[i].is_register);
   }
   
   fclose(assembler_logfile);
}

void assembly(const char *const inputFile_path, const char *const outputFile_path)
{
   dead(inputFile_path);
   
//   atexit(assembler_log);
   
   FILE *const inputFile  = fopen(inputFile_path, "r");
   const size_t inputFile_size = get_file_size(inputFile);
   
   char *const inputFile_content = (char *)calloc(inputFile_size, sizeof(char));
   
   fread(inputFile_content, sizeof(char), inputFile_size, inputFile);
   fclose(inputFile);
   
   commands_number = lex(inputFile_content, inputFile_size, &commands_lexemes);
   parse(commands_lexemes, commands_number, &commands);
   
   FILE *const outputFile = fopen(outputFile_path, "wb");
   
   fwrite(&commands_number, sizeof(size_t), 1, outputFile);
   for (size_t i = 0; i < commands_number; i++)
   {
      fwrite(commands + i, sizeof(Command), 1, outputFile);
   }
   
   assembler_log();
   
   free(inputFile_content);
   free_mem();
   fclose(outputFile);
}