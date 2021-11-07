#include "include/global.h"
#include "include/assembler.h"
#include "include/cpu.h"


int main()
{
   const char asmfile_path[] = "../examples/cuda"; //! TODO: command args
   const char binfile_path[] = "../binary";
   
   assembler(asmfile_path, binfile_path);
   processor(binfile_path);
   
   return 0;
}