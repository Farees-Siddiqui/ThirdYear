//==============================================================================
//C Code for fork() creation test
//==============================================================================

// we are including stdio.h for input/output functions such as printf() 
#include <stdio.h>
// lets us define exit() and exit codes
#include <stdlib.h>
// we are including unistd.h for the posix api. lets us ues functions such as fork() and waitpid()
#include <unistd.h>
// we are including sys/types.h so we can use the pid_t type
#include <sys/types.h>

#define NFORKS 100000

/*
  Timing: CPU Time => 1.801s + 13.095s = 14.896s
          Real Time => 15.625s
*/

// This function does nothing. It is used to waste time in the child process to test the fork() function. It initializes an integer to 0 and then does nothing.
void do_nothing() {
  int i;
  i= 0;
}

// main function used to run the program
int main(int argc, char *argv[]) {
  int pid, j, status;
  pid_t processID;

  // the for loop creates NFORKS child processes and then waits for them to finish
  for (j=0; j<NFORKS; j++) {
    // if the fork function returns a negative number, then the fork failed and an error message is printed. The program then exits.
    if ((processID = fork()) < 0 ) {
      printf ("fork failed with error code= %d\n", processID);
      exit(0);
    }
    // if the fork function returns 0, then the process is the child process. The do_nothing() function is called and then the child process exits.
    else if (processID == 0) {
      do_nothing();
      exit(0);
    }
    // if the fork function returns a positive number, then the process is the parent process. The parent process waits for the child process to finish.
    else {
      waitpid(processID, &status, 0);
    }
  }
}
