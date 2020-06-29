#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void encrypt (int n, char file1[80], char file2[80])
{
    //printf("hello");
    FILE *fp1, *fp2;
    fp1 = fopen(file1, "r");
    if (fp1 == NULL){
        printf("Error: File 1\n");
    } else {printf("\nFile 1 is opened");}
    fp2 = fopen(file2, "w");
    if (fp2 == NULL){
        printf("Error: File 2\n");
    } else {printf("\nFile 2 is opened");}
    char c;
    c = getc(fp1);
    while (!feof(fp1))
    {
        if (c >= 'A' && c <= 'Z'){
            c = c + (n % 26);
            if (c > 'Z'){
                c = 'A' + (c - 'Z') - 1;
            }
            fprintf (fp2, "%c", c);
        } else if (c >= 'a' && c <= 'z'){
            c = c + (n % 26);
            if (c > 'z'){
                c = 'a' + (c - 'z') - 1;
            }
            fprintf (fp2, "%c", c);
        } else {
            fprintf (fp2, "%c", c);
            }
        c = getc(fp1);
    }
    fclose (fp1);
    fclose (fp2);
}

void decrypt (int n, char file1[80], char file2[80])
{
    FILE *fp1, *fp2;

    fp1 = fopen(file1, "r");

    if (fp1 == NULL){
        printf("\nError: File 1");
    } else {printf("\nFile 1 is opened");}

    fp2 = fopen(file2, "w");

    if (fp2 == NULL){
        printf("\nError: File 2");
    } else {printf("\nFile 2 is opened");}

    char c;
    c = getc(fp1);
    while (!feof(fp1))
    {
        if (c >= 'A' && c <= 'Z'){
            c = c - (n % 26);
            if (c < 'A'){
                c = 'Z' - ('A' - c) + 1;
            }
            fprintf (fp2, "%c", c);
        } else if (c >= 'a' && c <= 'z'){
            c = c - (n % 26);
            if (c < 'a'){
                c = 'z' - ('a' - c) + 1;
            }
            fprintf (fp2, "%c", c);
        } else {
            fprintf (fp2, "%c", c);
            }
        c = getc(fp1);
    }
    fclose (fp1);
    fclose (fp2);
}

int main(int argc, char *argv[])
{
    //printf("%s", argv[1]);
    if ((argc != 5) && (argc != 2)){
        printf("Try 'Caesar.exe -help'");
        return 0;
    }
    if (argc == 5){
        int n = atoi(argv[2]);
        char encr[8] = "-encode";
        char decr[8] = "-decode";
        if (strcmpi(argv[1], encr) == 0){
            printf("numb: %d \nfile1: %s \nfile2: %s", n, argv[3], argv[4]);
            encrypt(n, argv[3], argv[4]);
        }
        if (strcmpi(argv[1], decr) == 0){
            printf("numb: %d \nfile1: %s \nfile2: %s", n, argv[3], argv[4]);
            decrypt(n, argv[3], argv[4]);
        }
    } else if (argc == 2){
        char help[6] = "-help";
        if (strcmpi(argv[1], help) == 0){
            printf("How to run script: \n Caesar.exe *-encode OR -decode* *number to move* *from FILE1* *to FILE2*");
        } else {
            printf("Try 'Caesar.exe -help'");
        }
    }

    //printf("%d", n);
    return 0;
}
