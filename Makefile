NAME = woody_woodpacker
CC=clang
FLAGS=-Werror -Wextra -Wall -g -Wno-unused-result -Qunused-arguments

SRCS_DIR = srcs
INCLUDES = -Iincludes -Ilibft
OBJS_DIR = .objs

SRCS =	main.c\
		parsing.c

OBJS =	$(addprefix $(OBJS_DIR)/,$(SRCS:.c=.o))

LIBFT = libft/libft.a

all:
	make -j$(shell nproc) $(NAME)

bonus: all

$(LIBFT):
	make -C libft

$(NAME): $(OBJS_DIR) $(OBJS) $(LIBFT)
	$(CC) $(FLAGS) -Llibft $(OBJS) -o $@ -lm -lft

$(OBJS_DIR):
	mkdir $(OBJS_DIR)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@
#$(OBJS_DIR)/%.pch: $(INCLUDES_DIR)/%.h
#	$(CC) $(FLAGS) -c $< -o $@

setcap: $(NAME)
	sudo setcap cap_net_raw+ep $(NAME)

clean:
	rm -rf $(OBJS_DIR) 
	make -C libft fclean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all bonus
