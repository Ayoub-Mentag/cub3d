#include "cub3d.h"

int grid[15][15] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

void	my_mlx_pixel_put(t_all *all, int x, int y, int color)
{
	char	*dst;

	dst = all->data.addr + (y * all->data.line_length + x * (all->data.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void    draw_line(t_all *all)
{
    int side = all->player->side;
    // //draw line
    t_point a, b;
    a.x = all->player->coor.x + (sqrt(2) * side * sin(M_PI / 4) * 0.5);
    a.y = all->player->coor.y + (sqrt(2) * side * sin(M_PI / 4) * 0.5);

    b.x = all->player->coor.x + (sqrt(2) * side * sin(M_PI / 4) * 0.5) + cos(all->player->rotationAngle) * 30;
    b.y = all->player->coor.y + (sqrt(2) * side * sin(M_PI / 4) * 0.5) + sin(all->player->rotationAngle) * 30;

    int dx = b.x - a.x;
    int dy = b.y - a.y;
    // int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    int steps = dx * dx + dy * dy;
    float x_increment = dx / (float) steps;
    float y_increment = dy / (float) steps;
    float x = a.x;
    float y = a.y;
    int i;

    for (i = 0; i <= steps; i++)
    {
		my_mlx_pixel_put(
            all,
            x,
            y,
            0x00000000);
        x += x_increment;
        y += y_increment;
    }
}

void    draw_player(t_all *all)
{
    for (int i = 0; i < all->player->side; i++)
	{
		for (int j = 0; j < all->player->side; j++)
		{
			my_mlx_pixel_put(all, all->player->coor.x + j, all->player->coor.y + i, 0x00FF0000);
		}
    }
}


void    update_coordination(t_all *all)
{
	all->player->rotationAngle += all->player->turnDirection * all->player->rotationSpeed;
	int moveStep = all->player->walkDirection * all->player->moveSpeed;
	double newPlayerX = all->player->coor.x + cos(all->player->rotationAngle) * moveStep;
    double newPlayerY = all->player->coor.y + sin(all->player->rotationAngle) * moveStep;
	all->player->coor.x = newPlayerX;
	all->player->coor.y = newPlayerY;
}

int    draw_map(t_all *all)
{
    int d1;
    int d2;
    int color;

    update_coordination(all);
	mlx_put_image_to_window(all->mlx, all->win, all->data.img, 0, 0);
    for (int i = 0; i < WINDOW_HEIGHT; i++)
    {
        for (int j = 0; j < 640; j++)
        {
			d1 = i / 32;
			d2 = j / 32;
            // if (d1 < 15 && d2 < 15 && grid[d1][d2] == 2)
            // {
            //     player->playerX = d1 * 32;
            //     player->playerY = d2 * 32;
            // }
			color = d1 >= 15 || d2 >= 15 || grid[d1][d2] == 1 ? 0x000000 : 0xFFFFFF;
			my_mlx_pixel_put(all, j, i, color);
		}
	}

    draw_player(all);
    draw_line(all);
    return (0);
}

t_player    *get_player()
{
    t_player    *player = malloc(sizeof(t_player));
    if (!player)
        exit(1);
    player->coor.x = WINDOW_WIDTH / 3;
    player->coor.y = WINDOW_HEIGHT / 2;
    player->side = 10;
    player->turnDirection = 0;
    player->walkDirection = 0;
    player->rotationAngle = M_PI / 2;
    player->moveSpeed = 2;
    player->rotationSpeed = 2 * (M_PI / 180);
    return (player);
}

t_all   *init_all()
{
    t_all *all = malloc(sizeof(t_all));
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Example");
    t_player    *player = get_player();
    
    all->player = player;
    all->mlx = mlx;
    all->win = win;

    all->data.img = mlx_new_image(all->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	all->data.addr = mlx_get_data_addr(all->data.img, &all->data.bits_per_pixel, &all->data.line_length,&all->data.endian);
    return (all);
}

int	key_hook(int key, void *p)
{
	t_all	*all;

	all = (t_all *)p;
	if (key == UP_ARROW)
	{
		// printf("Up pressed\n");
		all->player->walkDirection = 1;
	}
	else if (key == DOWN_ARROW)
	{
		all->player->walkDirection = -1;
		// printf("Down pressed\n");
	}
	else if (key == RIGHT_ARROW)
	{
		all->player->turnDirection = 1;
		// printf("Right pressed\n");
	}
	else if (key == LEFT_ARROW)
	{
		all->player->turnDirection = -1;
		// printf("left pressed\n");
	}
	else if (key == 53)
		exit(0);
	// draw_map(all->mlx, all->win, all->player);
	return (0);
}

int	key_released(int key, void *p)
{
    t_all   *all;
	(void)key;
    all = (t_all *)p;
    all->player->turnDirection = 0;
    all->player->walkDirection = 0;
    return (0);
}

int main()
{
    t_all   *all = init_all();

    mlx_hook(all->win, 2, 0, key_hook, all);
    mlx_hook(all->win, 3, 0, key_released, all);
    mlx_loop_hook(all->mlx, draw_map, all);
    mlx_loop(all->mlx);
    return 0;
}

