#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXGR 10

char *bigmas(char *w, int *len) {
	char *mas;
	int i = 0;
	mas = malloc((*len) * 2);
	while(i < *len)
	{
		mas[i] = w[i];
		i++;
	}
	*len = (*len) * 2;
	free(w);
	w = mas;
	return w;
}

void *process_str(regmatch_t rmatch[], char* string, char* substitution) {
    int after_bslash = 0;
    char *new_str;
	int len = strlen(string);
	new_str = malloc(len * sizeof(*new_str));
    int s1p = 0;
    int s2p = 0;
    char cur_c;
    int pocket_num;
    int pockets_am = 0;
    for (int j = 1; j < MAXGR; j++) {
      	if ((int)rmatch[j].rm_so != -1) {
            pockets_am = j;
        }
    }
    while (s1p != rmatch[0].rm_so) {
        new_str[s2p] = string[s1p];
        s1p++;
        s2p++;
    }
    s1p = 0;
    while (substitution[s1p]) {
        pocket_num = 0;
        cur_c = substitution[s1p];
        s1p++;
        if (cur_c == '\\') {
            after_bslash = !after_bslash;
        }
        else if (after_bslash){
            if (!isdigit(cur_c)) {
                fprintf(stderr, "Invalid reference in substitution (not a number)\n");
                return NULL;
            }
            pocket_num = cur_c - '0';
            if (pocket_num > pockets_am) {
                fprintf(stderr, "Invalid reference in substitution (no pocket with this number)\n");
                return NULL;
            }
            after_bslash = 0;
        }
        if (!after_bslash) {
            if (!pocket_num) {
                new_str[s2p] = cur_c;
                s2p++;
                if (s2p > len - 1) {
			        new_str = bigmas(new_str, &len);
                }
            }
            else {
                for (int i = rmatch[pocket_num].rm_so; i < rmatch[pocket_num].rm_eo; i++) {
                    new_str[s2p] = string[i];
                    s2p++;
                    if (s2p > len - 1) {
			            new_str = bigmas(new_str, &len);
                    }
                }
            }
        }      
    }
    if (after_bslash) {
        fprintf(stderr, "Backslash in the end of substitution\n");
        return NULL;
    }
    s1p = rmatch[0].rm_eo;
    while (string[s1p]) {
        new_str[s2p] = string[s1p];
        s1p++;
        s2p++;
        if (s2p > len - 1){
			new_str = bigmas(new_str, &len);
        }
    }
    new_str[s2p] = '\0';
    return new_str;
}

int main(int argc, char** argv) {
    if (argc != 4) {
        fprintf(stderr, "Wrong number of arguments (usage: ./prog 'regexp' 'substitution' 'string')\n");
    }

    char* substitution = argv[2];
    char* string = argv[3];

    const int err_msg_len = 100;

    regex_t reg_exp;
    int ret_value;
    regmatch_t rmatch[MAXGR];
    char err_msg[err_msg_len];


    if (ret_value = regcomp(&reg_exp, argv[1], REG_EXTENDED)) {
        regerror(ret_value, &reg_exp, err_msg, err_msg_len);
        fprintf(stderr, "Regcomp error: %s\n", err_msg);
        return -1;
    }

    
    if (ret_value = regexec(&reg_exp, string, MAXGR, rmatch, 0)) {
        if(ret_value == REG_NOMATCH) {
            fprintf(stderr, "%s\n", string);
        } else {
            regerror(ret_value, &reg_exp, err_msg, err_msg_len);
            fprintf(stderr, "Regexec error: %s\n", err_msg);
        }
    }
    else {
        char *new_str;
        new_str = process_str(rmatch, string, substitution);
        if (new_str) {
            printf("%s\n", new_str);
            free(new_str);
        }
    }
    regfree(&reg_exp);
    return 0;
}
