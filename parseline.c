/* lrising and blishii
 * 357-05
 * Nico
 * parseline
 */

#include"parseline.h"
#include<unistd.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
    int i, n, j, len;
    char line[CMD_LINE_MAX];
    char *startptr, *endptr;
    char *lines[CMD_PIPE_MAX];
    Command *commands[CMD_PIPE_MAX];

    startptr = line;

    initializeBuffer(line, CMD_LINE_MAX);
    
    printf("line: ");

    fflush(stdout);

    if ((n = read(STDIN_FILENO, line, CMD_LINE_MAX)) < 0) {
        perror("Could not read from stdin");
        exit(EXIT_FAILURE);
    }

    if (line[CMD_LINE_MAX - 1] != '\0' && line[CMD_LINE_MAX - 1] != '\n') {
        fprintf(stderr, "command too long\n");
        exit(EXIT_FAILURE);
    }

    i = 0;

    while(1) {
        endptr = strchr(startptr, '|');
        if (endptr != NULL) {
            len = endptr - startptr;
            lines[i] = calloc(len + 1, sizeof(char));
            strncpy(lines[i], startptr, len); 
        } else {
            endptr = &line[strlen(line)-1];
            len = endptr - startptr;
            lines[len] = 0;
            lines[i] = calloc(len + 1, sizeof(char));
            strncpy(lines[i], startptr, len); 
            i++;
            break;
        }
        startptr = endptr + 1;
        i++;
    }

    if (i > CMD_PIPE_MAX) {
        fprintf(stderr, "pipeline too deep\n");
        exit(EXIT_FAILURE);
    }

    //for testing
    for(j=0; j < i; j++) {
        printf("%s\n", lines[j]);
    }

    parseCommands(i, lines, commands);

    //need to free lines
    return 0;
}
