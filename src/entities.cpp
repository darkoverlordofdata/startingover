/** 
 * Entity Factory
 */
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdio>
#include <map>
#include <string>
#include <iostream>
#include <ctime>
#include <chrono>
#include <cmath>
#if (USE_GRESOURCE)
#include <glib.h>
#include <glib-object.h>
#include <gio/gio.h>
#endif
#include "components.h"
#include "game.h"
#include "systems.h"
#include "entities.h"

int uniqueId = 0;

/**
 * getResource
 *
 * gets resource from gio resource compiler 
 *
 * @param name
 * @return surface
 */
SDL_Surface* getResource(std::string name) {
    #if (USE_GRESOURCE)
    GError *err;
    const std::string path = "/darkoverlordofdata/shmupwarz/images/"+name;
    auto ptr = g_resources_lookup_data(path.c_str(), G_RESOURCE_LOOKUP_FLAGS_NONE, &err);
    if (ptr == nullptr) {
        return nullptr;
    } else {
        auto size = g_bytes_get_size(ptr);
        auto data = g_bytes_get_data(ptr, nullptr);
        auto raw = SDL_RWFromMem((void*)data, size);
        auto surface = IMG_LoadPNG_RW(raw);
        g_bytes_unref(ptr);
        return surface;
    }
    #else
    const std::string path = "assets/images/"+name;
    return IMG_Load(path.c_str());
    #endif
}

void createBackground(SDL_Renderer* renderer, std::vector<Entity>* entities, std::string path){
    entities->emplace_back(uniqueId++, "background", true);
    initBackground(renderer, &entities->back(), path);
}

void initBackground(SDL_Renderer* renderer, Entity* entity, std::string path) {
    entity->actor = Actor::BACKGROUND;
    entity->category = Category::BACKGROUND;
    auto surface = getResource("background.png");
    entity->sprite.texture = SDL_CreateTextureFromSurface(renderer, surface);
    const auto scale = 2.0;
    entity->sprite.width = surface->w*scale;
    entity->sprite.height = surface->h*scale;
    entity->bounds.w = surface->w*scale; 
    entity->bounds.h = surface->h*scale; 
    entity->scale.x = scale;
    entity->scale.y = scale;
    SDL_FreeSurface(surface);

}

Entity* createPlayer(SDL_Renderer* renderer, std::vector<Entity>* entities, std::string path) {
    entities->emplace_back(uniqueId++, "player", true);
    initPlayer(renderer, &entities->back(), path);
    return &entities->back();
}

void initPlayer(SDL_Renderer* renderer, Entity* entity, std::string path) {
    entity->actor = Actor::PLAYER;
    entity->category = Category::PLAYER;
    auto surface = getResource("spaceshipspr.png");
    entity->sprite.texture = SDL_CreateTextureFromSurface(renderer, surface);

    auto scale = 1.0;
    entity->sprite.width = surface->w*scale;
    entity->sprite.height = surface->h*scale;
    entity->bounds.w = surface->w*scale; 
    entity->bounds.h = surface->h*scale; 
    entity->scale.x = scale;
    entity->scale.y = scale;
    SDL_FreeSurface(surface);
}

void createBullet(SDL_Renderer* renderer, std::vector<Entity>* entities, std::string path) {
    entities->emplace_back(uniqueId++, "bullet", false);
    initBullet(renderer, &entities->back(), path);
}
void initBullet(SDL_Renderer* renderer, Entity* entity, std::string path) {
    entity->actor = Actor::BULLET;
    entity->category = Category::BULLET;
    auto surface = getResource("bullet.png");
    entity->sprite.texture = SDL_CreateTextureFromSurface(renderer, surface);

    auto scale = 1.0;
    entity->sprite.width = surface->w*scale;
    entity->sprite.height = surface->h*scale;
    entity->bounds.w = surface->w*scale; 
    entity->bounds.h = surface->h*scale; 
    entity->scale.x = scale;
    entity->scale.y = scale;
    SDL_FreeSurface(surface);
}

void refreshBullet(Entity* entity, int x, int y) {
    entity->position.x = x;
    entity->position.y = y;
    entity->expires = 1.0;
    entity->sound = Effect::PEW;
    entity->health = new Health(2, 2);
    entity->tint = new Color(0xd2, 0xfa, 0x00, 0xffa);
    entity->velocity = new Vector2d(0, -800);
    entity->active = true;
}

