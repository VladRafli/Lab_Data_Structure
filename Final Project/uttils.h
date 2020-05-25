/**
 * Uttility Functions
 * By Rafli Athala Jaskandi
 * 2301943402
 **/
#ifndef _UTTILS_H_
#define _UTTILS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define clrscr system("cls")
#ifdef _WINDOWS_H_
#define SUCCESS 0
#define FAILED -1
#else
#define SUCCESS 0
#define FAIL -1
#endif

int line(int line_len){
    int i;
    for(i = 0; i < line_len; i++)
        printf("\xCD");
    printf("\n");
    return 0;
}

int header(int text_len, const char *text, const char *type){
    int i;
    if(text_len == 0 || strlen(text) == 0){
        fprintf(stderr, "#Error on uttils.h: There's a Empty Parameter\n");
        return 1;
    }
    else{
        if(strcmp(type, "under") == 0){
            puts(text);
            for(i = 0; i < text_len; i++)
                printf("\xCD");
            printf("\n");
            return 0;
        }
        else if(strcmp(type, "block") == 0){
            for(i = 0; i < text_len + 4; i++)
                printf("\xCD");
            printf("\n");
            printf("\xBA %s \xBA", text);
            printf("\n");
            for(i = 0; i < text_len + 4; i++)
                printf("\xCD");
            printf("\n");
            return 0;
        }
        else{
            fprintf(stderr, "#Error on uttils.h: Undefined Type Parameter\n");
            return 1;
        }
    }
}

#endif