//
// Created by User on 04.11.2021.
//

#ifndef PROCESSOR_CPU_H
#define PROCESSOR_CPU_H

#include "global.h"

struct Command
{
   double key;
   double is_register;
   double is_ram;
   double argument;
};

void cpu(const char *const binaryFile_path);

#endif //PROCESSOR_CPU_H
