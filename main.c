#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int main()
{
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

            if(strcmp(str, "exit") == 0)
            {
                free(str);
                break;
            }

            write(1, str, sizeof(char) * strSize);
            write(1, "\n", 1);
            free(str);
            str = NULL;
            strSize = 0;
            write(1, shellName, strlen(shellName));
        }
        
    }

    
    return 0;
}