# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xmatute- <xmatute-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/02 14:41:52 by xmatute-          #+#    #+#              #
#    Updated: 2025/02/12 19:34:06 by xmatute-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

define ASCII_ART
                              
 ,---.  ,--.      ,--.        
/  .-',-'  '-.    |  | ,---.  
|  `-,'-.  .-'    |  |(  .-'  
|  .-'  |  |,----.|  |.-'  `) 
`--'    `--''----'`--'`----'  
                              
endef
export ASCII_ART

NAME := ft_ls

SRC :=	main.c \
		ft_ls.c \
		sort_paths.c \
		list_paths.c \
		list_files.c \
		list_directories.c \
		save_calloc.c \
		isdir.c \
		put_file.c \
		get_files.c \
		save_closedir.c \
		get_stat.c \
		

INC_DIR = ./includes

LIBFT_DIR := $(INC_DIR)/libft

LIBFT := $(LIBFT_DIR)/libft.a

HEADER := ft_ls.h

WHITE = \033[0;37m
RED = \033[0;31m
CYAN = \033[0;36m
GREEN = \033[0;32m
MAGENTA = \033[0;35m

OBJ := $(SRC:%.c=%.o)

SANI 	:= -fsanitize=address -g3

CC 		:= gcc
CFLAGS 	:= -Wall -Wextra -Werror

CFLAGS	:= $(CFLAGS) $(EFLAGS)

RM 		:= rm -rf

all : $(NAME)

$(NAME) : $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) -I$(INC_DIR) $(LIBFT) -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled...$(WHITE)"
	@echo "$(CYAN)$$ASCII_ART$(WHITE)"

$(LIBFT): $(LIBFT_DIR)
	make -C $(LIBFT_DIR)
	@echo "$(GREEN)libft compiled...$(WHITE)"

%.o: %.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR) -I./includes/libft/ft_printf -c $< -o $@

sani:
	$(MAKE) EFLAGS='$(SANI)' all

flagless:
	$(MAKE) CFLAGS='' all

normi:
	norminette $(SRC) $(HEADER)

commit:
	git branch temp
	git checkout temp
	git add $(SRC) $(HEADER) ./Makefile
	git commit -m "commit general"
	git push
	git status

test: all
	./$(NAME)
	LC_ALL=C ls
	./$(NAME) -la
	LC_ALL=C ls -la
	./$(NAME) -lR
	LC_ALL=C ls -lR

clean : 
		$(RM) $(OBJ)
		make clean -C $(LIBFT_DIR)
		@echo "$(RED)clean done...$(WHITE)"

fclean : clean
		make fclean -C $(LIBFT_DIR)
		$(RM) $(NAME)
		@echo "$(RED)fclean done...$(WHITE)"

re : fclean all

.PHONY : all clean fclean re sani flagless normi commit test
