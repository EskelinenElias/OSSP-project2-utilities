#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Buffer size for reading lines
#define BUFFER_SIZE 1024

// Function to uncompress file and feed to output
int uncompress_file(FILE* input, FILE* output) {
    int num_consecutive;
    char character;
    // Read until the end of the input file
    while (fread(&num_consecutive, sizeof(int), 1, input) == 1) {
        // Read the character
        if (fread(&character, sizeof(char), 1, input) != 1) {
            fprintf(stderr, "Error reading character from compressed file\n");
            return 1;  // Exit if there is an error in the file format
        }
        // Write the consecutive instances of the character
        for (int i = 0; i < num_consecutive; i++) {
            fputc(character, output);
        }
    }
    return 0;
} 

int main(int argc, char *argv[]) {
    // Check that the correct number of arguments were provided
    if (argc < 2) {
        fprintf(stdout, "wunzip: file1 [file2 ...]\n");
        return 1;
    }
    // Loop trough the files one by one
    for (int i=1; i<argc; i++) {
        // Get input file name from arguments
        const char *input_file = argv[i];
        // Open input file
        FILE *input = fopen(input_file, "r");        
        // Check that the input file opened successfully 
        if (input == NULL) { 
            fprintf(stdout, "wunzip: cannot open file\n"); 
            return 1; 
        }
        // Uncompress the file and feed to standard output
        uncompress_file(input, stdout); 
    }
    return 0; 
}