void createEnemy1(SDL_Renderer* renderer, std::vector<Entity>* entities, std::string path){
    entities->emplace_back(uniqueId++, "enemy1", false);
    initEnemy1(renderer, &entities->back(), path);
}
void initEnemy1(SDL_Renderer* renderer, Entity* entity, std::string path) {
    entity->actor = Actor::ENEMY1;
    entity->category = Category::ENEMY;
    auto surface = getResource("enemy1.png");
    entity->sprite.texture = SDL_CreateTextureFromSurface(renderer, surface);

    auto scale = 1.0;
    entity->sprite.width = surface->w*scale;
    entity->sprite.height = surface->h*scale;
    entity->bounds.w = surface->w*scale; 
    entity->bounds.h = surface->h*scale; 
    entity->scale.x = scale;
    entity->scale.y = scale;
    SDL_FreeSurface(surface);
}
void refreshEnemy1(Entity* entity, int x, int y) {
    entity->position.x = x;
    entity->position.y = y;
    entity->health = new Health(10, 10);
    entity->velocity = new Vector2d(0, 40);
    entity->active = true;
}

void createEnemy2(SDL_Renderer* renderer, std::vector<Entity>* entities, std::string path){
    entities->emplace_back(uniqueId++, "enemy2", false);
    initEnemy2(renderer, &entities->back(), path);
}
void initEnemy2(SDL_Renderer* renderer, Entity* entity, std::string path) {
    entity->actor = Actor::ENEMY2;
    entity->category = Category::ENEMY;
    auto surface = getResource("enemy2.png");
    entity->sprite.texture = SDL_CreateTextureFromSurface(renderer, surface);

    auto scale = 1.0;
    entity->sprite.width = surface->w*scale;
    entity->sprite.height = surface->h*scale;
    entity->bounds.w = surface->w*scale; 
    entity->bounds.h = surface->h*scale; 
    entity->scale.x = scale;
    entity->scale.y = scale;
    SDL_FreeSurface(surface);
}
void refreshEnemy2(Entity* entity, int x, int y){
    entity->position.x = x;
    entity->position.y = y;
    entity->health = new Health(20, 20);
    entity->velocity = new Vector2d(0, 30);
    entity->active = true;
}
void createEnemy3(SDL_Renderer* renderer, std::vector<Entity>* entities, std::string path){
    entities->emplace_back(uniqueId++, "enemy3", false);
    initEnemy3(renderer, &entities->back(), path);
}
void initEnemy3(SDL_Renderer* renderer, Entity* entity, std::string path) {
    entity->actor = Actor::ENEMY3;
    entity->category = Category::ENEMY;
    auto surface = getResource("enemy3.png");
    entity->sprite.texture = SDL_CreateTextureFromSurface(renderer, surface);

    auto scale = 1.0;
    entity->sprite.width = surface->w*scale;
    entity->sprite.height = surface->h*scale;
    entity->bounds.w = surface->w*scale; 
    entity->bounds.h = surface->h*scale; 
    entity->scale.x = scale;
    entity->scale.y = scale;
    SDL_FreeSurface(surface);
}
void refreshEnemy3(Entity* entity, int x, int y){
    entity->position.x = x;
    entity->position.y = y;
    entity->health = new Health(60, 60);
    entity->velocity = new Vector2d(0, 20);
    entity->active = true;
}

