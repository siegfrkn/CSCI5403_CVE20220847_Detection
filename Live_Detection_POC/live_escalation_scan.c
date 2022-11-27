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

  printf("Welcome to the proof of concept for dirtypipe live detection.\n");
  int status;
  /* start the sysdig scanning */
  FILE *fp = NULL;
  fp = fopen("spy_output.txt", "w+");

  switch ((pid = fork()))
  {
   case -1:
      /* Fork() has failed */
      break;
    case 0:
      /* This is processed by the child */
      printf("Beginning scan for unexpected root escalations...\n");
      fflush(stdout);
      fflush(fp);
      execv("detect_root_escalation", my_args);
      printf("Uh oh! If this prints, execv() must have failed\n");
      exit(EXIT_FAILURE);
     break;

    default:
      /* This is processed by the parent */
      signal(SIGCHLD, SIG_IGN);
      system("sudo stdbuf -oL sysdig -c spy_users | tee spy_output.txt");
      waitpid(-1, &status, WEXITED);
      printf("FINISHED CHILD\n");
      break;
   }


  fclose(fp);
  return 0;
}

