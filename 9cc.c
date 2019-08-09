#include<stdio.h>
#include<stdlib.h>

int main(int argc,char*argv[]){
    if (argc!=2){
        fprintf(stderr,"引数の個数が正しくありません\n");
        exit(1);
    }
    printf(".intel_syntax noprefix\n");
    printf(".global main\n");
    printf("main:\n");
    char *p=argv[1];
    printf(" mov eax, %ld\n",strtol(p,&p,10));
    while (*p!='\0'){
        if (*p=='+'){
            p++;
            printf(" add eax, %ld\n",strtol(p,&p,10));        
        }else if (*p=='-'){
            p++;
            printf(" sub eax, %ld\n",strtol(p,&p,10));        
        }else{
            fprintf(stderr,"予期しない文字です:%c\n",*p);
            exit(1);
        }
    }
    printf(" ret\n");
    
    return 0;
}