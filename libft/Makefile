# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile1                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: etorren <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/14 14:03:09 by etorren           #+#    #+#              #
#    Updated: 2020/11/18 16:32:19 by etorren          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
			  ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memcpy.c \
			  ft_memchr.c ft_memccpy.c ft_memcmp.c ft_memcpy.c ft_memmove.c \
			  ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
			  ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_strjoin.c \
			  ft_strlcat.c  ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c \
			  ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c \
			  ft_toupper.c ft_strcmp.c ft_itoa_base.c ft_samechar.c\
			  ft_strrev.c ft_numsize.c ft_strcpy.c ft_realloc.c ft_strecmp.c\
			  ft_qsort_c.c ft_qsort_d.c ft_qsort_f.c ft_qsort_s.c\
			  ft_arrcpy.c ft_arrsize.c ft_arrfree.c ft_arradd_str.c ft_arrdel_str.c\
			  get_next_line.c get_next_line_utils.c\
			  ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c \
			  ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c \
			  ft_nodeadd_back.c ft_nodeadd_front.c ft_nodeclear.c ft_nodedelone.c \
			  ft_nodeiter.c ft_nodelast.c ft_nodenew.c ft_nodesize.c ft_nodefirst.c\
			  ft_isspace.c ft_arradd_str_mod.c ft_arradd_str_back.c

FT_H		= libft.h

OBGS		= ${SRCS:.c=.o}

NAME		= libft.a

CC			= gcc
RM			= rm -f
FLAGS		= -Wall -Wextra -Werror

%.o:		%.c
	@${CC} ${FLAGS} ${FT_H} -c $<

$(NAME):	${OBGS}
	@ar rc ${NAME} ${OBGS}

all:		${NAME}

bonus:		${NAME} ${OBGS}
	@ar rc ${NAME} ${OBGS}

clean:
	@${RM} ${OBGS}

fclean:		clean
	@${RM} ${NAME}

re:			fclean all
