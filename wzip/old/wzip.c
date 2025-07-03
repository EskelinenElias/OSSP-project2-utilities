#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Buffer size for reading lines
#define BUFFER_SIZE 1024

// Function to combine files 
int concatenate_files(FILE* input1, FILE* input2, FILE* output) {
    char buffer[BUFFER_SIZE];
    // Read input 1 line by line until end of file
    while (fgets(buffer, BUFFER_SIZE, input1) != NULL) {
        // Write each line in input 1 to the end of output
        fputs(buffer, output);
    } 
    // Read input 2 line by line until end of file
    while (fgets(buffer, BUFFER_SIZE, input2) != NULL) {
        // Write each line in input 2 to the end of output
        fputs(buffer, output);
    } 
    return 0; 
}

// Function to compress file and feed to output
int compress_file(FILE* input, FILE* output) {
    char current_char = fgetc(input); 
    char previous_char = current_char; 
    int count = 1; 
    
    // Check if the file is empty
    if (current_char == EOF) { return 0; }
    
    // Read input character by character until end of file
    while ((current_char = fgetc(input)) != EOF) {
        if (current_char == previous_char) {
            count++;
        } else {
            // Write the character and the count to output
            fwrite(&count, sizeof(int), 1, stdout); 
            fwrite(&previous_char, sizeof(char), 1, output);
            // Reset count and set previous character to the current character
            count = 1; 
            previous_char = current_char; 
        }
    }
    // Write the last character and the count to output
    fwrite(&count, sizeof(int), 1, output); 
    fwrite(&previous_char, sizeof(char), 1, output);
    return 0; 
} 

// Main function parses arguments and calls function print_file accordingly
int main1(int argc, char *argv[]) {
    // Check if input file(s) were provided
    if (argc > 1) { // Input file(s) provided
        for (int i=1; i<argc; i++) {
            // Get input file name from arguments
            const char *input_file = argv[i];
            // Open input file
            FILE *input = fopen(input_file, "r");        
            // Check that the input file opened successfully 
            if (input == NULL) { 
                fprintf(stdout, "wgrep: cannot open file\n"); 
                return 1; 
            }
            // Concatenate input files
            concatenate_files(stdout, input, stdout);
            // Close the input file
            fclose(input);  
        }
        // Compress the input file and feed to standard output
        compress_file(stdin, stdout); 
    } else { // No input file(s)
        fprintf(stdout, "wzip: file1 [file2 ...]\n"); 
        return 1; 
    }
    return 0; 
}

int main(int argc, char *argv[]) {
    // Check that the correct number of arguments were provided
    if (argc < 2) {
        fprintf(stderr, "Usage: wzip <file1> [file2 ...]\n");
        return 1;
    }
    
    int pipefd[2];
    pid_t pid;
    
    // Create a pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }
}