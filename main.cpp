
#include "include/global.h"
#include "cpu/stack/include/stack.h"
#include "include/lexer.h"
#include "include/parser.h"


int main()
{
   Stack stack = {};
   
   stack_init(&stack, 0);
   
   const char text[30] = "PUSH[10]\n"
                         "POP    [rax] \n"
                         "";
   
   LineLexemes *lines_lexemes = nullptr;
   Command       *commands         = nullptr;
   const size_t lines_lexemes_number = lexer(text, 30, &lines_lexemes);
   
   printf("%s %s\n", lines_lexemes[0].command_name, lines_lexemes[0].argument_string);
   printf("%s %s\n", lines_lexemes[1].command_name, lines_lexemes[1].argument_string);
   printf("%s %s\n", lines_lexemes[2].command_name, lines_lexemes[2].argument_string);
   
   parse(lines_lexemes, lines_lexemes_number, &commands);
   
   printf("%lf %lf\n", commands[0].key, commands[0].argument);
   printf("%lf %lf\n", commands[1].key, commands[1].argument);
   printf("%lf %lf\n", commands[2].key, commands[2].argument);
   
   
   return 0;
}
