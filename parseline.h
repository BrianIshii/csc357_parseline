/* lrising and blishii
 * 357-05
 * Nico
 * parseline.h
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CMD_LINE_MAX 1024
#define CMD_PIPE_MAX 20
#define CMD_ARGS_MAX 20

/* exit status if user input sux */
#define MALFORMED_INPUT 1

typedef struct command Command;

struct command {
    char commandline[CMD_LINE_MAX];
    char *input;
    char *output;
    int argc;
    char **argv;
};

/* reads in a series of commands separated by pipes
 * and populates the array of command strings */
void parseCommands(int numCommands, char *line[], Command *commands[]);

Command *parseRegularCommand(char *argv[], int, int);

Command *parseRedirectCommand(char *argv[], int, int);

Command *singleRightRedirect(char **, int, int);

Command *singleLeftRedirect(char **, int, int);

Command *doubleRedirect(char **, int, int);

/* functions to help create commands*/
char *getInput(int stageNum, int totalCmds);
char *getOutput(int stageNum, int totalCmds);


/* reads in a string, deliminates it by tabs and spaces,
 * and populates the array */
void deliminateByWhitespace(char *, char **);

/* print a single command */
void printCommand(int stageNum, Command *command);

void initializeBuffer(char *ptr, int size);

/* error functions */
void errorNullCommand();
void errorBadRedirection(char *type, char *command);
