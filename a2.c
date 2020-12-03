#include "framework.h"
#include <stdio.h>

int getOption() {
    printf("\nWählen Sie bitte eine Option:\n"
           "1 - Verschlüsseln\n"
           "2 - Entschlüsseln\n"
           "0 - Programm beenden\n");

    int option = 0;
    scanf("%d ", &option);

    switch (option) {
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

int go_right(int x) {
    if (x % 5 == 4) {
        return x - 4;
    } else {
        return x + 1;
    }
}

void encrypt(char *key, char left_letter, char right_letter,
             char *result_left, char *result_right) {
    int left_letter_location, right_letter_location;
    for (int i = 0; i < 25; i++) {
        if (key[i] == left_letter) {
            left_letter_location = i;
        } else if (key[i] == right_letter) {
            right_letter_location = i;
        }
    }

    // They are on the same row
    if (left_letter_location / 5 == right_letter_location / 5) {
        *result_left = key[go_right(left_letter_location)];
        *result_right = key[go_right(right_letter_location)];
    } else if (left_letter_location % 5 == right_letter_location % 5) {

    }
}

int process_input(int option, char *key) {
    char input[100];
    char c;
    int size_input = 0;
    for (int i = 0; i < 50; i++) {
        c = getchar();
        if (c == '\0' || c == '\n') {
            input[i] = '\0';
            break;
        }
        input[size_input] = c;
        size_input++;
    }
    removeSpaces(input);
    toUpper(input);
    if (option == 1) { replaceLetters(input, 'W', 'V'); } // nur bei verschlüsseln
    if (size_input > 50) {
        printf("zu groß !, return 0; TODO: CHANGE TO CORRECT ERRORMSG!");
        return -1;
    }
//    int i = 0;
//    while (i < stringLength(input)) {
//        if (input[i] == input[i + 1]) {
//            for (int k = stringLength(input) + 1; k > i; k--) { input[k] = input[k - 1]; };
//            input[i + 1] = 'X';
//        }
//        i++;
//    }

    if (size_input > 50) {
        printf("zu groß !, return 0; TODO: CHANGE TO CORRECT ERRORMSG!");
        return -1;
    }

    int input_length = stringLength(input);
    char bigram[input_length][2];
    char cipher_text[input_length][2];
    int bigram_id = 0;
    for (int j = 0; j < input_length; j++) {
        if (j != input_length - 1 && input[j] != input[j + 1]) {
            bigram[bigram_id][0] = input[j];
            bigram[bigram_id][1] = input[j + 1];
            j++;
        } else {
            bigram[bigram_id][0] = input[j];
            bigram[bigram_id][1] = 'X';
        }
        char encrypted_left, encrypted_right;
        encrypt(key, bigram[bigram_id][0], bigram[bigram_id][1],
                &encrypted_left, &encrypted_right);
        cipher_text[bigram_id][0] = encrypted_left;
        cipher_text[bigram_id][1] = encrypted_right;

        printf("%c%c ", encrypted_left, encrypted_right);

        bigram_id++;
    }
    //TODO: HERE BIGRAM IST FERTIG
    // MIT OPTION KANN MAN ENTSCHEIDEN OB VER ODER ENTSCHLÜSSELN
    // JEW EINE FUNKT  SCHREIBEN DIE DAS MACHT
    // DA GIBT ES REGELN IN DER ANGABE ... BIGRAMM IST EIN 2D ARRAY.. MUSST DU RICHTIG DURCHITERIEREN

    printf("\n option ist %d\n", option);


    return 0;
}


int main() {

    char key[25];
    generatePlayfairSquare(key);

    //choose option
    int option = getOption();
    if (option == 0) {
        return 0;
    }

    int retval = process_input(option, key);
    if (retval == -1) { // meaning some kind of error
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
int stringLength(char *text) {
    // TODO: Implement
    int i = 0;
    while (text[i] != '\0') {
        i++;
    }
    // WARNING: Do not change the signature of the function
    return i;
}

//-----------------------------------------------------------------------------
void toUpper(char *text) {


    int i = 0;
    while (text[i] != '\0') {
        if (text[i] >= 'a' && text[i] <= 'z') {
            text[i] = text[i] - 32;
        }

        i++;
    }

    // TODO: Implement


    // WARNING: Do not change the signature of the function
}

//-----------------------------------------------------------------------------
void replaceLetters(char *text, char original, char new_char) {

    int i = 0;
    while (text[i] != '\0') {
        if (text[i] == original) {
            text[i] = new_char;
        }

        i++;
    }

    // TODO: Implement
    // WARNING: Do not change the signature of the function
}

