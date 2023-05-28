

UTILS = utils/rendering3dwalls.c utils/clear.c utils/distance_ray.c utils/drawing.c utils/init_set.c
SRCS = main.c ${UTILS}

OBJS = ${SRCS:.c=.o}

CFLAGS = -Wall -Wextra -Werror -Ofast
LINKS = -lmlx -framework OpenGL -framework AppKit

NAME = cub3d

all : $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LINKS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	@rm -rf ${OBJS}

fclean : clean
	@rm -rf $(NAME)

re : fclean all