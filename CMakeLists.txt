cmake_minimum_required(VERSION 3.20)
project(processor)

set(CMAKE_CXX_STANDARD 14)

add_executable(processor main.cpp asm/lexer.cpp include/lexer.h cpu/stack/include/stack.h cpu/stack/src/dump.cpp cpu/stack/include/dump.h cpu/stack/include/config.h cpu/stack/src/stack.cpp cpu/stack/include/stack.h cpu/stack/src/hash.cpp cpu/stack/include/hash.h cpu/stack/src/protect.cpp cpu/stack/include/protect.h include/global.h asm/parser.cpp include/parser.h asm/asm.cpp include/asm.h)

