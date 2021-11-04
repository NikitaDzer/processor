//
// Created by User on 03.11.2021.
//

#ifndef PROCESSOR_LEXER_H
#define PROCESSOR_LEXER_H

#include "global.h"

struct LineLexemes
{
   char  command_name[64];
   char *argument_string;
};

size_t lexer(const char *const source, const size_t file_size, LineLexemes **p_lines_lexemes);

#endif //PROCESSOR_LEXER_H
