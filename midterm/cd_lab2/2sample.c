#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 1024

void main(){
    FILE *input_file, *output_file;
    char inputfilename[256],outputfilename[256];
    char line[MAX_LINE_LENGTH];

    printf("enter input file name ");
    scanf("%s",inputfilename);
    printf("enter output file name ");
    scanf("%s",outputfilename);

    input_file = fopen(inputfilename,"r");
    output_file = fopen(outputfilename,"w");

    while(fgets(line,MAX_LINE_LENGTH,input_file)!=NULL){
        if(line[0]!= '#')
            fputs(line,output_file);

    }

    fclose(input_file);
    fclose(output_file);

}
