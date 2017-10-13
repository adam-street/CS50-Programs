#include <stdio.h>
#include <cs50.h>

int get_input(void);
void print_pyramid(int count);

int main(void)
{
    print_pyramid(get_input());
}

int get_input(void)
{
    while(true){
        printf("Height: ");
        int i = get_int();
        if(i <= 23 && i >= 0){
            return i;
        }
    }
}

void print_pyramid(int height)
{
    int width = height + 1;
    int _count = width - 2;
    
    if(height == 0){
        printf("\n");
    }
    
    else if(height == 1){
        printf("##\n");
    }
    
    else 
    {
        for(int i=0; i<height; i++)
        {
            for(int j=0; j<_count; j++){
                printf(" ");
            }
            
            for(int k=0; k<height-_count + 1; k++){
                printf("#");
            }
            
            printf("\n");
            _count--;
        }
    }
}