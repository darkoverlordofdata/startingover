#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <cstdio>
#include <map>
#include <string>
#include <iostream>
#include <ctime>
#include <chrono>
#include <list>
#include <algorithm>
#include <random>
#include "components.h"
#include "entities.h"
#include "systems.h"
#include "game.h"


Game::Game(std::string t, int width, int height, SDL_Window* w, SDL_Renderer* r)
    : title(t), width(width), height(height), window(w), renderer(r), frameSkip(0), running(0) {}

Game::~Game() {
    stop();
}

int Game::getKey(int key) {
    if (key > 255) return 0;
    return keys[key];
}
int Game::isRunning() {
    return running;
}

void Game::start() {
    init();
    systems = new Systems(this);
    running = 1;
}

void Game::draw(int fps, SDL_Rect *clip) {
    if (this->fps != fps) fpsChanged(fps);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    for (int i=0; i<entities.size(); i++) {
        if (!entities[i].active) continue;
        if (entities[i].category != Category::BACKGROUND) {
            entities[i].bounds.w = entities[i].sprite.width * entities[i].scale.x;
            entities[i].bounds.h = entities[i].sprite.height * entities[i].scale.y;
            entities[i].bounds.x = entities[i].position.x - entities[i].bounds.w / 2;
            entities[i].bounds.y = entities[i].position.y - entities[i].bounds.h / 2;
        }
        if (entities[i].tint) {
            auto c = entities[i].tint.value();
            SDL_SetTextureColorMod(entities[i].sprite.texture, c->r, c->g, c->b);
        }
        SDL_RenderCopy(renderer, entities[i].sprite.texture, clip, &entities[i].bounds);
    }
    SDL_RenderPresent(renderer);
}

void Game::stop() {
}

void Game::fpsChanged(int fps) {
    char szFps[ 128 ];
    sprintf(szFps, "%s: %d", title.c_str(), fps);
    SDL_SetWindowTitle(window, szFps);
    this->fps = fps;
}

void Game::quit() {
    running = 0;
}

void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        switch (event.type) {
            case SDL_QUIT:    
                quit();            
                break;
            case SDL_KEYDOWN: 
                keys[event.key.keysym.sym] = 1;
                break;
            case SDL_KEYUP:   
                keys[ event.key.keysym.sym ] = 0;
                break;
            case SDL_MOUSEBUTTONDOWN:
                mouseDown = 1;
                break;
            case SDL_MOUSEBUTTONUP:
                mouseDown = 0;
                break;
            case SDL_MOUSEMOTION:
                mouseX = event.motion.x;
                mouseY = event.motion.y;
                break;
        }
    }    
}

void Game::update(double delta) {

    this->delta = delta;

    systems->spawnSystem(player);
    for (int i=0; i<entities.size(); i++) systems->collisionSystem(&entities[i]);
    for (int i=0; i<entities.size(); i++) systems->entitySystem(&entities[i]);
    systems->inputSystem(player);
    // for (int i=0; i<entities.size(); i++) systems->soundSystem(&entities[i]);
    for (int i=0; i<entities.size(); i++) systems->physicsSystem(&entities[i]);
    for (int i=0; i<entities.size(); i++) systems->expireSystem(&entities[i]);
    for (int i=0; i<entities.size(); i++) systems->tweenSystem(&entities[i]);
    for (int i=0; i<entities.size(); i++) systems->removeSystem(&entities[i]);

}

void Game::init() {
	//const auto path = getResourcePath("images");
    const auto path = "assets/images/";
    entities.reserve(141);
    createBackground(renderer, &entities, path);
    for (int i=0; i<12; i++)    createBullet(renderer, &entities, path);
    for (int i=0; i<15; i++)    createEnemy1(renderer, &entities, path);
    for (int i=0; i<5; i++)     createEnemy2(renderer, &entities, path);
    for (int i=0; i<4; i++)     createEnemy3(renderer, &entities, path);
    for (int i=0; i<10; i++)    createExplosion(renderer, &entities, path);
    for (int i=0; i<12; i++)    createBang(renderer, &entities, path);
    for (int i=0; i<100; i++)   createParticle(renderer, &entities, path);
    player = createPlayer(renderer, &entities, path);
}

