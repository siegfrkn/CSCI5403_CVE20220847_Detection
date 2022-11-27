include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>

int main(void)
{
   char *my_args[5];
   pid_t pid_a, pid_b;

   my_args[0] = "detect_root_escalation";
   my_args[1] = "root) bash";
   my_args[2] = "spy_output.txt";
   my_args[3] = NULL;

   int status;
   /* start the sysdig scanning */
   FILE *fp = NULL;
   fp = fopen("spy_output.txt", "w+");

   switch ((pid_a = fork()))
   {
      case -1:
         /* Fork() has failed */
         perror ("fork");
         break;
        
      case 0:
         /* This is processed by the child */
         printf("\n\nWelcome to the proof of concept for dirtypipe live detection.\n");
         printf("Beginning scan for unexpected root escalations...\n\n");
         fflush(stdout);
         fflush(fp);
         execv("detect_root_escalation", my_args);
         printf("Uh oh! If this prints, execv() must have failed\n");
         exit(EXIT_FAILURE);
         break;
        
      default:
         switch ((pid_b = fork()))
         {
            case -1:
               /* Fork() has failed */
               perror ("fork");
               break;

            case 0:
               /* Child 2 */
               system("sudo stdbuf -oL sysdig -c spy_users | tee spy_output.txt");
               break;

            case 1:
               /* This is processed by the parent */
               signal(SIGCHLD, SIG_IGN);
               waitpid(pid_a, &status, WEXITED);
               break;
        }
        break;
   }
   return0;
}
