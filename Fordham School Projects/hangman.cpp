//Ahsan Salik
//Computer Science 1
//Hangaman Final Project

#include<iostream>
#include<cmath>
#include<string>
#include<ctime>
#include<cstdlib>
#include<bits/stdc++.h>

using namespace std;

//Displays the options of difficulty (easy, medium, hard) then prompts user to
//enter an number (1, 2, 3) that determines the difficulty. If the number is
//not (1, 2, 3) then reprompts user until a choice from (1, 2, 3) is entered.
//Does not return anything.
void difficulty_option(int &num);

//Takes the input of the user that they are guessing. If they enter an
//uppercase letter or if they repeat a previous guess, user will be reprompted
//to enter a valid input. Does not return anything.
void choice_determinant(string &guess);

//Determines whether the input is a match to the secret word. If it is a match,
//then the chances remain unchanged. If it is not a match, then the number of
// chances will be reduced by one. Does not return anything.
void input_chance(string guess, string &dashes, string &used, string secret_word, int &chances);

//If the secret word matches with the dashes (the dashes will be modified to
//match the secret word), then this function will display that the user has won.
//If the secret word does not match with the dashes after the user has used
//their chances, then the funtion will display that the user has lost.
//Does not return a value.
void victor_display(string secret_word, string dashes);

//Prompts the user to play again by asking them to input a char. Returns the
//char that the user inputted if it is a valid input. If it is not valid, user 
//will be prompted to enter a new input. The chars will be used to determine
//whether the user would like to play again and whether they would like to play
//the same word. Depending on their choices, bool variables will be be called
//by reference so that the while and if conditions are met or unmet.
//Does not return a value.
void def_loop(bool &loop_var, bool &loop_var2);

//Takes the secret word and depending on its length it sets the number of
//dashes needed to display. Does not return a value.
void renew_dashes(string secret_word, string &dashes);

//Checks whether the letter that the user inputs matches with any of the
//letters from the secret word. If there is a match, returns true. If there
//is not a match, returns false.
bool match(string letter, string word);

//The following comments apply to all three of the functions below.
//Creates an size 5 array of strings that are (easy, medium, hard) words. 
//Then, randomly chooses among the 5 words. According to the selected word, 
//references a string of dashes that matches the number of letters in the 
//selected word. Returns the selected word.
string def_easy(string &dashes);
string def_medium(string &dashes);
string def_hard(string &dashes);


int main()
{
    //bool variables that will let user play again and choose whether they
    //would like to play the same word or a new word.
    bool play_again(true), play_again2(true);

    //A string that is declared, and it is used to store the secret word.
    string secret_word;

    while(play_again == true){

         //The number of chances to guess.
         int chances(10);

         //The number for the difficulty of the word.
         int user_difficulty(0);    

         //wrong_set is an array to store the wrong guesses.
         char wrong_set[10];
    
         //dashes is declared, and it is used to store the number of dashes.
         //used is declared, and it is used to store the letters already used.
         //guess is initialized, and it is the user's guess.
         string dashes(" "), used(" "), guess(" ");

         if(play_again2 == true){
            difficulty_option(user_difficulty);
         
            //This series of if statements is used to call the appropriate
            //function depending on the difficulty the user chooses.
            if(user_difficulty == 1){
                secret_word = def_easy(dashes);
            }

            if(user_difficulty == 2){
                secret_word = def_medium(dashes);
            }

            if(user_difficulty == 3){
                secret_word = def_hard(dashes);
            }
         }
         else if(play_again2 == false){
             renew_dashes(secret_word, dashes);
         }

         //while the user still has chances and while the secret word does not
         //match with the total guesses made by the user, prompts the user to
         //enter a letter. The letter will be used in the parameter of
         //function choice_determinant to determine if it is a valid input.
         //Once a valid input is entered, the input is used in function
         //input_chance to determine if input matches a letter in the secret
         //word.
         while(chances > 0 && dashes != secret_word)
         {

             cout << dashes << endl;
             cout << chances << " chances left\n";
             cout << "Enter a letter: \n";
             cin >> guess;

             choice_determinant(guess);
        
             while(match(guess, used)){
                 cout << "You have guessed this letter before." << endl;
                 cout << "Enter a letter: \n";

                 cin >> guess;
            
                 choice_determinant(guess);
             }

             input_chance(guess, dashes, used, secret_word, chances);
         }

         victor_display(secret_word, dashes);
         def_loop(play_again, play_again2);
    }

    return 0;
}

