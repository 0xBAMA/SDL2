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
  SDL_Texture* tex;
  SDL_Texture* splash;

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

        cout << "quitting via kill";  //this is called when exiting via key combo/window x button
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
              cout << "  up  key pressed";
              aligned = true;   //if this is set to true, until you release that key, we'll be drawing the image on a grid
              break;

            case SDLK_DOWN:
              cout << "  down  key pressed";
              break;

            case SDLK_LEFT:
              cout << "  left  key pressed";
              break;

            case SDLK_RIGHT:
              cout << "  right  key pressed";
              break;

            case SDLK_ESCAPE:
              cout << " exiting (quitting via escape)";   // this is called when the escape button is hit
              quit = true;  //this will be seen in main
              break;

            case SDLK_f:
              cout << " going fullscreen";
              SDL_SetWindowFullscreen(win, SDL_WINDOW_FULLSCREEN);
              break;

            default:
              cout << " some other key pressed - ";
              cout << "scancode is: " << SDL_GetScancodeName(e.key.keysym.scancode);
              cout <<" with name: " <<  SDL_GetKeyName(e.key.keysym.sym);
              break;
        }
        if(e.key.repeat)
          cout << " and is being held ";
    }
    else if(e.type == SDL_KEYUP)
    { //this type means that you released a key
      //  ┬┌─┌─┐┬ ┬  ┬─┐┌─┐┬  ┌─┐┌─┐┌─┐┌─┐
      //  ├┴┐├┤ └┬┘  ├┬┘├┤ │  ├┤ ├─┤└─┐├┤
      //  ┴ ┴└─┘ ┴   ┴└─└─┘┴─┘└─┘┴ ┴└─┘└─┘

      switch( e.key.keysym.sym )
      {
        case SDLK_UP:
          cout << "  up  key let go";
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
          cout << "left click at x:" << e.button.x << " y:" << e.button.y;
          break;

        case SDL_BUTTON_MIDDLE:
          cout << "middle click at x:" << e.button.x << " y:" << e.button.y;
          break;

        case SDL_BUTTON_RIGHT:
          cout << "right click at x:" << e.button.x << " y:" << e.button.y;
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
          cout << "left click released at x:" << e.button.x << " y:" << e.button.y;
          break;

        case SDL_BUTTON_MIDDLE:
          cout << "middle click released at x:" << e.button.x << " y:" << e.button.y;
          break;

        case SDL_BUTTON_RIGHT:
          cout << "right click released at x:" << e.button.x << " y:" << e.button.y;
          break;
      }
    }
    cout << " at time " << e.key.timestamp << endl << endl;
  }
}


void game::draw_that_shit()
{
  SDL_RenderClear(ren); //clear our background

  if(SDL_GetTicks() < 5000)
  {

    SDL_Rect SrcRect; //where are we taking pixels from?
    SDL_Rect DestRect;  //the pixels we took from SrcRect?

    SrcRect.x = 0;
    SrcRect.y = 0;
    SrcRect.w = 720;
    SrcRect.h = 405;

    DestRect.x = 0;
    DestRect.y = 0;
    DestRect.w = 720;
    DestRect.h = 405;

    SDL_RenderCopy(ren, splash, &SrcRect, &DestRect);
    SDL_RenderPresent(ren); //swap buffers so that this most recently drawn material is shown to the user

    SDL_Delay(1200);

  }
  else
  {

    SDL_SetRenderDrawColor(ren,45,38,22,SDL_ALPHA_OPAQUE); //set the color you want to draw with

    SDL_Rect fullscreen;
    fullscreen.x = 0;
    fullscreen.y = 0;
    fullscreen.w = 720;
    fullscreen.h = 480;
    //put a base layer of that color down
    SDL_RenderFillRect(ren, &fullscreen);

    //set the new color to draw with
    SDL_SetRenderDrawColor(ren,45,45,45,SDL_ALPHA_OPAQUE); //set the color you want to draw with

    //learning how to chop up images with https://wiki.libsdl.org/SDL_RenderCopy
    //rectangles tell SDL where you want to read from/write from -

    //The implication here is that you have the opportunity to define where your pixels are going to show up on the screen, and what shape will they be.
    //Squashing/stretching can be achieved by changing the shape of that rectangle - look at the random generation of widths/heights to see examples.

    SDL_Rect SrcRect; //where are we taking pixels from?
    SDL_Rect DestRect;  //the pixels we took from SrcRect?

    //these random number generators give me some ability to randomly place the destination rectangles - you'll see
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> xdist(0,619);  //between zero and the width of the image
    std::uniform_int_distribution<int> sxdist(0,720);  //between zero and the width of the screen
    std::uniform_int_distribution<int> ydist(0,387);  //between zero and the height of the image
    std::uniform_int_distribution<int> sydist(0,480);  //between zero and the height of the screen
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
          DestRect.x = x*(620/4)+80+10*cos(0.0004f*SDL_GetTicks());
          DestRect.y = y*(387/4)+70+4*sin(0.0004f*SDL_GetTicks());
          DestRect.w = (620/4)-60+40*cos(0.0004f*SDL_GetTicks());
          DestRect.h = (387/4)-40+10*sin(0.0004f*SDL_GetTicks());
        }
        else
        { //give me some random location to draw this shit at
          DestRect.x = xdist(mt);     //tell me where that shit's at on x
          DestRect.y = ydist(mt);    //tell me where that shit's at on y
          DestRect.w = wdist(mt);   //tell me how wide that shit is
          DestRect.h = hdist(mt);  //tell me how tall that shit is
        }

        for(int i = 0; i < 4500; i++)
        {
          SDL_RenderDrawPoint(ren, sxdist(mt), sydist(mt));
        }

        SDL_RenderCopy(ren, tex, &SrcRect, &DestRect);  //copy from SrcRect to DestRect
      }//end y
    }//end x

    SDL_RenderPresent(ren); //swap buffers so that this most recently drawn material is shown to the user

    if(!aligned)
      SDL_Delay(1200); //wait some period of time so as not to cause as bad a seizure
  }

}
