#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

void PrintInitials(string name);

int main(void)
{
    //gets user input and send input to PrintInitials funciton
    PrintInitials(get_string());
}

void PrintInitials(string name)
{
    //checks if name is valid
    if(name != NULL)
    {
        //get char count of name
        int size = strlen(name);
        
        //keep track of if we are looking for whitespace
        bool looking_for_whitespace = false;
        
        //loop through each char in name
        for(int i = 0; i < size; i++)
        {
            //if we are not looking for whitespace and current char is not whitespace
            if(name[i] != ' ' && !looking_for_whitespace)
            {
                //print current char in name
                printf("%c",toupper(name[i]));
                //mark that we are now looking for whitespace
                looking_for_whitespace = true;
            }
            //if we are looking for whitespace and current char is whitespace
            else if(name[i] == ' ' && looking_for_whitespace)
            {
                //mark that we are now not looking for whitespace
                looking_for_whitespace = false;
            }
        }
        
        //print a new line
        printf("\n");
    }
}