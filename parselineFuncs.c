/* lrising and blishii
 * 357-05
 * Nico
 * parselineFuncs.c
 */


#include"parseline.h"

/* does what it looks like */
void deliminateByWhitespace(char *str, char *new[])
{
    int i, j;
    char *ptr;

    for(i = 0; i < CMD_ARGS_MAX; i++)
    {
        new[i] = NULL;
    }
    
    j = 0;
    ptr = str;
    while(*ptr != '\0' && *ptr != '\n')
    {
        while(*ptr == ' ' || *ptr == '\t')
        {
            ptr++;
        }
        if(*ptr == '\0' || *ptr == '\n')
        {
            break;
        }
        i = 0;
        while(ptr[i] != ' ' && ptr[i] != '\t')
        {
            if(ptr[i] == '\0' || ptr[i] == '\n')
            {
                break;
            }
            i++;
        }
        new[j] = calloc(i + 1, sizeof(char));
        strncpy(new[j], ptr, i);
        j++;
        ptr += i;
    }
    return;
}

/* gonna take a list of strings and turn them into a single command object */
Command *parseRegularCommand(char *argv[], int stageNum, int totalCmds)
{
    Command *command = (Command *) calloc(1, sizeof(Command));
    char **cmdArgv = calloc(CMD_ARGS_MAX, sizeof(char *));
    int i = 0;

    command->input = getInput(stageNum, totalCmds);
    command->output = getOutput(stageNum, totalCmds);

    while(argv[i] != NULL)
    {
        cmdArgv[i] = calloc(20, sizeof(char));
        strcpy(cmdArgv[i], argv[i]);
        i++;
    }

    if (cmdArgv[0] == NULL)
    {
        errorNullCommand();
    }

    command->argc = i;
    command->argv = cmdArgv;

    return command;
}

