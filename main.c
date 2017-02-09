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
    	printf("short/long\n");
        return false;
    }
    
    if (!isalpha(str[0])) {
    	printf("not alpha start\n");
        return false;
    }
    
    for (int i = 0; i < name_len; i++) {
        char currentChar = str[i];
        if (!(isalnum(currentChar) || currentChar == '-' || currentChar == '_')) {
        	printf("wrong stuff\n");
        	printf("%i\n", currentChar);
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

int min_int(int a, int b){
	return a < b ? a : b;
}

bool prompt(){
    printf("Enter a valid PSN ID: ");
    
    // PSN ID max = 16 chars + (\r\n + \0)
    const int max_len = 16 + 3;
    
    char id_name[max_len];
    fgets(id_name, max_len, stdin);
    size_t id_len = strlen(id_name);
    int new_line_loc = min_int(strcspn(id_name, "\n"), strcspn(id_name, "\r"));
    id_name[new_line_loc] = '\0';
    id_len = new_line_loc;
    
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
