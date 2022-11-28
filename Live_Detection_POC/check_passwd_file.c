/*
 * check_passwd_file.c
 * This is a secondary file which executes the pwck command in a loop to continually
 * monitor the /etc/passwd file to detect any changes to user manipulatons. This file is
 * executed from the main program. If a change in the file is detected than the admin
 * user who executed the main program will be alerted, and the sibling processes will
 * be terminated.
 *
 * Compile this file with
 * gcc check_passwd_file.c -o check_passwd_file
 *
 *
 * Author Katrina Siegfried, 2022
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

int main()
{
   printf("\n\n[SCAN] Beginning live scan of /etc/passwd file\n\n");
   int ret;

   /*
    * This while loop executes infinitely every 2 second if a change to the /etc/passwd file
    * is detected, in which case the process alerts the user, terminates the sibling
    * processes, and exits.
    */
   while(1) 
   {
      int printCount;
      ret = system("pwck -rq") / 255;
      
      /*
       * The system call to pwck will return with 2 if a change in the /etc/passwd file
       * is detected.
       */
      if (ret == 2)
      {
         /*
          * Only print the detection message one time.
          */
         if (printCount < 1)
         {
            printf("\n\n[SCAN] CHANGE IN PASSWORD FILE DETECTED\n");
            printCount++;
         }
         
         /*
          * Wait long enough that if this detection is made immediately that all of the child
          * processes have properly initialized. This is a TODO item for the future to use shared memory to
          * properly synchronize the processes.
          */
         sleep(10);
         
         /*
          * Terminate the sibling processes before exiting.
          */
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
