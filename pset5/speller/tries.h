/**
 * Defines a tries structre.
 */

 static const int children_size = 27;

// node struct
typedef struct node
{
    char letter;
    struct node *children[children_size];
    bool is_word;

    struct node *pre_node;
}
node;