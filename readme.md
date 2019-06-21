# startingover

Why? Because after reinstalling windows10 and MSys2, my opengl projects no longer cmpile due to an unresolved symbol 'typedef ptrddif_t' in glew. I'm running out of inspriation. Then retire, move, and hard drive fail. 6 months later.

"It'll be just like starting over" -- John Lennon
 
    use doran (cmake) to build desktop version
    use ctrl-b to build emscripten version

goals & vision - put the lime in the coconut

    colocation of data as in better-mousetrap - array of struct
    entitas style extension to make c++ static typeing more fluid
    artemis architecture for the engine using typescript
    mix of opengl & sdl2 similar to monogame
    run on desktop and emscripten

### step1

    replace vala and zerog with c++17. As much as I like vala, valagame must die. I learned about impelemting a monogame style engine using c/cpp.

    * implement the Breakout game from LearnOpenGL - [Breakout](https://learnopengl.com/In-Practice/2D-Game/Breakout)

        compiles and runs both desktop and emscripten

    * replace GLFW & SOIL with SDL2 - done!
    * replace classes with my doran-xna.framework style classes


