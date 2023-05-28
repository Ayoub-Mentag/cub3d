#include "../cub3d.h"


double distanceBetweenPoints(double x1, double y1, double x2, double y2)
{
    return (sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)));
}

int hits_wall(double x, double y)
{
    if (x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT)
        return 1;
    int i = floor(y / TILE_SIZE);
    int j = floor(x / TILE_SIZE);
    if (i >= 15 || j >= 15)
        return (1);
    return (grid[i][j] == 1);
}

t_point get_vertical(t_point player, double angle, int down, int left, int *foundVertWallHit)
{
    double  xstep;
    double  ystep;
    t_point vertical;
    t_point first;

    // Find the x-coordinate of the closest vertical grid intersenction
    first.x = floor(player.x / TILE_SIZE) * TILE_SIZE;
    first.x += !left ? TILE_SIZE : 0;

    // Find the y-coordinate of the closest vertical grid intersection
    first.y = player.y + (first.x - player.x) * tan(angle);

    // Calculate the increment xstep and ystep
    xstep = TILE_SIZE;
    xstep *= left ? -1 : 1;

    ystep = TILE_SIZE * tan(angle);
    ystep *= (!down && ystep > 0) ? -1 : 1;
    ystep *= (down && ystep < 0) ? -1 : 1;


    // Increment xstep and ystep until we find a wall

    while (1)
    {
        // printf("Hello\n");
        if (hits_wall(first.x - left, first.y)) {
            vertical.x = first.x;
            vertical.y = first.y;
            *foundVertWallHit = 1;
            break;
        } else {
            first.x += xstep;
            first.y += ystep;
        }
    }
    return (vertical);
}

t_point get_horizontal(t_point player, double angle, int down, int left, int *foundHorzWallHit)
{
    double xstep, ystep;
    t_point horizontal;
    t_point first;

    // Find the y-coordinate of the closest horizontal grid intersenction
    first.y = floor(player.y / TILE_SIZE) * TILE_SIZE;
    first.y += down ? TILE_SIZE : 0;

    // Find the x-coordinate of the closest horizontal grid intersection
    first.x = player.x + (first.y - player.y) / tan(angle);

    // Calculate the increment xstep and ystep
    ystep = TILE_SIZE;
    ystep *= !down ? -1 : 1;

    xstep = TILE_SIZE / tan(angle);
    xstep *= (left && xstep > 0) ? -1 : 1;
    xstep *= (!left && xstep < 0) ? -1 : 1;


    // Increment xstep and ystep until we find a wall
    while (1)
    {
        if (hits_wall(first.x, first.y - !down)) {
            *foundHorzWallHit = 1;
            horizontal.x = first.x;
            horizontal.y = first.y;
            break;
        } else {
            first.x += xstep;
            first.y += ystep;
        }
    }
    return (horizontal);
}

void    set_point(t_point player, t_ray *ray, int down, int left)
{
    int foundHorzWallHit = 0, foundVertWallHit = 0;
    t_point horizontal = get_horizontal(player, ray->rayAngle, down, left, &foundHorzWallHit);
    t_point vertical = get_vertical(player, ray->rayAngle, down, left, &foundVertWallHit);

    // Calculate both horizontal and vertical distances and choose the smallest value
    double horzHitDistance = (foundHorzWallHit)
        ? distanceBetweenPoints(player.x, player.y, horizontal.x, horizontal.y)
        : INT32_MAX;
    double vertHitDistance = (foundVertWallHit)
        ? distanceBetweenPoints(player.x, player.y, vertical.x, vertical.y)
        : INT32_MAX;

    // only store the smallest of the distances
    if (horzHitDistance < vertHitDistance)
    {
        ray->hitvertical = false;
        ray->coor.x = horizontal.x;
        ray->coor.y = horizontal.y;
    }
    else 
    {
        ray->hitvertical = true;
        ray->coor.x = vertical.x;
        ray->coor.y = vertical.y;
    }
    ray->distance = sqrt(pow(ray->coor.x - player.x, 2) + pow(ray->coor.y - player.y, 2));
}

int look_down(double rayAngle)
{
    return (rayAngle > 0 && rayAngle < M_PI);
}

int look_left(double rayAngle)
{
    return (rayAngle <= 1.5 * M_PI && rayAngle >= M_PI * 0.5);
}

void    set_hitted_point(t_point player, t_ray *ray)
{
    // TODO : use the walkdirection and turndirection instead of down and left ?? 
    //  TODO : like you do in rendering the minimap without clearing the window use when you render the 3d projection
    int down, left;

    ray->rayAngle = fmod(ray->rayAngle, 2 * M_PI);
    if (ray->rayAngle < 0) {
        ray->rayAngle = (2 * M_PI) + ray->rayAngle;
    }

    // int down = (ray->rayAngle > 0 && ray->rayAngle < M_PI) ? 1 : 0;
    // int left = (ray->rayAngle <= 1.5 * M_PI && ray->rayAngle >= M_PI * 0.5) ? 1 : 0;
    down = look_down(ray->rayAngle);
    left = look_left(ray->rayAngle);
    set_point(player, ray, down, left);
}