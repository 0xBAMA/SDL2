#include <SDL2/SDL.h>
#include <cstdlib>
#include <iostream>
#include <random>
using std::cerr;
using std::cout;
using std::endl;


class application
{
public:




  application();
  ~application();

  SDL_Window* win;
  SDL_Renderer* ren;
  SDL_Surface* bmp;
  SDL_Texture* tex;

  void handle_keyboard_shit();
  void draw_that_shit();


  //Event handler
  SDL_Event e;

  bool quit;
  bool aligned;

private:


};


application::application()
{
  quit=false;
  aligned=false;

  //null initialization of all sdl objects
  win = NULL;
  ren = NULL;
  bmp = NULL;
  tex = NULL;
}



application::~application()
{
  SDL_DestroyTexture(tex);
  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(win);
  SDL_Quit();
}


void application::handle_keyboard_shit()
{
  //Handle events on queue
  while( SDL_PollEvent( &e ) != 0 )
  {
    //User requests quit - this is through the x or keyboard shortcut
    if( e.type == SDL_QUIT )
    {
      // ┌─┐┬ ┬┌─┐┌┬┐┌─┐┌┬┐  ┌─┐─┐ ┬┬┌┬┐
      // └─┐└┬┘└─┐ │ ├┤ │││  ├┤ ┌┴┬┘│ │
      // └─┘ ┴ └─┘ ┴ └─┘┴ ┴  └─┘┴ └─┴ ┴

        quit = true;
        cout << "quitting via kill" << endl;
    }
    else if( e.type == SDL_KEYDOWN )
    {
      //  ┬┌─┌─┐┬ ┬  ┌─┐┬─┐┌─┐┌─┐┌─┐
      //  ├┴┐├┤ └┬┘  ├─┘├┬┘├┤ └─┐└─┐
      //  ┴ ┴└─┘ ┴   ┴  ┴└─└─┘└─┘└─┘

      //INFO:
      // https://wiki.libsdl.org/SDL_KeyboardEvent


        //switch based on key press
        switch( e.key.keysym.sym )
        {
            case SDLK_UP:
              cout << "  up  key pressed" << endl;
              aligned = true;
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
              cout << " exiting (quitting via escape)" << endl;
            quit = true;
              break;

            default:
              cout << " some other key pressed" << endl;
              cout << "scancode is: " << SDL_GetScancodeName(e.key.keysym.scancode);
              cout <<" with name: " <<  SDL_GetKeyName(e.key.keysym.sym) << endl;
              break;
        }

        if(e.key.repeat)
          cout << " and is being held ";

        cout << " at time " << e.key.timestamp << endl << endl;
    }
    else if(e.type == SDL_KEYUP)
    {
      //  ┬┌─┌─┐┬ ┬  ┬─┐┌─┐┬  ┌─┐┌─┐┌─┐┌─┐
      //  ├┴┐├┤ └┬┘  ├┬┘├┤ │  ├┤ ├─┤└─┐├┤
      //  ┴ ┴└─┘ ┴   ┴└─└─┘┴─┘└─┘┴ ┴└─┘└─┘

      switch( e.key.keysym.sym )
      {
        case SDLK_UP:
          cout << "  up  key let go" << endl;
          aligned = false;
          break;
      }
    }
    else if(e.type == SDL_MOUSEBUTTONDOWN)
    {
      //  ┌┬┐┌─┐┬ ┬┌─┐┌─┐  ┌─┐┬─┐┌─┐┌─┐┌─┐
      //  ││││ ││ │└─┐├┤   ├─┘├┬┘├┤ └─┐└─┐
      //  ┴ ┴└─┘└─┘└─┘└─┘  ┴  ┴└─└─┘└─┘└─┘
      switch(e.button.button) //this is stupid
      {
        case SDL_BUTTON_LEFT:
          cout << "left click at x:" << e.button.x << " y:" << e.button.y << endl;
          break;

        case SDL_BUTTON_MIDDLE:
          cout << "middle click at x:" << e.button.x << " y:" << e.button.y << endl;
          break;

        case SDL_BUTTON_RIGHT:
          cout << "right click at x:" << e.button.x << " y:" << e.button.y << endl;
          break;
      }
    }
    else if(e.type == SDL_MOUSEBUTTONUP)
    {
      //  ┌┬┐┌─┐┬ ┬┌─┐┌─┐  ┬─┐┌─┐┬  ┌─┐┌─┐┌─┐┌─┐
      //  ││││ ││ │└─┐├┤   ├┬┘├┤ │  ├┤ ├─┤└─┐├┤
      //  ┴ ┴└─┘└─┘└─┘└─┘  ┴└─└─┘┴─┘└─┘┴ ┴└─┘└─┘
      switch(e.button.button) //this is stupid
      {
        case SDL_BUTTON_LEFT:
          cout << "left click released at x:" << e.button.x << " y:" << e.button.y << endl;
          break;

        case SDL_BUTTON_MIDDLE:
          cout << "middle click released at x:" << e.button.x << " y:" << e.button.y << endl;
          break;

        case SDL_BUTTON_RIGHT:
          cout << "right click released at x:" << e.button.x << " y:" << e.button.y << endl;
          break;
        }
      }
    cout << " at time " << e.key.timestamp << endl << endl;
  }
}


