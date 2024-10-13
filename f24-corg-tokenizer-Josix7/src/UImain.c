#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"
#include "history.h"

int main()
{
    char string[100];  // Buffer to store the input string
    char *token;       // Pointer to store the token
    char select;       // Variable to store user selection
    List *history = init_history();  // Initialize the history list

    printf("Please make a selection for what you want to do\n");
    
    // Main loop to handle user input and actions
    while (1)
    {
        printf("Enter '1' to tokenize a new string, '2' to print the history, '3' to find an item in the history, or 'q' to exit\n");
        scanf(" %c", &select);  // Get the user's selection

        switch (select)
        {
        case '1':  // Tokenize a new string
            printf("Enter string to be tokenized\n>");
            scanf(" %[^\n]", string);  // Read input string including spaces
            
            char **tokens = tokenize(string);  // Tokenize the input string
            printf("\n");
            
            add_history(history, string);  // Add the string to history
            print_tokens(tokens);  // Print the tokens
            
            free_tokens(tokens);  // Free allocated memory for tokens
            break;

        case '2':  // Print the history
            print_history(history);
            break;

        case '3':  // Find an item in the history by its ID
            printf("Enter pos_id for the item you are looking for\n");
            int pos;
            scanf(" %d", &pos);  // Get the position ID from the user
            
            printf("Printing history item with ID: %d\n", pos);
            token = get_history(history, pos);  // Retrieve the item from history
            
            if (token != NULL)  // Check if the item exists
            {
                char **item = tokenize(token);  // Tokenize the retrieved item
                print_tokens(item);  // Print the tokens of the item
                
                free_tokens(item);  // Free the allocated memory
            }
            else
            {
                printf("Item with ID %d not found\n", pos);  // Item not found
            }
            printf("-------------------------------\n");
            break;

        case 'q':  // Exit the program
            printf("Exiting system...\n");
            free_history(history);  // Free memory allocated for the history list
            return 0;

        default:  // Handle invalid input
            printf("Invalid input, please try again.\n");
            break;
        }
    }
}
