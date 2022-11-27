#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

int main()
{
   printf("\n\n[SCAN] Beginning live scan of /etc/passwd file\n\n");
   /* local variable definition */
   int ret;

   /* while loop execution */
   while(1) 
   {
      int printCount;
      ret = system("pwck -rq") / 255;
      if (ret == 2)
      {
         if (printCount < 1)
         {
            printf("\n\n[SCAN] CHANGE IN PASSWORD FILE DETECTED\n");
            printCount++;
         }
         sleep(10);
         system("pkill sysdig");
         system("pkill detect_root_esc");
         printf("\n\n[SCAN] Terminating sibling processes...\n");
         sleep(1);
         printf("[SCAN] Program exiting...\n");
         exit(0);
      }
      sleep(2);
   }
   return 0;
}
