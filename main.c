#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lib.c"

int main(void) {
    FILE* text=fopen("lalaland.txt", "r");
    FILE* dict=fopen("large.txt", "r");

    NODE* dict_table[28886];
    load_dictionary(dict_table, dict); //populates the hash table (dict_table).

    char buffer[LENGTH+1];
    char buffer_letter;
    int letter_count=0;
    while (fread(&buffer_letter, 1,1, text)==1) {
        if (buffer_letter=='\n' || buffer_letter==',' || buffer_letter==' ' || buffer_letter=='.' ||                //
        buffer_letter==':' || buffer_letter=='?' || buffer_letter=='!' || buffer_letter=='-' || buffer_letter=='('  // check for word terminators
        ||buffer_letter==')'|| buffer_letter=='/' || buffer_letter==';' || buffer_letter=='"' ||  buffer_letter=='[' 
        || buffer_letter==']' || letter_count==45) {                                                                   //
            buffer[letter_count]='\0';
            if ((96<(int)buffer[0] && buffer[0]<123) || (64<buffer[0] && buffer[0]<91)) {
                if (!check(buffer, dict_table)) {
                    printf("%s\n", buffer);
                }
            }
            letter_count=0;
            memset(buffer, 0, sizeof(buffer));
            continue;
        }
        buffer[letter_count]=buffer_letter;
        letter_count++;
    }
}