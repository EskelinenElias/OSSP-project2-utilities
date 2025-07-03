#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define return codes
#define SUCCESS 0
#define ERROR 1

// Function to print lines in input that contain search term
int print_lines_containing_search_term(const char* search_term, FILE* input, FILE* output) {
    
    // Input validation
    if (!search_term || !input || !output) {
        
        // Invalid input
        fprintf(stderr, "Invalid input\n");
        return ERROR;
    }
    
    // Initialize buffer and length
    char *buffer = NULL; // Pointer to hold the line buffer
    size_t len = 0; // Size of the buffer
    
    // Read input line by line until end of file
    while (getline(&buffer, &len, input) != -1) {
        
        // Check if the line contains the search term
        if (strstr(buffer, search_term)) {
            
            // Print line to output
            fprintf(output, "%s", buffer); 
        }
    }
    
    // Free the buffer
    free(buffer);
    
    // Successfully printed lines containing search term
    return SUCCESS; 
} 

// Main function parses arguments and calls function print_file accordingly
int main(int argc, char *argv[]) {
    
    // Input validation
    if (argc < 2) {
        
        // Invalid input
        printf("wgrep: searchterm [file ...]\n");
        return ERROR;
    }
    
    // Get the search term
    const char* search_term = argv[1];
    
    // Check if only the search term was provided
    if (argc == 2) {
        
        // Use standard input as input
        if (print_lines_containing_search_term(search_term, stdin, stdout) != SUCCESS) {
        
            // Failed to print lines containing search term
            fprintf(stderr, "wgrep: failed to print lines containing search term\n");
            return ERROR;
        }
    }
        
    // If input files were provided, loop trough the input files one by one
    for (int i = 2; i < argc; i++) {
        
        // Get input file path
        const char *filepath = argv[i];
        if (!filepath) continue; 
        
        // Open input file 
        FILE* file = fopen(filepath, "r"); 
        if (!file) {
            
            // Failed to open file
            fprintf(stdout, "wgrep: cannot open file\n"); 
            return ERROR; 
        }
        
        // Call function cat and pass input file as argument
        if (print_lines_containing_search_term(search_term, file, stdout) != SUCCESS) {
            
            // Failed to print lines containing search term
            fprintf(stderr, "wgrep: failed to print lines containing search term\n");
            return ERROR;
        }
        
        // Close input file
        fclose(file); 
    }
    
    // Successfully printed lines containing search term
    return SUCCESS; 
}

// EOF