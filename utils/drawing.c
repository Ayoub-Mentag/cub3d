#include "../cub3d.h"

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