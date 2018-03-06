/* lrising and blishii
 * 357-05
 * Nico
 * parseline.h
 */


#include<stdio.h>
#include<string.h>

#define CMD_LINE_MAX 1024
#define CMD_PIPE_MAX 20
#define CMD_ARGS_MAX 20

typedef struct command Command;

struct command {
    char commandline[CMD_LINE_MAX];
    char *input;
    char *output;
    int argc;
    char *argv[CMD_ARGS_MAX];
};

/* reads in args and returns a command struct */
Command *parseCommand(char *line);

/* print commands */
void printCommand(int stageNum, Command *command);

void initializeBuffer(char *ptr, int size);