void application::draw_that_shit()
{
  SDL_RenderClear(ren);


  //learning how to chop up images with https://wiki.libsdl.org/SDL_RenderCopy
  SDL_Rect SrcRect;
  SDL_Rect DestRect;

  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_int_distribution<int> xdist(0,619);
  std::uniform_int_distribution<int> ydist(0,387);
  std::uniform_int_distribution<int> wdist(28,37);
  std::uniform_int_distribution<int> hdist(25,38);

  //image dimensions are 620,387

  for(int x = 0; x < 4; x++)
  {
    for(int y = 0; y < 4; y++)
    {
      SrcRect.x = x*(620/4);
      SrcRect.y = y*(387/4);
      SrcRect.w = (620/4);
      SrcRect.h = (387/4);

      if(aligned)
      {
        DestRect.x = x*(620/4)+80;
        DestRect.y = y*(387/4)+70;
        DestRect.w = (620/4)-60;
        DestRect.h = (387/4)-40;
      }
      else
      {
        DestRect.x = xdist(mt);
        DestRect.y = ydist(mt);
        DestRect.w = wdist(mt);
        DestRect.h = hdist(mt);
      }

      SDL_RenderCopy(ren, tex, &SrcRect, &DestRect);
    }
  }

  SDL_RenderPresent(ren);
  SDL_Delay(100);

}







application* main_application;


int main()
{

    main_application = new application();

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){ cerr << "SDL_Init Error: " << SDL_GetError() << endl; return EXIT_FAILURE; }

    main_application->win = SDL_CreateWindow("Hello World!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 720, 480, SDL_WINDOW_OPENGL);
    if (main_application->win == NULL){ cerr << "SDL_CreateWindow Error: " << SDL_GetError() << endl; return EXIT_FAILURE; }

    // SDL_SetWindowFullscreen(main_application->win, SDL_WINDOW_FULLSCREEN);

    main_application->ren  = SDL_CreateRenderer(main_application->win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (main_application->ren == NULL){ cerr << "SDL_CreateRenderer Error" << SDL_GetError() << endl; return EXIT_FAILURE; }

    main_application->bmp = SDL_LoadBMP("grumpy-cat.bmp");
    if (main_application->bmp == NULL){ cerr << "SDL_LoadBMP Error: " << SDL_GetError() << endl; return EXIT_FAILURE; }

    main_application->tex = SDL_CreateTextureFromSurface(main_application->ren, main_application->bmp);
    SDL_FreeSurface(main_application->bmp);
    if (main_application->tex == NULL){ cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << endl; return EXIT_FAILURE; }



    //Main loop flags
    main_application->quit = false;

    while(!main_application->quit)  //main loop
    {
      main_application->handle_keyboard_shit();
      main_application->draw_that_shit();
    }

    delete main_application;

    return EXIT_SUCCESS;
}
