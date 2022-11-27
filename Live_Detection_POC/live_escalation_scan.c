#include <stdint.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h> 
#include <sys/stat.h>
#include <errno.h>

int main(void)
{
   printf("\n\n[SCAN] Beginning scan for unexpected root escalations...\n\n");
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
         fflush(stdout);
         fflush(fp);
         execl("detect_root_escalation", "detect_root_escalation", "root) bash", "spy_output.txt", NULL);
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
  return 0;
}
