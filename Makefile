#---------------------------------Archive-------------------------------------#
NAME = pipex
LIBFTNAME = libft.a

#---------------------------------Flags---------------------------------------#
CC = @cc
CFLAGS = -Wall -Wextra -Werror
RM = @rm -f

#---------------------------------Directories---------------------------------#
SRC_DIR = .
LIBFT_DIR = ./libft

#---------------------------------Source Files--------------------------------#
SRC_FLS = 	$(SRC_DIR)/pipex.c $(SRC_DIR)/utils.c

#---------------------------------Colours-------------------------------------#
GREEN= \033[1;32m
CYAN= \033[1;36m
PURPLE= \033[1;35m
END= \033[0m

#---------------------------------Rules---------------------------------------#
all: $(NAME)

OBJS = $(SRC_FLS:.c=.o)

$(NAME): $(OBJS)
	@echo "${PURPLE}Compiling Libft${END}"
	@echo "${PURPLE}Compiling Pipex${END}"
	@make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_DIR)/$(LIBFTNAME) -o $@ 
	@echo "${GREEN}Pipex Compiled Successfully${END}"
clean:
	$(RM) $(OBJS)
	@make clean -C libft/
	@echo "${GREEN}Pipex Cleaned${END}"

fclean: clean
	$(RM) $(NAME)
	@rm -f libft/${LIBFTNAME}

re: fclean all

.PHONY: all clean fclean re
