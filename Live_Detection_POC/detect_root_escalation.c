/*
 * detect_root_escalation.c
 * This is the tertiary file which continually scans the output of the sysdig command
 * that is dumped into the spy_output.txt file. It is looking for a specific text pattern
 * indicative of a new root shell creation. Supposing that the admin who is running the
 * scan did not create that root shell, this indicates an escalation to root from a read-
 * only user. When this is detected the user is alerted, the sibling processes are
 * terminated, and the program exits.
 *
 * Compile this file with
 * gcc detect_root_escalation.c -o detect_root_escalation
 *
 *
 * Author Katrina Siegfried, 2022
 *
 */

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

      /*
       * Ensure the proper number of arguments are passed.
       */
      if (ac < 3)
      {
         fprintf(stderr, "A string pattern and a file name are required\n");
         exit(1);
      }

      /*
       * Open the spy_output.txt file with the output from the sysdig command, flush
       * the buffer to both that file and stdout. If unable to open, throw ane error.
       */
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

      /*
       * Read each line of the spy_output.txt file, and if the output matches the pattern
       * in the string passed to the program which indicates an escalation to root, then
       * alert the user, terminate sibling processes, and exit.
       */
      while (fgets(lineBuffer, BUFFER_LENGTH, fp))
      {
         fflush(stdout);
         fflush(fp);
         if(strstr(lineBuffer, av[1]))
         {
            printf("\n\n[SCAN] AN UNAUTHORIZED ROOT ESCALATION HAS BEEN DETECTED:\n%s\n", lineBuffer);
            fclose(fp);
            sleep(10);
            system("pkill sysdig");
            system("pkill check_passwd_fi");
            printf("\n[SCAN] Terminating sibling processes...\n");
            sleep(1);
            printf("[SCAN] Program exiting...\n");
            exit(0);      
         }
      }
      fclose(fp);
   }
   return 0;
}
