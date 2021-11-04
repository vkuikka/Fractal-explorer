#include "fractol.h"

static void	wait_threads(SDL_Thread *threads[THREAD_AMOUNT], int thread_amount)
{
	int	ret;
	int	i;

	i = 0;
	while (i < thread_amount)
	{
		SDL_WaitThread(threads[i], &ret);
		i++;
	}
}

static void	create_threads(t_settings *settings, t_window *window)
{
	SDL_Thread	*threads[THREAD_AMOUNT];
	t_rthread	thread_data[THREAD_AMOUNT];
	int			i;

	i = 0;
	while (i < settings->thread_amount)
	{
		thread_data[i].id = i;
		thread_data[i].settings = settings;
		thread_data[i].window = window;
		threads[i] = SDL_CreateThread(fractal_thread, "render",
				(void *)&thread_data[i]);
		i++;
	}
	wait_threads(threads, settings->thread_amount);
}

void	render(t_window *window, t_settings *settings)
{
	if (SDL_LockTexture(window->texture, NULL,
			(void **)&window->frame_buffer, &(int){0}) != 0)
		ft_error("failed to lock texture\n");
	ft_memset(window->frame_buffer, 0, RES_X * RES_Y * sizeof(int));

	create_threads(settings, window);

	SDL_UnlockTexture(window->texture);
	SDL_RenderCopy(window->SDLrenderer, window->texture, NULL, NULL);
	SDL_RenderPresent(window->SDLrenderer);
	SDL_RenderClear(window->SDLrenderer);
}

int			main()
{
	t_window	*window;
	t_settings	settings;

	init_window(&window);
	init_settings(&settings);
	while (1)
	{
		settings.color = 0;
		input(window, &settings);
		render(window, &settings);
	}
}
