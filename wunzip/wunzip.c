#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define return codes
#define SUCCESS 0
#define ERROR 1

// Function to uncompress file and feed to output
int uncompress_file(FILE* input, FILE* output) {
    
    // Input validation
    if (input == NULL || output == NULL) {
        
        // Invalid input
        fprintf(stderr, "Invalid input or output file\n");
        return ERROR;
    }
    
    // Initialize variables 
    int count;
    char character;
    
    // Read until the end of the input file
    while (fread(&count, sizeof(int), 1, input) == 1) {        
        
        // Read the character
        if (fread(&character, sizeof(char), 1, input) != 1 && !feof(input)) {
            
            // Failed to read the character
            fprintf(stderr, "Error reading character from compressed file\n");
            return ERROR;  
        }
        
        // Write the consecutive instances of the character
        for (int i = 0; i < count; i++) fputc(character, output);
    }
    
    // Verify that the input file has reached the end
    if (!feof(input)) {
        
        // Failed to read the count
        fprintf(stderr, "Error reading count from compressed file\n");
        return ERROR;  
    }
    
    // Successfully uncompressed file
    return SUCCESS;
} 

// Main function
int main(int argc, char *argv[]) {
    
    // Check that the correct number of arguments were provided
    if (argc < 2) {
        
        // Invalid input
        fprintf(stdout, "wunzip: file1 [file2 ...]\n");
        return ERROR;
    }
    
    // Loop trough the files one by one
    for (int i = 1; i < argc; i++) {
        
        // Get input file name from arguments
        const char* filepath = argv[i];
        if (!filepath) continue; 
        
        // Open input file
        FILE *file = fopen(filepath, "r");        
        if (!file) { 
            
            // Failed to open file
            fprintf(stdout, "wunzip: cannot open file\n"); 
            return ERROR; 
        }
        
        // Uncompress the file and feed to standard output
        if (uncompress_file(file, stdout) != SUCCESS) {
            
            // Failed to uncompress file
            fprintf(stderr, "Error uncompressing file\n");
            fclose(file);
            return ERROR; 
        } 
        
        // Close the file
        fclose(file);
    }
    
    // Successfully uncompressed files
    return SUCCESS; 
}

// EOF