#include <stdio.h>
#include <stdlib.h>
#include "main_adv.h"

int main() {
    char *line;
    while ((line = without_getline()) != NULL) {
        printf("read line: %s\n", line);
        free(line);
    }
    return 0;
}
