//
//  main.c
//  profile_gen
//
//  Created by tromie on 8/2/17.
//  Copyright © 2017 tromie. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool valid_psn_id(char *str, size_t name_len){
    if (name_len < 3 || name_len > 16) {
        return false;
    }
    
    if (!isalpha(str[0])) {
        return false;
    }
    
    for (int i = 0; i < name_len; i++) {
        char currentChar = str[i];
        if (!(isalnum(currentChar) || currentChar == '-' || currentChar == '_')) {
            return false;
        }
    }
    
    return true;
}

void write_profile(char *name, size_t name_len){
    FILE *myprofile = fopen("myprofile.dat", "w");
    
    const int profile_file_size = 328;
    
    for (int i = 0; i < profile_file_size; i++) {
        if (i < name_len) {
            fputc(name[i], myprofile);
        }else{
            fputc(0, myprofile);
        }
    }
    
    fclose(myprofile);
}

bool prompt(){
    printf("Enter a valid PSN ID: ");
    
    const int max_len = 16 + 1;
    
    char id_name[max_len];
    fgets(id_name, max_len, stdin);
    size_t id_len = strlen(id_name);
    
    if (valid_psn_id(id_name, id_len)) {
        write_profile(id_name, id_len);
        return true;
    }else{
        return false;
    }
}

int main(int argc, const char * argv[]) {
    while (!prompt()) {
        printf("Invalid PSN ID.\n"
               "Valid PSN IDs must satisfy the following requirements:\n"
               "\tBegin with a letter.\n"
               "\t3-16 alphanumeric characters\n"
               "\tMay contain a hyphen (-) or underscore (_).\n"
               );
    }
    printf("myprofile.dat written successfully.\n");
    
    return 0;
}
