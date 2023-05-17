SRC = main.c utils.c
SRC_OBJ = main.o utils.o
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
LINKS = -lmlx -framework OpenGL -framework AppKit

NAME = cub3d

all : $(NAME)

$(NAME): $(SRC_OBJ)
	@$(CC) $(CFLAGS) $(SRC_OBJ) $(LINKS) -o $(NAME)

%.o : %.c
	@$(CC) $(CFLAGS) -c $<


clean :
	@rm -rf *.o

fclean : clean
	@rm -rf $(NAME)

re : fclean all