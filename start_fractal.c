/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_fractal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 20:10:30 by vkuikka           #+#    #+#             */
/*   Updated: 2020/03/12 20:01:23 by vkuikka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
**	Values in info array:
**
**	info[0] = resolution x
**	info[1] = resolution y
**	info[2] = pixel color
**	image info:
**		info[3] = bits per pixel
**		info[4] = size of line
**		info[5] = endian
**	info[6] = amount of iterations
**	info[7] = image scaler
**	info[8] = fractal code (1 = mandelbrot, 2 = julia 3 = burning ship)
**	info[9] = mouse mode (values are given by mlx_hook in main)
**	info[10] = color theme
*/

void	*ft_get_image(void **params, int *info, char **pixel_color, void *image)
{
	if (!image)
	{
		info[0] = 1500;
		info[1] = 1000;
		info[2] = 0xffffff;
		info[3] = 0;
		info[4] = 0;
		info[5] = 0;
		info[6] = 20;
		info[7] = 1;
		info[8] = 0;
		info[9] = 1;
		info[10] = 1;
		info[8] = !ft_strcmp(params[2], "mandelbrot") ? 1 : info[8];
		info[8] = !ft_strcmp(params[2], "julia") ? 2 : info[8];
		info[8] = !ft_strcmp(params[2], "burning_ship") ? 3 : info[8];
	}
	if (image)
		mlx_destroy_image(params[0], image);
	if (!(image = mlx_new_image(params[0], info[0], info[1])))
		ft_stop(2);
	*pixel_color = mlx_get_data_addr(image, &info[3], &info[4], &info[5]);
	return (image);
}

void	ft_get_info(int key, int *info, double *location)
{
	if (key == 53)
		exit(1);
	if (key == -1000 && (location[0] = 750))
		location[1] = 500;
	if (key == 126 && info[10] < 10)
		info[10]++;
	if (key == 125 && info[10] > 1)
		info[10]--;
	if (key == 123 && info[6] > 1)
		info[6]--;
	if (key == 124)
		info[6]++;
	if (key == 5 && info[7] > 1)
		info[7] /= 2;
	if (key == 4 && info[7] < 1000000)
		info[7] *= 2;
}

int		main_fractal(int key, void **params, int x, int y)
{
	static int		*info = NULL;
	static void		*image = NULL;
	static char		*pixel_colors = NULL;
	static double	*loc;
	static int		*xy;

	if (!info)
	{
		if (!(loc = (double *)malloc(sizeof(double) * 2)) ||
			!(info = (int *)malloc(sizeof(int) * 11)) ||
			!(xy = (int *)malloc(sizeof(int) * 2)))
			ft_stop(0);
		image = ft_get_image(params, info, &pixel_colors, image);
		ft_get_info(-1000, info, loc);
	}
	info[9] = *(int *)params[3];
	if ((info[9] == 2 || info[9] == 0) && key != 4 && key != 5 && (loc[0] = x))
		loc[1] = y;
	else if (info[9] == 1 && (loc[0] += (double)x / info[7]))
		loc[1] += (double)y / info[7];
	ft_get_info(key, info, loc);
	if (key == 123 || key == 124)
		image = ft_get_image(params, info, &pixel_colors, image);
	ft_fractal(info, pixel_colors, xy, loc);
	return (mlx_put_image_to_window(params[0], params[1], image, 0, 0));
}
