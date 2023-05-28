#include "../cub3d.h"

int    update_coordination(t_all *all)
{
	int		d1;
	int		d2;
	double	newPlayerX;
	double	newPlayerY;
	double	moveStep = 0.0;

    if (!all->player->turnDirection && !all->player->walkDirection)
        return (0);
    moveStep = all->player->walkDirection * all->player->moveSpeed;
    if (all->player->turnDirection == 2)
    {
        newPlayerX = all->player->coor.x + cos(all->player->rotationAngle - M_PI / 2) * moveStep;
        newPlayerY = all->player->coor.y + sin(all->player->rotationAngle - M_PI / 2) * moveStep;
    }
    else if (all->player->turnDirection == -2)
    {
        newPlayerX = all->player->coor.x + cos(all->player->rotationAngle + M_PI / 2) * moveStep;
        newPlayerY = all->player->coor.y + sin(all->player->rotationAngle + M_PI / 2) * moveStep;
    }
    else 
    {
        all->player->rotationAngle += all->player->turnDirection * all->player->rotationSpeed;
        newPlayerX = all->player->coor.x + cos(all->player->rotationAngle) * moveStep;
        newPlayerY = all->player->coor.y + sin(all->player->rotationAngle) * moveStep;
    }

	d1 = newPlayerX;
	d2 = newPlayerY;

    if (grid[d2 / TILE_SIZE][d1 / TILE_SIZE] == 1)
        return (1);
    if (grid[(d2 - SIDE / 2) / TILE_SIZE][d1 / TILE_SIZE] == 1)
        return (1);
    if (grid[(d2 + SIDE / 2) / TILE_SIZE][d1 / TILE_SIZE] == 1)
        return (1);
    if (grid[d2 / TILE_SIZE][(d1 - SIDE / 2) / TILE_SIZE] == 1)
        return (1);
    if (grid[(d2 - SIDE / 2) / TILE_SIZE][(d1 + SIDE / 2) / TILE_SIZE] == 1)
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
    player->side = SIDE;
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

    all->north.img = mlx_xpm_file_to_image(mlx, "./textures/north.xpm", malloc(sizeof(int)), malloc(sizeof(int)));
    all->north.addr = mlx_get_data_addr(all->north.img, &all->north.bits_per_pixel, &all->north.line_length,&all->north.endian);
    all->north_array = (unsigned int *)all->north.addr;

    all->south.img = mlx_xpm_file_to_image(mlx, "./textures/south.xpm", malloc(sizeof(int)), malloc(sizeof(int)));
    all->south.addr = mlx_get_data_addr(all->south.img, &all->south.bits_per_pixel, &all->south.line_length,&all->south.endian);
    all->south_array = (unsigned int *)all->south.addr;

    all->east.img = mlx_xpm_file_to_image(mlx, "./textures/east.xpm", malloc(sizeof(int)), malloc(sizeof(int)));
    all->east.addr = mlx_get_data_addr(all->east.img, &all->east.bits_per_pixel, &all->east.line_length,&all->east.endian);
    all->east_array = (unsigned int *)all->east.addr;

    all->west.img = mlx_xpm_file_to_image(mlx, "./textures/west.xpm", malloc(sizeof(int)), malloc(sizeof(int)));
    all->west.addr = mlx_get_data_addr(all->west.img, &all->west.bits_per_pixel, &all->west.line_length,&all->west.endian);
    all->west_array = (unsigned int *)all->west.addr;
    return (all);
}