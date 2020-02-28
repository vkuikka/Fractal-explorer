/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 15:22:53 by vkuikka           #+#    #+#             */
/*   Updated: 2020/01/22 15:23:02 by vkuikka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_comp	ft_fractal_loc(t_comp *min, t_comp *max, int *info, double *location)
{
	static double	mouse_loc[2] = {0, 0};
	double			tmp;
	t_comp			factor;

	if (location)
	{
		mouse_loc[0] = location[0];
		mouse_loc[1] = location[1];
	}
	location[0] = mouse_loc[0];
	location[1] = mouse_loc[1];
	tmp = (double)3 / info[0] * (location[0] * info[7] - info[0] / 2) / info[7];
	min[0].real = -2 + tmp;
	max[0].real = 1 + tmp;
	tmp = (double)2 / info[1] * (location[1] * info[7] - info[1] / 2) / info[7];
	min[0].imag = -1 - tmp;
	max[0].imag = 1 - tmp;
	factor.real = (max[0].real - min[0].real) / (info[0] * info[7]);
	factor.imag = (max[0].imag - min[0].imag) / (info[1] * info[7]);
	return (factor);
}

int		ft_choose_fractal(t_comp c, t_comp z, int *info, double *location)
{
	int		ret;

	ret = 0;
	if (info[8] == 1 && ft_mandelbrot(c, z, info))
		return (1);
	else if (info[8] == 2)
	{
		ft_julia(c, z, info, location);
		return (1);
	}
	else if (info[8] == 3 && ft_burning_ship(c, z, info))
		return (1);
	return (0);
}

void	ft_fractal(int *info, char *pixel_colors, int *xy, double *location)
{
	t_comp	z;
	t_comp	c;
	t_comp	min;
	t_comp	max;
	t_comp	factor;

	factor = ft_fractal_loc(&min, &max, info, location);
	xy[1] = -1;
	while (++xy[1] < info[1] && (xy[0] = -1))
	{
		c.imag = max.imag - xy[1] * factor.imag;
		while (++xy[0] < info[0])
		{
			c.real = min.real + xy[0] * factor.real;
			z.real = c.real;
			z.imag = c.imag;
			if (ft_choose_fractal(c, z, info, location))
				ft_pixel_put_img(pixel_colors, info, xy, info[2]);
			else
				ft_pixel_put_img(pixel_colors, info, xy, 0xffffff);
			if (info[10] == 1 || info[10] == 2)
				info[2] = 0;
		}
	}
}
