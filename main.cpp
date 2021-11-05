
#include "include/global.h"
#include "include/assembler.h"
#include "include/cpu.h"


int main()
{
   const char asmfile_path[]  = "../examples/factorial";
   const char binfile_path[] = "../binary";
   
   assembly(asmfile_path, binfile_path);
   cpu(binfile_path);
   
   return 0;
}
