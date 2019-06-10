#ifndef SYSTEMS_H
#define SYSTEMS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

class Game;

class Systems {
public:
    Systems(Game* game);
    ~Systems();

    void inputSystem(Entity* entity);
    void soundSystem(Entity* entity);
    void physicsSystem(Entity* entity);
    void expireSystem(Entity* entity);
    void tweenSystem(Entity* entity);
    void removeSystem(Entity* entity);
    void spawnSystem(Entity* entity);
    void entitySystem(Entity* entity);
    void collisionSystem(Entity* entity);

    double spawnEnemy(double delta, double t, int enemy);
    bool intersects(SDL_Rect* r1, SDL_Rect* r2);
    void handleCollision(Entity* a, Entity* b);

private:
    Game* game;
    double FireRate = 0.1;
    double timeToFire = 0.0;
    double enemyT1 = 1.0;
    double enemyT2 = 4.0;
    double enemyT3 = 6.0;
    Mix_Chunk* pew;
    Mix_Chunk* asplode;
    Mix_Chunk* smallasplode;
};

#endif
