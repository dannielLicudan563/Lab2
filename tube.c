#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char* argv[])
{
    pid_t PID;
    int fds[2];
    int child1;
    int child2;
    int status1;
    int status2;

    pipe(fds);

    PID = fork();

    if(PID == 0)
    {
        //Child1
        char** args = malloc(sizeof(&argv));
        args = argv+1;
        dup2(fds[1], STDOUT_FILENO);
        close(fds[0]);
        execve(argv[1], args, NULL);
    }

    PID = fork();

    if(PID == 0)
    {
        //Child2
        char** args = malloc(sizeof(&argv));
        args = argv+2;
        dup2(fds[0], STDIN_FILENO);
        close(fds[1]);
        execve(argv[2], args, NULL);
    }

    close(fds[0]);
    close(fds[1]);
    child1 = waitpid(-1, &status1, WUNTRACED);
    child2 = waitpid(-1, &status2, WUNTRACED);
    fprintf(stderr,"Child1 PID:%d\n", child1);
    fprintf(stderr,"Child2 PID:%d\n", child2);
    fprintf(stderr,"Child1 Status:%d\n",status1);
    fprintf(stderr,"Child2 Status:%d\n",status2);



    return 0;
}
