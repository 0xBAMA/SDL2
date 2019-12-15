#include <SDL2/SDL.h>
// #include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <cstdlib>
#include <iostream>

int main()
{
    using std::cerr;
    using std::endl;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        cerr << "SDL_Init Error: " << SDL_GetError() << endl;
        return EXIT_FAILURE;
    }

    SDL_Window* win = SDL_CreateWindow("Hello World!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 720, 480, SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL);

    if (win == nullptr)
    {
        cerr << "SDL_CreateWindow Error: " << SDL_GetError() << endl;
        return EXIT_FAILURE;
    }

    SDL_SetWindowFullscreen(win, SDL_WINDOW_FULLSCREEN);




    SDL_Renderer* ren
        = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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


//need to get SDL_image working first
    // SDL_Surface* png = SDL_LoadIMG("grumpy-cat.png");
    // if (png == nullptr)
    // {
    //     cerr << "SDL_LoadPNG Error: " << SDL_GetError() << endl;
    //     return EXIT_FAILURE;
    // }




    SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, bmp);
    SDL_FreeSurface(bmp);
    if (tex == nullptr)
    {
        cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << endl;
        return EXIT_FAILURE;
    }







    TTF_Font* Sans = TTF_OpenFont("ShareTechMono-Regular.ttf", 12); //this opens a font style and sets a size

    SDL_Color yellow = {218, 200, 18};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "put your dang ol' text here", yellow); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

    SDL_Texture* Message = SDL_CreateTextureFromSurface(ren, surfaceMessage); //now you can convert it into a texture
    SDL_FreeSurface(surfaceMessage);


    SDL_Rect Message_rect; //create a rect
    Message_rect.x = 0;  //controls the rect's x coordinate
    Message_rect.y = 0; // controls the rect's y coordinte
    Message_rect.w = 100; // controls the width of the rect
    Message_rect.h = 100; // controls the height of the rect

    // //Mind you that (0,0) is on the top left of the window/screen, think a rect as the text's box, that way it would be very simple to understance
    // SDL_RenderCopy(renderer, Message, NULL, &Message_rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture
    // //Don't forget too free your surface and texture






    for (int i = 0; i < 20; i++)
    {
        SDL_RenderClear(ren);
        SDL_RenderCopy(ren, tex, nullptr, nullptr);
        SDL_RenderCopy(ren, Message, NULL, &Message_rect);
        SDL_RenderPresent(ren);
        SDL_Delay(100);
    }

    SDL_DestroyTexture(tex);
    SDL_DestroyTexture(Message);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return EXIT_SUCCESS;
}
