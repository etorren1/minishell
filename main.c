#include "libft.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <term.h>
#include <stdlib.h>
#include <termios.h>
#include <fcntl.h>
#define MINISHELL 15

int    ft_putint(int ch)
{
    write (1, &ch, 1);
    return (1);
}

void    ft_addchar(char **str, char ch, int i)
{
    char    *tail;
    int     j;

    j = 0;
    tail = malloc(ft_strlen(&(*str)[i - MINISHELL]) + 1);
    ft_strcpy(tail, &(*str)[i - MINISHELL]);
    (*str)[(i++) - MINISHELL] = ch;
    while (tail[j])
        (*str)[(i++) - MINISHELL] = tail[j++];
    free(tail);
}

void    ft_delchar(char **str, int i)
{
    char    *tail;
    int     j;

    j = 0;
    tail = malloc(ft_strlen(&(*str)[i - MINISHELL]) + 1);
    ft_strcpy(tail, &(*str)[(i--) - MINISHELL]);
    while (tail[j])
        (*str)[(i++) - MINISHELL] = tail[j++];
    free(tail);
}

int     main(int argc, char **argv, char **envp)
{
    struct  termios term;
    char    *str;
    int     i;
    int     count_symb;
    int     cursor_pos;
    int     fd;
    char    c;
    char    *command_line;

    tcgetattr(0, &term);
    term.c_lflag &= ~(ECHO);
    term.c_lflag &= ~(ICANON);
//    term.c_cc[VMIN] = 1;
//    term.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &term);

    tgetent(0, "xterm-256color");
    fd = open(".minishell_history", O_RDWR | O_CREAT, 0777);
    while ((i = get_next_line(fd, &str)) > 0)
        free(str);
    str = (char *)malloc(sizeof(*str) * 100);
    while (ft_strcmp(str, "\4"))
    {
        cursor_pos = MINISHELL;
        count_symb = MINISHELL;
        write (1, "minishell-0.1$ ", MINISHELL);
        tputs(save_cursor, 1, ft_putint);
        command_line = (char *)malloc(sizeof(*str) * 1024);
        str[0] = 0;
        while (ft_strcmp(str, "\n") && ft_strcmp(str, "\4"))
        {
            if (count_symb < cursor_pos)
                count_symb = cursor_pos;
            i = read(0, str, 100);
            str[i] = 0;
            // key_up for output previous command 
            if (!ft_strcmp(str, "\e[A"))
            {
                tputs(restore_cursor, 1, ft_putint);
                tputs(tgetstr("ce", 0), 1, ft_putint);
                write (1, "previous command", 16);
            }
            // key_down for output next command
            else if (!ft_strcmp(str, "\e[B"))
            {
                tputs(restore_cursor, 1, ft_putint);
                tputs(tgetstr("ce", 0), 1, ft_putint);
                write (1, "next command", 12);
            }
            // key_backspace for delite character
            else if (!ft_strcmp(str, "\177"))
            {
                if (cursor_pos > MINISHELL)
                {
                    ft_delchar(&command_line, cursor_pos);
                    cursor_pos--;
                    count_symb--;
                    tputs(cursor_left, 1, ft_putint);
                    tputs(tgetstr("dc", 0), 1, ft_putint);
                }
            }
            // key_left
            else if (!ft_strcmp(str, "\e[D"))
            {
                if (cursor_pos > MINISHELL)
                {
                    cursor_pos--;
                    tputs(cursor_left, 1, ft_putint);
                }
            }
            // key_right
            else if (!ft_strcmp(str, "\e[C"))
            {
                if (count_symb > cursor_pos)
                {
                    cursor_pos++;
                    tputs(cursor_right, 1, ft_putint);
                }
            }
            // add newline in command string
            else if (str[0] == '\n')
            {
                command_line[count_symb - MINISHELL] = str[0];
                command_line[1 + count_symb - MINISHELL] = '\0';
                write (1, str, i);
            }
            // command line edit
            else if (cursor_pos < count_symb)
            {
                ft_addchar(&command_line, str[0], cursor_pos);
                tputs(tgetstr("im", 0), 1, ft_putint);
                cursor_pos += write (1, str, 1 );
                count_symb++;
                tputs(tgetstr("ei", 0), 1, ft_putint);     
            }
            // standart output characters from user
            else
            {
                command_line[cursor_pos - MINISHELL] = str[0];
                cursor_pos += write (1, str, i);
                command_line[cursor_pos - MINISHELL] = '\0';
            }
        }
        write(fd, command_line, ft_strlen(command_line));
        free(command_line);
    }
    write (1, "\n", 1);
    close (fd);
    return (0);
}
