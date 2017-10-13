#import <stdio.h>
#import <cs50.h>
#import <string.h>   // for strlen
#import <stdlib.h>  // for atoi

char ceasar_cipher(int c, int secret);

int main(int argvc, string argv[])
{
    //validate command line argument
    if(argvc != 2)
    {
        printf("Error 1: Invalid command line argument.\n");
        return 1;
    }
    
    //store secret from command line as int
    int secret = atoi(argv[1]);
    
    //get text to encrypt
    printf("plaintext: ");
    string plainText = get_string();
    
    //get plainText length
    int count = strlen(plainText);
    
    //loop through each char in input and run ceasar_cipher then print return
    printf("ciphertext: ");
    for(int i=0; i<count; i++)
    {
        printf("%c", (char) ceasar_cipher((int) plainText[i], secret));    
    }
    
    //start a new line and end program with 0
    printf("\n");
    return 0;
}

//takes int as input and returns a char
char ceasar_cipher(int c, int secret)
{
    //upper case
    if(c > 64 && c < 91)
    {
        //stores index
        int index = c + secret;
        
        //if index > z then loop back to a
        while(index > 90)
        {
            index -= 25;
        }
        
        //return ciphered char
        return (char) index;
    }
    
    //lower case
    else if(c > 96 && c < 123)
    {
         //stores index
        int index = c + secret;
        
        //if index > z then loop back to a
        while(index > 122)
        {
            index -= 25;
        }
        
        //return ciphered char
        return (char) index;
    }
    
    //not a letter
    else
    {
        //return input as char
        return (char) c;
    }
}