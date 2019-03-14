/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 08:51:22 by aben-azz          #+#    #+#             */
/*   Updated: 2019/03/14 17:12:21 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

static void			put_legend(t_mlx *fractol)
{
	int i;

	i = 10;
	mlx_string_put(fractol->mlx, fractol->win, DRAW_W + 10, i, WHITE,
	"FdF Legend: ");
	mlx_string_put(fractol->mlx, fractol->win, DRAW_W + 10, i += 50, WHITE,
	"(Lshift/Rshift) + scroll  - change altitude");
	mlx_string_put(fractol->mlx, fractol->win, DRAW_W + 10, i += 50, WHITE,
	"scroll                    - zoom");
	mlx_string_put(fractol->mlx, fractol->win, DRAW_W + 10, i += 50, WHITE,
	"scroll click              - toggle projection");
	mlx_string_put(fractol->mlx, fractol->win, DRAW_W + 10, i += 50, WHITE,
	"Space                     - reset values");
	mlx_string_put(fractol->mlx, fractol->win, DRAW_W + 10, i += 50, WHITE,
	"arrow or A/D/W/S           - move");
}
//


void mandelbrot(t_mlx *fractal, long zoom, long iteration_max) {
  double c_x, c_y , a, b, tmp;
  int i, x, y;

  //double abs_min = x_zoom - h;
 // double abs_max = x_zoom + h;
 // double ord_min = y_zoom - h;
 // double ord_max = y_zoom + h;

  for(x = 0; x < DRAW_W; x++) {
    for(y = 0; y < WIN_H; y++) {
      /* Fractale de Mandelbrot : un peu de mathématique...
     Zn+1 = Zn² + (x + iy)
     Zo = 0
     On colorie en noir si le module de Zn+1 ne tend pas vers +oo

     On convertit la suite complexe en suite réelle :
     Re: a = a² - b² + x
     Im: b = 2ab + y
     Ao = Bo = 0 */
      a = 0;
      b = 0;
      i = 0;
      c_x = ((double)x - 700 ) / zoom;
      c_y = ((double)y-500) / zoom;
      while((a*a + b*b) < 4.0 && i < iteration_max) {
	    tmp = a;
	    a = a*a - b*b + c_x;
	    b = 2*tmp*b + c_y;
	    i++;
      }
      if(i == iteration_max)
	  	put_pixel_img(fractal, (t_point){x, y}, 0xFFFFFF);
      else {
	    if(i * 100 / iteration_max < 50)
			put_pixel_img(fractal, (t_point){x, y}, rgb2dec(i*255/(iteration_max*0.75), 0, i*255/(iteration_max*0.75)));
	    else
			put_pixel_img(fractal, (t_point){x, y}, rgb2dec(255, i*255/iteration_max, 0));
      }
    }
  }
}
void	draw(t_mlx *fractol)
{
	//mandelbrot(t_mlx *fractal, long zoom, long iteration_max, double x_zoom, double y_zoom, double h)
	mandelbrot(fractol, fractol->zoom, fractol->iteration_max);
	// int MAX_ITER;
	// double zx;
	// double zy;
	// double cX;
	// double cY;
	// double tmp;
	// int y;
	// int x;
	// int iter;
	//
	// MAX_ITER = 1000;
	// y = 0;
	// while (y < WIN_H)
	// {
	// 	x = 0;
	// 	while (x < DRAW_W)
	// 	{
	// 		zx = 0.0;
	// 		zy = 0.0;
	// 		cX = (x - 700) / fractol->zoom;
	// 		cY = (y - 500) / fractol->zoom;
	// 		iter = MAX_ITER;
	//
	//
	// 		while (zx * zx + zy * zy < 4 && iter > 0)
	// 		{
	// 			tmp = zx * zx - zy * zy + cX;
	// 			zy = 2.0 * zx * zy + cY;
	// 			zx = tmp;
	// 			iter--;
	// 		}
	// 		if (iter)
	// 			put_pixel_img(fractol, (t_point){x, y}, 0xFFFFFF);
	// 		else
	// 			put_pixel_img(fractol, (t_point){x, y}, 0x000000);
	// 		x++;
	// 	}
	// 	y++;
	// }
}

void				process(t_mlx *fractol)
{
	mlx_clear_window(fractol->mlx, fractol->win);
	(fractol->img) && mlx_destroy_image(fractol->mlx, fractol->img->ptr);
	if (!(fractol->img = (t_image *)malloc(sizeof(t_image))))
		exit(1);
	fractol->img->ptr = mlx_new_image(fractol->mlx, WIN_W, WIN_H);
	if (!(fractol->img->ptr))
		exit(1);
	fractol->img->data = mlx_get_data_addr(fractol->img->ptr,
			&fractol->img->bpp, &fractol->img->sizeline, &fractol->img->endian);
	fractol->img->bpp /= 8;
	draw(fractol);
	mlx_put_image_to_window(fractol->mlx, fractol->win, fractol->img->ptr, 0, 0);
	put_legend(fractol);
}

t_point				put_pixel_img(t_mlx *fractol, t_point p, int clr)
{
	int offset;
	int color;

	offset = ((p.x + p.y * WIN_W) * fractol->img->bpp);
	color = mlx_get_color_value(fractol->mlx, clr);
	if (fractol->is_border || (p.x < DRAW_W && p.x > 0 && p.y < WIN_H && p.y > 0))
		*(int *)(fractol->img->data + offset) = color;
	return (p);
}

static inline void	init_variables(t_mlx *fractol)
{
	fractol->img = NULL;
	fractol->zoom = 10;
	fractol->x_zoom = -30.0;
	fractol->y_zoom = -30.0;
	fractol->iteration_max = 20;
	fractol->h = 20;
	fractol->is_border = 0;
	fractol->is_shift = 0;
	fractol->is_pressed = 0;
}

static t_mlx inline	*init(void)
{
	t_mlx	*fractol;

	if (!(fractol = (t_mlx *)malloc(sizeof(t_mlx))))
		exit(1);
	fractol->mlx = mlx_init();
	fractol->win = mlx_new_window(fractol->mlx, WIN_W, WIN_H, "fractol");
	mlx_hook(fractol->win, KPRESS, 0, evt_live_key_pressed, fractol);
	mlx_hook(fractol->win, MMOVE, 0, evt_live_mouse_move, fractol);
	mlx_hook(fractol->win, MCLICK, 0, evt_live_mouse_clicked, fractol);
	mlx_hook(fractol->win, MPRESS, 0, evt_live_mouse_pressed, fractol);
	mlx_hook(fractol->win, KEYRELEASE, 0, evt_live_key_released, fractol);
	init_variables(fractol);
	return (fractol);
}

int					main(int argc, char **argv)
{
	t_mlx *fractol;

	(void)argv;
	(void)argc;
	fractol = init();
	process(fractol);
	mlx_loop(fractol->mlx);
	return (0);
}
