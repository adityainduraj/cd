#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_file_length 1024


void main(){

    FILE *inputfile, *outputfile;
    char inputfilename[max_file_length];
    char outputfilename[max_file_length];


    char ch, prevchar = '\0';

    printf("enter input file name");
    scanf("%s",inputfilename);
    printf("enter output file name");
    scanf("%s",outputfilename);

    inputfile = fopen(inputfilename,"r");
    outputfile=fopen(outputfilename,"w");

    while ((ch = fgetc(inputfile)) != EOF)
    {
        if(ch == ' ' || ch == '\t'){
            if(prevchar != ' ')
                fputc(' ',outputfile);
        }
        else
            fputc(ch,outputfile);
        prevchar = ch;
    }
    

    fclose(inputfile);
    fclose(outputfile);





}