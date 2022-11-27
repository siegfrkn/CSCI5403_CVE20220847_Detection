#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
   printf("\n\n[SCAN] Welcome to the proof of concept for dirtypipe live detection.\n\n");
   int i, pid, status, wpid;
   int j = 0;
   int numChildren = 2;
   for(j = 0;j< numChildren;j++)
   {
      sleep(1);
      pid = fork();
      switch(pid)
      {
         case -1:
            /* An error has occurred */
            perror("Fork Error");
            break;
         case 0:
            if (j == 0)
            {
               /* This code is executed by the first parent */
               execl("check_passwd_file", "check_passwd_file", NULL);
               exit(0);
               break;
            }
            else
            {
               execl("live_escalation_scan", "live_escalation_scan", NULL);
               exit(0);
               break;
            }
         default:
            /* This code is executed by the parent process */
            if(j == (numChildren - 1))
            {
               while((wpid = wait(&status)) > 0);
               printf("[SCAN] Scan Complete.\n");
            }
      }
   }
}
