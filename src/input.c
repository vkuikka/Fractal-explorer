#include "fractol.h"

void	input(t_window *window, t_settings *settings)
{
	SDL_Event		event;
	static t_vec2	mouse_pos = {0, 0};
	static int		mouse_down;
	static int		zoom_down;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			mouse_down = 1;
			mouse_pos.x = event.motion.x;
			mouse_pos.y = event.motion.y;
		}
		else if (event.type == SDL_MOUSEBUTTONUP)
		{
			mouse_down = 0;
			mouse_pos = (t_vec2){0, 0};
		}
		else if (event.type == SDL_MOUSEMOTION && mouse_down)
		{
			settings->pos.x += (mouse_pos.x - event.motion.x) / settings->scale;
			settings->pos.y += (mouse_pos.y - event.motion.y) / settings->scale;
			mouse_pos.x = event.motion.x;
			mouse_pos.y = event.motion.y;
		}
		else if (event.type == SDL_QUIT || event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			exit(1);
		else if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
		{
			if (event.key.keysym.scancode == SDL_SCANCODE_M)
				settings->mouse_mode = !settings->mouse_mode;
			else if (event.key.keysym.scancode == SDL_SCANCODE_EQUALS)
				settings->iters++;
			else if (event.key.keysym.scancode == SDL_SCANCODE_MINUS && settings->iters > 0)
				settings->iters--;
			else if (event.key.keysym.scancode == SDL_SCANCODE_RIGHTBRACKET)
				zoom_down = 1;
			else if (event.key.keysym.scancode == SDL_SCANCODE_LEFTBRACKET)
				zoom_down = -1;
			else if (event.key.keysym.scancode == SDL_SCANCODE_1)
				settings->mode = MANDELBROT;
			else if (event.key.keysym.scancode == SDL_SCANCODE_2)
				settings->mode = JULIA;
			else if (event.key.keysym.scancode == SDL_SCANCODE_3)
				settings->mode = BURNING_SHIP;
			else if (event.key.keysym.scancode == SDL_SCANCODE_COMMA && settings->theme > 2)
				settings->theme--;
			else if (event.key.keysym.scancode == SDL_SCANCODE_PERIOD && settings->theme < 10)
				settings->theme++;
		}
		else if (event.type == SDL_KEYUP && event.key.repeat == 0)
		{
			if (event.key.keysym.scancode == SDL_SCANCODE_RIGHTBRACKET)
				zoom_down = 0;
			else if (event.key.keysym.scancode == SDL_SCANCODE_LEFTBRACKET)
				zoom_down = 0;
		}
	}
	if (zoom_down == 1)
		settings->scale *= 1.1;
	if (zoom_down == -1)
		settings->scale /= 1.1;
}
