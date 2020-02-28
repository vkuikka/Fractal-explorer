/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 22:06:27 by vkuikka           #+#    #+#             */
/*   Updated: 2020/02/28 15:24:40 by vkuikka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# define R_HEX(x) ((x) * 65536)
# define G_HEX(x) ((x) * 256)
# define B_HEX(x) (x)
# define R_VAL(x) ((x) / 65536)
# define G_VAL(x) (((x) - ((x) / 65536) * 65536) / 256)
# define B_VAL(x) ((x) - ((x) / 256) * 256)
# include "mlx.h"
# include "libft.h"
# include <fcntl.h>
# include <math.h>

typedef struct	s_nums
{
	double		real;
	double		imag;
}				t_comp;

int				main_fractal(int key, void **params, int x, int y);
int				ft_stop(int code);
int				ft_deal_loop(void **params);
int				ft_mandelbrot(t_comp c, t_comp z, int *info);
int				ft_julia(t_comp c, t_comp z, int *info, double *location);
int				ft_burning_ship(t_comp c, t_comp z, int *info);
int				ft_get_color(int *info, int i, t_comp x, t_comp y);
void			ft_pixel_put_img(char *pixel_color,
				int *info, int *xy, int color);
void			ft_fractal(int *info, char *pixel_colors,
				int *xy, double *location);
int				ft_deal_key(int key, void **params);
int				ft_deal_button(int key, int x, int y, void **params);
int				ft_deal_mouse(int x, int y, void **params);
int				*ft_save_mode(void);

#endif
