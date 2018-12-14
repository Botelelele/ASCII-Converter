#include <SDL2/SDL.h>
#include <string>
#include <SDL2/SDL_image.h>
#include <fstream>
using namespace std;
int RGBAtoGray(Uint8* r, Uint8* g, Uint8* b, Uint8* a);
int main(int argc,char*argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Surface*surface=NULL;
    fstream str;
    char decoder[]={'.',
    ',',
    '*',
    '^',
    ';',
    'i',
    '!',
    '#'
    };
    string*path=new string;
    string *output=new string;
    if(argc<2){SDL_Log("Insufficient amount of arguments...");return 0;}
    else
    {
        *path=argv[1];
    }
    surface=IMG_Load(path->c_str());
    //600*450
    if(surface!=NULL)
    {
        Uint8 r,g,b,a;
        a=255;
        int value;
        int height=surface->h;
        SDL_LockSurface(surface);
        int bytes=(int)(surface->format->BytesPerPixel);
        Uint8* pixels=(Uint8*)surface->pixels;
        int pitch=surface->pitch;
        for(unsigned int x=0;x<pitch;x+=bytes)
        {
            for(unsigned int y=0;y<height;y++)
            {
                switch(bytes)
                {
                case 3:
                    {
                        break;
                    }
                case 4:
                    {
                        a=pixels[pitch*y+x+3];
                    }
                }
                r=pixels[pitch*y+x];
                g=pixels[pitch*y+x+1];
                b=pixels[pitch*y+x+2];
                value=RGBAtoGray(&r,&g,&b,&a);
                *output+=decoder[value];
            }
            *output+="\n";
        }
        SDL_UnlockSurface(surface);
        str.open("output.txt",ios_base::trunc|ios_base::out|ios_base::in);
        str<<*output;
        str.close();
    }
    else
    {
        SDL_Log(SDL_GetError());
    }
    delete path;
    delete output;
    SDL_FreeSurface(surface);
    return 0;
}

int RGBAtoGray(Uint8* r,Uint8* g,Uint8* b,Uint8* a)
{
    Uint8 value=((*r+1)>>7)+((*g+1)>>7)+((*b+1)>>7)+((*a+1)>>7);
    if(value!=0)
    {
        return value-1;
    }
    return value;
}
