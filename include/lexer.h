//
// Created by User on 03.11.2021.
//

#ifndef PROCESSOR_LEXER_H
#define PROCESSOR_LEXER_H

#include "global.h"

struct CommandLexemes
{
   char  command_name[COMMAND_NAME_MAX_SIZE];
   char *argument_string;
};

size_t lex(const char *const source, const size_t file_size, CommandLexemes **p_commands_lexemes);

#endif //PROCESSOR_LEXER_H
