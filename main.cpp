#include "include/global.h"
#include "include/assembler.h"
#include "include/cpu.h"


int main(int n_args, char *p_args[])
{
   if (n_args == 2)
   {
      assembler(p_args[0], p_args[1]);
      processor(p_args[1]);
   }
   else
   {
      const char asmfile_path[] = "../examples/sum";
      const char binfile_path[] = "../binary";
   
      assembler(asmfile_path, binfile_path);
      processor(binfile_path);
   }
   
   return 0;
}