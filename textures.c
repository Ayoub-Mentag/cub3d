#include "cub3d.h"

uint32_t    **generate_simple_texture()
{

    static uint32_t **simple_texture;
    if (simple_texture)
        return (simple_texture);
    simple_texture = malloc(sizeof(uint32_t *) * TEXT_HEIGHT);
    for (int i = 0; i < TEXT_HEIGHT; i++)
    {
        simple_texture[i] = malloc(sizeof(uint32_t) * TEXT_WIDTH);
        for (int j = 0; j < TEXT_WIDTH; j++)
        {
            if (i % 4 && j % 4)
                simple_texture[i][j] = 0xFF0000FF;
            else
                simple_texture[i][j] = 0x00000000;
        }
    }
    return (simple_texture);
}

