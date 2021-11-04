
#include "include/global.h"
#include "include/assembler.h"
#include "include/cpu.h"


int main()
{
   const char inputFile_path[]  = "../asscode";
   const char outputFile_path[] = "../binary";
   
   assembly(inputFile_path, outputFile_path);
   cpu(outputFile_path);
   
   return 0;
}
