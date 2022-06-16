#include <iostream>
#include <stdio.h>
#include "./lodepng/lodepng.h"
#include <vector>
#include <chrono>
#include <thread>
#include <string>
//#include <fcntl.h>
#include <unistd.h>

#define TERMINAL_H 80
#define TERMINAL_W 150
#define FPS 30
// using namespace std;

int main(int argc, char **argv)
{
    // char *filename = "frames/frame0.png";
    std::string folder = "frames";
    if (argc == 2)
        folder = argv[1];
    //std::vector<unsigned char> image; // the raw pixels
    unsigned width, height;
    std::vector<std::vector<unsigned char>> images;
    std::vector<std::vector<unsigned>> dims;
    // decode
    unsigned error = 0;
    int count = 0;
    std::string fname = folder + "/frame";
    printf("\x1b[?25l");
    int waitInterval = 1000 / FPS;
    while(!error){
        images.push_back(std::vector<unsigned char>());
        dims.push_back(std::vector<unsigned>(2,0));
         error = lodepng::decode(images[count], dims[count][1],  dims[count][0], fname + std::to_string(count) + ".png");
         count++;
          printf("\x1B[2J\x1B[H");
         printf("loading %d\n",count);
         
    }
    //printf("size %d\n",images.size());
    for(int t=0;t<images.size();t++)
    {
        auto start = std::chrono::system_clock::now();
        // write(1,"hi",2);
       printf("\x1B[2J\x1B[H");
        
       // image.clear();
        // printf("count %d\n",count);
        // for (int i = 0; i < TERMINAL_H + 10; i++)
        //     printf("\n");
        // system("clear");

       // error = lodepng::decode(image, width, height, fname + std::to_string(count) + ".png");

        // if there's an error, display it
        // if (error)
        // {
        //     std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
        //     break;
        // }

        // the pixels are now in the vector "image", 4 bytes per pixel, ordered RGBARGBA..., use it as texture, draw it, ...
        // printf("height %d width %d sizeOfVector %d w*h*4 %d\n",height,width,image.size(),height*width*4);

        // convet from hxw to thxtw
        //char screen[TERMINAL_H * TERMINAL_W * 3];
        height = dims[t][0];
        width = dims[t][1];
        unsigned int aspectH = height / TERMINAL_H;
        unsigned int aspectW = width / TERMINAL_W;
        for (int i = 0; i < height * 4; i += 4 * aspectH)
        {
            for (int j = 0; j < width * 4; j += 4 * aspectW)
            {
                // R G B (A -> ignored)
                unsigned int r = images[t][j + i * width];
                unsigned int g = images[t][j + i * width + 1];
                unsigned int b = images[t][j + i * width + 2];
                printf("\x1b[48;2;%d;%d;%dm \x1b[0m", r, g, b);
                // printf("i %d j %d indx %d\n",i,j,j+i*width);
            }
            printf("\n");
        }
        std::chrono::duration<double> interval = std::chrono::system_clock::now() - start;
        int msec = interval.count() * 1000;
        //printf("wait %d %d\n",waitInterval,msec);

       std::this_thread::sleep_for(std::chrono::milliseconds(std::max((int)1, waitInterval - msec)));
        //std::this_thread::sleep_for(std::chrono::milliseconds(5));
        //count++;
    }

    return 0;
}

/**
 * @brief
 * ESC[38;2;{r};{g};{b}m	Set foreground color as RGB.
ESC[48;2;{r};{g};{b}m  Set background color as RGB.
"\x1b[48;2;255;0;0m \x1b[0m"

 *
 */