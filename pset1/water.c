#include <stdio.h>
#include <cs50.h>

int convert(int i);

int main(void)
{
    printf("Minutes: ");
    int input = get_int();

    int water = convert(input);

    printf("Bottles of water: %i\n", water);
}

int convert(int i)
{
    return (192 * i) / 16;
}

