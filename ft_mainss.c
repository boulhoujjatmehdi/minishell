



#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main() {
    char *input;
    while ((input = readline("> ")) != NULL) {
        // Process the user input here
        printf("You entered: %s", input);

        // Move the cursor to a new line
        rl_on_new_line();
        rl_on_new_line();

        // Free the memory used by readline
        // free(input);
    }
    return 0;
}