#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STB_IMAGE_IMPLEMENTATION
#include "./headers/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "./headers/stb_image_write.h"

/**
 * Create a new 1-dimensional array with the given size
 * @param[in] _size the size of the array
 * @param[out] _ empty 1-dimensional array filled with 0
 */

unsigned char *uc_arrayNew_1d(int _size)
{
    return (unsigned char *)calloc(_size, sizeof(unsigned char));
}

void*background_subtraction(unsigned char *image,unsigned char *image_2,int width, int height, int channel)
{
    unsigned char *temp_array = uc_arrayNew_1d(width * height * channel);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int check = 0;
            for (int k = 0; k < channel; k++)
            {
                if(abs(image[i * width * channel + j * channel + k] - image_2[i * width * channel + j * channel + k]) < 80)
                {
                    check++;
                }
            }
            for (int k = 0; k < channel; k++)
            {
                if(check == 3)
                {
                    temp_array[i * width * channel + j * channel + k] = 0;
                }
                else
                {
                    temp_array[i * width * channel + j * channel + k] = image_2[i * width * channel + j * channel + k];
                }
            }
        }
        }
    return temp_array;
}
unsigned char *background_addition(unsigned char *image_sub_1, unsigned char *image_1, int width, int height, int channel)
{
    unsigned char *temp_array = uc_arrayNew_1d(width * height * channel);
    unsigned char n = image_sub_1[1*1*4+1];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            for (int j = 0; j < width; j++)
        {
                for (int k = 0; k < channel; k++)
                if (image_sub_1[i * width * channel + j * channel + k] == 0)
                {
                        temp_array[i * width * channel + j * channel + k] = image_1[i * width * channel + j * channel + k];
                }
                else
                {

                        temp_array[i * width * channel + j * channel + k] = image_sub_1[i * width * channel + j * channel + k];
                    
                }
        }
        }       
    }
    return temp_array;
            
}



int main()
{
    // declare variables
    int width, height, channel;
    char path_img[] = "./images/background.jpg";
    char save_path[] = "./images/98239648_p0-New.jpg";

    char path_img_1[]= "./images/new_background.jpg";
    char path_img_2[] = "./images/foreground.jpg";
    char save_path_1[] = "./images/98239648_p1-New.jpg";


    // read image data
    unsigned char *image   = stbi_load(path_img, &width, &height, &channel, 0);
    unsigned char *image_1 = stbi_load(path_img_1, &width, &height, &channel, 0);
    unsigned char *image_2 = stbi_load(path_img_2, &width, &height, &channel, 0);
    if ((image== NULL) &&(image_2 == NULL) )
    {
        printf("\nError in loading the image\n");
        exit(1);
    }
    printf("Width = %d\nHeight = %d\nChannel = %d\n", width, height, channel);

    //background subtraction
    unsigned char *image_sub_1 = background_subtraction(image,image_2,width,height,channel);
    unsigned char *image_add_1 = background_addition(image_sub_1,image_1,width,height,channel);
    stbi_write_png(save_path, width, height, channel, image_add_1, width * channel);
    printf("New image saved to %s\n", save_path);
}