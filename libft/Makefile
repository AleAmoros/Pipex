NAME	=	libft.a

AR		=	ar -rcs

CC		=	clang -O3

FLAGS	=	-Wall -Werror -Wextra

#directories
SRC_DIR					=	src/
OBJ_DIR					=	obj/
INC_DIR					=	include/
CURRENT_PATH			=	$(shell pwd)
CURRENT_DIRECTORY_NAME	=	$(shell basename $(CURRENT_PATH))
CURRENT_DIRECTORY		:=	./$(CURRENT_DIRECTORY_NAME)

#controll codes
RESET			=	\033[0m
GREEN			=	\033[32m
YELLOW			=	\033[33m
BLUE			=	\033[34m
RED				=	\033[31m
UP				=	\033[A
CUT				=	\033[K

#source files
SRC_FILES = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memcpy.c ft_memmove.c \
	ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c \
	ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atod.c ft_atof.c \
	ft_atoi.c ft_atol.c ft_calloc.c ft_strdup.c ft_putchar_fd.c ft_putstr_fd.c \
	ft_putendl_fd.c ft_putnbr_fd.c ft_striteri.c ft_strmapi.c ft_substr.c \
	ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c get_next_line.c \
	get_next_line_utils.c ft_printf.c ft_printf_utils.c ft_printf_utils2.c \
	ft_itoa_printf.c ft_strcmp.c ft_strstr.c
  
OBJ_FILES	=	$(SRC_FILES:.c=.o)

SRCBON_FILES	=	ft_lstnew_bonus.c \
					ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c \
					ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

OBJBON_FILES	= ${SRCBON:.c=.o}

#paths
SRC 		=	$(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ 		=	$(addprefix $(OBJ_DIR), $(OBJ_FILES))
SRCBON 		=	$(addprefix $(SRC_DIR), $(SRC_FILES))
OBJBON 		=	$(addprefix $(OBJ_DIR), $(OBJ_FILES))

all: $(NAME) 

#compile the library
$(NAME): $(OBJ)
	@echo "$(YELLOW)Compiling [$(NAME)]...$(RESET)"
	@$(AR) $(NAME) $(OBJ)
	@echo "$(GREEN)Finished [$(NAME)]$(RESET)"

#compile objects
$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@echo "$(YELLOW)Compiling [$@]...$(RESET)"
	@$(CC) $(FLAGS) -I $(INC_DIR) -o $@ -c $<
	@printf "$(UP)$(CUT)"
	@echo "$(GREEN)Finished [$@]$(RESET)"
	@printf "$(UP)$(CUT)"

bonus: $(OBJBON) $(OBJ)
	@$(AR) $(NAME) $(OBJBON) $(OBJ)
	@echo Making Libft bonus..

#clean rule
clean:
	@if [ -d "$(OBJ_DIR)" ]; then \
	rm -rf $(OBJ_DIR); \
	echo "$(BLUE)Deleting all objects from $(CURRENT_DIRECTORY)...$(RESET)"; else \
	echo "No objects to remove from $(CURRENT_DIRECTORY)."; \
	fi;

#fclean rule
fclean: clean
	@if [ -f "$(NAME)" ]; then \
	rm -f $(NAME); \
	echo "$(BLUE)Deleting $(RED)$(NAME)$(BLUE) library from $(CURRENT_DIRECTORY)$(RESET)"; else \
	echo "No library to remove from $(CURRENT_DIRECTORY)."; \
	fi;

#re rule
re: fclean all

#phony
.PHONY: all bonus clean fclean re
