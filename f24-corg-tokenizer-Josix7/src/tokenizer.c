#include <stdlib.h>
#include <stdio.h>
#include "tokenizer.h"

// Checks if a character is a space or tab.
int space_char(char c)
{
    return (c == ' ' || c == '\t') && c != '\0';
}

// Checks if a character is not a space or tab.
int non_space_char(char c)
{
    return !(c == ' ' || c == '\t' || c == '\0');
}

// Finds and returns the pointer to the next non-space character in the string.
char *token_start(char *str)
{
    int i = 0;
    while (*(str + i))
    {
        if (non_space_char(*(str + i)))
        {
            return str + i;
        }
        i++;
    }
    return str + i; // Return pointer at the end of string if no non-space is found.
}

// Finds and returns the pointer to the next space or tab character after a token.
char *token_terminator(char *token)
{
    int i = 0;
    while (*(token + i))
    {
        if (space_char(*(token + i)))
        {
            return token + i;
        }
        i++;
    }
    return token + i; // Return pointer at the end of string if no space/tab is found.
}

// Counts and returns the number of tokens (words) in the string.
int count_tokens(char *str)
{
    int count = 0;
    char *temp = str;
    temp = token_start(temp); // Skip initial spaces.

    while (*temp)
    {
        if (non_space_char(*temp))
        {
            count++;
        }
        temp = token_terminator(temp); // Move to the next space/tab.
        temp = token_start(temp);      // Move to the next non-space character.
    }

    return count;
}

// Creates a copy of a string segment of given length and null-terminates it.
char *copy_str(char *inStr, short len)
{
    char *Str_copy = malloc((len + 1) * sizeof(char)); // Allocate memory for the new string.
    for (int i = 0; i < len; i++)
    {
        Str_copy[i] = inStr[i]; // Copy each character.
    }
    Str_copy[len] = '\0'; // Add null terminator.
    return Str_copy;
}

// Tokenizes the input string and returns an array of tokens.
char **tokenize(char *str)
{
    int num_tokens = count_tokens(str); // Determine number of tokens.
    char **tokens = malloc(sizeof(char *) * (num_tokens + 1)); // Allocate memory for token pointers.
    char *token = str;

    for (int i = 0; i < num_tokens; i++)
    {
        token = token_start(token);           // Find the start of the next token.
        char *token_end = token_terminator(token); // Find the end of the token.
        int len = token_end - token;          // Calculate token length.
        tokens[i] = copy_str(token, len);     // Copy token to the tokens array.
        token = token_terminator(token);      // Move pointer to the next space/tab.
    }
    tokens[num_tokens] = NULL; // Null-terminate the token array.
    return tokens;
}

// Prints all tokens in the array.
void print_tokens(char **tokens)
{
    int i = 0;
    while (tokens[i] != NULL) // Loop through all tokens until the NULL token.
    {
        printf("Token #%d: %s\n", i, tokens[i]); // Print token number and its value.
        i++;
    }
    printf("Token #%d: %s\n", i, tokens[i]); // Print the NULL terminator.
}

// Frees memory allocated for each token and the tokens array itself.
void free_tokens(char **tokens)
{
    int i = 0;
    while (tokens[i])
    {
        free(tokens[i]); // Free each token's allocated memory.
        i++;
    }
    free(tokens); // Free the tokens array.
}
