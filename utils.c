#include "cub3d.h"


double distanceBetweenPoints(double x1, double y1, double x2, double y2)
{
    return (sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)));
}

int hits_wall(double x, double y)
{
    if (x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT)
        return 1;
    int i = floor(y / 32);
    int j = floor(x / 32);
    if (i >= 15 || j >= 15)
        return (1);
    return (grid[i][j] == 1);
}


t_point get_point(t_point player, double angle, int down, int left)
{
    int foundHorzWallHit = 0, foundVertWallHit = 0;
    double xstep, ystep;
    t_point vertical, horizontal;
    t_point first, i;

    // Find the y-coordinate of the closest horizontal grid intersenction
    first.y = floor(player.y / TILE_SIZE) * TILE_SIZE;
    first.y += down ? TILE_SIZE : 0;

    printf("first(%f, %f)\n", first.x / 32, first.y / 32);
    // Find the x-coordinate of the closest horizontal grid intersection
    first.x = player.x + (first.y - player.y) / tan(angle);

    // Calculate the increment xstep and ystep
    ystep = TILE_SIZE;
    ystep *= !down ? -1 : 1;

    xstep = TILE_SIZE / tan(angle);
    xstep *= (left && xstep > 0) ? -1 : 1;
    xstep *= (!left && xstep < 0) ? -1 : 1;
    i.x = first.x;
    i.y = first.y;


    // if (!down)
    //     i.y--;

        // Increment xstep and ystep until we find a wall
    while (i.x >= 0 && i.x <= WINDOW_WIDTH && i.y >= 0 && i.y <= WINDOW_HEIGHT) {
        if (hits_wall(i.x, i.y - !down)) {
            foundHorzWallHit = 1;
            horizontal.x = i.x;
            horizontal.y = i.y;
            break;
        } else {
            i.x += xstep;
            i.y += ystep;
        }
    }
        

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

        i.x = first.x;
        i.y = first.y;

        // if (left)
        //     i.x--;
        // Increment xstep and ystep until we find a wall
        while (i.x >= 0 && i.x <= WINDOW_WIDTH && i.y >= 0 && i.y <= WINDOW_HEIGHT) {
            // printf("Hello\n");
            if (hits_wall(i.x - left, i.y)) {
                vertical.x = i.x;
                vertical.y = i.y;
                foundVertWallHit = 1;
                break;
            } else {
                i.x += xstep;
                i.y += ystep;
            }
        }

        // Calculate both horizontal and vertical distances and choose the smallest value
        double horzHitDistance = (foundHorzWallHit)
            ? distanceBetweenPoints(player.x, player.y, horizontal.x, horizontal.y)
            : INT32_MAX;
        double vertHitDistance = (foundVertWallHit)
            ? distanceBetweenPoints(player.x, player.y, vertical.x, vertical.y)
            : INT32_MAX;

        t_point result;
        // only store the smallest of the distances
        result.x = (horzHitDistance < vertHitDistance) ? horizontal.x : vertical.x;
        result.y = (horzHitDistance < vertHitDistance) ? horizontal.y : vertical.y;
    return (result);
}

t_point get_length_of_ray(t_point player, double angle)
{
    angle = fmod(angle, 2 * M_PI);
    if (angle < 0) {
        angle = (2 * M_PI) + angle;
    }

    int down = (angle > 0 && angle < M_PI) ? 1 : 0;
    int left = (angle <= 1.5 * M_PI && angle >= M_PI * 0.5) ? 1 : 0;

    t_point result = get_point(player, angle, down, left);
    return (result);
}