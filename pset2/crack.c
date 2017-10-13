#include <stdio.h>
#include <cs50.h>
#include <string.h>

#define _GNU_SOURCE
#include <crypt.h>
#include <stdlib.h>

void crack_password(string cached_hash);

int main(int argc, string argv[])
{
    //validate command line argument
    if(argc != 2)
    {
        printf("Error 1: Missing command line argument or too many arguments.\n");
        return 1;
    }

    //run crack
    crack_password(argv[1]);
}

void crack_password(string cached_hash)
{
    //build salt string by looking at first two chars of the input hash
    char salt[3];
    salt[0] = cached_hash[0];
    salt[1] = cached_hash[1];
    salt[2] = '\0';

    //loop for space 1
    for(int i = 'A'; i <= 'z'; i++){

        //build password string
        char password1[2];
        password1[0] = i;
        password1[1] = '\0';

        //build hash
        string hash1 = crypt(password1, salt);

        //compare hash to input hash
        if(strcmp(cached_hash, hash1) == 0) //returns 0 if match
        {
            printf("%s\n", password1);
            return;
        }

        //loop for space 2
        for(int j = 'A'; j <= 'z'; j++){

            //build password string
            char password2[3];
            password2[0] = i;
            password2[1] = j;
            password2[2] = '\0';

            //build hash
            string hash2 = crypt(password2, salt);

            //compare hash to input hash
            if(strcmp(cached_hash, hash2) == 0) //returns 0 if match
            {
                printf("%s\n", password2);
                return;
            }

            //loop for space 3
            for(int k = 'A'; k <= 'z'; k++){

                //build password string
                char password3[4];
                password3[0] = i;
                password3[1] = j;
                password3[2] = k;
                password3[3] = '\0';

                //build hash
                string hash3 = crypt(password3, salt);

                //compare hash to input hash
                if(strcmp(cached_hash, hash3) == 0) //returns 0 if match
                {
                    printf("%s\n", password3);
                    return;
                }

                //loop for space 3
                for(int l = 'A'; l <= 'z'; l++){

                    //build password string
                    char password4[5];
                    password4[0] = i;
                    password4[1] = j;
                    password4[2] = k;
                    password4[3] = l;
                    password4[4] = '\0';

                    //build hash
                    string hash4 = crypt(password4, salt);

                    //compare hash to input hash
                    if(strcmp(cached_hash, hash4) == 0) //returns 0 if match
                    {
                        printf("%s\n", password4);
                        return;
                    }

                }
            }
        }
    }

    printf("Password not found!\n");
}