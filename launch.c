#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char* argv[])
{
   pid_t PID;
   int child;
   int status;


   PID = fork();
   if(PID == 0)
    {
        char** args = malloc(sizeof(&argv));
        args = argv+1;
        execve(argv[1], args, NULL);
    }
    else if(PID >= 1)
    {
        //Parent
        child = waitpid(0, &status, WUNTRACED);
        fprintf(stderr,"%d\n", child);
        fprintf(stderr,"%d\n",status);
    }
    else
    {
        printf("Error");
    }

    return 0;
}
