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
# define SIDE 32
# define TILE_SIZE 32
# define MINIMAP_SCALE_FACTORY 0.5

# define UP_ARROW 126
# define DOWN_ARROW 125
# define RIGHT_ARROW 124
# define LEFT_ARROW 123
# define MOVE_SPEED 2
# define FOV_ANGLE (M_PI / 3)


# define TEXT_WIDTH 32
# define TEXT_HEIGHT 32

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
    t_data			data_wall;
    void			*mlx;
    void			*win;
    t_player		*player;
    t_ray			rays[NUMBER_RAYS];
    void            *wall;
    unsigned int    *array;
} t_all;

void    set_hitted_point(t_point player, t_ray *ray);
void	my_mlx_pixel_put(t_all *all, int x, int y, int color);
void	render3d_projection(t_all *all);


uint32_t    *generate_simple_texture();
# endif