#include "../cub3d.h"

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