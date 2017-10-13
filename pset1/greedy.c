#include <stdio.h>
#include <cs50.h>
#include <math.h>

int get_change(float f);

int q = 25;
int d = 10;
int n =  5;
int p =  1;

int main(void){
    printf("O hai! How much change is owed?\n");
    float f = get_float();
    printf("%i\n", get_change(f));
}

int get_change(float money)
{
    int coin_count = 0;
    int change_remaining = lround(money*100);
    
    while(change_remaining > 0)
    {
        if(change_remaining >= q){
            change_remaining -= q;
            coin_count++;
        }
        
        else if(change_remaining >= d){
            change_remaining -= d;
            coin_count++;
        } 
        
        else if(change_remaining >= n){
            change_remaining -= n;
            coin_count++;
        } 
        
        else {
            change_remaining -= p;
            coin_count++;
        } 
    }
    
    return coin_count;
}