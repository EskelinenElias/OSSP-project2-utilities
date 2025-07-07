# UNIX Utilities

This project contains implementations of several UNIX utilities. It is a course project for the course "Operating Systems and Systems Programming" at LUT University; the exercise is from the book "Operating Systems: Three Easy Pieces" by Remzi H. Arpaci-Dusseau and Andrea C. Arpaci-Dusseau. 

## Utilities

The following utilities are implemented: 
- `wcat`, our implementation of the `cat` utility
- `wgrep`, our implementation of the `grep` utility
- `wzip`, our implementation of the `zip` utility, utilizing run-length encoding for compression
- `wunzip`, our implementation of the `unzip` utility, acting as a decompressor for the `wzip` utility


## Project structure

Each of the utilities are placed in their own directory. Each directory contains a `Makefile` for building the utility and tests for the utility. All of the utilities can be tested by running the script `run_tests.sh` in the root directory. The file `PROJECT-INSTRUCTIONS.md` in the root directory contains the original instructions for the project.

## Implementations

Here are descriptions of how the utilities have been implemented. 

### wcat

`wcat` is a simple implementation of the `cat` utility. It can be used to read the contents of one or more files to standard output. The filepaths are passed as arguments when calling the utility (for example `wcat file1 file2`); if no arguments are passed, the tool simply exits. 

The implementation consists of the `main` function and a function `concatenate`. The `main` function parses input arguments, opens files and passes them to the `concatenate` function. It also makes sure that all the files are closed after reading. The `concatenate` function takes as arguments two streams: `stream1` and `stream2`. It then reads the contents of `stream2` and writes them to the end of `stream1`. The main file always passes the standard output as `stream1` and the currently opened file as `stream2`; thus the files are "concatenated" to the end of standard output, one by one. 

Functions `fopen` and `fclose` are used to open and close files respectively. Functions `fgets` and `fputs` are used to read and write lines respectively. Function `fprintf` is used to print error messages to standard error stream. 

### wgrep 

`wgrep` is a simple implementation of the `grep` utility. It can be used to print lines in a file or multiple files containing a "search term". If no files are specified, the tool reads from standard input. The tool can be called with the command `wgrep searchterm [file ...]`; the `searchterm` argument is required, and leaving it empty will result in an error message being printed to standard error. 

The implementation consists of the `main` function and function `print_lines_containing_search_term`. The `main` function parses input arguments, opens files and passes them to the `print_lines_containing_search_term` function; while also making sure that all files are closed after reading, or in the case of an error. If filepaths are not provided, the tool passes the standard input to the function `print_lines_containing_search_term`.

The function `print_lines_containing_search_term` takes as arguments a search term and two streams `input` and `output`. In this implementation, the main function always passes standard output as the `output` stream. It then reads the file line by line and prints out any lines containing the search term. 

Functions `fopen` and `fclose` are used to open and close files respectively. Function `getline` is used to read lines from the `input` stream, as it allows the lines to be of any length. Function `strstr` is used to check if the line contains the searchterm, and function `fprintf` is used to print the line to the `output` stream, as well as for printing error messages to standard error stream. Function `free` is used to free the memory allocated for the line read from the input stream by the function `getline`.


### wzip 

`wzip` is a simple implementation of the `zip` utility. It can be used to compress one or more files to standard output or a single output file using run-length encoding. The tool can be called with the command `wzip [file1 ...]` and redirected to a file with the command `wzip [file1 ...] > output_file`.

The implementation consists of the `main` function and function `compress_file`. The `main` function parses input arguments, opens files and passes them to the `compress_file` function, while also making sure that all files are closed after reading, or in the case of an error. If filepaths are not provided, the tool prints an error message to standard error stream. 

The `compress_file` function takes as arguments an input stream, an output stream, a character pointer `current_char` and an integer pointer `current_count`. The input stream is the current file, the output stream is by default the standard output, but can be redirected to a file. The `current_char` and `current_count` are used to handle file boundaries; they hold the last character and count of the previous file so that if the first character of the next file matches the last character of the previous file, the count is incremented instead of writing a new character and count. The `compress_file` function reads characters from the input stream, and prints the count of consecutive matching characters and the character to the output stream. The `current_char` and `current_count` are written to the output stream at the end of the program. 

Functions `fopen` and `fclose` are used to open and close files respectively. Function `fgetc` is used to read characters from the input stream, and function `fwrite` is used to write counts and characters to the output stream. Function `feof` is used for checking for end of file. Function `fprintf` is used for printing error messages to standard error stream.


### wunzip 

`wunzip` is a simple implementation of the `unzip` utility. It can be used to decompress one or more files to standard output or a single output file using run-length encoding. The tool can be called with the command `wunzip [file1 ...]` and redirected to a file with the command `wunzip [file1 ...] > output_file`.

The implementation consists of the `main` function and function `uncompress_file`. The `main` function parses input arguments, opens files and passes them to the `uncompress_file` function, while also making sure that all files are closed after reading, or in the case of an error. If filepaths are not provided, the tool prints an error message to standard error stream. 

The `uncompress_file` function takes as arguments an input stream and an output stream. It reads the run-length encoded count-character pairs from the input stream and writes the decompressed data to the output stream. If the input data is corrupted, the function prints an error message and returns an error code to the `main` function, which then closes any open files and exits. 

Functions `fopen` and `fclose` are used to open and close files respectively. Function `fread` is used for reading the counts and characters, and function `feof` is used for checking for end of file. Function `fputc` is used for writing characters to the output stream, and function `fprintf` is used for printing error messages to standard error stream.

## Sources

- GeeksForGeeks, EOF, getc() and feof() in C, available: https://www.geeksforgeeks.org/c/eof-and-feof-in-c/
