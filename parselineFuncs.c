/* lrising and blishii
 * 357-05
 * Nico
 * parselineFuncs.c
 */


#include"parseline.h"

void printCommand(int stageNum, Command *command) {
    printf("stage num : %d", stageNum); /* temp line remove later*/
}

void initializeBuffer(char *ptr, int size) {
    int i;

    for(i=0; i < size; i++) {
        ptr[i] = 0;
    }
}
