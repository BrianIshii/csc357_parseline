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
Command *parseRegularCommand(char *argv[])
{
    Command *command;
    command = NULL;
    return command;
}

/* ^^ what he said */
Command *parseRedirectCommand(char *argv[])
{  
    Command *command;
    command = NULL;
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
    while(j < numCommands)
    {
        deliminateByWhitespace(line[i], argv);
        i = 0;
   
        /* checks for redirects */
        while(argv[i] != NULL)
        {
            printf("%s", argv[i]);
            if(*argv[i] == '>' || *argv[i] == '<')
            {
                commands[j] = parseRedirectCommand(argv);
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
            commands[j] = parseRegularCommand(argv);
        } 
        
        i = 0;
        while(argv[i] != NULL)
        {
            free(argv[i]);
            i++;
        }
        j++;
    }
}

void printCommand(int stageNum, Command *command)
{
    printf("---------\n");
    printf("Stage %d: \"%s\"\n", stageNum, command->commandline);
    printf("---------\n");
    /* TBD */
    printf("      input: \n");
    printf("     output: \n");
    printf("       argc: \n");
    printf("       argv: \n");
}

void initializeBuffer(char *ptr, int size)
{
    int i;

    for(i=0; i < size; i++) {
        ptr[i] = 0;
    }
}
