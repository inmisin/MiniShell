#include "ft_printf.h"
#include <unistd.h>

char ft_getchar(void)
{
    char c = 0;

    read(0, &c, 1);

    return c;
}

int ft_putchar(char c)
{
    return write(1, &c, 1);
}

int ft_putnbr(int n)
{
    int len = 0;
    if (n < 0)
    {
        ft_putchar(*"-");
        n = -n;
        len++;
    }
    if(n >= 10)
    {
        ft_putnbr(n/10);
        ft_putnbr(n%10);
        len++;
    }
    else
    {
        ft_putchar(n+'0');
        len++;
    } 
    
    return len;
    
}

int ft_putstr(char *str)
{
    int len = 0;
    if(!str)
    {
        str = "(null)";
    }
    while(*str != '\0')
    {
        ft_putchar(*str);
        str++;
        len++;
    }
    return len;
}