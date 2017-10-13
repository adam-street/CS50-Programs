#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>     // uint8_t
#include <sys/stat.h>   // stat()

int main(int argvc, char *argv[])
{
    // check for correct command line arg
    if(argvc != 2)
    {
        fprintf(stderr, "Usage: ./recover infile\n");
        return 1;
    }

    // save filename
    char *file = argv[1];

    //open infile
    FILE *card = fopen(file, "r");

    // check that infile opened correctly
    if(card == NULL)
    {
        fprintf(stderr, "Could not open infile\n");
        return 2;
    }

    // find the infiles length
    struct stat st;
    stat(file, &st);

    // create a pointer to use when creating jpgs
    FILE *pic;

    // create a buffer to store the file names and a counter to store the file count
    char name_buffer[8];
    int file_count = 0;

    // define the size of a block
    uint8_t block[512];

    // get the amount of blocks in the infile
    long block_count = st.st_size / sizeof(block);

    // create a var to keep track of file status (0 = closed / 1 = open)
    int file_open = 0;

    for (long i=0; i < block_count; i++)
    {
        // read block
        fread(&block , sizeof(block), 1, card);

        //check first 3 bytes for "magic numbers"
        if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && (block[3] & 0xf0) == 0xe0)
        {
            //check that file is open then close it and add to file counter
            if(file_open == 1)
            {
                file_count++;
                fclose(pic);
            }

            // convert file counter to char* then create a file with that name and mark file as open
            sprintf(name_buffer,"%03d.jpg", file_count);
            pic = fopen(name_buffer, "w");
            file_open = 1;


            //error checking
            if(pic == NULL)
            {
                fprintf(stderr, "Could not create new jpg.\n");
                return 3;
           }
        }

        //check that file is open then write block
        if(file_open == 1)
            fwrite(&block, sizeof(block), 1, pic);

    }

    //close files
    fclose(pic);
    fclose(card);

    //end
    return 0;
}