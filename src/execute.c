#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/color.h"
#include "include/execute.h"

#include "instruction/print.h"

int execute(char* instruction) {
    if (strncmp(instruction, "print", strlen(instruction)) == 0) {
        print();
        return 1;
    }
    else {
        printf(RED "fonction '%s' non-implémentée..." reset, instruction);
        return -1;
    }
}