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
    int i, j, n, len;
    char line[CMD_LINE_MAX];
    char temp[CMD_LINE_MAX];
    char *cmdlines[CMD_PIPE_MAX + 1];
    Command *commands[CMD_PIPE_MAX + 1];
    char *startptr, *endptr;
    //Command *command;

    for(i = 0; i < CMD_PIPE_MAX + 1; i++)
    {
        commands[i] = NULL;
    }

    startptr = line;

    //initializeBuffer(commands, CMD_PIPE_MAX + 1);
    //initializeBuffer(cmdlines, CMD_PIPE_MAX + 1);
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
    j = 0;
    while(1) {
        endptr = strchr(startptr, '|');
        if (endptr != NULL) {
            cmdlines[j] = (char *) calloc(endptr - startptr + 1, sizeof(char));
            strncpy(cmdlines[j++], startptr, endptr - startptr); 
        } else {
            endptr = &line[len-1];
            cmdlines[j] = (char *) calloc(endptr - startptr + 1, sizeof(char)); 
            strncpy(cmdlines[j++], startptr, endptr - startptr); 
            //command = parseCommand(temp);
            //printCommand(i, command);
            break;
        }
        //command = parseCommand(temp);
        //printCommand(i, command);
        initializeBuffer(temp, CMD_LINE_MAX);
        startptr = endptr + 1;
        i++;
    }
    /* cmdlines is now populated */

    parseCommands(j, cmdlines, commands);
    i = 0;
    while(commands[i] != NULL)
    {
        printCommand(i, commands[i]);
        i++;
    }

    return 0;
}
