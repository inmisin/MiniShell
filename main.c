#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <stdio.h>

#include "ft_strcmp.h"

void execute_command(char **args)
{
    if (args[0] == NULL)
    {
        return;
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
    while (true)
    {
        read(0, &token, 1);
        if (token != '\n')
        {
            strSize++;
            char *temp = realloc(str, (strSize + 1) * sizeof(char));
            if (temp == NULL)
            {
                write(1, "Memory is not allocated!\n", 25);
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
                write(1, shellName, strlen(shellName));
                continue;
            }

            char *cmdlist[256];
            char *piece = strtok(str, " ");
            int commandCount = 0;
            while (piece != NULL)
            {
                /*
                write(1, piece, strlen(piece));
                write(1, "\n", 1);
                */
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
                    //write(1, "child\n", 6); // it works btw

                    if (ft_strcmp(cmdlist[0], "ls") == 0 || ft_strcmp(cmdlist[0], "cat") == 0  || ft_strcmp(cmdlist[0], "grep") == 0 )
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
                        chdir(cmdlist[1]);
                        char s[100];
                        printf("%s\n", getcwd(s, 100));
                    }
                    // shows directory
                    // char s[100];
                    // printf("%s\n", getcwd(s, 100));
                    // write(1, "parent\n", 7); // it works btw
                }
            }

            /*
            write(1, str, sizeof(char) * strSize);
            write(1, "\n", 1);
            free(str);
            str = NULL;
            strSize = 0;

            */
            free(str);
            str = NULL;
            strSize = 0;
            write(1, shellName, strlen(shellName));
        }
    }

    return 0;
}