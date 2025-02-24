# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: etorren <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/17 19:32:45 by etorren           #+#    #+#              #
#    Updated: 2021/05/22 22:44:29 by ruslan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= main.c core.c\
			$(wildcard ./processor/*.c ./processor/builtin_cmd/*.c\
			./utils/*.c ./parser/*.c ./readterm/casecore/*.c\
			./readterm/*.c)

OBJS		= $(SRCS:.c=.o)

HEADER		= -I ./includes

FLAGS		= -g -Wall -Werror -Wextra

LIB_PATH	= ./libft/libft.a

NAME		= minishell

%.o: %.c
	@gcc $(FLAGS) $(HEADER) -c $< -o $(<:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) bonus -C ./libft
	@gcc $(OBJS) $(LIB_PATH) $(HEADER) -ltermcap -o $(NAME)
	@echo "\033[33mCompiling complete\033[0m"

clean:
	@$(MAKE) clean -C ./libft
	@rm -rf $(OBJS)
	@echo "\033[33mClean objects files\033[0m"

fclean: clean
	@$(MAKE) fclean -C ./libft
	@rm -rf $(NAME)
	@echo "\033[33mAll cleaned\033[0m"

re: fclean all

norm:
	@echo "\033[46m\033[30mLIBFT\033[0m"; \
	cd libft; \
	norminette *.c *.h; \
	cd ../includes; \
	echo "\033[46m\033[30mHEADERS\033[0m"; \
	norminette *.h; \
	cd ../readterm; \
	echo "\033[46m\033[30mREADTERM\033[0m"; \
	norminette *.c */*.c; \
	cd ../processor; \
	echo "\033[46m\033[30mPROCESSOR\033[0m"; \
	norminette *.c */*.c; \
	cd ../parser; \
	echo "\033[46m\033[30mPARSER\033[0m"; \
	norminette *.c */*.c; \
	cd ../utils; \
	echo "\033[46m\033[30mUTILS\033[0m"; \
	norminette *.c */*.c; \
	cd ..; \
	echo "\033[46m\033[30mCORE\033[0m"; \
	norminette core.c; \
	echo "\033[46m\033[30mMAIN\033[0m"; \
	norminette main.c
	
