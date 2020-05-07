#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

//global variables
//int blocks = 1;
int count = 0;

//functions
void recursion(int *buffer);
bool findblocks(int *buffer, FILE *file);

int main(int argc, char *argv[])
{
    // Check usage
    if (argc != 2)
    {
        printf("Usage: %s image\n", argv[0]);
        return 1;
    }

    //unsigned char buffer[512]; //buffer array holding 512 bytes
    char filename[8];
    //unsigned char *filename = malloc(sizeof(char));
    unsigned char *buffer = malloc(512 * sizeof(unsigned char)); //malloc must use unused char

    // Open file
    FILE *file = fopen(argv[1], "r");

    if (!file)
    {
        printf("Unable to open file!");
        return 1;
    }

    bool firstjpg = true;
    bool jpgexists = false;
    FILE *img = NULL;

    while(fread(buffer,512,1,file)==1)
    {

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {

            if (firstjpg == true) //if it is the first jpeg
            {
                firstjpg = false;
                jpgexists = true;
            }

            else //if firstjpg = false;
            {
                fclose(img); //if jpg exists and another jpg header is found, close previous one
                //free(buffer);
                firstjpg = false;
                jpgexists = true;
            }


            sprintf(filename,"%03i.jpg",count);
            img = fopen(filename, "w"); //open file
            fwrite(buffer,512,1,img); //write data to it
            count++; //increase count only if header jpg are found //update with new count

        }

        else //if jpg header files not found
        {
            if (jpgexists == true) //& if jpg alr exists
            {
                fwrite(buffer,512,1,img); //continue writing to img
            }

        }

    }

    fclose(img);
    free(buffer);
    fclose(file);
    return 0;
}