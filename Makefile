NAME = ft_ping
CC=clang
FLAGS=-Werror -Wextra -Wall -g -Wno-unused-result -Qunused-arguments

SRCS_DIR = srcs
INCLUDES_DIR = includes
OBJS_DIR = .objs

SRCS =	main.c

INCLUDES = 

OBJS =	$(addprefix $(OBJS_DIR)/,$(SRCS:.c=.o))\
		$(addprefix $(OBJS_DIR)/,$(INCLUDES:.h=.pch))

all: $(NAME)

bonus: all

$(NAME): $(OBJS_DIR) $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $@ -lm

$(OBJS_DIR):
	mkdir $(OBJS_DIR)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	$(CC) $(FLAGS) -c $< -o $@
$(OBJS_DIR)/%.pch: $(INCLUDES_DIR)/%.h
	$(CC) $(FLAGS) -c $< -o $@

setcap: $(NAME)
	sudo setcap cap_net_raw+ep $(NAME)

clean:
	rm -rf $(OBJS_DIR) 

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all
