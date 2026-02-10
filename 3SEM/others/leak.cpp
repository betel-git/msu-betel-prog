#include <stdlib.h>
#include <stdio.h>
void leak_memory();

void leak_memory() {
    int* ptr = (int*)malloc(100 * sizeof(int)); // Утечка!
    // забыли free(ptr);
}

int main() {
    leak_memory();
    printf("test\n");
    return 0;
}