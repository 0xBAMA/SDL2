#include <SDL2/SDL.h>
#include <cstdlib>
#include <iostream>
using std::cerr;
using std::cout;
using std::endl;

int main()
{

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        cerr << "SDL_Init Error: " << SDL_GetError() << endl;
        return EXIT_FAILURE;
    }

    // SDL_Window* win = SDL_CreateWindow("Hello World!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 720, 480, SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL);
    SDL_Window* win = SDL_CreateWindow("Hello World!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 720, 480, SDL_WINDOW_OPENGL);
    if (win == nullptr)
    {
        cerr << "SDL_CreateWindow Error: " << SDL_GetError() << endl;
        return EXIT_FAILURE;
    }

    // SDL_SetWindowFullscreen(win, SDL_WINDOW_FULLSCREEN);

    SDL_Renderer* ren  = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr)
    {
        cerr << "SDL_CreateRenderer Error" << SDL_GetError() << endl;
        return EXIT_FAILURE;
    }



    SDL_Surface* bmp = SDL_LoadBMP("grumpy-cat.bmp");
    if (bmp == nullptr)
    {
        cerr << "SDL_LoadBMP Error: " << SDL_GetError() << endl;
        return EXIT_FAILURE;
    }



    SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, bmp);
    SDL_FreeSurface(bmp);
    if (tex == nullptr)
    {
        cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << endl;
        return EXIT_FAILURE;
    }



    // for (int i = 0; i < 20; i++)
    // {
    //     SDL_RenderClear(ren);
    //     SDL_RenderCopy(ren, tex, nullptr, nullptr);
    //     SDL_RenderPresent(ren);
    //     SDL_Delay(100);
    // }










    //Event handler
    SDL_Event e;

    //Main loop flag
    bool quit = false;
    while(!quit)  //main loop
    {

      //Handle events on queue
      while( SDL_PollEvent( &e ) != 0 )
      {
        //User requests quit
        if( e.type == SDL_QUIT )
        {
            quit = true;
        }
        else if( e.type == SDL_KEYDOWN )
        {
            //Select surfaces based on key press
            switch( e.key.keysym.sym )
            {
                case SDLK_UP:
                cout << "  up  key pressed" << endl;
                break;

                case SDLK_DOWN:
                cout << "  down  key pressed" << endl;
                break;

                case SDLK_LEFT:
                cout << "  left  key pressed" << endl;
                break;

                case SDLK_RIGHT:
                cout << "  right  key pressed" << endl;
                break;

                case SDLK_ESCAPE:
                cout << " exiting" << endl;
                quit = true;
                break;

                default:
                cout << " some other key pressed" << endl;
                break;
            }
        }
      }

      SDL_RenderClear(ren);
      SDL_RenderCopy(ren, tex, nullptr, nullptr);
      SDL_RenderPresent(ren);
      SDL_Delay(100);

    }








    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return EXIT_SUCCESS;
}
