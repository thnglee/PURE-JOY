#include "game.h"
#undef main

const int WIDTH = 1600;
const int HEIGHT = 900;
Game* game = nullptr;

int main(int argc, const char* argv[]) {

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
	// 1000 miliseconds / 10 frames = 100 mili per frame
	// 1000 miliseconds / 60 frames = 16 mili per frame
	// 1000 miliseconds / 120 frames = 8 mili per frame

	Uint32 frameStart;
	int frameTime;

	game = new Game();
	game->init("PURE JOY", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, false);

	while (game->running())
	{ 	
		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;
		// know how long frame has taken
		if (frameDelay > frameTime) {
			// if frameDelay longer than frameTime, it'll continue the delay process
			SDL_Delay(frameDelay - frameTime);
		} // each frame delays for 1000 / FPS milisecond no matter what.
	}
	game->clean();
	return 0;
}