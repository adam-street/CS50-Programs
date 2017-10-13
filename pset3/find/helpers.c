/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */

#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    //return false if n is a non-positive int
    if(n < 1)
    {
        return false;
    }

    //look at each value in values and check for a match if so return true
    for(int i = 0; i < n; i++)
    {
        if(value == values[i]){
            return true;
        }
    }

    //return false if value not found
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    //create new array size of n
    int sortedArray[n];

    //sort array with algorithom i-1
    for(int i = n; i > 0; i--){
        sortedArray[i-1] = i;
    }

}
