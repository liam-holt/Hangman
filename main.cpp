#include <iostream>
#include <string>

using namespace std;

const int height = 10; //height of display
const int width = 40; //width of display
const int a = 97; //ascii
const int z = 122; //ascii
enum hangedPieces {noHarm, head, torso, oneArm,
        twoArms, oneLeg, roundOver}; //hanged pieces
const int maxGuesses = 26; //26 letters

void InitializeHangman(char[height][width]);
void PrintHangman(char[height][width], const int&);
string InputWord();
void PrintWord(const string&);
string MakeHiddenWord(const string&);
bool CheckVictory(const string&);
string GetGuess(string[maxGuesses]);
bool CheckGuess(const string&, const string&);
string ModifyWord(const string&, string, const string&);
bool Replay();

int main() {
    char hangedMan[height][width]; //game display
    int harm; //number of pieces to draw of the hanged man
    string word; //the word to guess for the round
    string hiddenWord; //a string of '_' that changes with correct guesses
    string guess; //user's guess of letter in word
    bool isInWord; //checks if guess is in word
    bool isVictory; //checks if hiddenWord no longer has '_'
    bool replay; //user choice to replay
    string guesses [maxGuesses]; //stores each guess to prevent repeats
    int numGuess; //iterator for guesses array

    //game loop
    do {
        //reset to initial conditions
        InitializeHangman(hangedMan);
        harm = noHarm;
        PrintHangman(hangedMan, harm);
        word = InputWord();
        hiddenWord = MakeHiddenWord(word);
        isVictory = false;
        numGuess = 0;

        for (auto & i : guesses) {
            i = "";
        }

        //round loop
        while (harm < roundOver && ! isVictory) {
            //print display
            PrintHangman(hangedMan, harm);
            PrintWord(hiddenWord);

            //get user's guess
            guess = GetGuess(guesses);
            guesses[numGuess] = guess;
            numGuess++;

            //check if guess in word
            isInWord = CheckGuess(guess, word);

            if (! isInWord) {
                ++harm;
            } else {
                hiddenWord = ModifyWord(word, hiddenWord, guess);
                isVictory = CheckVictory(hiddenWord);
            }
        }
        //round over
        PrintHangman(hangedMan, harm);
        PrintWord(word);
        cout << endl;
        harm == roundOver ? cout << "You lose!" : cout << "You win!";
        cout << endl;

        //ask for replay
        replay = Replay();
    } while (replay);

    return 0;
}
// Input: empty 2D array
// Output: Draws the gallows
void InitializeHangman(char hangedMan[height][width]) {
    //builds 2D array of all '_'
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j){
            hangedMan[i][j] = ' ';
        }
    }


    // Flavor text
    if (width / 2 >= 20) {
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
    }
    else if (width / 2 > 10){
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
        //hangedMan[1][0] = ' ';
        hangedMan[1][1] = 'H';
        hangedMan[1][2] = 'a';
        hangedMan[1][3] = 'n';
        hangedMan[1][4] = 'g';
        hangedMan[1][5] = 'm';
        hangedMan[1][6] = 'a';
        hangedMan[1][7] = 'n';
    }

    else{
        hangedMan[0][0] = 'L';
        hangedMan[0][1] = 'e';
        hangedMan[0][2] = 't';
        hangedMan[0][3] = '\'';
        hangedMan[0][4] = 's';
        //hangedMan[0][5] = ' ';
        hangedMan[1][0] = 'P';
        hangedMan[1][1] = 'l';
        hangedMan[1][2] = 'a';
        hangedMan[1][3] = 'y';
        //hangedMan[0][10] = ' ';
        hangedMan[2][0] = 'H';
        hangedMan[2][1] = 'a';
        hangedMan[2][2] = 'n';
        hangedMan[2][3] = 'g';
        hangedMan[3][0] = 'm';
        hangedMan[3][1] = 'a';
        hangedMan[3][2] = 'n';
    }

    //builds gallows' base
    for (int j = 0; j < width; ++j) {
        hangedMan[height - 1][j] = '=';
        hangedMan[height - 2][j] = '=';
    }

    //gallows' pole
    for (int i = 0; i < height - 2; ++i) {
        hangedMan[i][width - width / 8] = '|';
        hangedMan[i][width - width / 8 - 1] = '|';
    }

    //gallows' branch
    for (int j = width - width/3; j < width - width/10; ++j) {
        hangedMan[0][j] = '=';
    }

    //noose
    hangedMan[1][width - width/3 + 2] = '|';
}

//Input: The 2D array from InitializeHangedMan()
//Output: adds a hanging man, piece by piece based on harm done to him
void PrintHangman(char hangedMan[height][width], const int& harm) {

    //draws current pieces of hanged man
    switch (harm) {
        case roundOver:
            hangedMan[5][width - width/3 + 1] = '/';
        case oneLeg:
            hangedMan[5][width - width/3 + 3] = '\\';
        case twoArms:
            hangedMan[3][width - width/3 + 1] = '\\';
        case oneArm:
            hangedMan[3][width - width/3 + 3] = '/';
        case torso:
            hangedMan[3][width - width/3 + 2] = '|';
            hangedMan[4][width - width/3 + 2] = '|';
        case head:
            hangedMan[2][width - width/3 + 2] = 'O';
        default:
            break;
    }

    // prints the current status of the hanged man
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

        for (char i : word) {
            if (tolower(i) < a || tolower(i) > z) {
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
string MakeHiddenWord (const string& word) {
    string hiddenWord = word;

    for (char & i : hiddenWord) {
        i = '_';
    }

    return hiddenWord;
}

//Input: A string
//Output: A string separated by spaces
void PrintWord(const string& word) {
    for (char i : word) {
        cout << i << ' ';
    }
    cout << endl;
}

//Input: The hiddenWord (that started as all '_')
//Output: A boolean, true if there are no '_' left
bool CheckVictory(const string& word) {
    bool isVictory = true;

    for (char i : word) {
        if (i == '_') {
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

        for (char & i : guess) {
            i = tolower(i);
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
bool CheckGuess(const string& guess, const string& word) {
    for (char i : word) {
        if (tolower(i) == tolower(guess[0])) {
            return true;
        }
    }

    return false;
}

//Input: a letter, the word chosen at start, and it's hidden version ('_')
//Output: Any of the letter found in the word will be revealed in the hidden word
string ModifyWord(string const& word,string hiddenWord, const string& guess) {
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

        for (char & i : replay) {
            i = tolower(i);
        }

    } while (cin.fail() ||
        ! (replay == "y" || replay == "n" || replay == "yes" || replay == "no"));

    return replay == "y" || replay == "yes";
}