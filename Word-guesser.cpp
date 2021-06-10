#include <iostream>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <string>
using namespace std;

//FUNCTIONS TO BE USED
void guessWord(string word);
//This function allows the user to guess the word letter by letter

void findNumber(string testWord);
//This function outputs to the user the length of the word along with the
//"_" associated

void loadFile();
//Loads in the words to be guessed

void playGame();
//This function runs the whole game

void getWord(string wordArray[]);
//Get a random word from the array and pass it into the guess word function

void resetPuzzle();
//Reset game and choose a new word

//--------------------
//START OF CODE BELOW
//--------------------

//main() is used to call the playGame() function to start the game
int main() {
    string playerName;
    int index = 0;

    //Get player name and greet them
    do {
        cout << "Enter your name: " << endl;
        cin >> playerName;
        index += 1;
    }
    while (index != 1);
    cout << "\nWelcome " << playerName << " to UMBC's Word Guess!" << endl;

    playGame();

    return 0;
}

//playGame function will control the entire game
void playGame(){
    string userChoice;

    cout << "Enter \"play\" to load file and play a game!";
    cin >> userChoice;

    //If statement will load the file and start the game
    if (userChoice == "play") {
        cout << "Downloading file now! \n" << endl;
        loadFile();}

        //else statement will reprompt the user until ready to play
    else{
        main();}
}


//Loads the word in to be guessed
void loadFile(){
    string guessWords[3422] = {};
    fstream wordFile;

    wordFile.open("words.txt");

    //Check to see if the file can be opened
    if (wordFile.is_open()){
        for (int i = 0; i < 3422; i++)
            wordFile >> guessWords[i];

        //Display to the user that the file was loaded successfully
        cout << "Your file was imported!\n"
             << "3422 words imported.\n" << endl;

        wordFile.close();}

        //If the file cannot be opened end the program
    else{
        cout << "Unable to open the file, try again!" << endl;}

    //Pass the array to the getWord function for a random word to be chosen
    getWord(guessWords);}


//Takes a random number and extracts a random word from the array
void getWord(string wordArray[]){

    //Random Seed used to choose a random word
    srand (time(NULL));

    //Generate a number within the bounds of the array
    int numWord = rand() % 3422 + 1;
    string wordGuess = wordArray[numWord];

    //Pass the word into numberFound to output the length of the word
    findNumber(wordGuess);

    //Pass the word into guessWord to allow the user to begin guessing
    guessWord(wordGuess);}


//Gives the length of the word
void findNumber(string word){
    int numWord = 0;

    //For loop to find the length of word
    for (int i = 0; word[i] != '\0'; i++)
        numWord += 1;



    //Print the size of the word and the blank spaces associated
    cout << "Ok. I am thinking of a word with " << numWord << " letters." << endl;
    cout << numWord << " letters remain." << endl;

    //For loop is used to output underscores
    for (int i = 0; i < numWord; i++) {
        cout << '_';}

    //Space to clean up the output display
    cout << " " << endl;}

//Where the user will guess the word
void guessWord(string word) {
    char guess;
    string updatedWord;
    char wrongGuesses[6] = {};
    int arrayIndex = 0;
    int numWrong = 6;
    bool correctGuess = false;
    int numWord = 0;
    int lettersLeft = 0;

    //For loop to find the length of word
    for (int i = 0; word[i] != '\0'; i++)
        numWord += 1;

    lettersLeft = numWord;

    //For loop used to add necessary '_' to updatedWord
    for (int i = 0; i < numWord; i++)
        updatedWord += '_';

    cout << "What letter would you like to guess? " << endl;
    cin >> guess;

    //While the user does not guess more than 6 wrong guesses
    //and while the user does not guess the word, allow for more guesses
    while (numWrong > 0 && updatedWord != word){

        //Iterate through word and check if guess is in the word
        for (int i = 0; i < numWord; i++)
            if (guess >= 'a' && guess <= 'z') {
                if (guess == word[i] && guess != updatedWord[i]) {
                    updatedWord[i] = guess;
                    lettersLeft -= 1;
                    correctGuess = true;
                }
            }

                //Input validation for when the guess is uppercase
            else{
                cout << "Please use only lowercase letters!" << endl;
                guessWord(word);
            }

        //Print updated word
        cout << updatedWord << "\n" << endl;

        //If statement which checks to see if the guess was incorrect
        if (correctGuess == false){
            wrongGuesses[arrayIndex] = guess;
            numWrong -= 1;
            cout << "There are no " << guess << "\'s in the puzzle" << endl;
            cout << "You have " << numWrong << " bad guesses left.\n" << endl;
            arrayIndex += 1;
        }

        //If the word has been guessed, this if statement doesn't allow for another guess
        if (updatedWord != word && numWrong != 0){
            cout << lettersLeft << " letters remain." << endl;
            cout << "What letter would you like to guess? " << endl;
            cin >> guess;
            correctGuess = false;
        }
    }
    //If the user wins
    if (updatedWord == word) {
        cout << "Congrats you won!" << endl;
        cout << "The correct word was: " << word << "\n" << endl;
    }
        //If the user loses
    else{
        cout << "Sorry, you lost" << endl;
        cout << "The correct word was: " << word << endl;
    }
    resetPuzzle();
}


//Reset the puzzle and choose a new word
void resetPuzzle(){
    char userInput;

    //Ask the user whether they want to start a new game
    cout << "Another game? y/n" << endl;
    cin >> userInput;

    //If yes, load the file again and start over with a new word
    if (userInput == 'y'){
        cout << "" << endl;
        loadFile();}

    //reprompt the user for an invalid input
    if (userInput != 'y' && userInput != 'n') {
        cout << "Enter a valid response!" << endl;
        resetPuzzle();}

    //If no, end the game and thank the player for playing
    if (userInput == 'n'){
        cout << "Thank you for playing!" << endl;
    }
}
