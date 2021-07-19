#include "../includes/readterm.h"

static int	*ft_arradd_int(int	*arr, int size, int	val)
{
	int *tmp;

	if (!arr)
	{
		arr = malloc(sizeof(int));
		arr[0] = val;
		return (arr);
	}
	else
	{
		tmp = malloc(sizeof(int) * (size));
		tmp[--size] = val;
		while (--size >= 0)
			tmp[size] = arr[size];
		free(arr);
		return (tmp);
	}
}

void    findstop(char *(*bufstr), t_rl *rl, t_hd *hd, int i)
{
    int end;
    int z;

    z = 0;
    end = i;
    while ((*bufstr)[end] && ft_isspace((*bufstr)[end]))
        end++;
    while ((*bufstr)[end] && !ft_isspace((*bufstr)[end]) && !ft_strchr(";|<>", (*bufstr)[end]))
        end++;
    while ((*bufstr)[end] && ft_isspace((*bufstr)[end]))
        end++;
    hd->tail = ft_substr((*bufstr), end, ft_strlen((*bufstr)) - end);
    hd->stoper = ft_substr((const char *)(*bufstr), i, end - i);
    hd->stoper = ft_strtrim(hd->stoper, " \t");
    if ((hd->stoper[0] == '\'' || hd->stoper [0] == '\"') 
        && (hd->stoper[ft_strlen(hd->stoper) - 1] == '\'' || hd->stoper [ft_strlen(hd->stoper) - 1] == '\"'))
    {
        hd->stoper = ft_strtrim(hd->stoper, "\'\"");
        rl->mode = ft_arradd_int(rl->mode, ++z, 1);
    }
    else
        rl->mode = ft_arradd_int(rl->mode, ++z, 0);
}

static void    readtermhd(char *(*bufstr), t_rl *rl, t_hd *hd, int *i)
{
    while (ft_strcmp(rl->command_line, hd->stoper) && ft_strcmp(rl->buf, "\3")
		&& (ft_strcmp(rl->buf, "\4") || rl->command_line[0] != 0))
    {
        rl->plen = 2;
        rl->cursor_pos = rl->plen;
        rl->count_symb = rl->plen;
        write (1, "> ", rl->plen);
        tputs(tgetstr("sc", 0), 1, ft_putint);
        clear_buf(rl->command_line, rl->len);
        clear_buf(rl->buf, BUF_SIZE);
        casecore(rl, &rl->histnode);
        if (ft_strcmp(rl->command_line, hd->stoper))
        {
            (*bufstr) = ft_strjoin((*bufstr), rl->command_line);
            (*bufstr) = ft_strjoin((*bufstr), "\n");
            *i += ft_strlen(rl->command_line) + 1;
        }
    }
}

static void addendhd(char *(*bufstr), t_hd *hd)
{
    char *tmp;

    tmp = malloc(2);
    tmp[0] = -1;
    tmp[1] = 0;
    (*bufstr) = ft_strjoin((*bufstr), tmp);
    (*bufstr) = ft_strjoin((*bufstr), hd->tail);
    free(tmp);
    free(hd->tail);
    free(hd->stoper);
    free(hd);
}

char	*readheredoc(t_rl *rl)
{
	int		i;
    char    (*bufstr);
    t_hd    *hd;

	i = 1;
	bufstr = ft_strdup(rl->command_line);
	while (bufstr[i])
	{
		if (bufstr[i] == '<' && bufstr[i - 1] == '<')
		{
            hd = malloc(sizeof(t_hd));
			findstop(&bufstr, rl, hd, ++i);
			bufstr[i] = 0;
			clear_buf(rl->command_line, rl->len);			
			readtermhd(&bufstr, rl, hd, &i);
            addendhd(&bufstr, hd);
		}
		if (bufstr[i] == '*' && bufstr[i + 1] == '*')
		{
			ft_strcpy(&bufstr[i], &bufstr[i + 1]);
			i--;
		}
		i++;
	}
	return (bufstr);
}
