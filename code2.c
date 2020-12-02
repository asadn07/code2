#include "framework.h"
#include <stdio.h>

int getOption()
{
    printf("\nPlease select an option:\n"
           "1 - Encrypt\n"
           "2 - Decrypt\n"
           "0 - End program\n");

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
            return getOption();
    }
}

int readIn(int option)
{
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
    if(option == 1) {replaceLetters(input,'W','V');} // only with encrypt
    if(size_input > 50)
    {
        printf("too big !, return 0; TODO: CHANGE TO CORRECT ERRORMSG!");
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
    { printf("too big !, return 0; TODO: CHANGE TO CORRECT ERRORMSG!");
        return -1;
    }

    if((stringLength(input)) % 2 == 1)
    { // add uneven X!
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
   	//HERE BIGRAM IS READY
	//WITH OPTION YOU CAN DECIDE WHETHER TO ENCRYPT OR DECRYPT
	//EVERYWHERE A FUNCTION IS WRITING THE POWER
	//THERE ARE RULES IN THE SPECIFICATION ... BIGRAMM IS A 2D ARRAY. YOU HAVE T    //QUOTE CORRECTLY
	
    printf("\n option ist %d\n" , option);
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

    int retval = readIn(option);
    if(retval == -1)
    { // meaning some kind of error
        printf("ERROR OR anything else!\n");
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
    
    // TODO: Implement
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

    // TODO: Implement
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

    // TODO: Implement
    // WARNING: Do not change the signature of the function
}
