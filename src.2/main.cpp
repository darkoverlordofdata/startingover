#include "game.h"
#ifdef __EMSCRIPTEN__
#include <functional>
#include <emscripten.h>
#endif
/**
 */
inline void logSDLError(std::ostream &os, const std::string &msg){
	os << msg << " error: " << SDL_GetError() << std::endl;
}

void checkSDLError(int line = -1)
{
#ifndef NDEBUG
	const char *error = SDL_GetError();
	if (*error != '\0')
	{
		printf("SDL Error: %s\n", error);
		if (line != -1)
			printf(" + line: %i\n", line);
		SDL_ClearError();
	}
#endif
}

#ifdef __EMSCRIPTEN__
std::function<void()> loop;
void main_loop() { loop(); }
#endif

int main(int argc, char** argv){



    using namespace std::chrono;
    std::srand(std::time(0));    

    auto title = "Shmupwarz";
    auto width = 900;
    auto height = 600;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER | SDL_INIT_AUDIO)) {
        logSDLError(std::cout, "Init SDL");
        return 0;
    }

    /* Request opengl 3.3 context.
     * SDL doesn't have the ability to choose which profile at this time of writing,
     * but it should default to the core profile */
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    /* Turn on double buffering with a 24bit Z buffer.
     * You may need to change this to 16 or 32 for your system */
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    SDL_GLContext maincontext; /* Our opengl context handle */

    auto window = SDL_CreateWindow(title, 
                    SDL_WINDOWPOS_CENTERED, 
                    SDL_WINDOWPOS_CENTERED, 
                    width, 
                    height, 
                    SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    maincontext = SDL_GL_CreateContext(window);
    checkSDLError(__LINE__);

    auto renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    TTF_Init();
    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        logSDLError(std::cout, "Init image");
    }
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) == -1) {
        logSDLError(std::cout, "Init mixer");
    }

    auto delta = 0.0;
    auto d = 0.0;
    auto fps = 60;
    auto k = 0;
    auto t = 0.0;
    auto k2 = 0;
    auto game = new Game(title, width, height, window, renderer);
    auto mark1 = high_resolution_clock::now();

    game->start();

#ifdef __EMSCRIPTEN__
    loop = [&] 
    {
#else
    while (game->isRunning()) {
#endif
        auto mark2 = high_resolution_clock::now();
        delta = ((double) duration_cast<microseconds>(mark2 - mark1).count()) / 1000000.0;
        mark1 = mark2;
        k += 1;
        d += delta;
        if (d >= 1.0) {
            fps = k;
            k = 0;
            d = 0;
        }
        game->handleEvents();
        if (game->getKey(SDLK_ESCAPE)) game->quit();
        
        auto m1 = high_resolution_clock::now();
        game->update(delta);
        auto m2 = high_resolution_clock::now();
        k2 = k2 +1;
        t += ((double) duration_cast<microseconds>(m2 - m1).count()) / 1000000.0;

        if (k2 >= 1000) {
	        std::cout << t/1000 << "\n" << std::flush;
            k2 = 0;
            t = 0.0;
        }
        game->draw(fps);
    }
#ifdef __EMSCRIPTEN__
    ;
    emscripten_set_main_loop(main_loop, 0, true);
#endif
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
	IMG_Quit();
    SDL_Quit();
    delete game;
    return 0;
}

