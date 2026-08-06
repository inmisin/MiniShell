#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

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
            char *cmdlist[256];
            char *piece = strtok(str, " ");
            int i = 0;
            while (piece != NULL)
            {
                /*
                write(1, piece, strlen(piece));
                write(1, "\n", 1);
                */
                cmdlist[i] = piece;
                i++;
                piece = strtok(NULL, " ");
            }
            cmdlist[i+1] = NULL;

            if (str == NULL)
            {
                write(1, shellName, strlen(shellName));
                continue;
            }

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
                    write(1, "Hello\n", 7);

                    char *test[] = {"ls", NULL};
                    execvp(cmdlist[0], cmdlist);

                    // güvenli kapanış
                    exit(127);
                }
                else
                {
                    // child bitmesi bekleniyor
                    wait(NULL);
                    // write(1, "World!\n", 7);
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