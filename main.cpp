#include <iostream>
#include <string>

using namespace std;

const int height = 10;
const int width = 40;
const int a = 97; //ascii
const int z = 122; //ascii

void InitializeHangman(char[height][width]);
void PrintHangman(char[height][width], int);
string InputWord();
void PrintWord(string);
string MakeHiddenWord(string);
bool CheckVictory(string);
string GetGuess(string[26]);
bool CheckGuess(string, string);
string ModifyWord(string, string, string);
bool Replay();

int main() {
    char hangedMan[height][width];
    int harm;
    string word;
    string hiddenWord;
    string guess;
    bool isInWord;
    bool isVictory;
    bool replay;
    string guesses [26];
    int inter;

    do {
        InitializeHangman(hangedMan);
        harm = 0;
        PrintHangman(hangedMan, harm);
        word = InputWord();
        hiddenWord = MakeHiddenWord(word);
        isVictory = false;
        inter = 0;

        for (int i = 0; i < 26; ++i) {
            guesses[i] = "";
        }

        while (harm < 6 && !isVictory) {
            PrintHangman(hangedMan, harm);
            PrintWord(hiddenWord);
            guess = GetGuess(guesses);
            guesses[inter] = guess;
            inter++;
            isInWord = CheckGuess(guess, word);

            if (! isInWord) {
                ++harm;
            } else {
                hiddenWord = ModifyWord(word, hiddenWord, guess);
                isVictory = CheckVictory(hiddenWord);
            }
        }
        PrintHangman(hangedMan, harm);

        PrintWord(word);

        cout << endl;

        harm == 6 ? cout << "You lose!" : cout << "You win!";

        cout << endl;

        replay = Replay();
    } while (replay);

    return 0;
}
// Input: empty 2D array
// Output: Draws the gallows
void InitializeHangman(char hangedMan[height][width]) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j){
            hangedMan[i][j] = ' ';
        }
    }

    hangedMan[0][0] = 'L';
    hangedMan[0][1] = 'e';
    hangedMan[0][2] = 't';
    hangedMan[0][3] = '\'';
    hangedMan[0][4] = 's';
    hangedMan[0][5] = ' ';
    hangedMan[0][6] = 'P';
    hangedMan[0][7] = 'l';
    hangedMan[0][8] = 'a';
    hangedMan[0][9] = 'y';
    hangedMan[0][10] = ' ';
    hangedMan[0][11] = 'H';
    hangedMan[0][12] = 'a';
    hangedMan[0][13] = 'n';
    hangedMan[0][14] = 'g';
    hangedMan[0][15] = 'm';
    hangedMan[0][16] = 'a';
    hangedMan[0][17] = 'n';

    for (int j = 0; j < width; ++j) {
        hangedMan[height - 1][j] = '=';
        hangedMan[height - 2][j] = '=';
    }

    for (int i = 0; i < height - 2; ++i) {
        hangedMan[i][width - 5] = '|';
        hangedMan[i][width - 6] = '|';
    }

    for (int j = width - 15; j < width - 4; ++j) {
        hangedMan[0][j] = '=';
    }

    hangedMan[1][width -13] = '|';
}

//Input: The 2D array from InitializeHangedMan()
//Output: adds a hanging man, piece by piece based on harm done to him
void PrintHangman(char hangedMan[height][width], const int harm) {

    //Will draw all the needed parts as the cases do not have breaks.
    switch (harm) {
        case 6:
            hangedMan[5][width - 14] = '/';
        case 5:
            hangedMan[5][width - 12] = '\\';
        case 4:
            hangedMan[3][width - 14] = '\\';
        case 3:
            hangedMan[3][width - 12] = '/';
        case 2:
            hangedMan[3][width - 13] = '|';
            hangedMan[4][width - 13] = '|';
        case 1:
            hangedMan[2][width - 13] = 'O';
        default:
            break;
    }

    // prints the current status of the hanging man
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            cout << hangedMan[i][j];
        }
        cout << endl;
    }
}
//Output : a word. No spaces, no numbers, no symbols, all lowercase
string InputWord() {
    string word;
    bool isValid;
    do {
        isValid = true;
        cout << "Please enter a word: \n";
        getline(cin, word);

        for (int i = 0; i < word.length(); ++i) {
            if (tolower(word[i]) < a || tolower(word[i]) > z) {
                isValid = false;
            }
        }
        if (! isValid) {
            cout << "Invalid Word. \n";
        }
    } while(! isValid);

    return word;
}

//Input: The word from InputWord()
//Output: Makes a string the same length as the input word, but entirely '_'
string MakeHiddenWord (const string word) {
    string hiddenWord = word;

    for (int i = 0; i < word.length(); ++i) {
        hiddenWord[i] = '_';
    }

    return hiddenWord;
}

//Input: A string
//Output: A string separated by spaces
void PrintWord(const string word) {
    for (int i = 0; i < word.length(); ++i) {
        cout << word[i] << ' ';
    }
    cout << endl;
}

//Input: The hiddenWord (that started as all '_')
//Output: A boolean, true if there are no '_' left
bool CheckVictory(const string word) {
    bool isVictory = true;

    for (int i = 0; i < word.length(); ++i) {
        if (word[i] == '_') {
            isVictory = false;
        }
    }
    return isVictory;
}

//Output: A letter, lowercase
string GetGuess(string guesses[26]) {
    string guess;
    bool isGuessed;

    do {
        isGuessed = false;
        cout << "Guess a letter: \n";
        getline(cin, guess);

        for (int i = 0; i < guess.length(); ++i) {
            guess[i] = tolower(guess[i]);
        }

        if (guess.length() == 1 && !(guess[0] < a || guess[0] > z)) {
            for (int i = 0; i < 26; ++i) {
                if (guess == guesses[i]) {
                    isGuessed = true;
                    cout << "You've already guessed " << guess << endl;
                }
            }
        }


    } while (cin.fail() || isGuessed ||
        guess.length() > 1 || guess[0] < a || guess[0] > z);

    return guess;
}

//Input: a lower case letter, and the word chosen at start
//Output: a boolean, true if the letter is in the word
bool CheckGuess(const string guess, const string word) {
    for (int i = 0; i < word.length(); ++i) {
        if (tolower(word[i]) == tolower(guess[0])) {
            return true;
        }
    }

    return false;
}

//Input: a letter, the word chosen at start, and it's hidden version ('_')
//Output: Any of the letter found in the word will be revealed in the hidden word
string ModifyWord(string const word,string hiddenWord, const string guess) {
    for (int i = 0; i < word.length(); ++i) {
        if (tolower(word[i]) == tolower(guess[0])) {
            hiddenWord[i] = word[i];
        }
    }
    return hiddenWord;

}


//Output: a boolean, true is the user wants to replay
bool Replay() {
    string replay;

    do {
        cout << "Would you like to play again? (y/n) \n";
        getline(cin, replay);

        for (int i = 0; i < replay.length(); ++i) {
            replay[i] = tolower(replay[i]);
        }

    } while (cin.fail() ||
        ! (replay == "y" || replay == "n" || replay == "yes" || replay == "no"));

    return replay == "y" || replay == "yes";
}