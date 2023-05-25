#include "cub3d.h"
int grid[15][15] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 2, 0, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

void	my_mlx_pixel_put(t_all *all, int x, int y, int color)
{
	char	*dst;
	dst = all->data.addr + (y * all->data.line_length + x * (all->data.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void    draw_line(t_all *all, t_point a, t_point b)
{
    int steps;
    double x_increment;
    double y_increment;    
    double x = a.x;
    double y = a.y;

    if (fabs(b.x - a.x) > fabs(b.y - a.y))
        steps = fabs(b.x - a.x);
    else
        steps = fabs(b.y - a.y);
    x_increment = (b.x - a.x) / (double) steps;
    y_increment = (b.y - a.y) / (double) steps;
    while (steps--)
    {
		my_mlx_pixel_put(
            all,
            x * MINIMAP_SCALE_FACTORY,
            y * MINIMAP_SCALE_FACTORY,
            0x00ff00);
        x += x_increment;
        y += y_increment;
    }
}

void    draw_player(t_all *all)
{
    int half;
    int i;
    int j;

    half = all->player->side / 2;
    i = -half;
    while (i < half)
    {
        j = -half;
        while (j < half)
        {
			my_mlx_pixel_put(all, (all->player->coor.x + j) * MINIMAP_SCALE_FACTORY, (all->player->coor.y + i) * MINIMAP_SCALE_FACTORY, 0x00FF0000);
            j++;
        }
        i++;
    }
}

int    update_coordination(t_all *all)
{
	int		d1;
	int		d2;
	double	newPlayerX;
	double	newPlayerY;
	double	moveStep;

    if (!all->player->turnDirection && !all->player->walkDirection)
        return (0);

	all->player->rotationAngle += all->player->turnDirection * all->player->rotationSpeed;
	moveStep = all->player->walkDirection * all->player->moveSpeed;
	newPlayerX = all->player->coor.x + cos(all->player->rotationAngle) * moveStep;
    newPlayerY = all->player->coor.y + sin(all->player->rotationAngle) * moveStep;

	d1 = newPlayerX;
	d2 = newPlayerY;

    if (grid[d2 / TILE_SIZE][d1 / TILE_SIZE] == 1)
        return (1);

	all->player->coor.x = newPlayerX;
	all->player->coor.y = newPlayerY;
    return (1);
}

void    set_rays(t_all *all)
{
    t_point	origin;
	double	rayAngle;
	double	angle;
    int     i;

    i = 0;
	angle = all->player->rotationAngle - (M_PI / 6);
	origin.x = all->player->coor.x;
	origin.y = all->player->coor.y;
	rayAngle = (M_PI / (3 * NUMBER_RAYS));
    while (i < NUMBER_RAYS)
    {
        all->rays[i].rayAngle = angle;
        set_hitted_point(origin, &(all->rays[i]));
	    angle += rayAngle;
        i++;
    }
}

void    draw_rays(t_all *all)
{
    int i;

    i = 0;
    while (i < NUMBER_RAYS)
    {
        draw_line(all, all->player->coor, all->rays[i].coor);
        i++;
    }
}

void    draw_square(t_all *all, int x, int y, int color)
{
    int i;
    int j;

    i = y;
    while (i < y + TILE_SIZE)
    {
        j = x;
        while (j < x + TILE_SIZE)
        {
            my_mlx_pixel_put(all, j * MINIMAP_SCALE_FACTORY, i * MINIMAP_SCALE_FACTORY, color);
            j++;
        }
        i++;
    }
}

void    draw_mini_map(t_all *all)
{
    int color;
    int i;
    int j;

    i = 0;
    while (i < 15)
    {
        j = 0;
        while (j < 15)
        {
            if (grid[i][j] == 1)
                color = 0x000000;
            else
                color = 0xFFFFFF;
            draw_square(all, j * TILE_SIZE, i * TILE_SIZE, color);
            j++;
        }
        i++;
    }
    draw_player(all);
    draw_rays(all);
}

void    init_player(t_point *coor)
{
    int i;
    int j;

    i = 0;
    while (i < 15)
    {
        j = 0;
        while (j < 15)
        {
            if (grid[i][j] == 2)
            {
                coor->x = j * TILE_SIZE;
                coor->y = i * TILE_SIZE;
            } 
            j++;
        }
        i++;
    }
}

void    set_player(t_all *all)
{
    t_player    *player = malloc(sizeof(t_player));
    if (!player)
        exit(1);
    init_player(&player->coor);
    player->side = 10;
    player->turnDirection = 0;
    player->walkDirection = 0;
    player->rotationAngle = M_PI / 2;
    player->moveSpeed = MOVE_SPEED;
    player->rotationSpeed = 2 * (M_PI / 180);
    all->player = player;
}

t_all   *init_all()
{
    t_all *all;
    void *mlx;
    void *win;

    all = malloc(sizeof(t_all));
    mlx = mlx_init();
    win = mlx_new_window(mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Example");
    set_player(all);
    set_rays(all);
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
		all->player->walkDirection = 1;
	else if (key == DOWN_ARROW)
		all->player->walkDirection = -1;
	else if (key == RIGHT_ARROW)
		all->player->turnDirection = 1;
	else if (key == LEFT_ARROW)
		all->player->turnDirection = -1;
	else if (key == 53)
		exit(0);
	return (0);
}

int	key_released(int key, void *p)
{
    t_all   *all;

	(void)key;
    all = (t_all *)p;
    all->player->walkDirection = 0;
    all->player->turnDirection = 0;
    return (0);
}

void    clear_image(t_all *all)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < WINDOW_HEIGHT)
    {
        j = 0;
        while (j < WINDOW_WIDTH)
        {
            my_mlx_pixel_put(all, j, i, 0x000000);
            j++;
        }
        i++;
    }
}

int    loop(t_all *all)
{
    mlx_put_image_to_window(all->mlx, all->win, all->data.img, 0, 0);
    clear_image(all);
    update_coordination(all);
    set_rays(all);
    render3d_projection(all);
    draw_mini_map(all);
    return (0);
}

int main()
{
    t_all   *all = init_all();
    mlx_hook(all->win, 2, 0, key_hook, all);
    mlx_hook(all->win, 3, 0, key_released, all);
    mlx_loop_hook(all->mlx, loop, all);
    mlx_loop(all->mlx);
    return 0;
}
