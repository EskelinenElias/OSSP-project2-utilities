#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define return codes
#define SUCCESS 0
#define ERROR 1

// Function to write count and character to output
void write_count_and_char(FILE* output, char character, size_t count) {
    
    // Write count and character to output
    fwrite(&count, sizeof(int), 1, output);
    fwrite(&character, sizeof(char), 1, output);
}

// Function to compress file and feed to output
int compress_file(FILE* input, FILE* output, char* current_char, size_t* current_count) {
    
    // Input validation
    if (!input || !output) {
        
        // Invalid input
        fprintf(stderr, "Error: Invalid input or output file.\n");
        return ERROR;
    }
    
    // Check if the file is empty
    if (feof(input)) return SUCCESS;
    
    // Initialize character and count
    if (*current_char == EOF || *current_count == 0) {
        *current_char = fgetc(input);
        *current_count = 1; 
    }
    
    // Read input character by character until end of file
    char next_char = EOF; 
    while ((next_char = fgetc(input)) != EOF) {
        
        // Check if the current character is the next character
        if (*current_char == next_char) {
            
            // Increment the count of the current character
            (*current_count)++;
            
        } else if (*current_char != EOF && *current_count != 0) { // The current character is not the next character

            // Write the character and the count to output
            fwrite(current_count, sizeof(int), 1, output);
            fwrite(current_char, sizeof(char), 1, output);
            
            // Swap the current character to the next character
            *current_char = next_char;
            *current_count = 1;
        }
    }
    
    // Successfully compressed file
    return SUCCESS; 
} 

// Main function
int main(int argc, char *argv[]) {

    // Check that the correct number of arguments were provided
    if (argc < 2) {
        
        // Invalid input
        fprintf(stdout, "wzip: file1 [file2 ...]\n");
        return 1;
    }
    
    // Initialize character and count variables for handling file boundaries
    char current_char = 0; 
    size_t current_count = 0;

    // Loop trough the input files one by one
    for (size_t i = 1; i < argc; i++) {
        
        // Get file path
        char* filepath = argv[i];
        
        // Open the read end of the pipe as a input stream
        FILE *input = fopen(filepath, "r");
        if (!input) {
            
            // Cannot open file
            fprintf(stderr, "wzip: cannot open file '%s'\n", filepath);
            return ERROR;
        }
        
        // Compress file content
        if (compress_file(input, stdout, &current_char, &current_count) != SUCCESS) {
            
            // Failed to compress file
            fprintf(stderr, "wzip: failed to compress file '%s'\n", filepath);
            return ERROR;
        }
        
        // Close the file stream
        fclose(input);
    }
    
    // Write the last character and the count to output
    fwrite(&current_count, sizeof(int), 1, stdout);
    fwrite(&current_char, sizeof(char), 1, stdout);
    
    // Successfully compressed all files
    return SUCCESS; 
}

// EOF