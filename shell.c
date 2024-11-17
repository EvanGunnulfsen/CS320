#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>

// function to fork and run commands
void executeCommand(char *args[]){
    // create child process
        int pid = fork(); 
        // check for child
        if(pid == 0) {
            // check if execvp fails
            if(execvp(args[0], args) == -1) {
                perror("Program failed");
                exit(1);
            }
        // check for parent and wait for child to finish
        } else if(pid > 0) {
            wait(NULL);
        } else {
            perror("Fork failed");
        }
}

// function to tokenize inputs
void tokenize_input(char *input, char *args[]){ 
        // splits string into tokens with " " as delimitizer, and returns pointer to token
        char *token = strtok(input, " ");

        int i = 0;
        // goes through rest of input
        while(token != NULL) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        // at this point, i should be last element of ary, so we use it to set that element to NULL
        args[i] = NULL;
}



int main() {

    // variables to be used for tokenize

        // char ary
    char input[1024];
        // ary of pointers to the tokens
    char *args[64];
    
    //
    while (1) {
        // prompt user to enter command
        printf("Enter input: ");

        // check for end of file
        if(fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }

        // checks for new line
        input[strcspn(input, "\n")] = 0;

        // call to tokenize function
        tokenize_input(input, args);

        // check for more input
        if(args[0] == NULL) {
            continue;
        }
        // call function to fork and run the command
        executeCommand(args);
    }

    return 0;
}