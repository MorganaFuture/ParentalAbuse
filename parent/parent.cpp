#include "parent.h"

#include <sys/wait.h>
#include <unistd.h>

#include <string>

namespace Parent
{
    int exec_prog(const char **argv)
    {
        pid_t pid = 0;

        if (0 == (pid = fork())) 
        {
                if (-1 == execve(argv[0], (char **)argv , NULL)) 
                {
                        perror("child process execve failed [%m]");
                        return -1;
                }
        }
        return pid;
    }

    void run_process(const char **argv)
    {
        pid_t pid = exec_prog(argv);
        int status = 0;
        while(true)
        {
            if (waitpid(pid, &status, WUNTRACED))
                pid = exec_prog(argv);
        }
    }
}   // Parent
