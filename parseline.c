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
    int i, n, len;
    char line[CMD_LINE_MAX];
    char temp[CMD_LINE_MAX];
    char *startptr, *endptr;
    Command *command;

    startptr = line;

    initializeBuffer(line, CMD_LINE_MAX);
    initializeBuffer(temp, CMD_LINE_MAX);
    
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

    len = strlen(line);
    i = 0;

    while(1) {
        endptr = strchr(startptr, '|');
        if (endptr != NULL) {
            strncpy(temp, startptr, endptr - startptr); 
        } else {
            endptr = &line[len-1];
            strncpy(temp, startptr, endptr - startptr); 
            printf("%s", temp);
            break;
        }
        printf("%s", temp);
        command = parseCommand(temp);
        printCommand(i, command);
        initializeBuffer(temp, CMD_LINE_MAX);
        startptr = endptr + 1;
        i++;
    }
    printf("\n%s\n", line);

    return 0;
}
