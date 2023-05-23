SRC = main.c utils.c rendering3dwalls.c textures.c
SRC_OBJ = main.o utils.o rendering3dwalls.o textures.o
CFLAGS = -Wall -Wextra -Werror -Ofast
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