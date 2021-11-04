//
// Created by User on 04.11.2021.
//

#ifndef PROCESSOR_PARSER_H
#define PROCESSOR_PARSER_H

#include "global.h"
#include "lexer.h"

struct Command
{
   double key;
   double argument;
   bool   has_argument;
};

void parse(const LineLexemes *const lines_lexemes, const size_t lines_lexemes_number, Command **p_commands);

#endif //PROCESSOR_PARSER_H
