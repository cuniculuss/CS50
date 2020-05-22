#include "helpers.h"
#include <math.h>

void blue(int i, int j, int height, int width, RGBTRIPLE image[height][width], RGBTRIPLE copy[height][width]);
void green(int i, int j, int height, int width, RGBTRIPLE image[height][width], RGBTRIPLE copy[height][width]);
void red(int i, int j, int height, int width, RGBTRIPLE image[height][width], RGBTRIPLE copy[height][width]);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
        for (int i = 0; i < height; i++)
        {
                for (int j = 0; j < width; j++)
                {
                        float average = image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen;
                        average = round(average / 3);
                        image[i][j].rgbtBlue = (int) average;
                        image[i][j].rgbtRed = (int) average;
                        image[i][j].rgbtGreen = (int) average;
                }
        }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
        for (int i = 0; i < height; i++)
        {
                for (int j = 0; j < width; j++)
                {
                        int b = round (0.131*image[i][j].rgbtBlue + 0.272*image[i][j].rgbtRed + 0.534*image[i][j].rgbtGreen);
                        int r = round(0.189*image[i][j].rgbtBlue + 0.393*image[i][j].rgbtRed + 0.769*image[i][j].rgbtGreen);
                        int g = round(0.168*image[i][j].rgbtBlue + 0.349*image[i][j].rgbtRed + 0.686*image[i][j].rgbtGreen);
                        if (b  > 255)
                                image[i][j].rgbtBlue = 255;
                        else
                                image[i][j].rgbtBlue = b;
                        if (g > 255)
                                image[i][j].rgbtGreen = 255;
                        else
                                image[i][j].rgbtGreen = g;
                        if (r  > 255)
                                image[i][j].rgbtRed = 255;
                        else
                                image[i][j].rgbtRed = r;
                }
        }
    return;
}


// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

        for (int i = 0; i < height; i++)
        {
                for (int j = 0; j < width / 2; j++)
                {
                        int t = image[i][j].rgbtBlue;
                        image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
                        image[i][width - j - 1].rgbtBlue = t;
                        t = image[i][j].rgbtRed;
                        image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
                        image[i][width - j - 1].rgbtRed = t;
                        t = image[i][j].rgbtGreen;
                        image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
                        image[i][width - j - 1].rgbtGreen = t;
                }
        }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j].rgbtBlue = image[i][j].rgbtBlue;
            copy[i][j].rgbtRed = image[i][j].rgbtRed;
            copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
        }
    }
        for (int i = 0; i < height; i++)
        {
                for (int j = 0; j < width; j++)
                {
                        blue(i, j, height, width, image, copy);
                        red(i, j, height, width, image, copy);
                        green(i, j, height, width, image, copy);
                }
        }

    return;
}

void blue(int i, int j, int height, int width, RGBTRIPLE image[height][width], RGBTRIPLE copy[height][width])
{
                        int average = 0;
                        int count = 0;
                        if (i != 0)
                        {
                                if (j != 0)
                                {
                                        average += copy[i - 1][j - 1].rgbtBlue;
                                        count++;
                                }
                                average += copy[i - 1][j].rgbtBlue;
                                count++;
                                if (j != width - 1)
                                {
                                        average += copy[i - 1][j + 1].rgbtBlue;
                                        count++;
                                }
                        }

                        if (i != height - 1)
                        {

                                if (j != 0)
                                {
                                        average += copy[i + 1][j - 1].rgbtBlue;
                                        count++;
                                }
                                average += copy[i + 1][j].rgbtBlue;
                                count++;
                                if (j != width - 1)
                                {
                                        average += copy[i + 1][j + 1].rgbtBlue;
                                        count++;
                                }
                        }
                        if (j != 0)
                        {
                                average += copy[i][j - 1].rgbtBlue;
                                count++;
                        }
                        average += copy[i][j].rgbtBlue;
                        count++;
                        if (j != width - 1)
                        {
                                average += copy[i][j + 1].rgbtBlue;
                                count++;
                        }

                        image[i][j].rgbtBlue = round((float) average / count);
}


void red(int i, int j, int height, int width, RGBTRIPLE image[height][width], RGBTRIPLE copy[height][width])
{

                        int average = 0;
                        int count = 0;
                        if (i != 0)
                        {
                                if (j != 0)
                                {
                                        average += copy[i - 1][j - 1].rgbtRed;
                                        count++;
                                }
                                average += copy[i - 1][j].rgbtRed;
                                count++;
                                if (j != width - 1)
                                {
                                        average += copy[i - 1][j + 1].rgbtRed;
                                        count++;
                                }
                        }

                        if (i != height - 1)
                        {

                                if (j != 0)
                                {
                                        average += copy[i + 1][j - 1].rgbtRed;
                                        count++;
                                }
                                average += copy[i + 1][j].rgbtRed;
                                count++;
                                if (j != width - 1)
                                {
                                        average += copy[i + 1][j + 1].rgbtRed;
                                        count++;
                                }
                        }

if (j != 0)
                        {
                                average += copy[i][j - 1].rgbtRed;
                                count++;
                        }
                        average += copy[i][j].rgbtRed;
                        count++;
                        if (j != width - 1)
                        {
                                average += copy[i][j + 1].rgbtRed;
                                count++;
                        }
                        image[i][j].rgbtRed = round((float) average / count);
}





void green(int i, int j, int height, int width, RGBTRIPLE image[height][width], RGBTRIPLE copy[height][width])
{

                        int average = 0;
                        int count = 0;
                        if (i != 0)
                        {
                                if (j != 0)
                                {
                                        average += copy[i - 1][j - 1].rgbtGreen;
                                        count++;
                                }
                                average += copy[i - 1][j].rgbtGreen;
                                count++;


                                if (j != width - 1)
                                {
                                        average += copy[i - 1][j + 1].rgbtGreen;
                                        count++;
                                }
                        }

                        if (i != height - 1)
                        {

                                if (j != 0)
                                {
                                        average += copy[i + 1][j - 1].rgbtGreen;
                                        count++;
                                }
                                average += copy[i + 1][j].rgbtGreen;
                                count++;
                                if (j != width - 1)
                                {
                                        average += copy[i + 1][j + 1].rgbtGreen;
                                        count++;
                                }
                        }

                        if (j != 0)
                        {
                                average += copy[i][j - 1].rgbtGreen;
                                count++;
                        }
                        average += copy[i][j].rgbtGreen;
                        count++;
                        if (j != width - 1)
                        {
                                average += copy[i][j + 1].rgbtGreen;
                                count++;
                        }
                        image[i][j].rgbtGreen = round((float) average / count);

}

