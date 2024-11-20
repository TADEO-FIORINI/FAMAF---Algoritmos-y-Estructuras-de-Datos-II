#include <stdbool.h>
#include <assert.h>

#include "fixstring.h"

unsigned int fstring_length(fixstring s) {
    int i=0;
    while (s[i]!='\0'){
        i++;
    }
    return i;
}

bool fstring_eq(fixstring s1, fixstring s2) {
    bool r;
    int i;
    r = false;
    i=0;
    if (fstring_length(s1) == fstring_length(s2)){
        r = true;
        while (s1[i] != '\0' && s2[i] != '\0'){
                r = r && s1[i] == s2[i];
                i++;
            }
    }
    return r;
    }    

bool fstring_less_eq(fixstring s1, fixstring s2) {
    bool r;
    r = true;
    int i;
    i=0;
    while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '0'){
        i++;
    }
    if (s2[i]<s1[i]){
        r = false;
    }
    return r;
}

