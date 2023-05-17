# ifndef CUB3D_H

# define CUB3D_H
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <mlx.h>
# include <stdio.h>
# include <math.h>

# define WINDOW_WIDTH 640
# define WINDOW_HEIGHT 480
# define NUMBER_RAYS 320
# define SIDE 32

# define UP_ARROW 126
# define DOWN_ARROW 125
# define RIGHT_ARROW 124
# define LEFT_ARROW 123


extern int grid[15][15];

typedef struct	s_data {
	void	*img;
	char	*addr;
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

typedef struct s_all
{
    t_data          data;
    void            *mlx;
    void            *win;
    struct s_player *player;
} t_all;

t_point get_length_of_ray(t_point player, double angle);

# endif