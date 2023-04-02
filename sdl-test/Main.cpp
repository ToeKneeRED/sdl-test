#include <SDL.h>
#include <stdio.h>
#include <string>

const int SCREEN_HEIGHT = 480;
const int SCREEN_WIDTH = 640;

enum KeyPressSurfaces
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

bool init();
bool loadMedia();
void close();
SDL_Surface* loadSurface(std::string path);

SDL_Window* g_window = nullptr;
SDL_Surface* g_windowSurface = nullptr;
SDL_Surface* g_imageSurface = nullptr;
SDL_Surface* g_currentSurface = nullptr;
SDL_Surface* g_keyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];
SDL_Event e;
bool quit = false;

int main(int argc, char* args[])
{
	// Initialize and load media
	if(!init())
	{
		printf("Failed to initialize.\n");
	}
	else
	{
		if (!loadMedia())
		{
			printf("Failed to load media.\n");
		}
		else
		{
			g_currentSurface = g_keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];

			while (!quit)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					else if (e.type == SDL_KEYDOWN)
					{
						switch (e.key.keysym.sym)
						{
						case SDLK_UP:
							g_currentSurface = g_keyPressSurfaces[KEY_PRESS_SURFACE_UP];
							break;

						case SDLK_DOWN:
							g_currentSurface = g_keyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
							break;

						case SDLK_LEFT:
							g_currentSurface = g_keyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
							break;

						case SDLK_RIGHT:
							g_currentSurface = g_keyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
							break;

						default:
							g_currentSurface = g_keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
							break;
						}
					}
				}

				SDL_BlitSurface(g_currentSurface, nullptr, g_windowSurface, nullptr);
				SDL_UpdateWindowSurface(g_window);
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
	//Loading success flag
	bool success = true;

	g_keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface(R"(../snail.bmp)");
	if (!g_keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT])
	{
		printf("Failed to load default image!\n");
		success = false;
		SDL_SetWindowResizable(g_window, SDL_TRUE);
		SDL_SetWindowSize(g_window, loadSurface(R"(../snail.bmp)")->w, loadSurface(R"(../snail.bmp)")->h);
	}

	g_keyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface(R"(../toekneered.bmp)");
	if (!g_keyPressSurfaces[KEY_PRESS_SURFACE_UP])
	{
		printf("Failed to load up image!\n");
		success = false;
		SDL_SetWindowResizable(g_window, SDL_TRUE);
		SDL_SetWindowSize(g_window, loadSurface(R"(../toekneered.bmp)")->w, loadSurface(R"(../toekneered.bmp)")->h);
	}

	g_keyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface(R"(../toekneered2.bmp)");
	if (!g_keyPressSurfaces[KEY_PRESS_SURFACE_DOWN])
	{
		printf("Failed to load down image!\n");
		success = false;
		SDL_SetWindowResizable(g_window, SDL_TRUE);
		SDL_SetWindowSize(g_window, loadSurface(R"(../toekneered2.bmp)")->w, loadSurface(R"(../toekneered2.bmp)")->h);
	}

	g_keyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface(R"(../toekneered3.bmp)");
	if (!g_keyPressSurfaces[KEY_PRESS_SURFACE_LEFT])
	{
		printf("Failed to load left image!\n");
		success = false;
		SDL_SetWindowResizable(g_window, SDL_TRUE);
		SDL_SetWindowSize(g_window, loadSurface(R"(../toekneered3.bmp)")->w, loadSurface(R"(../toekneered3.bmp)")->h);
	}

	g_keyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface(R"(../toekneered4.bmp)");
	if (!g_keyPressSurfaces[KEY_PRESS_SURFACE_RIGHT])
	{
		printf("Failed to load right image!\n");
		success = false;
		SDL_SetWindowResizable(g_window, SDL_TRUE);
		SDL_SetWindowSize(g_window, loadSurface(R"(../toekneered4.bmp)")->w, loadSurface(R"(../toekneered4.bmp)")->h);
	}
	return success;
}

SDL_Surface* loadSurface(std::string path)
{
	SDL_Surface* tempSurface = SDL_LoadBMP(path.c_str());

	if (!tempSurface)
		printf("Unable to load image %s. SDL Error: %s\n", path.c_str(), SDL_GetError());

	return tempSurface;
}

void close()
{
	SDL_FreeSurface(g_windowSurface);
	g_windowSurface = nullptr;

	SDL_DestroyWindow(g_window);
	g_window = nullptr;

	SDL_Quit();
}