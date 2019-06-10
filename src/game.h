#ifndef GAME_H
#define GAME_H

#include <list>
#include <vector>

enum {
    DISPLAY_WIDTH  = 480,
    DISPLAY_HEIGHT = 320,
    UPDATE_INTERVAL = 1000/60,
    HERO_SPEED = 2
};

class Systems;
    
class Game {
friend class Systems;
public:
    Game(std::string title, int width, int height, SDL_Window* window, SDL_Renderer* renderer);
    ~Game();
    void start();
    void stop();
    void draw(int fps, SDL_Rect *clip = nullptr);
    void handleEvents();
    void update(double delta);
    void init();
    void fpsChanged(int fps);
    void quit();
    int isRunning();
    int getKey(int key);

private:
    int mouseX;
    int mouseY;
    int mouseDown = 0;
    double delta;
    int width;
    int height;
    std::list<Point2d> bullets;
    std::list<Point2d> enemies1;
    std::list<Point2d> enemies2;
    std::list<Point2d> enemies3;
    std::list<Point2d> explosions;
    std::list<Point2d> bangs;
    std::list<Point2d> particles;
    std::vector<Entity> entities;
    
    int running;
    int fps;
    std::string title;
    std::map<int,int> keys;
    int frameSkip;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* image;
    Entity* player;
    Systems* systems;
};

#endif
