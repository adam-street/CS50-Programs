/**
 * Implements a dictionary's functionality.
 */
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>     // strlen()
#include <sys/stat.h>   // stat()
#include <ctype.h>      // lolower()

#include "dictionary.h"
#include "tries.h"

// function declaration
void clear_nodes(node *t_node);
node *create_node(void);

// variable declaration
node *root;
node *c_node;
long word_count;
bool dictionary_loaded;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    // sets pointer to root node
    c_node = root;

    // loops over every letter in the word
    for(int i=0; i < strlen(word); i++)
    {
        // gets the number index of the current letter
        int pos = tolower(word[i]) - 97;

        // checks for a apostrophe
        if (pos == -58)
            pos = 26;

        // checks to be sure the letter index in the current pointer is not NULL
        if (c_node -> children[pos] != NULL)
            // sets the pointer to the node of the letter index
            c_node = c_node -> children[pos];

        // reached a null pointer before the end of the word
        else
            return false;
    }

    // checks that the pointer is maked as word when at the end of the word
    if(c_node -> is_word == true)
        return true;
    // reached the end of the word and the current pointer is not marked as word
    else
        return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    //open dictionary file
    FILE *d_file = fopen(dictionary, "r");
    if(d_file == NULL)
    {
        fprintf(stderr, "Error opening file.");
        return false;
    }

    // create root node
    root = create_node();

    // create temp node to handle moving through data structure
    //node* c_node = create_node();
    c_node = root;

    // find the dictionary length
    struct stat st;
    stat(dictionary, &st);
    long loop_count = st.st_size;

    // loop through dictionary file
    for(int i=0; i < loop_count; i++)
    {
        // read letter from file
        char letter = tolower(fgetc(d_file));

        // save pos of letter
        int pos = letter - 97;

        // check for ' and if found set pos to last index
        if (pos == -58)
            pos = 26;

        // if the current letter is not a \n
        if(pos != -87)
        {
            // if the index of the current letter in the current pointers children list
            // is not null, change the pointer to that node.
            if(c_node -> children[pos] != NULL)
                c_node = c_node -> children[pos];


            // found null node before end of word so create new node and fill info
            else
            {
                node *new_node = create_node();
                new_node -> letter = letter;
                c_node -> children[pos] = new_node;
                c_node = new_node;
            }
        }

        // at the end of the word, set is_word to true on current pointer and set pointer
        // back to the root node
        else
        {
            word_count++;
            c_node -> is_word = true;
            c_node = root;
        }
    }

    //close file, mark dictionary loaded. and return true
    fclose(d_file);
    dictionary_loaded = true;
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // checks if dictionary is loaded and returns true else return false
    if(dictionary_loaded == true)
        return word_count;

    return 0;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    // clears all nodes from memory
    clear_nodes(root);
    return true;
}

/**
 * Navigates tries data structre recursively freeing nodes from memory
 */
void clear_nodes(node *t_node)
{
    if(t_node != NULL)
    {
        for (int i=0; i<27; i++)
        {
            if(t_node -> children[i] != NULL)
            {
                clear_nodes (t_node -> children[i]);
            }
        }

        free(t_node);
    }
}


/**
 * Creates new node struct and initializes its values
 */
node *create_node(void)
{
    node *new_node = malloc(sizeof(node));
    new_node -> letter = ' ';
    new_node -> is_word = NULL;

    for (int i=0; i<27; i++)
        new_node -> children[i] = NULL;

    return new_node;
}
