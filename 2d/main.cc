#include "game.h"


//this is used for the instantiation in main
game* my_game;

int main()
{

    my_game = new game(); //so we have a new one - calls constructor and gets it ready to go

    //we went over all this yesterday, I made the error checking more compact but it's still distracting
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){ cerr << "SDL_Init Error: " << SDL_GetError() << endl; return EXIT_FAILURE; }

    my_game->win = SDL_CreateWindow("Hello World!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 720, 405, SDL_WINDOW_OPENGL);
    if (my_game->win == NULL){ cerr << "SDL_CreateWindow Error: " << SDL_GetError() << endl; return EXIT_FAILURE; }

    my_game->ren  = SDL_CreateRenderer(my_game->win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (my_game->ren == NULL){ cerr << "SDL_CreateRenderer Error" << SDL_GetError() << endl; return EXIT_FAILURE; }


    SDL_Surface* bmp1 = NULL;
    SDL_Surface* bmp2 = NULL;


    bmp1 = SDL_LoadBMP("grumpy-cat.bmp");
    if (bmp1 == NULL){ cerr << "SDL_LoadBMP Error: " << SDL_GetError() << endl; return EXIT_FAILURE; }

    my_game->tex = SDL_CreateTextureFromSurface(my_game->ren, bmp1);
    SDL_FreeSurface(bmp1);
    if (my_game->tex == NULL){ cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << endl; return EXIT_FAILURE; }


    bmp2 = SDL_LoadBMP("splash.bmp");
    if (bmp2 == NULL){ cerr << "SDL_LoadBMP Error: " << SDL_GetError() << endl; return EXIT_FAILURE; }

    my_game->splash = SDL_CreateTextureFromSurface(my_game->ren, bmp2);
    SDL_FreeSurface(bmp2);
    if (my_game->splash == NULL){ cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << endl; return EXIT_FAILURE; }

    //The main loop -
      //this is what iterates per-frame in your game. You generally want to do your animation based on fixed time steps, so for now we'll
      //just kind of not not worry about that.

      //Basically the main loop just runs until the user has told us that they want to quit - until that time, we'll continue to
      //loop through this process of handling the shit for the keyboard, then drawing the shit that we do in the draw function



      SDL_Init( SDL_INIT_VIDEO );
      SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
      SDL_GL_SetAttribute( SDL_GL_ACCELERATED_VISUAL, 1 );
      SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
      SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
      SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
      SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 8 );

      SDL_GL_SetAttribute( SDL_GL_MULTISAMPLEBUFFERS, 1);
      SDL_GL_SetAttribute( SDL_GL_MULTISAMPLESAMPLES, 8);

      SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 4 );
      SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 5 );
      SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );



      auto window = SDL_CreateWindow( "OpenGL Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 100, 200, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
      auto context = SDL_GL_CreateContext( window );


      SDL_Delay(1000);

    //Main loop flags
    my_game->quit = false;

    while(!my_game->quit)  //main loop
    {
      my_game->handle_keyboard_shit();
      my_game->draw_that_shit();
    }

    delete my_game;  //this calls the destructor and deallocates all the SDL stuff - there's better ways to do this




























    return EXIT_SUCCESS;
}
