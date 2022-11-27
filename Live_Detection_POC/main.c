/*
 * main.c
 * This is the primary file which executes two different scanning processes which aim
 * to detect the dirtypipe cache manipulation in real time and alert the user. This
 * program is to be run from the admin account on a target machine to scan for exploitations
 * across all machine users.
 *
 * Compile this file with
 * gcc main.c -o main
 *
 *
 * Author Katrina Siegfried, 2022
 *
 */

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
   
   /*
    * This loop will fork() multiple children processes from a single parent process. The
    * number of children processes to be created is defined above.
    */
   for(j = 0;j< numChildren;j++)
   {
      sleep(1);
      pid = fork();
      switch(pid)
      {
         /*
          * If an error has occured, return with an error and break.
          */
         case -1:
            perror("Fork Error");
            break;
         /*
          * If fork() returns 0 then this is the child process. If this is the first child
          * it will execute the code in the first if clause, otherwise because only two
          * children have been defined the second child will execute the code in the else
          * clause.
          */
         case 0:
            /*
             * The first child process calls the execution of the check_passwd_file program
             * which calls the pwck function in an infinite loop to detect changes to the
             * /etc/passwd cached file. If a change is detected, the user is notified and
             * the scan exits.
             */
            if (j == 0)
            {
               execl("check_passwd_file", "check_passwd_file", NULL);
               exit(0);
               break;
            }
            /*
             *
             */
            else
            {
               execl("live_escalation_scan", "live_escalation_scan", NULL);
               exit(0);
               break;
            }
         /*
          * This is the code exeuc
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
