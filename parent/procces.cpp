#include "procces.h"

#include <sys/wait.h>
#include <unistd.h>

#include <string>

int Procces::exec_prog(const char **argv)
{
    pid_t my_pid;

    if (0 == (my_pid = fork())) 
    {
            if (-1 == execve(argv[0], (char **)argv , NULL)) 
            {
                    perror("child process execve failed [%m]");
                    return -1;
            }
    }
    return my_pid;
}

void Procces::restart_prog(const char **argv)
{
    pid_t my_pid = exec_prog(argv);
    int status;
    while(true)
    {
        if (waitpid(my_pid, &status, WUNTRACED))
            my_pid = exec_prog(argv);
    }
}
