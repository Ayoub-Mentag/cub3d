#include "cub3d.h"

int get_start_color(t_ray ray)
{
    int         index;

    if (ray.hitvertical)
    {
        index = (int)ray.coor.y % TILE_SIZE;
    }
    else
    {
        index = (int)ray.coor.x % TILE_SIZE;
    }
    return (index);
}


void draw_rectangle(t_all *all, t_ray ray, int x, int height)
{
    int color;
    int i;
    int y = (WINDOW_HEIGHT / 2) - (height / 2);
    uint32_t    **simple_texture = generate_simple_texture();


    t_point p;

    color = 0x808080;
    for (i = 0; i < y; i++)
    {
        for (int j = x; j < x + THICK; j++)
        {
            if (i >= 0 && i < WINDOW_HEIGHT && j >= 0 && j < WINDOW_WIDTH)
            {
                my_mlx_pixel_put(all, j, i, color);
            }
        }
    }
	
    p.y = 0;
    if (ray.hitvertical)
		p.x = fmod(ray.coor.y, TILE_SIZE);
	else 
		p.x = fmod(ray.coor.x, TILE_SIZE);

    for (i = y; i < y + height; i++)
    {
        for (int j = x; j < x + THICK; j++)
        {
            if (i >= 0 && i < WINDOW_HEIGHT && j >= 0 && j < WINDOW_WIDTH)
            {
                my_mlx_pixel_put(all, j, i, simple_texture[(int)(p.y)][(int)(p.x)]);
                (p.y)++;
		        if (p.y >= TEXT_HEIGHT)
			        p.y = 0;
            }
        }
    }
    // exit(1);



	color = 0xFF0000;
	for (i = y + height; i < WINDOW_HEIGHT; i++)
	{
		for (int j = x; j < x + THICK; j++)
		{
			if (i >= 0 && i < WINDOW_HEIGHT && j >= 0 && j < WINDOW_WIDTH)
			{
				my_mlx_pixel_put(all, j, i, color);
			}
		}
	}
}


void    render3dProjection(t_all *all)
{
    double  correctDistance;
    double  distanceProjectionPlane;
    double  height;

    distanceProjectionPlane = (WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2);
    for (int i = 0; i < NUMBER_RAYS; i++)
    {
        correctDistance = all->rays[i].distance * cos(all->player->rotationAngle - all->rays[i].rayAngle);
        height = (TILE_SIZE / correctDistance) * distanceProjectionPlane;
        draw_rectangle(
            all,
            all->rays[i],
            i * THICK,
            height
        );
    }
} 