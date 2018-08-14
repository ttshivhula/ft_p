# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/11 11:29:48 by ttshivhu          #+#    #+#              #
#    Updated: 2018/08/11 11:59:06 by ttshivhu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER = server
CLIENT = client
CC = @gcc
CFLAGS = -Wall -Werror -Wextra -I. -Ilibft
SRC = get_dir.c cutils.c file_handling.c generic.c ls.c pwd_cd.c local.c
SILENT = --no-print-directory
OBJ = $(SRC:.c=.o)
all: $(SERVER)

$(SERVER): $(OBJ)
	@make -C libft $(SILENT)
	@gcc -c $(CFLAGS) smain.c
	@gcc -c $(CFLAGS) cmain.c
	@gcc $(OBJ) smain.o $(CFLAGS) -Llibft -lft -o $(SERVER)
	@gcc $(OBJ) cmain.o $(CFLAGS) -Llibft -lft -o $(CLIENT)
	@printf "\x1b[32mCompiled $(SERVER) and $(CLIENT)\x1b[0m\n"

clean:
	@make clean -C libft $(SILENT)
	@/bin/rm -f $(OBJ)
	@/bin/rm -f smain.o cmain.o

fclean: clean
	@make fclean -C libft $(SILENT)
	@/bin/rm -f $(SERVER) $(CLIENT)

re: fclean all
