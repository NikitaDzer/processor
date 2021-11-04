//
// Created by User on 04.11.2021.
//

#ifndef PROCESSOR_PARSER_H
#define PROCESSOR_PARSER_H

#include "global.h"
#include "lexer.h"

void parse(const CommandLexemes *const commands_lexemes, const size_t commands_number, Command **p_commands);

#endif //PROCESSOR_PARSER_H
