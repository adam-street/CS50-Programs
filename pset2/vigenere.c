#import <stdio.h>
#import <cs50.h>
#import <string.h>  // for strlen
#import <ctype.h>   // for isaplha

int convert_secret(char c);
char vigenere_cipher(int c, int secret);

int main(int argvc, string argv[])
{
    //validate command line argument
    if(argvc != 2)
    {
        printf("Error 1: Invalid command line argument.\n");
        return 1;
    }
    
    //create array from input by runing convert_secret on each char
    int secretLength = strlen(argv[1]); //get length of input
    int secret[secretLength];           //create array
    for(int i=0; i<secretLength; i++)   //fill array 
    {
        //writes secret key into secret[]
        if(isalpha(argv[1][i]))
        {
            secret[i] = convert_secret(argv[1][i]);
        }
        
        //ends with error if non apha char found in input
        else 
        {
            printf("Error 1: Invalid command line argument.\n");
            return 1;
        }
    }
    
    //get text to encrypt
    printf("plaintext: ");
    string plainText = get_string();
    
    //get plainText length
    int plainTextLength = strlen(plainText);
    
    //loop through each char in input and run vigenere_cipher then print return
    printf("ciphertext: ");
    int secret_index = 0;
    for(int i=0; i<plainTextLength; i++) //loop each char in plainText
    {
        if(secret_index > secretLength - 1)
        {
            secret_index = 0;
        }
        
        printf("%c", (char) vigenere_cipher((int) plainText[i], secret[secret_index]));
        secret_index++;
    }
    
    //start a new line and end program with 0
    printf("\n");
    return 0;
}

int convert_secret(char c)
{
    //upper case
    if(c > 64 && c < 91)
    {
        return (int) c - 65; 
    }
    
    //lower case
    else
    {
        return (int) c - 97;
    }
}

//takes int as input and returns a char
char vigenere_cipher(int c, int secret)
{
    //upper case
    if(c > 64 && c < 91)
    {
        //stores index
        int index = c + secret;
        
        //if index > z then loop back to a
        while(index > 90)
        {
            index -= 26;
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
            index -= 26;
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