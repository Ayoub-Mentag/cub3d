#include "cub3d.h"

int hits_wall(t_point p)
{
    int i = p.y / 32;
    int j = p.x / 32;

    return (grid[i][j] == 1);
}

t_point get_horizontal(t_point player, double angle, int down, int left)
{
    t_point first_intersection;
    double  ystep;
    double  xstep;
    t_point i;

    first_intersection.y = (floor(player.y / SIDE)) * SIDE;
    first_intersection.y += down ? SIDE : 0;

    first_intersection.x = player.x + ((first_intersection.y - player.y) / tan(angle));

    printf("HORIZONTAL : first (%.2f, %.2f)\n", first_intersection.x, first_intersection.y);
    ystep = SIDE;
    ystep *= !down ? -1 : 1;

    xstep = SIDE / tan(angle);
    xstep *= (left && xstep > 0) ? -1 : 1;
    xstep *= (!left && xstep < 0) ? -1 : 1;

    i.x = first_intersection.x;
    i.y = first_intersection.y;

    //why this
    if (!down)
        i.y--;

    while (i.y >= 0 && i.y <= WINDOW_HEIGHT && i.x >= 0 && i.x <= WINDOW_WIDTH)
    {
        if (hits_wall(i))
            return (i);
        i.x += xstep;
        i.y += ystep;
    }
    i.x = -1;
    i.y = -1;
    return (i);
}


t_point get_vertical(t_point player, double angle, int down, int left)
{
    t_point first_intersection;
    double  ystep;
    double  xstep;
    t_point i;

    first_intersection.x = (floor(player.x / SIDE)) * SIDE;
    first_intersection.x += !left ? SIDE : 0;
    first_intersection.y = player.y + ((first_intersection.x - player.x) * tan(angle));

    printf("VERTICAL : first (%.2f, %.2f)\n", first_intersection.x, first_intersection.y);

    xstep = SIDE;
    xstep *= left ? -1 : 1;

    ystep = SIDE * tan(angle);
    ystep *= !down && ystep > 0 ? -1 : 1;
    ystep *= down && ystep < 0 ? -1 : 1;

    i.x = first_intersection.x;
    i.y = first_intersection.y;

    if (left)
        first_intersection.x--;

    while (i.y >= 0 && i.y <= WINDOW_HEIGHT && i.x >= 0 && i.x <= WINDOW_WIDTH)
    {
        if (hits_wall(i))
            return (i);
        i.x += xstep;
        i.y += ystep;
    }
    i.x = -1;
    i.y = -1;
    return (i);
}

t_point get_length_of_ray(t_point player, double angle)
{
    double  hor, ver;
    angle = fmod(angle, 2 * M_PI);
    if (angle < 0) {
        angle = (2 * M_PI) + angle;
    }

    int down = (angle > 0 && angle < M_PI) ? 1 : 0;
    int left = (angle <= 1.5 * M_PI && angle >= M_PI * 0.5) ? 1 : 0;

    t_point hor_intersection = get_horizontal(player, angle, down, left);
    t_point ver_intersection = get_vertical(player, angle, down, left);
    // printf("hor (%.2f, %.2f) ; ver (%.2f, %.2f)\n", hor_intersection.x, hor_intersection.y, ver_intersection.x, ver_intersection.y);

    hor = hor_intersection.x != -1 ? sqrt(pow(player.x - hor_intersection.x, 2) + pow(player.y - hor_intersection.y, 2)) : INT32_MAX;
    ver = ver_intersection.x != -1 ? sqrt(pow(player.x - ver_intersection.x, 2) + pow(player.y - ver_intersection.y, 2)) : INT32_MAX;
    t_point result = hor < ver ? hor_intersection : ver_intersection;
    hor < ver ? printf("VER\n") : printf("HOR\n");
    return (result);
}