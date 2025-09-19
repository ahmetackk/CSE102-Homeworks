#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int num = 1;
    char name[20];

    sprintf(name, "familytree%d.txt", num);
    printf("%s\n", name);

    num = 10;
    do
    {
        num++;
        printf("%d\n", num);
        if (num == 20)
        {
            num = 10;
        }
        
    } while (num != 10);
    
}