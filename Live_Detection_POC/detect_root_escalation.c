#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define BUFFER_LENGTH 511

int main( int ac, char* av[] )
{
   while(1)
   {
      char lineBuffer[BUFFER_LENGTH+1];
      FILE *fp = NULL;
      int count = 0;

      if (ac < 3)
      {
         fprintf(stderr, "A string pattern and a file name are required\n");
         exit(1);
      }

      fp = fopen(av[2], "r");
      fflush(fp);
      int fd;
      fd = fileno(fp);
      fsync(fd);
      fflush(stdout);
      if(!fp)
      {
         fprintf(stderr, "Error - unable to open %s\n", av[2]);
         exit(2);
      }

      while (fgets(lineBuffer, BUFFER_LENGTH, fp))
      {
         fflush(stdout);
         fflush(fp);
         if(strstr(lineBuffer, av[1]))
         {
            printf("\nAN UNAUTHORIZED ROOT ESCALATION HAS BEEN DETECTED:\n%s\n", lineBuffer);
            fclose(fp);

            printf("TERMINATING PROCESSES...\n");
            int total_length = 512;
            char line[total_length];
            FILE * command = popen("pidof sysdig","r");
            fgets(line,total_length,command);
            pid_t pid = strtoul(line,NULL,10);
            pclose(command);
            printf("PID OF SYSDIG: %d\n", pid);
            kill(pid, SIGKILL);
            sleep(1);
            printf("Program exiting...\n");
            exit(0);
         }
      }
          fclose(fp);
   }
   return 0;
}
               
