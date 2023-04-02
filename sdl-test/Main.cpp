#include <SDL.h>
#include <stdio.h>

const int SCREEN_HEIGHT = 480;
const int SCREEN_WIDTH = 640;

bool init();
bool loadMedia();
void close();

SDL_Window* g_window = nullptr;
SDL_Surface* g_windowSurface = nullptr;
SDL_Surface* g_imageSurface = nullptr;

int main(int argc, char* args[])
{
	if(!init())
	{
		printf("Failed to initialize.\n");
	}
	else
	{
		if (!loadMedia())
			printf("Failed to load media.\n");
		else
		{
			SDL_BlitSurface(g_imageSurface, NULL, g_windowSurface, NULL);
			SDL_UpdateWindowSurface(g_window);

			SDL_Event e;
			bool quit = false;
			while (quit == false)
			{
				while (SDL_PollEvent(&e))
					if (e.type == SDL_QUIT) quit = true;
			}
		}
	}
	close();

	return 0;
}

bool init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		printf("SDL was not initialized. SDL_Error: %s\n", SDL_GetError());
	else
	{
		g_window = SDL_CreateWindow("SDL Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if(!g_window)
		{
			printf("Window was not created. SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			g_windowSurface = SDL_GetWindowSurface(g_window);
		}
	}

	return success;
}

bool loadMedia()
{
	bool success = true;

	g_imageSurface = SDL_LoadBMP("G:\\GitHub\\sdl-test\\snail.bmp");

	if (!g_imageSurface)
	{
		printf("Image was not loaded. SDL_Error: %s\n", SDL_GetError());
		success = false;
	}

	return success;
}

void close()
{
	SDL_FreeSurface(g_windowSurface);
	g_windowSurface = nullptr;

	SDL_DestroyWindow(g_window);
	g_window = nullptr;

	SDL_Quit();
}