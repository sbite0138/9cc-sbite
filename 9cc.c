#include<stdio.h>
#include<stdlib.h>

/*
文字列のポインタから数値を切り出す
char *p="123+1";
parse_num(p); #=> 123
p++;
parse_num(p); #=> 1
*/
int parse_num(char *p){
    int ret=0;
    while (*p!='\n' && ('0'<=*p && *p<='9')){
        ret=ret*10+(*p-'0');
        p++;
    }
    return ret;
}

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