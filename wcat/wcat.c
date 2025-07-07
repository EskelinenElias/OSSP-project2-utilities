#include <stdio.h>
#include <stdlib.h>

// Define return codes
#define SUCCESS 0
#define ERROR 1

// Buffer size for reading lines
#define BUFFER_SIZE 1024

// Function to write contents of stream 2 to stream 1
int concatenate(FILE* stream1, FILE* stream2) {
    
    // Input validation
    if (!stream1 || !stream2) {
        
        // Invalid input
        fprintf(stderr, "wcat: invalid input files\n");
        return ERROR;
    }
    
    // Initialize buffer
    char buffer[BUFFER_SIZE];
    
    // Read stream 2 until end is reached
    while (fgets(buffer, BUFFER_SIZE, stream2)) {
        
        // Write contents to the end of stream 1
        fputs(buffer, stream1);
    } 
    
    // Successfully concatenated
    return SUCCESS; 
}

// Main function
int main(int argc, char *argv[]) {
    
    // Check if input files were provided
    if (argc <= 1)  return SUCCESS; 
        
    // Loop trough the files one by one
    for (int i = 1; i < argc; i++) {
        
        // Get input file name from arguments
        const char *filepath = argv[i];
        if (!filepath) continue; 
        
        // Open input file
        FILE *file = fopen(filepath, "r");        
        if (!file) { 
            
            // Input file could not be opened
            fprintf(stdout, "wcat: cannot open file\n"); 
            return ERROR; 
        }
        
        // Write the contents of the input file to the end of standard output
        if (concatenate(stdout, file) != SUCCESS) {
            
            // Failed to concatenate file contents
            fprintf(stderr, "wcat: error concatenating file '%s'\n", filepath);
            return ERROR;
        }
        
        // Close the input file
        fclose(file); 
    }
    
    // Successfully concatenated all files
    return SUCCESS; 
}

// EOF