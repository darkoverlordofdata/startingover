#include<iostream>
using namespace std;

#include <SDL.h>

/*
    The theory here is this: You don't want letterboxing. You want the game to be taken from it's original size and
stretched to fit the window no matter what. So you just render everything to a back buffer by setting the target
to it, instead of to the window's buffer, then at the end of your rendering cycle, switch the target back to the
screen and RenderCopy the back buffer onto the screen rescaling if neccessary, then set the target back to your
back buffer and repeat. It's slightly trickier than it sounds
*/

/*
    NOTE:
    There is a delay in the resizing of the screen the first time it is resized, but after that it's fine.
    I have no idea why.
*/

//The SDL event structure
// SDL_Event event;

//The original resolution
SDL_Rect nativeSize;
SDL_Rect newWindowSize;

float scaleRatioW;//This is to change anything that might rely on something like mouse coords
float scaleRatioH; //(such as a button on screen) over to the new coordinate system scaling would create

SDL_Window * window; //Our beautiful window
SDL_Renderer * renderer; //The renderer for our window
SDL_Texture * backBuffer; //The back buffer that we will be rendering everything to before scaling up

SDL_Texture * ballImage; //A nice picture to demonstrate the scaling;

bool resize;

void InitValues(); //Initialize all the variables needed
void InitSDL();     //Initialize the window, renderer, backBuffer, and image;
bool HandleEvents(); //Handle the window changed size event
void Render();            //Switches the render target back to the window and renders the back buffer, then switches back.
void Resize();      //The important part for stretching. Changes the viewPort, changes the scale ratios

void InitValues()
{
    nativeSize.x = 0;
    nativeSize.y = 0;
    nativeSize.w = 256;
    nativeSize.h = 224; //A GameBoy size window width and height

    scaleRatioW = 1.0f;
    scaleRatioH = 1.0f;

    newWindowSize.x = 0;
    newWindowSize.y = 0;
    newWindowSize.w = nativeSize.w;
    newWindowSize.h = nativeSize.h;

    window = NULL;
    renderer = NULL;
    backBuffer = NULL;
    ballImage = NULL;

    resize = false;
}

void InitSDL()
{
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER) < 0)
    {
        cout << "Failed to initialize SDL" << endl;
    }

    //Set the scaling quality to nearest-pixel
    if(SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0") < 0)
    {
        cout << "Failed to set Render Scale Quality" << endl;
    }

    //Window needs to be resizable
    window = SDL_CreateWindow("Rescaling Windows!",
                                                    SDL_WINDOWPOS_CENTERED,
                                                    SDL_WINDOWPOS_CENTERED,
                                                    256,
                                                    224,
                                                    SDL_WINDOW_RESIZABLE);

    //You must use the SDL_RENDERER_TARGETTEXTURE flag in order to target the backbuffer
    renderer = SDL_CreateRenderer(window,
                                                      -1,
                                                      SDL_RENDERER_ACCELERATED |
                                                      SDL_RENDERER_TARGETTEXTURE);

    //Set to blue so it's noticeable if it doesn't do right.
    SDL_SetRenderDrawColor(renderer, 0, 0, 200, 255);

    //Similarly, you must use SDL_TEXTUREACCESS_TARGET when you create the texture
    backBuffer = SDL_CreateTexture(renderer,
                                                       SDL_GetWindowPixelFormat(window),
                                                       SDL_TEXTUREACCESS_TARGET,
                                                       nativeSize.w,
                                                       nativeSize.h);

    //IMPORTANT Set the back buffer as the target
    SDL_SetRenderTarget(renderer, backBuffer);

    //Load an image yay
    SDL_Surface * image = SDL_LoadBMP("Ball.bmp");

    ballImage = SDL_CreateTextureFromSurface(renderer, image);

    SDL_FreeSurface(image);
}

