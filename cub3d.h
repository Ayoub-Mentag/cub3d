# ifndef CUB3D_H

# define CUB3D_H
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <mlx.h>
# include <stdio.h>
# include <math.h>
# include <stdbool.h>

# define WINDOW_WIDTH 1980
# define WINDOW_HEIGHT 1024
# define THICK 1
# define NUMBER_RAYS (WINDOW_WIDTH / THICK)
# define SIDE 20
# define TILE_SIZE 64
# define MINIMAP_SCALE_FACTORY 0.2

# define A 0
# define S 1
# define D 2
# define W 13
# define RIGHT_ARROW 124
# define LEFT_ARROW 123
# define MOVE_SPEED 5
# define FOV_ANGLE (M_PI / 3)


# define TEXT_WIDTH 64
# define TEXT_HEIGHT 64

extern int grid[15][15];


typedef struct	s_data {
	void	*img;
    char    *addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct  s_point
{
    double x;
    double y;
} t_point;

typedef struct s_player
{
    t_point         coor;
    int             side;
    int             turnDirection;
    int             walkDirection;
    double          rotationAngle;
    int             moveSpeed;
    double          rotationSpeed;
} t_player;

typedef struct	s_ray
{
	double	distance;
	double	rayAngle;
	bool	hitvertical;
	t_point	coor;
}	t_ray;

typedef struct s_all
{
    t_data			data;
    t_data			north;
    t_data			south;
    t_data			west;
    t_data			east;
    void			*mlx;
    void			*win;
    t_player		*player;
    t_ray			rays[NUMBER_RAYS];
    void            *wall;
    unsigned int    *north_array;
    unsigned int    *south_array;
    unsigned int    *west_array;
    unsigned int    *east_array;
} t_all;



void    set_hitted_point(t_point player, t_ray *ray);
void	my_mlx_pixel_put(t_all *all, int x, int y, int color);
void	render3d_projection(t_all *all);
void    clear_image(t_all *all);
void    set_hitted_point(t_point player, t_ray *ray);
void    render3d_projection(t_all *all);
t_all   *init_all();
void    set_player(t_all *all);
void    init_player(t_point *coor);
void    set_rays(t_all *all);
void    draw_line(t_all *all, t_point a, t_point b);
void    draw_player(t_all *all);
void    draw_square(t_all *all, int x, int y, int color);
void    draw_rays(t_all *all);
void    draw_mini_map(t_all *all);
int    update_coordination(t_all *all);

# endif