/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 09:25:27 by aben-azz          #+#    #+#             */
/*   Updated: 2019/10/12 21:53:36 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include "../mlx/mlx.h"
# include "custom.h"
# include "../libft/includes/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <pthread.h>
# define WIN_W 1500
# define WIN_H  1000
# define DRAW_W  WIN_W - 500
# define ORIGINALJULIAX -0.7f
# define ORIGINALJULIAY 0.27015f
# define MINJ -3.200
# define MAXJ 3.200
# define KPRESS 2
# define KCLICK	3
# define MCLICK	4
# define MPRESS 5
# define MMOVE 	6
# define DROITE 124
# define GAUCHE 123
# define HAUT 126
# define BAS 125
# define ESC 53
# define WHEELUP 5
# define WHEELDOWN 4
# define WHEELCLICK 3
# define RIGHTCLICK 2
# define LEFTCLICK 2
# define THREADS 12

typedef struct	s_map
{
	int				**board;
	int				x;
	int				y;
}				t_map;

typedef struct	s_image
{
	void		*ptr;
	char		*data;
	int			bpp;
	int			sizeline;
	int			endian;
}				t_image;

typedef struct	s_point
{
	int				x;
	int				y;
}				t_point;
typedef struct	s_dpoint
{
	long double		x;
	long double		y;
}				t_dpoint;
typedef struct	s_points
{
	t_point			p1;
	t_point			p2;
}				t_points;
typedef struct	s_mlx
{
	void			*mlx;
	void			*win;
	t_image			*img;
	t_map			*map;
	long double		zoom;
	long double		iteration_max;
	pthread_t		thread[THREADS];
	void			*(*fract[6]) (void *);
	int				is_pressed;
	int				is_shift;
	int				is_var;
	int				type;
	t_dpoint		x;
	t_dpoint		y;
	long double		julia_var;
	long double		julia_var2;
	int				multi;
}				t_mlx;

/*
** BURNINGSHIP.C
*/
void			*draw_bship(void *data);
/*
** DRAW.C
*/

void			draw_fractal(t_mlx *m);
void			process(t_mlx *fractol);
t_point			put_pixel_img(t_mlx *fractol, t_point p, int clr);
/*
** EVENTS.C
*/
int				mouse_position(int x, int y, void *param);
int				evt_live_key_pressed(int key, t_mlx *m);
int				evt_live_key_released(int key, t_mlx *m);
int				evt_live_mouse_clicked(int keycode, int x, int y, t_mlx *m);
/*
** INIT.C
*/
t_mlx			*init(void);
/*
** JULIA.C
*/
void			*draw_julia(void *data);
/*
** MAIN.C
*/
unsigned int	get_thread(pthread_t id, pthread_t *threads);
int				error(char err, t_mlx *fractol, char mode);
int				select_fractal(int argc, char **argv, t_mlx *fractol);
int				get(int n, int iter_max);
int				main(int ac, char **av);
/*
** MANDELBROT.c
*/
void			*draw_mandelbrot(void *data);
/*
** MULTIBROT.c
*/
void			*draw_multibrot(void *data);
/*
** MULTIJULIA.c
*/
void			*draw_multijulia(void *data);
/*
** TRICORN.C
*/
void			*draw_tricorn(void *data);
#endif
