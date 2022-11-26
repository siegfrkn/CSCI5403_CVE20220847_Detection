#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int main(void)
{
   char *my_args[5];
   pid_t pid;

   my_args[0] = "detect_root_escalation";
   my_args[1] = "root) bash";
   my_args[2] = "spy_output.txt";
   my_args[3] = NULL;

   /* start the sysdig scanning */
   FILE *fp = NULL;
   fp = fopen("spy_output.txt", "w+");
   system("sudo sysdig -c spy_users > spy_output.txt");


  switch ((pid = fork()))
   {
      case -1:
         /* Fork() has failed */
         perror ("fork");
         break;
      case 0:
         /* This is processed by the child */
         puts("Beginning scan for unexpected root escalations...");
         while(1)
         {
           execv ("detect_root_escalation", my_args);
         }
           puts("Uh oh! If this prints, execv() must have failed");
           exit(EXIT_FAILURE);
         break;
      default:
         /* This is processed by the parent */
         puts ("Welcome to the proof of concept for dirtypipe live detection.");
         wait(NULL);
         break;
   }

   fclose(fp);
   puts ("PERFORM ACTION HERE TO NOTIFY OR RESOLVE DETECTED ESCALATION");
   return 0;
}
