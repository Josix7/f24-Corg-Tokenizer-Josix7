#include <stdio.h>
#include <stdlib.h>
#include "history.h"

#define MAXTOKENS 100

// Initializes the history list and returns a pointer to the new list.
List* init_history()
{
    List *history = (List*)malloc(sizeof(List)); // Allocate memory for the list.
    if (history != NULL)
    {
        history->root = NULL; // Set root to NULL to indicate an empty list.
    }
    return history;
}

// Adds a new history item (string) to the list.
void add_history(List *list, char *str)
{
    static int pos_id = 1; // Static variable to keep track of item IDs.
    Item *new_item = (Item*)malloc(sizeof(Item)); // Allocate memory for a new item.
    if (list == NULL) // Check for memory allocation failure.
    {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }

    int len = 0; // Variable to store the length of the input string.
    while (*(str + len) != '\0' && *(str + len) != '\n') // Calculate the string length.
    {
        len++;
    }

    new_item->str = (char*)malloc((len + 1) * sizeof(char)); // Allocate memory for the string copy.
    if (new_item->str == NULL) // Handle memory allocation failure.
    {
        fprintf(stderr, "Memory allocation for new_item->str failed\n");
        free(new_item); // Free the allocated memory for the item.
        return;
    }

    // Copy the string into the new item's string field.
    for (int i = 0; i < len; i++)
    {
        new_item->str[i] = str[i];
    }
    new_item->str[len] = '\0'; // Null-terminate the copied string.

    new_item->next = NULL; // Set the next pointer of the new item to NULL.

    // If the list is empty, set the root to the new item.
    if (list->root == NULL)
    {
        new_item->id = pos_id; // Assign an ID to the new item.
        list->root = new_item;
    }
    else // If the list is not empty, append the new item at the end.
    {
        Item *list_cpy = list->root; // Create a copy of the list's root.
        while (list_cpy->next != NULL) // Traverse to the last item in the list.
        {
            list_cpy = list_cpy->next;
        }
        new_item->id = list_cpy->id + 1; // Set the ID for the new item.
        list_cpy->next = new_item; // Link the last item to the new item.
    }
    pos_id++; // Increment the static item counter.
}

// Retrieves the string associated with the given ID from the history list.
char *get_history(List *list, int id)
{
    Item *temp = list->root; // Temporary pointer to traverse the list.
    if (list->root == NULL || list == NULL) // If the list is empty, return NULL.
        return NULL;

    // Traverse the list to find the item with the matching ID.
    while (temp != NULL)
    {
        if (temp->id == id) // If the ID matches, return the string.
        {
            return temp->str;
        }
        temp = temp->next; // Move to the next item.
    }
    return NULL; // If the ID is not found, return NULL.
}

// Prints all items in the history list.
void print_history(List *list)
{
    if (list->root == NULL || list == NULL) // If the list is empty, print a message and return.
    {
        printf("Nothing is in the history\n");
        return;
    }

    Item *temp = list->root; // Temporary pointer to traverse the list.
    printf("Printing History: \n");
    
    // Traverse and print each item in the list.
    while (temp != NULL)
    {
        if (temp->str != NULL) // Check if the string is not NULL.
        {
            printf("[ID:[%d] : %s]\n", temp->id, temp->str); // Print the ID and string.
        }
        else
        {
            printf("[ID:[%d] : NULL]\n", temp->id); // If the string is NULL, print NULL.
        }
        temp = temp->next; // Move to the next item.
    }
}

// Frees the memory allocated for the history list.
void free_history(List *list)
{
    if (!list) // If the list is empty, return.
    {
        return;
    }

    Item *temp; // Temporary pointer to help free the list.
    Item *curr_item = list->root; // Pointer to the current item in the list.

    // Traverse and free each item in the list.
    while (curr_item)
    {
        temp = curr_item; // Store the current item in temp.
        curr_item = curr_item->next; // Move to the next item.
        free(temp->str); // Free the string memory.
        free(temp); // Free the item.
    }
}

