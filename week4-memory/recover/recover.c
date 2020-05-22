#include <stdio.h>
#include <stdlib.h>

#define TRUE 1

int main(int argc, char *argv[])
{
    // checks for correct number of arguments (1)
    if (argc != 2)
    {
        printf("Usage: recover file.\n");
        return 1;
    }

    // Opens source file
    FILE *source = fopen(argv[1], "r");

    // Checks if file opens correctly
    if (!source)
    {
        printf("The program failed trying to open the file.\n");
        return 1;
    }

    int count = 0;
    FILE *photo;
    char filename[9];
    int block = 512;
    while (TRUE)
    {
        // Reads block of 512 bytes
        unsigned char bytes[block];
        if (fread(bytes, block, 1, source) == 0)
            break;

        // Check first three bytes
        if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff && (bytes[3] & 0xf0) == 0xe0)
        {
            // printf formated file number to string filename
            sprintf(filename, "%03i.jpeg", count);

            photo = fopen(filename, "w");
            fwrite(bytes, block, 1, photo);
            fclose (photo);
            count++;
        }
        else if (count > 0)
        {
            photo = fopen (filename, "a");
            fwrite (bytes, block, 1, photo);
            fclose (photo);
        }
    }

    // Close file
    fclose(source);

}


