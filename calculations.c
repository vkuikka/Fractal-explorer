/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 20:40:23 by vkuikka           #+#    #+#             */
/*   Updated: 2020/02/28 15:14:19 by vkuikka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		ft_mandelbrot(t_comp c, t_comp z, int *info)
{
	double	tmp;
	int		i;

	i = 0;
	while (i < info[6])
	{
		if (z.real * z.real + z.imag * z.imag > 4)
		{
			ft_get_color(info, i, z, c);
			return (1);
		}
		tmp = z.real * z.real - z.imag * z.imag + c.real;
		z.imag = 2 * (z.real * z.imag) + c.imag;
		z.real = tmp;
		i++;
	}
	if (info[10] == 5)
		info[2] = 0;
	return (0);
}

int		ft_julia(t_comp c, t_comp z, int *info, double *mouse_loc)
{
	static double	old_loc[2];
	double			tmp;
	int				i;

	i = -1;
	if (info[9] == 0)
	{
		old_loc[0] = mouse_loc[0];
		old_loc[1] = mouse_loc[1];
	}
	c.real = (double)3 / info[0] * (old_loc[0] - info[0] / 2);
	c.imag = (double)2 / info[1] * (old_loc[1] - info[1] / 2);
	while (++i < info[6])
	{
		if (z.real * z.real + z.imag * z.imag > 4)
		{
			ft_get_color(info, i, z, c);
			return (0);
		}
		tmp = z.real * z.real - z.imag * z.imag + c.real;
		z.imag = 2 * z.real * z.imag + c.imag;
		z.real = tmp;
	}
	info[2] = 0xffffff;
	return (0);
}

int		ft_burning_ship(t_comp c, t_comp z, int *info)
{
	double	tmp;
	int		i;
	int		out;

	i = -1;
	out = 0;
	while (++i < info[6])
	{
		if (z.real < 0)
			z.real *= -1;
		if (z.imag < 0)
			z.imag *= -1;
		if (z.real * z.real + z.imag * z.imag > 4 && (out = 1))
			break ;
		tmp = z.real * z.real - z.imag * z.imag + c.real;
		z.imag = 2 * (z.real * z.imag) + c.imag;
		z.real = tmp;
	}
	if (out && ft_get_color(info, i, z, c))
		return (1);
	if (info[10] == 5)
		info[2] = 0;
	return (0);
}
