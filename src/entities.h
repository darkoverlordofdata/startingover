#ifndef ENTITIES_H
#define ENTITIES_H

void createBackground(SDL_Renderer* renderer, std::vector<Entity>* entities, std::string path);
Entity* createPlayer(SDL_Renderer* renderer, std::vector<Entity>* entities, std::string path);
void createBullet(SDL_Renderer* renderer, std::vector<Entity>* entities, std::string path);
void createEnemy1(SDL_Renderer* renderer, std::vector<Entity>* entities, std::string path);
void createEnemy2(SDL_Renderer* renderer, std::vector<Entity>* entities, std::string path);
void createEnemy3(SDL_Renderer* renderer, std::vector<Entity>* entities, std::string path);
void createExplosion(SDL_Renderer* renderer, std::vector<Entity>* entities, std::string path);
void createBang(SDL_Renderer* renderer, std::vector<Entity>* entities, std::string path);
void createParticle(SDL_Renderer* renderer, std::vector<Entity>* entities, std::string path);


void initBackground(SDL_Renderer* renderer, Entity* entity, std::string path);
void initPlayer(SDL_Renderer* renderer, Entity* entity, std::string path);
void initBullet(SDL_Renderer* renderer, Entity* entity, std::string path);
void initEnemy1(SDL_Renderer* renderer, Entity* entity, std::string path);
void initEnemy2(SDL_Renderer* renderer, Entity* entity, std::string path);
void initEnemy3(SDL_Renderer* renderer, Entity* entity, std::string path);
void initExplosion(SDL_Renderer* renderer, Entity* entity, std::string path);
void initBang(SDL_Renderer* renderer, Entity* entity, std::string path);
void initParticle(SDL_Renderer* renderer, Entity* entity, std::string path);

void refreshBullet(Entity* entity, int x, int y);
void refreshEnemy1(Entity* entity, int x, int y);
void refreshEnemy2(Entity* entity, int x, int y);
void refreshEnemy3(Entity* entity, int x, int y);
void refreshExplosion(Entity* entity, int x, int y);
void refreshBang(Entity* entity, int x, int y);
void refreshParticle(Entity* entity, int x, int y);

#endif