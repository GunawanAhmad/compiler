#include "lex.h"
#include <stdio.h>
#include <stdlib.h> // for malloc, free

int main() {
    char *input = "-+=*/==>= <= < >";
    Lexer *lexer = create_lexer(input);
    
    if (lexer == NULL) {
        fprintf(stderr, "Failed to create lexer\n");
        return 1; // Exit with error code
    }

    while (lexer->curChar != '\0') {
        Token* token = getToken(lexer);
        if (token == NULL) {
            fprintf(stderr, "Failed to get token\n");
            break; // Exit loop if getToken fails
        }
        printf("%s\n", token->text);
    }

    free(lexer); 
    return 0;
}

