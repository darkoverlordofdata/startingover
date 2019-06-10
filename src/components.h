#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <experimental/optional>

using namespace std::experimental;


enum class Actor {
    BACKGROUND,
    TEXT,
    LIVES,
    ENEMY1,
    ENEMY2,
    ENEMY3,
    PLAYER,
    BULLET,
    EXPLOSION,
    BANG,
    PARTICLE,
    HUD
};
enum class Category {
    BACKGROUND,
    BULLET,
    ENEMY,
    EXPLOSION,
    PARTICLE,
    PLAYER
};

enum class Effect {
    PEW,
    SMALLASPLODE,
    ASPLODE
};

class Point2d {
public:
    Point2d(): x(0), y(0) {}
    Point2d(double x, double y): x(x), y(y) {}
    double x;
    double y;
};

class Vector2d {
public:
    Vector2d(): x(0), y(0) {}
    Vector2d(double x, double y): x(x), y(y) {}
    double x;
    double y;
};

class Scale {
public:
    Scale(): x(0), y(0) {}
    Scale(double x, double y): x(x), y(y) {}
    double x;
    double y;
};

class Color {
public:
    Color(): r(0), g(0), b(0), a(0) {}
    Color(int r, int g, int b, int a): r(r), g(g), b(b), a(a) {}
    int r;
    int g;
    int b;
    int a;
};

class Health {
public:
    Health(): current(0), maximum(0) {}
    Health(int c, int m): current(c), maximum(m) {}
    int current;
    int maximum;
};

class Tween {
public:
    Tween(): min(0), max(0), speed(0), repeat(false), active(false) {}
    Tween(double m, double x, double s, bool r, bool a): min(m), max(x), speed(s), repeat(r), active(a) {}
    double min;
    double max;
    double speed;
    bool repeat;
    bool active;
};

class Sprite {
public:
    SDL_Texture* texture;
    int width;
    int height;
};


class Entity {
public:
    Entity(int id, std::string name, bool active): id(id), name(name), active(active) {}
    
    int id;
    std::string name;
    bool active;
    Actor actor;
    Category category;
    Point2d position;
    SDL_Rect bounds;
    Vector2d scale;
    Sprite sprite;

    optional<Effect> sound;
    optional<Color*> tint;
    optional<double> expires;
    optional<Health*> health;
    optional<Tween*> tween;
    optional<Vector2d*> velocity;


};



#endif