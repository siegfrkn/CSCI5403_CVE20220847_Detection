/*
 * live_escalation_scan.c
 * This is a secondary file which forks and runs both the system command for sysdig and
 * a subprocess called detect_root_escalation which continually checks the spy_output.txt
 * file that the sysdig command is dumpting to in search of a new root shell being spawned.
 * If a new root shell is spawned, this is indicative of an escalation of privledges from
 * a read-only user, assuming the admin who is running this process, did not create the
 * new shell. If an excalation to root is detected than the admin user who executed the main
 * program will be alerted, and the sibling processes will be terminated.
 *
 * Compile this file with
 * gcc live_escalation_scan.c -o live_escalation_scan
 *
 *
 * Author Katrina Siegfried, 2022
 *
 */

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

   /*
    * Define arguments for the child process for the system call to sysdig
    */
   my_args[0] = "detect_root_escalation"; 
   my_args[1] = "root) bash";
   my_args[2] = "spy_output.txt";
   my_args[3] = NULL;

   /*
    * Open the file to write out the output from the sysdig command for analysis.
    */
   int status;
   FILE *fp = NULL;
   fp = fopen("spy_output.txt", "w+");

   /*
    * Run the fork() call to create a child process to run the sysdig command, while the
    * parent process runs the scanning of the output for root escalation.
    */
   switch ((pid_a = fork()))
   {
      /*
       * If an error has occured, return with an error and break.
       */
      case -1:
         perror ("fork");
         break;
      /*
       * If fork() returns 0 then this is the child process. This case will flush the buffer for the file
       * that has been opened and for stdout. It then executes the subprogram detect_root_escalation which
       * runs the detection on the file that contains the output from the sysdig call.
       */
      case 0:
         fflush(stdout);
         fflush(fp);
         execl("detect_root_escalation", "detect_root_escalation", "root) bash", "spy_output.txt", NULL);
         exit(EXIT_FAILURE);
         break;
      /*
       * This is the parent process which runs the sysdig command. The stdbuf flag is passed as a part of
       * the command so that the sysdig command will buffer out line by line instead of by block. The command
       * then dumps into the text file spy_output.txt. It does this by running the fork() command to spawn
       * yet another child process.
       */
      default:
         switch ((pid_b = fork()))
         {
            /*
             * If an error has occured, return with an error and break.
             */
            case -1:
               perror ("fork");
               break;
            /*
             * If fork() returns 0 then this is the child process. This case will execute the sysdig command
             * with a line-by-line buffering and output the file to the spy_output.txt file.
             */
            case 0:
               system("sudo stdbuf -oL sysdig -c spy_users | tee spy_output.txt");
               break;
            /*
             * This is the parent process which waits for the sysdig command to terminate.
             */
            case 1:
            signal(SIGCHLD, SIG_IGN);
            waitpid(pid_a, &status, WEXITED);
            break;
         }
         break;
   } 
  return 0;
}
