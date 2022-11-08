#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct fun_desc {
    char *name;
    char (*fun)(char);
};

int inRange(char c){
    return (c >= 0x20 && c <= 0x7E);
}

char censor(char c) {
    if(c == '!')
        return '.';
    else
        return c;
}

char* map(char *array, int array_length, char (*f) (char)){
    char* mapped_array = (char*)(malloc(array_length*sizeof(char)));
    for(int i = 0 ; i < array_length ; i++){
        mapped_array[i] = (*f)(array[i]);
    }
    return mapped_array;
}


/* Ignores c, reads and returns a character from stdin using fgetc. */
char my_get(char c){
    c = fgetc(stdin);
    return c;
}

/* If c is a number between 0x20 and 0x7E, cprt prints the character of ASCII value c followed by a new line. Otherwise, cprt prints the dot ('.') character. After printing, cprt returns the value of c unchanged. */
char cprt(char c){
    if (inRange(c)){
        printf("%c\n", c);
    }else{
        printf("%c\n", '.');
    }
    return c;
}

/* Gets a char c and returns its encrypted form by adding 3 to its value. If c is not between 0x20 and 0x7E it is returned unchanged */
char encrypt(char c) {
    if (inRange(c)) {
        return c + 3;
    }
    return c;
}

/* Gets a char c and returns its decrypted form by reducing 3 to its value. If c is not between 0x20 and 0x7E it is returned unchanged */
char decrypt(char c){
    if (inRange(c)){
        return c - 3;
    }
    return c;
}

/* xprt prints the value of c in a hexadecimal representation followed by a new line, and returns c unchanged. */
char xprt(char c){
    if (inRange(c)){
        printf("%x\n", c);
    }else{
        printf("%c\n", '.');
    }
    return c;
}

/* Gets a char c, and if the char is 'q' , ends the program with exit code 0, Otherwise returns c. */
char quit(char c){
    if(c == 'q'){
        exit(0);
    }
    return c;
}

int main(){
    char* carray = (char*)(malloc(5*sizeof(char)));
    struct fun_desc menu[] = { {"Type And Print Input Letters", &my_get },
                               {"Print Text Letter By Letter", &cprt},
                               {"Prine Char Value In Hex", &xprt},
                               {"Cenaor Text", &censor},
                               {"Encrypts Text By Ceasar Cypher", &encrypt},
                               {"Encrypts Text By Ceasar Cypher", &decrypt},
                               {"Quit", &quit}};
    while(1){
        for(int i = 0; i < (*(&menu + 1) - menu); i++){
            printf("%d) %s\n", i,  menu[i].name);
        }
        printf("Please enter your choice\n");
        char c[10];
        if(fgets(c, 10, stdin) != NULL){
            int index = atoi(c);
            if(index >= 0 && index <=(*(&menu + 1) - menu)-1){
                printf("With in bound\n");
                carray = map(carray, 5, menu[index].fun);
                printf("DONE\n");
            }else{
                printf("Out of bound\n");
                free(carray);
                exit(0);
            }
        }
    }
    free(carray);
    return 0;
}