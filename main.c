#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <stdio.h>

#include "ft/ft_strcmp.h"
#include "ft/ft_printf.h"

void command_cd(char *arg)
{
    if (arg != NULL)
    {
        chdir(arg);
        char s[100];
        ft_printf("%s\n", getcwd(s, 100));
    }
}

void command_echo(char **args, int count)
{
    if (ft_strcmp(args[1], "-n") == 0)
    {
        for (int i = 2; i < count; i++)
        {
            ft_printf("%s ", args[i]);
        }
    }
    else
    {
        for (int i = 1; i < count; i++)
        {
            ft_printf("%s ", args[i]);
        }
        ft_putchar('\n');
    }
}

int main()
{
    pid_t pid;
    char *shellName = "\033[0;35mft_shell> \033[0m";
    char token = 0;
    char *str = 0;
    int strSize = 0;
    write(1, shellName, strlen(shellName));
    while (1)
    {
        read(0, &token, 1);
        if (token != '\n')
        {
            strSize++;
            char *temp = realloc(str, (strSize + 1) * sizeof(char));
            if (temp == NULL)
            {
                ft_printf("Memory is not allocated!\n");
                free(str);
                return 0;
            }

            str = temp;
            str[strSize - 1] = token;
            str[strSize] = '\0'; // strcmp için
        }
        else
        {
            if (str == NULL)
            {
                ft_printf("%s", shellName);
                continue;
            }

            char *cmdlist[256];
            char *piece = strtok(str, " ");
            int commandCount = 0;
            while (piece != NULL)
            {
                cmdlist[commandCount] = piece;
                commandCount++;
                piece = strtok(NULL, " ");
            }
            cmdlist[commandCount] = NULL;

            if (strcmp(str, "exit") == 0)
            {
                free(str);
                break;
            }
            else
            {
                pid = fork();
                if (pid < 0)
                {
                    write(1, "frok failed!", 12);
                    free(str);
                    return 1;
                }
                else if (pid == 0)
                {
                    // write(1, "child\n", 6); // it works btw

                    if (ft_strcmp(cmdlist[0], "ls") == 0 || ft_strcmp(cmdlist[0], "cat") == 0 || ft_strcmp(cmdlist[0], "grep") == 0)
                    {
                        execvp(cmdlist[0], cmdlist);
                    }

                    // güvenli kapanış
                    free(str);
                    exit(127);
                }
                else
                {
                    // child bitmesi bekleniyor
                    wait(NULL);

                    if (ft_strcmp(cmdlist[0], "cd") == 0)
                    {
                        command_cd(cmdlist[1]);
                    }
                    else if (ft_strcmp(cmdlist[0], "echo") == 0)
                    {
                        command_echo(cmdlist, commandCount);
                    }
                }
            }

            free(str);
            str = NULL;
            strSize = 0;
            write(1, shellName, strlen(shellName));
        }
    }

    return 0;
}