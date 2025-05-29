#include "minishell.h"

int main(int argc , char **argv , char **envp)
{
    int  g_exit_status;
    (void)argc;
    (void)argv;
    pid_t pid ;
    char *s[] = {"./a.out",NULL};
    pid = fork();
    if (pid == 0)
    {
        execve("/home/saamouss/Desktop/minminimini", s , envp);
        perror("execve failed");
        exit(127);
    }
    else
    {
        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status))
            g_exit_status = WEXITSTATUS(status);
        else
            g_exit_status = 1;
    printf("%d\n", g_exit_status);
    }
}