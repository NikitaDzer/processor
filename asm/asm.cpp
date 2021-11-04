//
// Created by User on 04.11.2021.
//

#include "../include/asm.h"
#include "../include/global.h"

static size_t get_file_size(FILE* const file) {
   long currentIndex = ftell(file);
   size_t file_size = 0;
   
   fseek(file, 0, SEEK_END);
   file_size = ftell(file);
   fseek(file, currentIndex, SEEK_SET);
   
   return file_size;
}

void assembly(const char *const inputFile_path)
{
   dead(inputFile_path);
   
   FILE *const inputFile  = fopen(inputFile_path, "r");
   const size_t file_size = get_file_size(inputFile);
   
   
}