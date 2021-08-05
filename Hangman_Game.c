#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const char *words[] = {
    "apple",
    "banana",
    "home"};

size_t string_length(const char str[]);
size_t init_arr(char *word_guess, int len);
int check_win(char A[], const char B[], int num_guess);
size_t check_char(char chr, char *chr_guessed, int len);
size_t to_lower(char letter);
int check_in_word(char character, const char *word);
void replace_char(char *word_guess, const char *word, char chr);

int main()
{
    srand(time(0));
    int random_word_num = (rand() % 3);
    int len = string_length(words[random_word_num]);
    const char *word = words[random_word_num];
    char word_guess[7] = {0};
    init_arr(word_guess, len);
    int num_guess = 10;
    char chr_guessed[11] = {0}; //string that holds every letter guessed
    int j = 0;
    while ((check_win(word_guess, word, num_guess)) != 0)
    {
        printf("%s (%d guesses remaining)\n", word_guess, num_guess);
        printf("Please enter a letter: ");
        char chr = '\0';
        scanf(" %c", &chr);
        chr = to_lower(chr);
        while ((check_char(chr, chr_guessed, len)) == 1 || (check_char(chr, chr_guessed, len)) == -1)
        {
            switch (check_char(chr, chr_guessed, len))
            {
            case (-1): // entered something else then letter
                printf("Your guess '%c' is not a letter.\n", chr);
                printf("Please enter a letter: ");
                scanf(" %c", &chr);
                chr = to_lower(chr);
                break;
            case 1: //already guessed letter
                printf("You already guessed '%c'.\n", chr);
                printf("Please enter a letter: ");

                scanf(" %c", &chr);
                chr = to_lower(chr);
                break;
            }
        }
        if (check_in_word(chr, word) == 1) // letter appears in the word
        {
            printf("Good guess!\n");
            replace_char(word_guess, word, chr);
        }
        else
        {
            printf("No appearances of '%c'...\n", chr);
            num_guess--;
        }
        chr_guessed[j] = chr;
        j++;
    }
    j++;
    printf("You win! the word is: %s\n", word);
    return 0;
}

size_t string_length(const char str[])
{
    assert(str);
    size_t i = 0;
    while (str[i] != '\0')
    {
        i++;
    }
    return i;
}

size_t init_arr(char *word_guess, int len)
{
    for (int i = 0; i < len; i++)
    {
        word_guess[i] = '?';
    }
    word_guess[len] = '\0';
}

size_t check_char(char chr, char *chr_guessed, int len) //1- check if input is a char, //2- check if the char is in the word
{
    if ((chr >= 97) && (chr <= 122)) // if enters- that is char
    {
        for (int i = 0; chr_guessed[i] != '\0'; i++) // check if that letter already guessed
        {
            if (chr_guessed[i] == chr)
            {
                return 1; // already guessed char
            }
        }
        return 0;
    }
    else
    {
        return -1; //not a char
    }
}

size_t to_lower(char letter)
{
    if ((letter >= 65) && (letter <= 90))
    {
        letter += 32;
    }
}

int check_win(char A[], const char B[], int num_guess)
{
    // 0 = win
    int i;
    if (num_guess > 0)
    {
        for (i = 0; ((A[i] != '\0') || (B[i] != '\0')); i++)
        {
            if (A[i] != B[i])
            {
                return 1;
            }
        }
        return 0;
    }
    else
    {
        printf("No more guesses remaining....you lost!\n");
        exit(0);
    }
}

int check_in_word(char character, const char *word)
{
    for (int i = 0; word[i] != '\0'; i++)
    {
        if (word[i] == character)
        {
            return 1; // the letter appears in the word
        }
    }
    return 0; // NOT appear in the word
}

void replace_char(char *word_guess, const char *word, char chr)
{
    for (int i = 0; word[i] != '\0'; i++)
    {
        if (word[i] == chr)
        {
            word_guess[i] = chr;
        }
    }
}