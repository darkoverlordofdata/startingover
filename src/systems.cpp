#include "systems.h"
#include "game.h"


Systems::Systems(Game* g): game(g) {
    pew = Mix_LoadWAV("assets/sounds/pew.wav");
    asplode = Mix_LoadWAV("assets/sounds/asplode.wav");
    smallasplode = Mix_LoadWAV("assets/sounds/smallasplode.wav");
}
Systems::~Systems(){}

void Systems::inputSystem(Entity* entity){
    entity->position.x = game->mouseX;
    entity->position.y = game->mouseY;
    if (game->getKey(122) || game->mouseDown) {
        timeToFire -= game->delta;
        if (timeToFire < 0.0) {
            game->bullets.emplace_back(entity->position.x - 27, entity->position.y + 2);
            game->bullets.emplace_back(entity->position.x + 27, entity->position.y + 2);
            timeToFire = FireRate;
        }
    }
}

void Systems::soundSystem(Entity* entity){
    if (entity->active && entity->sound) {
        switch(entity->sound.value()) {
            case Effect::PEW: 
                Mix_PlayChannelTimed(-1, pew, 0, 0);
                break;

            case Effect::ASPLODE: 
                Mix_PlayChannelTimed(-1, asplode, 0, 0);
                break;

            case Effect::SMALLASPLODE: 
                Mix_PlayChannelTimed(-1, smallasplode, 0, 0);
                break;
        }
    }
}

void Systems::physicsSystem(Entity* entity){
    if (entity->active && entity->velocity) {
        entity->position.x += entity->velocity.value()->x * game->delta;
        entity->position.y += entity->velocity.value()->y * game->delta;
    }
}

void Systems::expireSystem(Entity* entity){
    if (entity->active && entity->expires) {
        auto exp = entity->expires.value() - game->delta;
        entity->expires = exp;
        if (entity->expires.value() < 0) {
            entity->active = false;
        }
    }
}

void Systems::tweenSystem(Entity* entity){
    if (entity->active && entity->tween) {

        auto x = entity->scale.x + (entity->tween.value()->speed * game->delta);
        auto y = entity->scale.y + (entity->tween.value()->speed * game->delta);
        auto active = entity->tween.value()->active;


        if (x > entity->tween.value()->max) {
            x = entity->tween.value()->max;
            y = entity->tween.value()->max;
            active = false;
        } else if (x < entity->tween.value()->min) {
            x = entity->tween.value()->min;
            y = entity->tween.value()->min;
            active = false;
        }
        entity->scale.x = x; 
        entity->scale.y = y; 
        entity->tween = new Tween(entity->tween.value()->min, 
                                    entity->tween.value()->max, 
                                    entity->tween.value()->speed, 
                                    entity->tween.value()->repeat, active);
    }
}

void Systems::removeSystem(Entity* entity){
    if (entity->active) {
        switch(entity->category) {
            case Category::ENEMY:
                if (entity->position.y > game->height) {
                    entity->active = false;
                }
                break;
            case Category::BULLET:
                if (entity->position.y < 0) {
                    entity->active = false;
                }
                break;
            default:
                break;
        }
    }
}

double Systems::spawnEnemy(double delta, double t, int enemy) {
    auto d1 = t-delta;
    if (d1 < 0.0) {
        switch(enemy) {
            case 1:
                game->enemies1.emplace_back((std::rand() % (game->width-70))+35, 35);
                return 1.0;
            case 2:
                game->enemies2.emplace_back((std::rand() % (game->width-170))+85, 85);
                return 4.0;
            case 3:
                game->enemies3.emplace_back((std::rand() % (game->width-320))+160, 160);
                return 6.0;
            default:
                return 0;
        }
    } else return d1;    
}

void Systems::spawnSystem(Entity* entity){
    enemyT1 = spawnEnemy(game->delta, enemyT1, 1);
    enemyT2 = spawnEnemy(game->delta, enemyT2, 2);
    enemyT3 = spawnEnemy(game->delta, enemyT3, 3);

}

void Systems::entitySystem(Entity* entity){
    if (!entity->active) {
        switch(entity->actor) {

            case Actor::BULLET: 
                if (game->bullets.empty()) break;
                refreshBullet(entity, game->bullets.back().x, game->bullets.back().y);
                game->bullets.pop_back();
                break;

            case Actor::ENEMY1:
                if (game->enemies1.empty()) break;
                refreshEnemy1(entity, game->enemies1.back().x, game->enemies1.back().y);
                game->enemies1.pop_back();
                break;

            case Actor::ENEMY2:
                if (game->enemies2.empty()) break;
                refreshEnemy2(entity, game->enemies2.back().x, game->enemies2.back().y);
                game->enemies2.pop_back();
                break;

            case Actor::ENEMY3:
                if (game->enemies3.empty()) break;
                refreshEnemy3(entity, game->enemies3.back().x, game->enemies3.back().y);
                game->enemies3.pop_back();
                break;

            case Actor::EXPLOSION:  
                if (game->explosions.empty()) break;
                refreshExplosion(entity, game->explosions.back().x, game->explosions.back().y);
                game->explosions.pop_back();
                break;

            case Actor::BANG:
                if (game->bangs.empty()) break;
                refreshBang(entity, game->bangs.back().x, game->bangs.back().y);
                game->bangs.pop_back();
                break;

            case Actor::PARTICLE:
                if (game->particles.empty()) break;
                refreshParticle(entity, game->particles.back().x, game->particles.back().y);
                game->particles.pop_back();
                break;

            default:
                break;
        }
    }

}

void Systems::handleCollision(Entity* a, Entity* b){
    game->bangs.emplace_back(b->bounds.x, b->bounds.y);
    b->active = false;
    for (int i=0; i<3; i++) game->particles.emplace_back(b->bounds.x, b->bounds.y);
    if (a->health) {
        auto h = a->health.value()->current - 2;
        if (h < 0) {
            game->explosions.emplace_back(a->position.x, a->position.y);
            a->active = false;
        } else {
            a->health = new Health(h, a->health.value()->maximum);
        }   
    }
}

// bool Systems::intersects(SDL_Rect* r1, SDL_Rect* r2) {
//     return ((r1->x < r2->x + r2->w) && 
//             (r1->x + r1->w > r2->x) && 
//             (r1->y < r2->y + r2->h) && 
//             (r1->y + r1->h > r2->y));
// }

void Systems::collisionSystem(Entity* entity){
    if (entity->active && entity->category == Category::ENEMY) {
        for (int i=0; i<game->entities.size(); i++) {
            auto bullet = &game->entities[i];
            if (bullet->active && bullet->category == Category::BULLET) {
                if (SDL_HasIntersection(&entity->bounds, &bullet->bounds)) {
                    if (entity->active && bullet->active) handleCollision(entity, bullet);
                    return;
                }
            }
        }
    }
}
