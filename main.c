#include "minishell.h"

int main(int argc, char **argv, char **envp)
{

    (void) argc ;
    (void) argv;
    setup_signals();
    ft_propt(envp);
    return 0;
}
