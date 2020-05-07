#include "helpers.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int b = 0;
    int g = 0;
    int r = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            b = image[i][j].rgbtBlue;
            g = image[i][j].rgbtGreen;
            r = image[i][j].rgbtRed;

            float avg = (b + g + r)/3.0; //must use 3.0 instead of 3 when assigning as float.
            //if not it will round down for u instead of rounding up

            if (avg > 255)
            {
                avg = 255;
            }

            image[i][j].rgbtBlue = round(avg);
            image[i][j].rgbtGreen = round(avg);
            image[i][j].rgbtRed = round(avg);

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        int halfwidth = 0;
        halfwidth = floor(width/2);

        for (int j = 0; j < halfwidth; j++)
        {
            int newj = width -1 - j;
            int tempBlue = 0;
            int tempGreen = 0;
            int tempRed = 0;
            //set temp variables to store initial position
            tempBlue = image[i][j].rgbtBlue;
            tempGreen = image[i][j].rgbtGreen;
            tempRed = image[i][j].rgbtRed;
            //swap
            image[i][j].rgbtBlue = image[i][newj].rgbtBlue;
            image[i][j].rgbtGreen = image[i][newj].rgbtGreen;
            image[i][j].rgbtRed = image[i][newj].rgbtRed;

            //assign temp to new position
            image[i][newj].rgbtBlue = tempBlue;
            image[i][newj].rgbtGreen = tempGreen;
            image[i][newj].rgbtRed = tempRed;

            //./filter -r images/tower.bmp out.bmp
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE newimage[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float count = 0;
            float sumb = 0;
            float sumg = 0;
            float sumr = 0;

            for (int x = -1; x < 2; x++) //i
            {

                for (int y = -1; y < 2; y++)//j //is this necessary? put between i & j?
                {
                    int ht = i+x;//height
                    int hz = j+y; //width

                    if (ht >= 0 && ht < height && hz >= 0 && hz < width)
                    {

                        int b = image[ht][hz].rgbtBlue;
                        int g = image[ht][hz].rgbtGreen;
                        int r = image[ht][hz].rgbtRed;
                        sumb = sumb + b;
                        sumg = sumg + g;
                        sumr = sumr + r;
                        count++; //count may be correct

                    }
                }

            }

            int avgb = round(sumb/count); // will lead to rounding down problems again
            int avgg = round(sumg/count);// need to change count to float
            int avgr = round(sumr/count);

            newimage[i][j].rgbtBlue = avgb; //do not assign to ij will be replaced with the avg values
            newimage[i][j].rgbtGreen = avgg;//avg values will be used in the next calculation of pixels
            newimage[i][j].rgbtRed = avgr; //only assign values AFTER all avg has been computed

        }
    }
    //./filter -b images/yard.bmp out.bmp

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = newimage[i][j].rgbtBlue;
            image[i][j].rgbtGreen = newimage[i][j].rgbtGreen;
            image[i][j].rgbtRed = newimage[i][j].rgbtRed;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE newimage[height][width];
    int Gx[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};
    int Gy[3][3] = {{-1,-2,-1},{0,0,0},{1,2,1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //sum of gx kernal
            int sumgxb = 0;
            int sumgxg = 0;
            int sumgxr = 0;
            //sum of gy kernal
            int sumgyb = 0;
            int sumgyg = 0;
            int sumgyr = 0;
            
            for (int x = -1; x < 2; x++) //i
            {

                for (int y = -1; y < 2; y++)//j //is this necessary? put between i & j?
                {
                    int ht = i+x;//height
                    int hz = j+y; //width

                    int kht = 1+x; //kernal height
                    int khz = 1+y; //kernal width

                    //colours of each pixel
                    int b = 0;
                    int g = 0;
                    int r = 0;
                    //weighted pixels for Gx
                    int gxb = 0;
                    int gxg = 0;
                    int gxr = 0;
                    
                    //weighted pixels for Gy
                    int gyb = 0;
                    int gyg = 0;
                    int gyr = 0;                    

                    if (ht >= 0 && ht < height && hz >= 0 && hz < width) //for kernal within image boundary
                    {
                        b = image[ht][hz].rgbtBlue;
                        g = image[ht][hz].rgbtGreen;
                        r = image[ht][hz].rgbtRed;
                    }

                    else //for kernal exceeding image boundary
                    {
                        b = 0;
                        g = 0;
                        r = 0;
                    }

                        gxb = b*Gx[kht][khz];
                        gxg = g*Gx[kht][khz];
                        gxr = r*Gx[kht][khz];
                        
                        gyb = b*Gy[kht][khz];
                        gyg = g*Gy[kht][khz];
                        gyr = r*Gy[kht][khz];

                        sumgxb = sumgxb + gxb;
                        sumgxg = sumgxg + gxg;
                        sumgxr = sumgxr + gxr;

                        sumgyb = sumgyb + gyb;
                        sumgyg = sumgyg + gyg;
                        sumgyr = sumgyr + gyr;                        
                }

            }
            
            int finalb = round(sqrt(pow(sumgxb,2) + pow(sumgyb,2)));
            int finalg = round(sqrt(pow(sumgxg,2) + pow(sumgyg,2)));
            int finalr = round(sqrt(pow(sumgxr,2) + pow(sumgyr,2)));
            
            if (finalb > 255)
            {
                finalb = 255;
            }
            
            if (finalg > 255)
            {
                finalg = 255;
            }
            
            if (finalr > 255)
            {
                finalr = 255;
            }

            newimage[i][j].rgbtBlue = finalb; //do not assign to ij will be replaced with the avg values
            newimage[i][j].rgbtGreen = finalg;//avg values will be used in the next calculation of pixels
            newimage[i][j].rgbtRed = finalr; //only assign values AFTER all avg has been computed

        }
    }
    

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = newimage[i][j].rgbtBlue;
            image[i][j].rgbtGreen = newimage[i][j].rgbtGreen;
            image[i][j].rgbtRed = newimage[i][j].rgbtRed;
        }
    }
    
    //./filter -e images/stadium.bmp out.bmp
    return;
}