bool HandleEvents()
{
    SDL_Event event;
    while(SDL_PollEvent(&event) != 0)
    {
        if(event.type == SDL_QUIT)
        {
            return true;
        }
        else if(event.type == SDL_WINDOWEVENT)
        {
            if(event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
            {
                resize = true;
            }
        }

        return false;
    }
}

void Render()
{
    SDL_RenderCopy(renderer, ballImage, NULL, NULL); //Render the entire ballImage to the backBuffer at (0, 0)

    SDL_SetRenderTarget(renderer, NULL); //Set the target back to the window

        if(resize)
        {
            Resize();
            resize = false;
        }

        SDL_RenderCopy(renderer, backBuffer, &nativeSize, &newWindowSize); //Render the backBuffer onto the screen at (0,0)
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer); //Clear the window buffer

    SDL_SetRenderTarget(renderer, backBuffer); //Set the target back to the back buffer
    SDL_RenderClear(renderer); //Clear the back buffer

}

void Resize()
{
    int w, h;

    SDL_GetWindowSize(window, &w, &h);

    scaleRatioW = w / nativeSize.w;
    scaleRatioH = h / nativeSize.h;  //The ratio from the native size to the new size

    newWindowSize.w = w;
    newWindowSize.h = h;

    //In order to do a resize, you must destroy the back buffer. Try without it, it doesn't work
    SDL_DestroyTexture(backBuffer);
    backBuffer = SDL_CreateTexture(renderer,
                                   SDL_GetWindowPixelFormat(window),
                                   SDL_TEXTUREACCESS_TARGET, //Again, must be created using this
                                   nativeSize.w,
                                   nativeSize.h);

    SDL_Rect viewPort;
    SDL_RenderGetViewport(renderer, &viewPort);

    if(viewPort.w != newWindowSize.w || viewPort.h != newWindowSize.h)
    {
        //VERY IMPORTANT - Change the viewport over to the new size. It doesn't do this for you.
        SDL_RenderSetViewport(renderer, &newWindowSize);
    }
}

int main(int argc, char * argv[])
{
    InitValues();
    InitSDL();

    bool quit = false;

    while(!quit)
    {
        quit = HandleEvents();
        Render();
    }

    return 0;
}

//void Window::Resize()
//{
//    int newX = 0, newY = 0;
//
//    SDL_GetWindowPosition(m_Window, &newX, &newY);
//
//    int newWidth = 0, newHeight = 0;
//
//    SDL_GetWindowSize(m_Window, &newWidth, &newHeight);
//
//    m_WindowWidth = newWidth;
//    m_WindowHeight = newHeight;
//
//    //Keep the position up to date
//    m_WindowPosX = newX;
//    m_WindowPosY = newY;
//
//    //Set the new scale ratios
//    g_wScale = newWidth / m_NativeSize.w;
//    g_hScale = newHeight / m_NativeSize.h;
//
//    m_BufferScaledSize.w = newWidth;
//    m_BufferScaledSize.h = newHeight;
//
//    resized = true;
//}
//
//void Window::Refresh()
//{
//    SDL_SetRenderDrawColor(m_Renderer, 0, 0, 200, 255); //Set the color for clearing
//
//    SDL_SetRenderTarget(m_Renderer, NULL);
//
//        SDL_RenderCopy(m_Renderer, m_BackBuffer, &m_NativeSize, &m_BufferScaledSize);
//        SDL_RenderPresent(m_Renderer);
//        SDL_RenderClear(m_Renderer);
//
//        if(resized)
//        {
//            SDL_Rect viewPort;
//
//            SDL_RenderGetViewport(m_Renderer, &viewPort);
//
//            if(viewPort.w != m_BufferScaledSize.w || viewPort.h != m_BufferScaledSize.h)
//            {
//                SDL_RenderSetViewport(m_Renderer, &m_BufferScaledSize);
//            }
//
//            SDL_DestroyTexture(m_BackBuffer);
//            m_BackBuffer = SDL_CreateTexture(m_Renderer, SDL_GetWindowPixelFormat(m_Window), SDL_TEXTUREACCESS_TARGET, m_NativeSize.w, m_NativeSize.h);
//
//            resized = false;
//        }
//
//    SDL_SetRenderTarget(m_Renderer, m_BackBuffer);
//
//    SDL_RenderClear(m_Renderer);
//}