void difficulty_option(int &num){

    cout << "Please enter a difficulty.\n";
    cout << "The number 1 for easy.\n";
    cout << "The number 2 for medium.\n";
    cout << "The number 3 for hard.\n";
    cin >> num;

    while(num != 1 && num != 2 && num != 3)
    {
        cout << "Invalid Input. Please Enter A New Value.\n";
        cin >> num;
    }
}

void choice_determinant(string &guess){
    
    while(guess.length() > 1 || guess[0] > 'z' || guess[0] < 'a'){ 
        if(guess.length() > 1){
            cout << "Cannot exceed more than one character as input.\n";
            cin >> guess;
        }
        if(guess[0] > 'z' || guess[0] < 'a'){
            cout << "Cannot be upper-case letter.\n";
            cin >> guess;
        }
    }
}

void input_chance(string guess, string &dashes, string &used, string secret_word, int &chances){
    
    size_t index_found = secret_word.find(guess);
    if(index_found != string::npos)
    {
        for(int i = 0; i < secret_word.length(); ++i)
        {
            if(secret_word[i] == guess[0])
            {
                dashes[i] = guess[0];
            }
        }

        cout << "Correct Match!\n";
    }
    else
    {
        cout << "Incorrect." << endl;
        used += guess[0];
        sort(used.begin(), used.end());
        cout << "Incorrect Letters Used: " << used << endl;
        chances = chances - 1;                
    }
}

void victor_display(string secret_word, string dashes){

    if(dashes == secret_word)
    {
        cout << "You Win!" << endl;
        cout << "The word is: " << secret_word << endl;
    }
    else
    {
        cout << "You lose." << endl;
        cout << "The word is: " << secret_word << endl;
    }
}

void def_loop(bool &loop_var, bool &loop_var2){

    char call;
    char sec_call;

    cout << "Would you like to play again?" << endl;
    cout << "Enter [Y]es or [N]o." << endl;
    cin >> call;

    while(call != 'Y' && call != 'N' && call != 'y' && call != 'n'){
        cout << "Invalid input. Please enter a new input." << endl;
        cout << "Enter [Y]es or [N]o." << endl;
        cin >> call;
    }

    if(call == 'Y' || call == 'y'){

         loop_var = true;

         cout << "Would you like to play the same word? Enter [Y]es or [N]o" << endl;
         cin >> sec_call;

         while(sec_call != 'Y' && sec_call != 'N' && sec_call != 'y' && sec_call != 'n'){
             cout << "Invalid input.  Please enter a new input." << endl;
             cout << "Enter [Y]es or [N]o." << endl;
             cin >> sec_call;
         }

         if(sec_call == 'Y' || sec_call == 'y'){
             loop_var2 = false;
         }

         if(sec_call == 'N' || sec_call == 'n'){
             loop_var2 = true;
         }
    }

    if(call == 'N' || call == 'n'){
        loop_var = false;
    }
}

void renew_dashes(string secret_word, string &dashes){

    if(secret_word.length() == 7){
        dashes = "- - - -";
    }

    if(secret_word.length() == 17){
        dashes = "- - - - - - - - -";
    }

    if(secret_word.length() == 25){
        dashes = "- - - - - - - - - - - - -";
    }
}

bool match(string letter, string word){
    return (word.find(letter) != string::npos );
}

string def_easy(string &dashes)
{
    using namespace std;
    string word;
    string choices[5] = {"c o o l","f r e e", "n i c e", "b o r e", "b e a n"};
    dashes = "- - - -";

    srand(time(0));
    word = choices[rand() % 5];

    return word;
}

string def_medium(string &dashes)
{
    string word;
    string choices[5] = {"q u i z z i c a l", "a r d u o u s l y", "u n i n v i t e d",
        "f e a r f u l l y","b l a c k j a c k"};
    dashes = "- - - - - - - - -";

    srand(time(0));
    word = choices[rand() % 5];

    return word;
}

string def_hard(string &dashes)
{
    string word;
    string choices[5] = {"p h o t o o x i d i z e d", "t h y m e c t o m y z e d",
        "o b s t r e p e r o u s", "d y s f u n c t i o n a l", "e l e c t r o m a g n e t"};
    dashes = "- - - - - - - - - - - - -";

    srand(time(0));
    word = choices[rand() % 5];

    return word;
}

