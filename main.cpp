#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <fstream>
using namespace std;
//function coverting tgb to gray scale
//returns value that equals from 0 to 7
int RGBAtoGray(Uint8* r, Uint8* g, Uint8* b, Uint8* a);
int main(int argc,char*argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);//initializing the SDL

    SDL_Surface*surface=NULL;//declaring and defining the structure that hold our surface
    fstream str;//stream used to save our output

    char decoder[]={'.',//table that is contained with characters used to convert gray scale value to ascii
    ',',
    '*',
    '^',
    ';',
    'i',
    '!',
    '#'};

    string*path=new string;//pointer to our path to picture
    string *output=new string;//output saved in output.txt

    if(argc<2){SDL_Log("Insufficient amount of arguments...");return 0;}
    else
    {
        *path=argv[1];
    }

    surface=IMG_Load(path->c_str());//load the picture

    if(surface!=NULL)//if surface is loaded properly
    {
        Uint8 r,g,b,a;
        a=255;//just in case if the picture is in RGB format
        int value;//value of our gray scale
        int height=surface->h;//height of our picture

        SDL_LockSurface(surface);//allows us to get access to pixels
        int bytes=(int)(surface->format->BytesPerPixel);//coun of bytes in pixel - deciding whether it is RGB or RGBA
        Uint8* pixels=(Uint8*)surface->pixels;//pointer to our pixels - exactlyt to one
        int pitch=surface->pitch; 
        for(unsigned int y=0;y<height;y++)
        {
            for(unsigned int x=0;x<pitch;x+=bytes)
            {
                switch(bytes)//check whether the picture is in RGB or RGBA
                {
                case 3://picture is saved in RGB
                    {
                        break;
                    }
                case 4://picture is saved in RGBA
                    {
                        a=pixels[pitch*y+x+3];
                    }
                }
                //caluclating the offsetts of each color of pixel
                r=pixels[pitch*y+x];
                g=pixels[pitch*y+x+1];
                b=pixels[pitch*y+x+2];
                //converting to gray scale
                value=RGBAtoGray(&r,&g,&b,&a);
                //adding result oour output string
                *output+=decoder[value];
            }
            *output+="\n";
        }
        SDL_UnlockSurface(surface);//finish reading pixels and low level access to picture
        //save the output to output.txt
        str.open("output.txt",ios_base::trunc|ios_base::out|ios_base::in);
        str<<*output;
        str.close();
    }
    else//if not - return the error code
    {
        SDL_Log(SDL_GetError());
    }
    //clear the memory
    delete path;
    delete output;
    SDL_FreeSurface(surface);
    return 0;
}

int RGBAtoGray(Uint8* r,Uint8* g,Uint8* b,Uint8* a)
{
    Uint8 value=((*r+1)>>7)+((*g+1)>>7)+((*b+1)>>7)+((*a+1)>>7);
    if(value!=0)//to prevent function from returning  -1
    {
        return value-1;
    }
    return value;
}
