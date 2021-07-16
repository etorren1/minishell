/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorren <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 17:42:01 by etorren           #+#    #+#             */
/*   Updated: 2021/05/22 22:31:48 by ruslan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include "get_next_line.h"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

typedef struct s_node
{
	void			*content;
	struct s_node	*next;
	struct s_node	*prev;
}				t_node;

int				ft_nodesize(t_node *node);
void			ft_nodeiter(t_node *node, void (*f)(void *));
void			ft_nodeadd_front(t_node **node, t_node *new);
void			ft_nodeadd_back(t_node **node, t_node *new);
void			ft_nodedelone(t_node *node, void (*del)(void *));
void			ft_nodeclear(t_node **node, void (*del)(void *));
t_node			*ft_nodemap(t_node *node, void *(*f)(void *),
					 void (*del)(void *));
t_node			*ft_nodenew(void *content);
t_node			*ft_nodelast(t_node *node);
t_node			*ft_nodefirst(t_node *node);
int				ft_lstsize(t_list *lst);
void			ft_lstiter(t_list *lst, void (*f)(void *));
void			ft_lstadd_front(t_list **lst, t_list *new);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstclear(t_list **lst, void (*del)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
					 void (*del)(void *));
t_list			*ft_lstnew(void *content);
t_list			*ft_lstlast(t_list *lst);
int				ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
int				ft_putstr_fd(char *s, int fd);
int				ft_putchar_fd(char c, int fd);
int				ft_atoi(const char *str);
void			ft_bzero(void *dest, size_t n);
char			*ft_realloc(char *str, size_t size);
void			*ft_calloc(size_t count, size_t size);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memccpy(void *dest, const void *src, int c, size_t n);
void			*ft_memchr(const void *arr, int c, size_t n);
int				ft_memcmp(const void *arr1, const void *arr2, size_t n);
void			*ft_memset(void *dest, int c, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);
int				ft_isprint(int c);
int				ft_isdigit(int c);
int				ft_isascii(int c);
int				ft_isalpha(int c);
int				ft_isalnum(int c);
int				ft_tolower(int ch);
int				ft_toupper(int ch);
int				ft_numsize(int num);
char			*ft_strchr(const char *str, int ch);
size_t			ft_strlen(const char *str);
char			*ft_strdup(const char *s1);
char			*ft_strjoin(char const *s1, char const *s2);
size_t			ft_strlcat(char *dest, const char *src, size_t dstsize);
size_t			ft_strlcpy(char *dest, const char *src, size_t dstsize);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strncmp(const char *str1, const char *str2, size_t n);
char			*ft_strnstr(const char *haystack,
					 const char *needle, size_t len);
char			*ft_strrchr(const char *str, int ch);
char			*ft_itoa(int val);
char			**ft_split(char const *s, char c);
char			*ft_strtrim(char *s1, char const *set);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strcpy(char *dest, const char *src);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strecmp(const char *s1, const char *s2);
char			*ft_strrev(char *str);
int				ft_samechar(char a, char b);
char			*ft_itoa_base(int val, int base);
void			ft_qsort_d(int *arr, int beg, int end);
void			ft_qsort_c(char *arr, int beg, int end);
void			ft_qsort_s(char **arr, int beg, int end);
void			ft_qsort_f(float *arr, int beg, int end);
int				ft_arrsize(char **arr);
void			ft_arrfree(char **arr);
char			**ft_arrcpy(char **dest, char **arr);
char			**ft_arrdel_str(char **arr, int pos);
char			**ft_arradd_str(char **arr, char *str, int pos);
char			**ft_arradd_str_mod(char **arr, char *freeable_str, int pos);
char			**ft_arradd_str_back(char **arr, char *str);
int				ft_isspace(int c);

#endif
