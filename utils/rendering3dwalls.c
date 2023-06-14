#include "../cub3d.h"

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
    // uint32_t    *simple_texture = generate_simple_texture();

    t_point p;

    color = 0xadd8e6;
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
                    p.y = ((double)(i - y) / height) * TEXT_WIDTH;
                    my_mlx_pixel_put(all, x, i, all->west_array[((int)p.x + (TEXT_WIDTH * (int)p.y))]);

        //     for (int j = x; j < x + THICK; j++)
        //     {
        //         if (i >= 0 && i < WINDOW_HEIGHT && j >= 0 && j < WINDOW_WIDTH)
        //         {
        //             p.y = ((double)(i - y) / height) * TEXT_WIDTH;

        //             if (ray.hitvertical == 0)
        //             {
        //                 //NORTH
        //                 if (ray.rayAngle >= M_PI && ray.rayAngle <= 2 * M_PI)
        //                 {
        //                     my_mlx_pixel_put(all, j, i, all->north_array[((int)p.x + (TEXT_WIDTH * (int)p.y))]);
        //                 }
        //                 //SOUTH
        //                 else
        //                     my_mlx_pixel_put(all, j, i, all->south_array[((int)p.x + (TEXT_WIDTH * (int)p.y))]);
        //             }
        //             else
        //             {
        //                 //WEST
        //                 if (ray.rayAngle >= M_PI / 2 && ray.rayAngle <= 3 * M_PI / 2)
        //                     my_mlx_pixel_put(all, j, i, all->west_array[((int)p.x + (TEXT_WIDTH * (int)p.y))]);

        //                 //EAST
        //                 else
        //                     my_mlx_pixel_put(all, j, i, all->east_array[((int)p.x + (TEXT_WIDTH * (int)p.y))]);
        //             }
        //                 // my_mlx_pixel_put(all, j, i, simple_texture[((int)p.x + (TEXT_WIDTH * (int)p.y))]);
        //             // my_mlx_pixel_put(all, j, i, simple_texture[(int)(p.y)][(int)(p.x)]);
        //         }
        // }
    }

	color = 0x808080;
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


void    render3d_projection(t_all *all)
{
    double  correctDistance;
    double  distanceProjectionPlane;
    double  height;
    int     i;

    distanceProjectionPlane = (WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2);
    i = 0;
    while (i < NUMBER_RAYS)
    {
        correctDistance = all->rays[i].distance * cos(all->player->rotationAngle - all->rays[i].rayAngle);
        height = (TILE_SIZE / correctDistance) * distanceProjectionPlane;
        draw_rectangle(
            all,
            all->rays[i],
            i * THICK,
            height
        );
        i++;
    }
} 