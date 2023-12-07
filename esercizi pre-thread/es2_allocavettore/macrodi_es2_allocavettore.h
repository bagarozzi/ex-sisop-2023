#define ALLOCAVETTORE(p) p=malloc(10*sizeof(int)); \
if(p!=NULL){ \
    int j=0; \
    for(;j<10;j++){ \
        p[j]= -1000+j;\
    }\
}\
