# Specification for Assignment 2

## Learning objective
Functions, parameter passing, pointers, arrays, strings, ASCII

## Task

Create a program that implements a modified version of the [Playfair cipher](https://de.wikipedia.org/wiki/Playfair). After entering a key (A-Z and space, max. 25 characters) the program can encrypt and decrypt a string of characters (A-Z and space, max. 50 characters).

### Preparation (=cleaning) of the key

A valid key may only contain the letters A-Z (case insensitive, minimum 1 letter) and spaces, and may be a maximum of 25 characters long (including spaces). To use the key, it must first be cleaned. This process consists of the following steps:

* Spaces are removed.
* All characters are converted to upper case.
* W is replaced with V.
* In the case of letters that occur several times, only the first occurrence of the letter is retained. All other occurrences of the letter are removed.

---
**Example:**
```
We program -> VIRPOGAMS
```

---

### Create the Playfair square

The 5x5 Playfair square is filled starting from the top left (index 0). First all fields with even indexes are filled and only then all fields with odd indexes. 
The filling is done first with the cleaned key, then all unused letters of the alphabet are inserted.

Example: see [Program flow](#program flow)


### Encryption

A valid plaintext (=the text to be encoded) may only contain the letters A-Z (case insensitive, at least one letter) and spaces and may be a maximum of 50 characters long (including spaces).

The plaintext is prepared as follows:

* Spaces are removed.
* All characters are converted to upper case.
* W is replaced with V.

The plaintext is then processed into bigrams. A bigram is a pair of letters, which means that e.g. the prepared plaintext TIP is converted into the bigrams SP, IT, and ZE. The following rules apply to this conversion in this order:

* If two identical characters occur in a bigram, the letter X is inserted between the letters (e.g. DO PP EL T -> DO PX PE LT). Attention, the maximum length of 50 characters also applies to the bigrams! That means, if the bigrams grow to a total length of more than 50 characters because of inserted 'X', the plaintext is also invalid.
* If the text now has an odd number of characters, the last bigram is filled up with X (e.g. ESP -> ES PX or BETT -> BE TX T -> BE TX TX)

The encryption process uses the following three Playfair cipher rules:

1. if both letters are in the same line of the Playfair square, they are each replaced with their *right* neighbor letter in the square If there is a letter on the right edge of the square, it will be replaced with the letter on the left edge of the same line of the square.
2. if both letters are in the same column of the Playfair square, they will be replaced with their *lower* neighbor letter in the square If there is a letter at the bottom of the square, it will be replaced with the letter at the top of the same column.
3. if the letters are in different rows and columns of the Playfair square, the letter will be replaced with the letter in the same row but the column of the other letter (the two letters form a rectangle in the Playfair square and are replaced with their respective corners).

*Note:* The case that the plaintext contains an XX or is padded to XX does not need to be taken into account in the encryption.

Example: see [Program flow](#program flow)

### Decryption

A valid ciphertext (=encrypted text) may only contain the letters A-Z (case insensitive, at least 2 letters) and spaces and may be a maximum of 50 characters long (including spaces). The number of letters in the ciphertext must be an even number and the text must not contain the letter W or bigrams with two equal letters.

For the decoding the ciphertext is prepared as follows:

* Spaces are removed.
* All characters are converted to upper case.

The decryption process is the reverse of encryption with the following rules:

1. if both letters are in the same line of the Playfair square, they are replaced with their *left* neighbor letter in the square. If there is a letter on the left edge of the square, it will be replaced with the letter on the right edge of the same line of the square.
2. if both letters are in the same column of the Playfair square, they will be replaced with their *upper* neighbor letter in the square If there is a letter at the top of the square, it will be replaced with the letter at the bottom of the same column.
If the letters are in different rows and columns, the decryption is the same as for encryption (rule 3).

Example: see [Program flow](#program flow)

## Program flow:

After program start the prompt for entering the key should be displayed directly:

```
Please enter key: <key>
```

Where `<key>' is replaced with user input followed by Enter (without square brackets).
If an invalid key was entered, the last query is repeated.
If a valid key was entered, the [cleaned key](#preparation-clean-up-the-key) followed by the playfair square is output.

Example with key [Hello World
```
Selected key: HALOVET

Playfair Square:
H J A K L
M O N V P
E Q T R B
S C U D X
F Y G Z I
```

Then the user* is asked with the following output whether he/she wants to encrypt or decrypt a text or quit the program.
``` 

Please select an option:
1 - Encrypt
2 - Decrypt
0 - End program
  
<value>
```
In this output, `<value>' corresponds to the user input.
If `<value>' has the value 0, the program is terminated with the return value 0.
If an invalid value was entered (i.e., neither '0' nor '1' or '2'), the last query is repeated.

If 1 or 2 was selected, the text will be encrypted or decrypted with the procedure below.
Then the above query of options is repeated until the user* ends the program.

### Encryption

If a plaintext is encrypted, the text is queried first:
```
Plain text: <text>
```
Here `<text>' corresponds to the user input.
If an invalid text was entered, the last query is repeated.

Then the text is prepared as described above, encrypted and output in the following format:

Example with plain text 'Programming is fun' with key from above (HALOVET)
```
Prepared plain text: PR OG RA MX MI ER EN MA CH TS PA SX SX
Ciphertext: VB NY TK PS PF QB TM NH SJ EU NL CS CS
```

### Decryption
If a cipher text is decrypted, the text is queried first:
```
Ciphertext: <text>
```
Here `<text>' corresponds to the user input.
If an invalid text was entered, the last query is repeated.

Then the text is prepared as described above, decoded and output in the following format:

Example with ciphertext 'vbnytkpspfqbtmnhsjeunlcs' with key from above (`HALOVET`)
```
Prepared Ciphertext: VB NY TK PS PF QB TM NH SJ EU NL CS CS
Plain text: PR OG RA MX MI ER EN MA CH TS PA SX SX 
```

### Example
```
Please enter your key: Hello World
Selected key: HALOVET

Playfair Square:
H J A K L
M O N V P
E Q T R B
S C U D X
F Y G Z I

Please select an option:
1 - Encrypt
2 - Decrypt
0 - End program

1
Plain text: Programming is fun
Prepared plain text: PR OG RA MX MI ER EN MA CH TS PA SX SX
Ciphertext: VB NY TK PS PF QB TM NH SJ EU NL CS CS

Please select an option:
1 - Encrypt
2 - Decrypt
0 - End program

2
Ciphertext: vbnytkpspfqbtmnhsjeunlcscs
Prepared Ciphertext: VB NY TK PS PF QB TM NH SJ EU NL CS CS
Plain text: PR OG RA MX MI ER EN MA CH TS PA SX SX

Please select an option:
1 - Encrypt
2 - Decrypt
0 - End program

0
```

## Framework

A framework, which takes over the creation of the Playfair square, is provided in [framework.h](./framework.h)
The function [generatePlayfairSquare] of the framework can be used to query the key, clean it up and then output the Playfair square. The `generatePlayfairSquare` function is passed the `square` parameter which represents the Playfair square.

For the 'generatePlayfairSquare' to work correctly, the following three functions must be implemented in the file 'a2.c':

* `int stringLength(char *text)`: Returns the length of the zero terminated string `text` as int. (Length of the string without the zero terminator \0)
* `void toUpper(char *text)`: Converts all letters of the string `text` to upper case.
* `void replaceLetters(char *text, char original, char new_char)`: Replaces all occurrences of the character `original` in the string `text` with the character `new_char`.

*Note:* Strings longer than SIZE_BUFFER are NOT tested by the TestSystem. 

## Specification

**No functions related to dynamic memory management** may be used (malloc).
* Also **not allowed libraries**: <string.h> and <stdlib.h>
* No additional output
* All issues are made on stdout
* No issues on stderr
* Delivery until *at the latest*: 05.12.2020 23:59 (time valid in Austria)
* Delivery: a2.c


