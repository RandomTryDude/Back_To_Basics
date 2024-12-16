#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>

#define USC "\033[4m" // underline
#define RESET "\033[0m"
#define COLOR_GREEN "\033[32m"
#define COLOR_RESET "\033[0m"

void underline_letter(const char *word) {
    for (int i = 0; i < strlen(word); i++) {
        printf(USC "%c" RESET " ", word[i]);
    }
    printf("\n");
}

void print_banner(void) {
    const char word[] = "HANGMAN";
    printf(
        "\n"
        "|=======================================|\n"
        "|\t%sTo this C implementation%s\t|\n"
        "|\t%sof a Hangman game%s\t\t|\n"
        "|\t\t\t RandomCodeCorp |\n"
        "|=======================================|\n", COLOR_GREEN, COLOR_RESET, COLOR_GREEN, COLOR_RESET);
    printf(
        "\n"
        "_______\n"
        "|     |\n"
        "|     O\n"
        "|    /|\\\n"
        "|    / \\\n"
        "=====\t    \n\n");

    underline_letter(word);
}

void hang_setup(int number) {
    printf(
        "\n"
        "|=======================================|\n"
        "|\t%sTo this C implementation%s\t|\n"
        "|\t%sof a Hangman game%s\t\t|\n"
        "|\t\t\t RandomCodeCorp |\n"
        "|=======================================|\n", COLOR_GREEN, COLOR_RESET, COLOR_GREEN, COLOR_RESET);

    switch (number) {
        case 0: break;
        case 1: printf("\n\n\n\n=====" RESET "\n\n"); break;
        case 2: printf("\n|\n|\n|\n|\n=====" RESET "\n\n"); break;
        case 3: printf("_______\n|\n|\n|\n|\n=====" RESET "\n\n"); break;
        case 4: printf("_______\n|     |\n|\n|\n|\n=====" RESET "\n\n"); break;
        case 5: printf("_______\n|     |\n|     O\n|\n|\n=====" RESET "\n\n"); break;
        case 6: printf("_______\n|     |\n|     O\n|     |\n|\n=====" RESET "\n\n"); break;
        case 7: printf("_______\n|     |\n|     O\n|    /|\n|\n=====" RESET "\n\n"); break;
        case 8: printf("_______\n|     |\n|     O\n|    /|\\\n|\n=====" RESET "\n\n"); break;
        case 9: printf("_______\n|     |\n|     O\n|    /|\\\n|    /\n=====\t    \n\n"); break;
        case 10: printf("_______\n|     |\n|     O\n|    /|\\\n|    / \\\n=====\t    \n\n"); break;
    }
}

void display_word(const char *word_to_guess, const bool *guessed, int wordlen) {
    for (int i = 0; i < wordlen; i++) {
        if (guessed[i]) {
            printf("%c ", word_to_guess[i]);
        } else {
            printf("_ ");
        }
    }
    printf("\n\n");
}

void solo(void) {
    system("clear");
    const char *animals[] = {
        "aardvark", "albatross", "alligator", "ant", "anteater",
        "antelope", "ape", "armadillo", "donkey", "baboon",
        "badger", "barracuda", "bat", "bear", "beaver",
        "bee", "bison", "boar", "buffalo", "butterfly",
        "camel", "capybara", "caribou", "cassowary", "cat",
        "caterpillar", "cattle", "chameleon", "cheetah", "chicken",
        "chimpanzee", "chinchilla", "cobra", "cockroach", "cod",
        "cormorant", "coyote", "crab", "crane", "crocodile",
        "crow", "deer", "dinosaur", "dog", "dolphin",
        "dove", "dragonfly", "duck", "eagle", "echidna",
        "eel", "elephant", "elk", "emu", "falcon",
        "ferret", "finch", "firefly", "fish", "flamingo",
        "fox", "frog", "gazelle", "gerbil", "giraffe",
        "goat", "goldfish", "goose", "gorilla", "grasshopper",
        "grouse", "guinea pig", "gull", "hamster", "hare",
        "hawk", "hedgehog", "heron", "herring", "hippopotamus",
        "hornet", "horse", "hummingbird", "hyena", "iguana",
        "impala", "jaguar", "jellyfish", "kangaroo", "kingfisher",
        "koala", "kookaburra", "kouprey", "kudu", "lapwing",
        "lark", "lemur", "leopard", "lion", "llama"
    };

    char word_to_guess[32];
    strcpy(word_to_guess, animals[rand() % 100]);
    int wordlen = strlen(word_to_guess);
    bool guessed[wordlen];
    memset(guessed, false, wordlen);

    char tried_letters[26];
    int tried_count = 0;
    int number = 0;
    int correct_guesses = 0;
    bool word_guessed = false;

    while (true) {
        hang_setup(number);
        display_word(word_to_guess, guessed, wordlen);

        if (word_guessed || correct_guesses == wordlen) {
            printf("Congratulations! You saved the man! The word was: %s\n", word_to_guess);
            break;
        }

	 printf("Tried letters: ");
        for (int i = 0; i < tried_count; i++) {
            printf("%c ", tried_letters[i]);
        }
        printf("\n");
        
        
        printf("Enter a letter: ");
        char guess;
        scanf(" %c", &guess);
        guess = tolower(guess);

        // Check if the letter was already guessed
       
        

        

        // Add to the list of guessed letters
        if (tried_count < sizeof(tried_letters) / sizeof(tried_letters[0])) {
            tried_letters[tried_count++] = guess;
        }
        

        bool found = false;
        for (int i = 0; i < wordlen; i++) {
            if (tolower(word_to_guess[i]) == guess && !guessed[i]) {
                guessed[i] = true;
                correct_guesses++;
                found = true;
            }
        }

        if (!found) {
            number++;
            if (number == 10) {
                hang_setup(number);
                printf("Game over! The word was: %s\n", word_to_guess);
                break;
            }
        }

        // Display guessed letters
        

        system("clear");
    }
}

int main(void) {
    system("clear");
    srand(time(NULL));

    print_banner();
    printf("\nPress any button to start\n");
    getchar();
    
    while (getchar() != '\n' && getchar() != EOF); // clear the buffer if user type a char instead of just enter
    solo();

    return 0;
}
