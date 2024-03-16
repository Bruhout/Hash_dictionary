#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include "lib.h"


unsigned int hash_func(const char *word)
{
    // TODO: Improve this hash function
    int hash_value=0;
    int char_value;
    for (int i=0; i<4; i++) {
        if (word[i]=='\0') {    //
            return hash_value;    // For words shorter than 4 letters.
        }                       //

        char_value=(int)word[i];
        if (64<char_value && char_value<91) {
            hash_value+=(1000/pow(10, i))*(char_value-65);
        }
        else if (96<char_value && char_value<123) {
            hash_value+=(1000/pow(10, i))*(char_value-97);
        }
    }
    return hash_value;
}

int remove_newline(char* word) {
    if (word==NULL) {
        printf("Invalid string passed \n");
        return -1;
    }
    char* buffer=word;
    for (int i=0; i<strlen(word); i++) {
        if (*buffer=='\n') {
            *buffer='\0';
            return 0;
        }
        buffer++;
    }
    return 2;
}

void load_dictionary(NODE* table[28886], FILE* dictionary) {
    for (int i=0; i<28886; i++) {
        table[i]=NULL;
    }
    char buffer[LENGTH+1];
    NODE* buffer_node;
    int hash_value;
    NODE* new_node;
    while (fgets(buffer, LENGTH+1, dictionary)!=NULL) {
        remove_newline(buffer);
        hash_value=hash_func(buffer);

        new_node=malloc(sizeof(NODE));  //
        new_node->next_node=NULL;       //Setup next_node for insertion
        strcpy(new_node->word, buffer); //

        buffer_node=table[hash_value];
        if (table[hash_value]==NULL) {
            table[hash_value]=new_node;
        }
        else {
            while(buffer_node->next_node!=NULL) { //buffer is set to the last element.
                buffer_node=buffer_node->next_node;
            }
            buffer_node->next_node=new_node;
        }
    }
}

void print_dictionary(NODE* table[28886]) {
    NODE* buffer=table[0];
    for (int i=0; i<28886; i++) {
        buffer=table[i];
        while(buffer!=NULL) {
            printf("%s:%i\n", buffer->word, i);
            buffer=buffer->next_node;
        }
    }
}

bool check(char* word, NODE* table[28886]) {
    int hash_value=hash_func(word);
    NODE* buffer=table[hash_value];
    while (buffer!=NULL) {
        if (strcasecmp(buffer->word, word)==0) {
            return true;
        }
        buffer=buffer->next_node;
    }
    return false;
}

void free_dictionary(NODE* table[28886]) {
    NODE* buffer1;
    NODE* buffer2;
    for (int i=0; i<28886; i++) {
        buffer1=table[i];
        buffer2=table[i];
        while (buffer1!=NULL) {
            buffer1=buffer1->next_node;
            free(buffer2);
            buffer2=buffer1;
        }
    }
    printf("Freed\n");
}

/*
int main(void) {
    FILE* dict=fopen("large.txt", "r");
    NODE* table[28886];
    load_dictionary(table, dict);
    print_dictionary(table);
    char* check_word="zygOte";
    if (check(check_word, table)) {
        printf("found\n");
    }
    else {
        printf("not found\n");
    }
    free_dictionary(table);
}
*/