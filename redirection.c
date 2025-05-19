#include "minishell.h"

int redirect_input(const char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        perror("open input");
        return (-1);
    }
    if (dup2(fd, STDIN_FILENO) < 0)
    {
        perror("dup2 input");
        close(fd);
        return (-1);
    }
    close(fd);
    return (0);
}

int redirect_output(const char *filename, int append)
{
    int fd;
    
    if (append)
        fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
    else
        fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
    {
        perror("open output");
        return (-1);
    }
    if (dup2(fd, STDOUT_FILENO) < 0)
    {
        perror("dup2 output");
        close(fd);
        return (-1);
    }
    close(fd);
    return (0);
}

// int main(void)
// {
//     if (redirect_output("test_delete.txt", 1) == -1)
//         return (1);

//         printf("new Hello world\n");

//     // int i = 1; 
//     // while (i)
//     // {
//     //     printf("you put number %d\n", i);
//     //     scanf("%d", &i);
//     // }
    


//     // if (redirect_input("test_delete.txt") == -1)
//     //     return (1);

//     // char buffer[100];

//     // while (fgets(buffer, sizeof(buffer), stdin))
//     //     printf("Read line: %s", buffer);

//     return (0);
// }
