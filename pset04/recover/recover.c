#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef uint8_t BYTE;
const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
    }

    FILE *raw_file = fopen(argv[1], "r");
    if (raw_file == NULL)
    {
        return 1;
    }

    BYTE *buffer = malloc(BLOCK_SIZE);

    int count = 0;
    char *filename = malloc(strlen("###.jpg") + 1);
    while (fread(buffer, 1, BLOCK_SIZE, raw_file) == BLOCK_SIZE)
    {
        printf("buffer[0]=%x, buffer[1]=%x, buffer[2]=%x\n", buffer[0], buffer[1], buffer[2]);
        if ((buffer[0] == 0xff) &&
            (buffer[1] == 0xd8) &&
            (buffer[2] == 0xff) &&
            ((buffer[3] & 0xf0) == 0xe0))
        {

            sprintf(filename, "%03i.jpg", count);
            FILE *file_jpg = fopen(filename, "w");
            fwrite(buffer, 1, BLOCK_SIZE, file_jpg);
            fclose(file_jpg);
            count++;
        }
        else
        {
            if (count > 0)
            {
                FILE *file_jpg = fopen(filename, "a");
                fwrite(buffer, 1, BLOCK_SIZE, file_jpg);
                fclose(file_jpg);
            }
        }
    }
    free(filename);
    free(buffer);
    fclose(raw_file);
}