Command *singleLeftRedirect(char *argv[], int stageNum, int totalCmds)
{
    Command *command;
    int i, j, cmdLength;
    char **cmdArgv;

    cmdArgv = calloc(CMD_ARGS_MAX, sizeof(char *));
    command = (Command *) calloc(1, sizeof(Command));

    i = 0;
    j = 0;
    cmdLength = 0;

    /* count num of args */
    while (argv[cmdLength] != NULL)
    {
        cmdLength++;
    }

    if(!strcmp(argv[cmdLength - 1], "<"))
    {   /* last arg is the redirect */
        errorBadRedirection("input", argv[0]);
    }

    if(stageNum)
    {   /* if not the first stage, redirect doesn't work */
        fprintf(stderr, "%s: ambiguous input\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    while(argv[i] != NULL)
    {
        if(!strcmp(argv[i], "<"))
        {
            command->input = calloc(sizeof(argv[i + 1]) + 1, sizeof(char));
            strcpy(command->input, argv[i + 1]);
            i += 2;
        }
        else
        {
            cmdArgv[j] = calloc(sizeof(argv[i]) + 1, sizeof(char));
            strcpy(cmdArgv[j], argv[i]);
            i++;
            j++;
        }
    }

    if (cmdArgv[0] == NULL)
    {
        errorNullCommand();
    }

    command->argc = cmdLength - 2;
    command->argv = cmdArgv;

    command->output = getOutput(stageNum, totalCmds);

    return command;
}

char *getOutput(int stageNum, int totalCmds)
{
    char *output = NULL;
    char *stdoutput = "original stdout";
    char *pipeout = "pipe to stage ";
    char stage;

    if(stageNum + 1 == totalCmds)
    {
        output = (char *) calloc(sizeof(stdoutput), sizeof(char));
        strcpy(output, stdoutput);
    }
    else
    {
        stage = '0' + stageNum + 1;
        output = (char *) calloc(sizeof(pipeout) + 2, sizeof(char));
        strcpy(output, pipeout);
        strncat(output, &stage, 1);
    }
    
    if (output == NULL)
    {
        perror("Could not calloc memory for output");
        exit(EXIT_FAILURE);
    }

    return output;
}

char *getInput(int stageNum, int totalCmds)
{
    char *input = NULL;
    char *stdinp = "original stdin";
    char *pipeinp = "pipe from stage ";
    char stage;

    if(!stageNum)
    {
        input = (char *) calloc(sizeof(stdinp), sizeof(char));
        strcpy(input, stdinp);
    }
    else
    {
        stage = '0' + stageNum - 1;
        input = (char *) calloc(sizeof(pipeinp) + 2, sizeof(char));
        strcpy(input, pipeinp);
        strncat(input, &stage, 1);
    }
    
    if (input == NULL)
    {
        perror("Could not calloc memory for input");
        exit(EXIT_FAILURE);
    }

    return input;
}

Command *doubleRedirect(char *argv[], int stageNum, int totalCmds)
{
    Command *command;
    int i, j, cmdLength;
    char **cmdArgv;

    cmdArgv = calloc(CMD_ARGS_MAX, sizeof(char *));
    command = (Command *) calloc(1, sizeof(Command));

    i = 0;
    j = 0;
    cmdLength = 0;

    /* count num of args */
    while (argv[cmdLength] != NULL)
    {
        cmdLength++;
    }

    if(!strcmp(argv[cmdLength - 1], "<") || !strcmp(argv[0], ">"))
    {   /* checks both redirects */
        errorBadRedirection("input", argv[0]);
    }

    if(stageNum || totalCmds > 1)
    {   /* if not the first stage and last stage */
        fprintf(stderr, "%s: ambiguous input\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    while(argv[i] != NULL)
    {
        if(!strcmp(argv[i], "<"))
        {
            command->input = calloc(sizeof(argv[i + 1]) + 1, sizeof(char));
            strcpy(command->input, argv[i + 1]);
            i += 2;
        }
        else if(!strcmp(argv[i], ">"))
        {
            command->output = calloc(sizeof(argv[i + 1]) + 1, sizeof(char));
            strcpy(command->output, argv[i + 1]);
            i += 2;
        }
        else
        {
            cmdArgv[j] = calloc(sizeof(argv[i]) + 1, sizeof(char));
            strcpy(cmdArgv[j], argv[i]);
            i++;
            j++;
        }
    }

    if (cmdArgv[0] == NULL)
    {
        errorNullCommand();
    }

    command->argc = cmdLength - 4;
    command->argv = cmdArgv;

    return command;
}

Command *singleRightRedirect(char *argv[], int stageNum, int totalCmds)
{
    Command *command = (Command *) calloc(1, sizeof(Command));
    int i, j, cmdLength;
    char **cmdArgv = calloc(CMD_ARGS_MAX, sizeof(char *));

    i = 0;
    j = 0;
    while(argv[i] != NULL)
    {
        if(!strcmp(argv[i], ">"))
        {
            command->output = (char *) 
                calloc(sizeof(argv[i + 1]) + 1, sizeof(char));
            strcpy(command->output, argv[i + 1]);
            i += 2;
        }
        else
        {
            cmdArgv[j] = calloc(sizeof(argv[i]) + 1, sizeof(char));
            strcpy(cmdArgv[j], argv[i]);
            i++;
            j++;
        }
    }
    cmdLength = i;
    command->argc = i - 2;
    command->argv = cmdArgv;
    
    if(!strcmp(argv[0], ">"))
    {   /* first arg is the redirect */
        fprintf(stderr, "that makes no sense\n");
    }
    if(!strcmp(argv[cmdLength - 1], ">"))
    {   /* last arg is the redirect */
        fprintf(stderr, "how though?\n");
    }
    if(stageNum != totalCmds - 1)
    {   /* if not the last stage, redirect doesn't work */
        fprintf(stderr, "ambiguous output\n");
    }

    command->input = getInput(stageNum, totalCmds);

    return command;

}

/* ^^ what he said */
Command *parseRedirectCommand(char *argv[], int stageNum, int totalCmds)
{  
    Command *command;
    int i = 0;
    int numLeft, numRight;
    numLeft = 0;
    numRight = 0;
    while(argv[i] != NULL)
    {
        if(!strcmp(argv[i], ">"))
        {
            numRight++;
        }
        else if(!strcmp(argv[i], "<"))
        {
            numLeft++;
        }
        i++;
    }
    if(!numLeft)
    {
        if(numRight == 1)
        {
            command = singleRightRedirect(argv, stageNum, totalCmds);
        }
        else
        {
            fprintf(stderr, "bad IO redirection\n");
        }
    }
    else
    {
        if(numLeft == 1)
        {
            if(numRight == 1)
            {
                command = doubleRedirect(argv, stageNum, totalCmds);
            }
            else if(numRight == 0)
            {
                command = singleLeftRedirect(argv, stageNum, totalCmds);
            }
            else
            {
                fprintf(stderr, "bad IO redirection\n");
            }
        }
        else
        {
            fprintf(stderr, "bad IO redirection\n");
        }
    }
    return command;
}

/* reads a series of strings (that were once separated by pipes) and
 * populates the commands array with Command structures */
void parseCommands(int numCommands, char *line[], Command *commands[])
{
    int i, j;
    char *argv[CMD_ARGS_MAX];

    j = 0;
    /* initialize argv */
    for(; j < numCommands; j++)
    {
        deliminateByWhitespace(line[j], argv);
        i = 0;

        if(argv[i] == NULL) {
            fprintf(stderr, "invalid null command\n");
            exit(EXIT_FAILURE);
        }
        
        /* checks for redirects */
        while(argv[i] != NULL)
        {
            if(*argv[i] == '>' || *argv[i] == '<')
            {
                commands[j] = parseRedirectCommand(argv, j, numCommands);
                initializeBuffer(commands[j]->commandline, CMD_LINE_MAX);
                strcpy(commands[j]->commandline, line[j]);
                break;
            }
            else
            {
                i++;
            }
        }

        /* we iterated through the entirety of argv and found
         * no redirect symbols */
        if(argv[i] == NULL)
        {
            commands[j] = parseRegularCommand(argv, j, numCommands);
            strcpy(commands[j]->commandline, line[j]);
        } 
        
        i = 0;
        while(argv[i] != NULL)
        {
            free(argv[i]);
            i++;
        }
    }
}

void printCommand(int stageNum, Command *command)
{
    int i = 0;
    printf("--------\n");
    printf("Stage %d: \"%s\"\n", stageNum, command->commandline);
    printf("--------\n");
    /* TBD */
    printf("      input: %s\n", command->input);
    printf("     output: %s\n", command->output);
    printf("       argc: %d\n", command->argc);
    printf("       argv: ");
    for(; i < command->argc - 1; i++)
    {
        printf("\"%s\", ", command->argv[i]);
    }
    printf("\"%s\"\n", command->argv[i]);
}

void initializeBuffer(char *ptr, int size)
{
    int i;

    for(i=0; i < size; i++) {
        ptr[i] = 0;
    }
}

void errorNullCommand()
{
    fprintf(stderr, "invalid null command\n");
    exit(EXIT_FAILURE);
}

void errorBadRedirection(char *type, char *command)
{
    fprintf(stderr, "%s: bad %s redirection\n", command, type);
    exit(EXIT_FAILURE);
}
