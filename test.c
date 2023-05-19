#include "cub3d.h"

t_point get_point()
{
    t_point a;
    a.x = 10;
    a.y = 10;
    return (a);
}

int main()
{
    t_point a = get_point();
    printf("(%f, %f)\n", a.x, a.y);
    return 0;
}