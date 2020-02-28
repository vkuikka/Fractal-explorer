/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 14:04:26 by vkuikka           #+#    #+#             */
/*   Updated: 2020/01/22 14:04:50 by vkuikka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_pixel_put_img(char *pixel_color, int *info, int *xy, int color)
{
	int		spot;

	if (xy[0] && xy[1] && xy[0] < info[0] && xy[1] < info[1])
	{
		spot = xy[1] * info[4] + xy[0] * 4;
		pixel_color[spot] = (unsigned char)B_VAL(color);
		pixel_color[spot + 1] = (unsigned char)G_VAL(color);
		pixel_color[spot + 2] = (unsigned char)R_VAL(color);
		pixel_color[spot + 3] = 0;
	}
}

void	ft_theme_one(int i, int *info)
{
	if (i <= 15)
		info[2] += B_HEX(i * i);
	else if (i <= 40)
	{
		info[2] -= B_HEX((i - 15) * 10);
		info[2] += G_HEX((i - 15) * 10);
	}
	else if (i <= 168)
	{
		info[2] -= G_HEX((i - 40) * 2);
		info[2] += R_HEX((i - 40) * 2);
	}
	else
		info[2] = 0xff0000;
}

void	ft_theme_two(int i, int *info)
{
	if (i <= 15)
	{
		info[2] += R_HEX(i * i);
		info[2] += G_HEX(i * i);
	}
	else if (i <= 40)
	{
		info[2] = 0xffff00;
		info[2] -= R_HEX((i - 15) * 10);
		info[2] += B_HEX((i - 15) * 10);
	}
	else if (i <= 167)
	{
		info[2] = 0x00ffff;
		info[2] -= B_HEX((i - 40) * 2);
	}
	else
		info[2] = 0x00ff00;
}

int		ft_get_color(int *info, int i, t_comp x, t_comp y)
{
	if (info[10] == 5)
		info[2] += i - info[7];
	if (info[10] == 4)
		info[2] = x.real * 21000;
	if (info[10] == 3)
		info[2] = (x.real - y.real) / (x.imag - y.imag);
	if (info[10] == 1)
		ft_theme_one(i, info);
	if (info[10] == 2)
		ft_theme_two(i, info);
	return (1);
}
