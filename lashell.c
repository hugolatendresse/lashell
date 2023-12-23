#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 1024
#define DELIMITER " "

int lsh_cd(char **args);
int lsh_help(char **args);
int lsh_exit(char **args);

char *builtin_str[] = {
    "cd",
    "help",
    "exit"};

int (*builtin_func[])(char **) = {
    &lsh_cd,
    &lsh_help,
    &lsh_exit};

int lsh_num_builtins()
{
    return sizeof(builtin_str) / sizeof(char *);
}

// Implementations of built-in functions
int lsh_cd(char **args)
{
    if (args[1] == NULL)
    {
        fprintf(stderr, "lsh: expected argument to \"cd\"\n");
    }
    else
    {
        if (chdir(args[1]) != 0)
        {
            perror("lsh");
        }
    }
    return 1;
}

int lsh_help(char **args)
{
    printf("Type program names and arguments, and hit enter.\n");
    printf("The following are built in:\n");

    for (int i = 0; i < lsh_num_builtins(); i++)
    {
        printf("  %s\n", builtin_str[i]);
    }

    printf("Use the man command for information on other programs.\n");
    return 1;
}

int lsh_exit(char **args)
{
    return 0;
}


void execute_command(char *command)
{
    int lsh_execute(char **args)
    {
        int i;

        if (args[0] == NULL)
        {
            // An empty command was entered.
            return 1;
        }

        for (i = 0; i < lsh_num_builtins(); i++)
        {
            if (strcmp(args[0], builtin_str[i]) == 0)
            {
                return (*builtin_func[i])(args);
            }
        }

        return lsh_launch(args);
    }
}

int main()
{
    char *line;
    char **args;
    int status;

    do
    {
        printf("> ");
        line = lsh_read_line();
        args = lsh_split_line(line);
        status = lsh_execute(args);

        free(line);
        free(args);
    } while (status);

    return EXIT_SUCCESS;
}

