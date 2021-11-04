#include "fractol.h"

void	input(t_window *window, t_settings *settings)
{
	SDL_Event		event;
	static int		mouse_is_down;
	static int		zoom_down;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_MOUSEBUTTONDOWN)
			mouse_is_down = 1;
		else if (event.type == SDL_MOUSEBUTTONUP)
			mouse_is_down = 0;
		else if (event.type == SDL_MOUSEMOTION)
		{
			if (mouse_is_down)
			{
				settings->pos.x += (settings->mouse.x - event.motion.x) / settings->scale;
				settings->pos.y += (settings->mouse.y - event.motion.y) / settings->scale;
			}
			settings->mouse.x = event.motion.x;
			settings->mouse.y = event.motion.y;
		}
		else if (event.type == SDL_QUIT || event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			exit(1);
		else if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
		{
			if (event.key.keysym.scancode == SDL_SCANCODE_M)
				settings->mouse_mode = !settings->mouse_mode;
			else if (event.key.keysym.scancode == SDL_SCANCODE_T)
			{
				if (settings->thread_amount == THREAD_AMOUNT)
					settings->thread_amount = 1;
				else
					settings->thread_amount = THREAD_AMOUNT;
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_9)
				settings->inside_color = rand() % 0xffffff;
			else if (event.key.keysym.scancode == SDL_SCANCODE_0)
			{
				if (settings->inside_color == 0)
					settings->inside_color = 0xffffff;
				else
					settings->inside_color = 0;
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_1)
			{
				settings->mode = MANDELBROT;
				SDL_SetWindowTitle(window->SDLwindow, "MANDELBROT");
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_2)
			{
				settings->mode = JULIA;
				SDL_SetWindowTitle(window->SDLwindow, "JULIA");
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_3)
			{
				settings->mode = BURNING_SHIP;
				SDL_SetWindowTitle(window->SDLwindow, "BURNING SHIP");
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_COMMA && settings->theme > 1)
				settings->theme--;
			else if (event.key.keysym.scancode == SDL_SCANCODE_PERIOD && settings->theme < 10)
				settings->theme++;
			else if (event.key.keysym.scancode == SDL_SCANCODE_RIGHTBRACKET)
				zoom_down = 1;
			else if (event.key.keysym.scancode == SDL_SCANCODE_LEFTBRACKET)
				zoom_down = -1;
		}
		else if (event.type == SDL_KEYUP && event.key.repeat == 0)
		{
			if (event.key.keysym.scancode == SDL_SCANCODE_RIGHTBRACKET)
				zoom_down = 0;
			else if (event.key.keysym.scancode == SDL_SCANCODE_LEFTBRACKET)
				zoom_down = 0;
		}
		if (event.key.keysym.scancode == SDL_SCANCODE_EQUALS)
			settings->iters++;
		else if (event.key.keysym.scancode == SDL_SCANCODE_MINUS && settings->iters > 0)
			settings->iters--;
	}
	if (zoom_down == 1)
		settings->scale *= 1.1;
	if (zoom_down == -1)
		settings->scale /= 1.1;
}
