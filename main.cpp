#include <SDL2/SDL.h> //we're just using the base SDL2 libraries - not going to get into the extensions right now
#include <cstdlib>
#include <iostream>
#include <random>
using std::cerr;
using std::cout;
using std::endl;



//[this class is just a real rough thing I threw together, to hold everything. 12/15/2019]

  //I think the best way to break things up would be if I wrote engine code, and
  //presented you an interface like this, where you could access the main functions
  //really easily, would make it so you could do more of the logic of the game.

class game
{
public:
  game();
  ~game();

  SDL_Window* win;
  SDL_Renderer* ren;
  SDL_Surface* bmp;
  SDL_Texture* tex;

  void handle_keyboard_shit();
  void draw_that_shit();

  bool quit;      //used in main loop, to tell if you want to quit or not
  bool aligned;   //are we going to draw aligned chunks of grumpy cat

private:


};


game::game()
{
  quit=false;     //you don't want to quit when you're instantiating
  aligned=false;  //default this to off

  //null initialization of all sdl objects - they're all created in main()
  win = NULL;
  ren = NULL;
  bmp = NULL;
  tex = NULL;
}



game::~game()
{//deallocation of all SDL stuff
  SDL_DestroyTexture(tex);
  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(win);
  SDL_Quit();
}


void game::handle_keyboard_shit()
{

  //so SDL maintains a queue of events that take place, this includes mouse, keyboard, touch activity, as well as things like controllers
  //and other sorts of peripherals. We use SDL_PollEvent with an SDL_Event object to get the information about the current event -
  //it contains a number of fields, the most important of which is the top level type - it tells you what kind of event this is so you
  //decide how you want to deal with it.

  //I am currently handling 5 types of input events - SDL_QUIT, SDL_KEYDOWN, SDL_KEYUP, SDL_MOUSEBUTTONDOWN and SDL_MOUSEBUTTONUP

  //Event handler
  SDL_Event e;

  //Handle events on queue
  while( SDL_PollEvent( &e ) != 0 ) //give me the next event, put it in e - if that function returns zero there is no events left, and we continue
  {
    //User requests quit - this is through the x or keyboard shortcut
    if( e.type == SDL_QUIT )
    {//this type means you got a message to quit
      // ┌─┐┬ ┬┌─┐┌┬┐┌─┐┌┬┐  ┌─┐─┐ ┬┬┌┬┐
      // └─┐└┬┘└─┐ │ ├┤ │││  ├┤ ┌┴┬┘│ │
      // └─┘ ┴ └─┘ ┴ └─┘┴ ┴  └─┘┴ └─┴ ┴

        cout << "quitting via kill" << endl;  //this is called when exiting via key combo/window x button
        quit = true;  //this will be seen from main
    }
    else if( e.type == SDL_KEYDOWN )
    {// this type means you pressed a key
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
              aligned = true;   //if this is set to true, until you release that key, we'll be drawing the image on a grid
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
              cout << " exiting (quitting via escape)" << endl;   // this is called when the escape button is hit
              quit = true;  //this will be seen in main
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
    { //this type means that you released a key
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
    {//you clicked the mouse button down, at some xy - note that y goes from 0 at the top to whatever value at the bottom
      //  ┌┬┐┌─┐┬ ┬┌─┐┌─┐  ┌─┐┬─┐┌─┐┌─┐┌─┐
      //  ││││ ││ │└─┐├┤   ├─┘├┬┘├┤ └─┐└─┐
      //  ┴ ┴└─┘└─┘└─┘└─┘  ┴  ┴└─└─┘└─┘└─┘
      switch(e.button.button) //this is stupid notation
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
    {//you let go of a mouse button, at some xy - again, same deal with y being inverted
      //  ┌┬┐┌─┐┬ ┬┌─┐┌─┐  ┬─┐┌─┐┬  ┌─┐┌─┐┌─┐┌─┐
      //  ││││ ││ │└─┐├┤   ├┬┘├┤ │  ├┤ ├─┤└─┐├┤
      //  ┴ ┴└─┘└─┘└─┘└─┘  ┴└─└─┘┴─┘└─┘┴ ┴└─┘└─┘
      switch(e.button.button)
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


void game::draw_that_shit()
{
  SDL_RenderClear(ren); //clear our background

  //learning how to chop up images with https://wiki.libsdl.org/SDL_RenderCopy
  //rectangles tell SDL where you want to read from/write from -

  //The implication here is that you have the opportunity to define where your pixels are going to show up on the screen, and what shape will they be.
  //Squashing/stretching can be achieved by changing the shape of that rectangle - look at the random generation of widths/heights to see examples.

  SDL_Rect SrcRect; //where are we taking pixels from?
  SDL_Rect DestRect;  //the pixels we took from SrcRect?

  //these random number generators give me some ability to randomly place the destination rectangles - you'll see
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_int_distribution<int> xdist(0,619);  //between zero and the width
  std::uniform_int_distribution<int> ydist(0,387);  //between zero and the height
  std::uniform_int_distribution<int> wdist(16,128);  //some range of values
  std::uniform_int_distribution<int> hdist(25,175);  //some range of values

  //image dimensions are 620,387
  //I'm going to chop that into a 4x4 grid


  for(int x = 0; x < 4; x++)
  {
    for(int y = 0; y < 4; y++)
    {
      SrcRect.x = x*(620/4);    //here's some math to get x
      SrcRect.y = y*(387/4);   //here's some math to get y
      SrcRect.w = (620/4);    //width is just distance between two samples
      SrcRect.h = (387/4);   //similar situation for height

      if(aligned)
      { //'shrunk in' version of the cat face - this was kind of trial and error
        DestRect.x = x*(620/4)+80+15*cos(0.001*SDL_GetTicks());
        DestRect.y = y*(387/4)+70+8*sin(0.001*SDL_GetTicks());
        DestRect.w = (620/4)-60+15*cos(0.001*SDL_GetTicks());
        DestRect.h = (387/4)-40+8*sin(0.001*SDL_GetTicks());
      }
      else
      { //give me some random location to draw this shit at
        DestRect.x = xdist(mt);     //tell me where that shit's at on x
        DestRect.y = ydist(mt);    //tell me where that shit's at on y
        DestRect.w = wdist(mt);   //tell me how wide that shit is
        DestRect.h = hdist(mt);  //tell me how tall that shit is
      }

      SDL_RenderCopy(ren, tex, &SrcRect, &DestRect);  //copy from SrcRect to DestRect
    }//end y
  }//end x

  SDL_RenderPresent(ren); //swap buffers so that this most recently drawn material is shown to the user
  // SDL_Delay(100); //wait some period of time so as not to cause as bad a seizure

}






//this is used for the instantiation in main
game* my_game;

int main()
{

    my_game = new game(); //so we have a new one - calls constructor and gets it ready to go

    //we went over all this yesterday, I made the error checking more compact but it's still distracting
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){ cerr << "SDL_Init Error: " << SDL_GetError() << endl; return EXIT_FAILURE; }

    my_game->win = SDL_CreateWindow("Hello World!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 720, 480, SDL_WINDOW_OPENGL);
    if (my_game->win == NULL){ cerr << "SDL_CreateWindow Error: " << SDL_GetError() << endl; return EXIT_FAILURE; }

    // SDL_SetWindowFullscreen(my_game->win, SDL_WINDOW_FULLSCREEN);

    my_game->ren  = SDL_CreateRenderer(my_game->win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (my_game->ren == NULL){ cerr << "SDL_CreateRenderer Error" << SDL_GetError() << endl; return EXIT_FAILURE; }

    my_game->bmp = SDL_LoadBMP("grumpy-cat.bmp");
    if (my_game->bmp == NULL){ cerr << "SDL_LoadBMP Error: " << SDL_GetError() << endl; return EXIT_FAILURE; }

    my_game->tex = SDL_CreateTextureFromSurface(my_game->ren, my_game->bmp);
    SDL_FreeSurface(my_game->bmp);
    if (my_game->tex == NULL){ cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << endl; return EXIT_FAILURE; }


    //The main loop -
      //this is what iterates per-frame in your game. You generally want to do your animation based on fixed time steps, so for now we'll
      //just kind of not not worry about that. There's functionality for timers but we'll get there

      //Basically the main loop just runs until the user has told us that they want to quit - until that time, we'll continue to
      //loop through this process of handling the shit for the keyboard, then drawing the shit that we do in the draw function


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
