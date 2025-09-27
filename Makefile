NAME = woody_woodpacker
CC=clang
FLAGS=-Werror -Wextra -Wall -g


OBJS_DIR = .objs/
INCLUDES = -Ilibft
INCLUDES_DIR = includes/
SRCS_DIR = srcs/


PACKER_SUBDIR = packer/

PACKER_SRCS =	main.c\
				parsing.c

PACKER_OBJS =	$(addprefix $(OBJS_DIR)$(PACKER_SUBDIR),$(PACKER_SRCS:.c=.o))


STUB_SUBDIR = stub/

STUB_SRCS =	main.c

STUB_OBJS =	$(addprefix $(OBJS_DIR)$(STUB_SUBDIR),$(STUB_SRCS:.c=.o))

STUB=$(OBJS_DIR)$(STUB_SUBDIR)stub
STUB_HEADER=$(OBJS_DIR)stub_code.h


LIBFT = libft/libft.a

all: $(NAME)

bonus: all

stub: $(STUB_HEADER)

$(STUB): $(STUB_OBJS) $(LIBFT)
	$(CC) $(FLAGS) -Llibft $(STUB_OBJS) -o $@ -lft

$(STUB_HEADER): $(STUB)
	xxd -n stub_code -i $< > $@

$(LIBFT):
	make -C libft

$(NAME): $(PACKER_OBJS) $(LIBFT)
	$(CC) $(FLAGS) -Llibft $(PACKER_OBJS) -o $@ -lft

$(OBJS_DIR)%/:
	mkdir -p $@

$(OBJS_DIR)$(PACKER_SUBDIR)%.o: $(SRCS_DIR)$(PACKER_SUBDIR)%.c $(STUB_HEADER) $(OBJS_DIR)$(PACKER_SUBDIR)
	$(CC) $(FLAGS) $(INCLUDES) -I$(INCLUDES_DIR)packer -I.objs -c $< -o $@

$(OBJS_DIR)$(STUB_SUBDIR)%.o: $(SRCS_DIR)$(STUB_SUBDIR)%.c  $(OBJS_DIR)$(STUB_SUBDIR)
	$(CC) $(FLAGS) $(INCLUDES) -I$(INCLUDES_DIR)stub -c $< -o $@

clean:
	rm -rf $(OBJS_DIR)
	make -C libft fclean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all bonus
