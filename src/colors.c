/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 14:04:26 by vkuikka           #+#    #+#             */
/*   Updated: 2021/10/21 02:41:25 by vkuikka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	theme_one(int i, int *color)
{
	if (i <= 15)
		*color += B_HEX(i * i);
	else if (i <= 40)
	{
		*color -= B_HEX((i - 15) * 10);
		*color += G_HEX((i - 15) * 10);
	}
	else if (i <= 168)
	{
		*color -= G_HEX((i - 40) * 2);
		*color += R_HEX((i - 40) * 2);
	}
	else
		*color = 0xff0000;
}

void	theme_two(int i, int *color)
{
	if (i <= 15)
	{
		*color += R_HEX(i * i);
		*color += G_HEX(i * i);
	}
	else if (i <= 40)
	{
		*color = 0xffff00;
		*color -= R_HEX((i - 15) * 10);
		*color += B_HEX((i - 15) * 10);
	}
	else if (i <= 167)
	{
		*color = 0x00ffff;
		*color -= B_HEX((i - 40) * 2);
	}
	else
		*color = 0x00ff00;
}

int	themes(t_settings *s, int i, t_comp x, t_comp y)
{
	int	col;

	col = 0x000000ff;
	if (s->theme == 5)	// add color
		col = i - s->scale;
	if (s->theme == 4)
		col = x.real * 21000;
	if (s->theme == 3)
		col = (x.real - y.real) / (x.imag - y.imag);
	if (s->theme == 1)
		theme_one(i, &col);
	if (s->theme == 2)
		theme_two(i, &col);
	return (col);
}
