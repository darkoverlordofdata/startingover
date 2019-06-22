/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#define GLEW_STATIC
#define GL3_PROTOTYPES 1
#include <GLES3/gl3.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <chrono>
#ifdef __EMSCRIPTEN__
#include <functional>
#include <emscripten.h>
std::function<void()> loop;
void main_loop() { loop(); }
#else
#include <GL/glew.h>
#endif

#include "game.h"
#include "resource_manager.h"

// The Width of the screen
const GLuint SCREEN_WIDTH = 800;
// The height of the screen
const GLuint SCREEN_HEIGHT = 600;

Game Breakout(SCREEN_WIDTH, SCREEN_HEIGHT);

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

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER | SDL_INIT_AUDIO)) {
        logSDLError(std::cout, "Init SDL");
        return 0;
    }

    /* Request opengl 3.3 context.
     * SDL doesn't have the ability to choose which profile at this time of writing,
     * but it should default to the core profile */
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
#ifdef __EMSCRIPTEN__
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#else
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
#endif

    /* Turn on double buffering with a 24bit Z buffer.
     * You may need to change this to 16 or 32 for your system */
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    auto window = SDL_CreateWindow("Breakout", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    SDL_GLContext maincontext = SDL_GL_CreateContext(window);
    checkSDLError(__LINE__);

    #ifdef __EMSCRIPTEN__
    const auto img_flags = IMG_INIT_PNG;
    #else
    const auto img_flags = IMG_INIT_PNG | IMG_INIT_JPG;
    #endif

    if (IMG_Init(img_flags) != img_flags) {
        logSDLError(std::cout, "Init image");
    }

    /** 
     * 
     * Repalces MonoGame.OpenGL.GL.LoadEntryPoints():
     */
    #ifndef __EMSCRIPTEN__
    glewExperimental = GL_TRUE;
    glewInit();
    glGetError(); // Call it once to catch glewInit() bug, all other errors are now from our application.
    #endif
    // OpenGL configuration
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    using namespace std::chrono;
    std::srand(std::time(0));    

    // Initialize game
    Breakout.Init();

    // DeltaTime variables
    GLfloat deltaTime = 0.0f;
    GLfloat lastFrame = 0.0f;

    // Start Game within Menu State
    Breakout.State = GAME_ACTIVE;
    auto mark1 = high_resolution_clock::now();

#ifdef __EMSCRIPTEN__
    loop = [&] 
    {
#else
    while (Breakout.State == GAME_ACTIVE) 
    {
#endif

        // Calculate delta time
        auto mark2 = high_resolution_clock::now();
        GLfloat deltaTime = ((double) duration_cast<microseconds>(mark2 - mark1).count()) / 1000000.0;
        mark1 = mark2;

        // Manage user input
        Breakout.ProcessInput(deltaTime);

        // Update Game state
        Breakout.Update(deltaTime);

        // Render
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        Breakout.Render();

        SDL_GL_SwapWindow(window);
    }
#ifdef __EMSCRIPTEN__
    ;
    emscripten_set_main_loop(main_loop, 0, true);
#endif

    // Delete all resources as loaded using the resource manager
    ResourceManager::Clear();

    SDL_DestroyWindow(window);
	// IMG_Quit();
    SDL_Quit();
    return 0;
}

