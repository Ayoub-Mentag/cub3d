#include "cub3d.h"

uint32_t    *generate_simple_texture()
{
    int line, column;
    static uint32_t *simple_texture;
    if (simple_texture)
        return (simple_texture);
    simple_texture = malloc(sizeof(uint32_t) * TEXT_HEIGHT * TEXT_WIDTH);
    for (int i = 0; i < TEXT_HEIGHT * TEXT_WIDTH; i++)
    {
        line = i / TEXT_HEIGHT;
        column = i % TEXT_WIDTH;
        if (line % 4 && column % 4)
        {
            simple_texture[i] = 0x00ff00;
        }
        else
            simple_texture[i] = 0x000000;
    }
    return (simple_texture);
}

// for (int i = 0; i < TEXT_HEIGHT; i++)
// {
//     simple_texture[i] = malloc(sizeof(uint32_t) * TEXT_WIDTH);
//     for (int j = 0; j < TEXT_WIDTH; j++)
//     {
//         if (i % 4 && j % 4)
//             simple_texture[i][j] = 0x00ff00;
//         else
//             simple_texture[i][j] = 0x000000;
//     }
// }