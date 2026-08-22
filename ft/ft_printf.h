#ifndef FT_PRINTF_H
#define FT_PRINTF_H

#include <unistd.h>
#include <stdarg.h>

char ft_getchar(void);
int ft_putchar(char c);
int ft_putnbr(int n);
int ft_putstr(char *str);
int ft_printf(const char *format, ...);

#endif
