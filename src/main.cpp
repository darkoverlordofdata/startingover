#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <cstdio>
#include <iostream>
#include <chrono>
#include <string>
#include <map>
#ifdef __EMSCRIPTEN__
#include <functional>
#include <emscripten.h>
#endif
#include "components.h"
#include "game.h"
/**
 */
inline void logSDLError(std::ostream &os, const std::string &msg){
	os << msg << " error: " << SDL_GetError() << std::endl;
}

#ifdef __EMSCRIPTEN__
std::function<void()> loop;
void main_loop() { loop(); }
#endif

int main(int argc, char** argv){



    using namespace std::chrono;
    std::srand(std::time(0));    

    auto title = "Shmupwarz";
    auto width = 720;
    auto height = 600;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER | SDL_INIT_AUDIO)) {
        logSDLError(std::cout, "Init SDL");
        return 0;
    }
    auto window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
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

