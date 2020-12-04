#include "framework.h"
#include <stdio.h>

int getOption()
{
    printf("\nWählen Sie bitte eine Option:\n"
           "1 - Verschlüsseln\n"
           "2 - Entschlüsseln\n"
           "0 - Programm beenden\n");

    int option = 0;
    scanf("%d ", &option);

    switch(option)
    {
        case 0:
            return 0;
        case 1:
            return 1;
        case 2:
            return 2;
        default:
            return option;
    }
}

int encrypt(char* playfair)
{
    printf("Klartext: ");
    char input[100];
    char c;
    int size_input = 0;
    for(int i = 0; i < 50; i++)
    {
        c = getchar();
        if(c == '\0' || c =='\n')
        {
            input[i] = '\0';
            break;
        }
        input[size_input] = c;
        size_input++;
    }
    removeSpaces(input);
    toUpper(input);
    replaceLetters(input,'W','V');


    if(size_input > 50)
    {
        printf("zu groß !, return 0; TODO: CHANGE TO CORRECT ERRORMSG!");
        return -1;
    }
    int i = 0;
    while(i < stringLength(input))
    {
        if(input[i] == input[i+1])
        {
            for (int k = stringLength(input) + 1; k > i; k--)
            {input[k] = input[k - 1];};
            input[i+1] = 'X';
        }
        i++;
    }

    if(size_input > 50)
    { printf("zu groß !, return 0; TODO: CHANGE TO CORRECT ERRORMSG!");
        return -1;
    }

    if((stringLength(input)) % 2 == 1)
    { // ungerade X hinzufügen!
        input[stringLength(input)] = 'X';
    }

    char bigram[(stringLength(input))/2][2];

    int pos_in_input = 0 ;

    for(int j = 0; j < stringLength(input) / 2; j++)
    {
        for(int k = 0; k < 2; k++)
        {
            bigram[j][k] = input[pos_in_input];
            pos_in_input++;
        }
    }

    printf("Vorbereiteter Klartext: ");
    for(int j = 0; j < stringLength(input) / 2; j++)
    {
        for(int k = 0; k < 2; k++)
        {
            printf("%c",bigram[j][k]);
        }
        printf(" ");
    }

    pos_in_input = 0;
    int pos_bi1 = 0;
    int pos_bi2 = 0;
    for(int j = 0; j < stringLength(input) / 2; j++)
    {
        while (pos_in_input < 25)
        {
            if (playfair[pos_in_input] == bigram[j][0])
            {
                pos_bi1 = pos_in_input;
            }
            if (playfair[pos_in_input] == bigram[j][1])
            {
                pos_bi2 = pos_in_input;
            }
            pos_in_input++;
        }
        pos_in_input = 0;
        //selbe spalte
        if(pos_bi1 - pos_bi2 == 5 || pos_bi2 - pos_bi1 == 5)
        {
            if(pos_bi1 + 5 < 25)
            {
                bigram[j][0] = playfair[pos_bi1+5];
            }else
                {
                bigram[j][0] = playfair[pos_bi1-20];
            }
            if(pos_bi2 + 5 < 25)
            {
                bigram[j][1] = playfair[pos_bi2+5];
            }
            else
                {
                bigram[j][1] = playfair[pos_bi2-20];
            }
        }
    }

    printf("\nCiphertext: ");
    for(int j = 0; j < stringLength(input) / 2; j++)
    {
        for(int k = 0; k < 2; k++)
        {
           // bigram[j][1] = 66;
            printf("%c", bigram[j][k]);
        }
        //printf(" ");
    }
    printf("\n");

    return 0;
}

int main()
{
    char key[25];
    generatePlayfairSquare(key);
    //choose option
    int option = getOption();
    if(option == 0 )
    {
        return 0;
    }

    int retval = encrypt(key);

    if(retval == -1)
    { // meaning some kind of error
        printf("ERROR ODER irgendwas ANDERES!\n");
    }

    return 0;
}

//-----------------------------------------------------------------------------
// Computes and returns the length of a string
//
// @param text string to check
//
// @return length of the string
//
int stringLength(char *text);

//-----------------------------------------------------------------------------
// Changes a string to upper case
//
// @param text string to modify
//
void toUpper(char *text);

//-----------------------------------------------------------------------------
// Replace all the occurences of a letter in a string with another letter
//
// @param text string to modify
// @param original letter to replace
// @param new_char letter used for the substitution
//
void replaceLetters(char *text, char original, char new_char);


//-----------------------------------------------------------------------------
int stringLength(char *text)
{
    int i = 0;
    while(text[i] != '\0')
    {
        i++;
    }
    return i;
    // WARNING: Do not change the signature of the function
}

//-----------------------------------------------------------------------------
void toUpper(char *text)
{
    int i = 0;
    while(text[i] != '\0')
    {
        if(text[i] >= 'a' && text[i] <= 'z')
        {
            text[i] = text[i] -32;
        }

        i++;
    }
    // WARNING: Do not change the signature of the function
}

//-----------------------------------------------------------------------------
void replaceLetters(char *text, char original, char new_char)
{

    int i = 0;
    while(text[i] != '\0')
    {
        if(text[i] == original)
        {
            text[i] = new_char;
        }
        i++;
    }
    // WARNING: Do not change the signature of the function
}
