/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 08:51:22 by aben-azz          #+#    #+#             */
/*   Updated: 2019/03/13 17:37:10 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

static void			put_legend(t_mlx *fdf)
{
	int i;

	i = 10;
	mlx_string_put(fdf->mlx, fdf->win, DRAW_W + 10, i, WHITE,
	"FdF Legend: ");
	mlx_string_put(fdf->mlx, fdf->win, DRAW_W + 10, i += 50, WHITE,
	"(Lshift/Rshift) + scroll  - change altitude");
	mlx_string_put(fdf->mlx, fdf->win, DRAW_W + 10, i += 50, WHITE,
	"scroll                    - zoom");
	mlx_string_put(fdf->mlx, fdf->win, DRAW_W + 10, i += 50, WHITE,
	"scroll click              - toggle projection");
	mlx_string_put(fdf->mlx, fdf->win, DRAW_W + 10, i += 50, WHITE,
	"Space                     - reset values");
	mlx_string_put(fdf->mlx, fdf->win, DRAW_W + 10, i += 50, WHITE,
	"arrow or A/D/W/S           - move");
}

void				process(t_mlx *fdf)
{
	mlx_clear_window(fdf->mlx, fdf->win);
	(fdf->img) && mlx_destroy_image(fdf->mlx, fdf->img->ptr);
	if (!(fdf->img = (t_image *)malloc(sizeof(t_image))))
		exit(1);
	fdf->img->ptr = mlx_new_image(fdf->mlx, WIN_W, WIN_H);
	if (!(fdf->img->ptr))
		exit(1);
	fdf->img->data = mlx_get_data_addr(fdf->img->ptr,
			&fdf->img->bpp, &fdf->img->sizeline, &fdf->img->endian);
	fdf->img->bpp /= 8;
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img->ptr, 0, 0);
	put_legend(fdf);
}

t_point				put_pixel_img(t_mlx *fdf, t_point p, int clr)
{
	int offset;
	int color;

	offset = ((p.x + p.y * WIN_W) * fdf->img->bpp);
	color = mlx_get_color_value(fdf->mlx, clr);
	if (fdf->is_border || (p.x < DRAW_W && p.x > 0 && p.y < WIN_H && p.y > 0))
		*(int *)(fdf->img->data + offset) = color;
	return (p);
}

static inline void	init_variables(t_mlx *fdf)
{
	fdf->img = NULL;
	fdf->zoom = 100;
	fdf->is_border = 0;
	fdf->is_shift = 0;
	fdf->is_pressed = 0;
}

static t_mlx inline	*init(void)
{
	t_mlx	*fdf;

	if (!(fdf = (t_mlx *)malloc(sizeof(t_mlx))))
		exit(1);
	fdf->mlx = mlx_init();
	fdf->win = mlx_new_window(fdf->mlx, WIN_W, WIN_H, "fractol");
	mlx_hook(fdf->win, KPRESS, 0, evt_live_key_pressed, fdf);
	mlx_hook(fdf->win, MMOVE, 0, evt_live_mouse_move, fdf);
	mlx_hook(fdf->win, MCLICK, 0, evt_live_mouse_clicked, fdf);
	mlx_hook(fdf->win, MPRESS, 0, evt_live_mouse_pressed, fdf);
	mlx_hook(fdf->win, KEYRELEASE, 0, evt_live_key_released, fdf);
	init_variables(fdf);
	return (fdf);
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