void createExplosion(SDL_Renderer* renderer, std::vector<Entity>* entities, std::string path){
    entities->emplace_back(uniqueId++, "explosion", false);
    initExplosion(renderer, &entities->back(), path);
}
void initExplosion(SDL_Renderer* renderer, Entity* entity, std::string path) {
    entity->actor = Actor::EXPLOSION;
    entity->category = Category::EXPLOSION;
    auto surface = getResource("explosion.png");
    entity->sprite.texture = SDL_CreateTextureFromSurface(renderer, surface);

    auto scale = 0.6;
    entity->sprite.width = surface->w*scale;
    entity->sprite.height = surface->h*scale;
    entity->bounds.w = surface->w*scale; 
    entity->bounds.h = surface->h*scale; 
    entity->scale.x = scale;
    entity->scale.y = scale;
    SDL_FreeSurface(surface);
}
void refreshExplosion(Entity* entity, int x, int y){
    auto scale = 0.6;
    entity->position.x = x;
    entity->position.y = y;
    entity->bounds.x = x; 
    entity->bounds.y = y; 
    entity->scale.x = scale;
    entity->scale.y = scale;
    entity->sound = Effect::ASPLODE;
    entity->tween = new Tween(scale/100.0, scale, -3, false, true);
    entity->tint = new Color(0xd2, 0xfa, 0xd2, 0xfa);
    entity->expires = 0.2;
    entity->active = true;
}
void createBang(SDL_Renderer* renderer, std::vector<Entity>* entities, std::string path){
    entities->emplace_back(uniqueId++, "bang", false);
    initBang(renderer, &entities->back(), path);
}
void initBang(SDL_Renderer* renderer, Entity* entity, std::string path) {
    entity->actor = Actor::BANG;
    entity->category = Category::EXPLOSION;
    auto surface = getResource("explosion.png");
    entity->sprite.texture = SDL_CreateTextureFromSurface(renderer, surface);

    auto scale = 0.4;
    entity->sprite.width = surface->w*scale;
    entity->sprite.height = surface->h*scale;
    entity->bounds.w = surface->w*scale; 
    entity->bounds.h = surface->h*scale; 
    entity->scale.x = scale;
    entity->scale.y = scale;
    SDL_FreeSurface(surface);
}
void refreshBang(Entity* entity, int x, int y){
    auto scale = 0.4;
    entity->position.x = x;
    entity->position.y = y;
    entity->bounds.x = x; 
    entity->bounds.y = y; 
    entity->scale.x = scale;
    entity->scale.y = scale;
    entity->sound = Effect::SMALLASPLODE;
    entity->tween = new Tween(scale/100.0, scale, -3, false, true);
    entity->tint = new Color(0xd2, 0xfa, 0xd2, 0xfa);
    entity->expires = 0.2;
    entity->active = true;
}
void createParticle(SDL_Renderer* renderer, std::vector<Entity>* entities, std::string path){
    entities->emplace_back(uniqueId++, "particle", false);
    initParticle(renderer, &entities->back(), path);
}
void initParticle(SDL_Renderer* renderer, Entity* entity, std::string path) {
    entity->actor = Actor::PARTICLE;
    entity->category = Category::PARTICLE;
    auto surface = getResource("star.png");
    entity->sprite.texture = SDL_CreateTextureFromSurface(renderer, surface);

    auto scale = 1.0;
    entity->sprite.width = surface->w*scale;
    entity->sprite.height = surface->h*scale;
    entity->bounds.w = surface->w*scale; 
    entity->bounds.h = surface->h*scale; 
    entity->scale.x = scale;
    entity->scale.y = scale;
    SDL_FreeSurface(surface);
}

// var radians:number = Math.random()*Tau
// var magnitude:number = MathUtils.random(200)
// var velocityX = magnitude * Math.cos(radians)
// var velocityY = magnitude * Math.sin(radians)

void refreshParticle(Entity* entity, int x, int y){
    auto Tau = 6.28318;
    // auto radians = ((double)std::rand()/1.0) * Tau;
    // auto magnitude = std::rand() % 100 + 50;
    // auto velocityX = magnitude * cos(radians);
    // auto velocityY = magnitude * sin(radians);
    auto radians = ((double)std::rand()/(double)1.0) * (double)Tau;
    auto magnitude = std::rand() % 100 + 50;
    auto velocityX = magnitude * cos(radians);
    auto velocityY = magnitude * sin(radians);
    auto scale = (double)(std::rand() % 10) / 10.0;
    // std::cout << velocityX << ", " << velocityY << "\n" << std::flush;
    entity->position.x = x;
    entity->position.y = y;
    entity->bounds.x = x; 
    entity->bounds.y = y; 
    entity->scale.x = scale;
    entity->scale.y = scale;
    entity->velocity = new Vector2d(velocityX, velocityY);
    entity->tint = new Color(0xfa, 0xfa, 0xd2, 0xff);
    entity->expires = 0.75;
    entity->active = true;
}

