#include "cub3d.h"
int grid[15][15] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1},
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

int	key_hook(int key, void *p)
{
	t_all	*all;

	all = (t_all *)p;
	if (key == W)
    {
		all->player->walkDirection = 1;

    }
	else if (key == S)
    {
		all->player->walkDirection = -1;
    }
    else if (key == A)
    {
		all->player->turnDirection = -2;
        all->player->walkDirection = 1;
    }
    else if (key == D)
	{
		all->player->turnDirection = 2;
        all->player->walkDirection = 1;
    }
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

int ft_exit()
{
    exit(0);
}

int main()
{
    t_all   *all = init_all();
    mlx_hook(all->win, 2, 0, key_hook, all);
    mlx_hook(all->win, 3, 0, key_released, all);
    mlx_hook(all->win, 17, 0, &ft_exit, NULL);
    mlx_loop_hook(all->mlx, loop, all);
    mlx_loop(all->mlx);
    return 0;
}
