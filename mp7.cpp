#include <bits/stdc++.h> // adds all standard libraries
#include "windows.h"

using namespace std;


enum Variables {  //enum with name Variables
    firstIndex = 0, //for the first word in sentence
    addCounter = 1, //for increments
    sleepTime = 1000, //1 second sleepTime
};

Variables timeSleep = sleepTime; //declares variables using enums
Variables IndexFirst = firstIndex;
Variables addToCounter = addCounter;
ofstream outFile("mp7output.txt"); //opens the output file





//function to count the number of words in the sentence
int countNumberOfWords(string sentence){
    int numberOfWords = 0; //declare variables
    size_t i;

    if (isalpha(sentence[IndexFirst])) { //checks if it is a letter
        numberOfWords+= addToCounter; //adds 1 to the number of words counter
    }

    for (i = 1; i < sentence.length(); i+=addToCounter) { //uses length function to iterate through string
        if ((isalpha(sentence[i])) && (!isalpha(sentence[i-1]))) { //checks if the previous letter is not a letter
            numberOfWords+= addToCounter; // adds 1 to the number of words counter
        }
    }

    return numberOfWords; //returns the integer
}

int checkLengths(string correctWord, string words[],int numWords, int &insertion, int &deletion){//pass by reference for the insertion and deletion

    string firstWord = correctWord; //stores the first word in a new variable


    for(int i=1; i <numWords; i+=addToCounter){ //iterates through the array by the number of words it has

        string compareWord = words[i]; //the word being compared stored in a varaible

        if(firstWord.length() > compareWord.length()){ //if correct word is longer, then the comparative word is shorter
            outFile<<compareWord<< " has too few letters"<<endl;
            deletion+= addCounter; //adds one to deletion error
            continue;
        }
        else if(firstWord.length() < compareWord.length()){ //of correct word is shorts, then the comparative word is longer
            outFile<<compareWord<< " has too many letters"<<endl;
            insertion+= addCounter; //adds one to the insertion error
            continue;
        }

    }

}

void checkSubstitution(string correctWord, string words[],int numWords, int &substitution, int &correct, int &tooManyErrors){

    string firstWord = correctWord; //stores the correct word in variable


    for(int i=1; i <numWords; i+=addToCounter){//iterates through the words in the array
        int counter = 0; //sets error counter every time a new word comes
        string compareWord = words[i]; //sets comparative word to the index

        if(firstWord.length() != compareWord.length()){ //skips over the words that are not same length, as that is redundant
            continue;
        }
        else if(firstWord == compareWord){ //if words are equal then the word is correct
            outFile<<compareWord << " is correct"<<endl;
            correct += addToCounter; //adds one to the correct counter
            continue;
        }

        for(int i = 0; i < compareWord.length(); i+=addToCounter){ //iterates through the comparative word length, as both are the same now
            if(compareWord[i] != firstWord[i]){ //if the letters are not equal
                if(correctWord[i+1] == compareWord[i] && correctWord[i] == compareWord[i+1]){//if it is a transposition it sets counter to 3 so it is not the same as too many errors
                    counter=3;
                }
                counter+=addToCounter; // adds one to the error counter

                continue;
            }

        }

        if(counter == 1){ //if there is 1 error, then it is a substitution
            outFile<<compareWord<< " has a substitution error"<<endl;
            substitution+=addToCounter; //adds one to the substitution error
        }
        else if(counter ==2){ //if it equals 2 then it is too many errors, this works because if it is a transposition error, then the number would be greater than 2
            outFile<<compareWord<< " has too many errors"<<endl;
            tooManyErrors += addToCounter; //adds one to the tooManyError counter
        }
    }
}

void transpositionCheck(string correctWord, string words[],int numWords, int &transposition){
string baseWord = correctWord;

for(int i = 1; i<numWords; i+=addToCounter){
    int counter = 0;
    string testWord = words[i];

  if (baseWord.length() != testWord.length() || baseWord == testWord){
    continue;
  } else{
  for (int i = 0; i < baseWord.length(); i+=addToCounter) {
      if(baseWord[i] != testWord[i]){
          if(baseWord[i+1] == testWord[i] && baseWord[i] == testWord[i+1]){ //same as other function but this one adds 1 to the counter when it detects transposition
            counter+=addToCounter;
          }
      }

  }
    if(counter == 1){
        outFile<<testWord<<" has a transposition error"<<endl;
        transposition+=addToCounter; //adds one to transposition counter
      }

}
}
}

void printArr(string words[], int numWords){ //prints array
    for(int i = 0; i<numWords; i++){
        outFile<<words[i] << " ";
    }
}

int main() {

    ifstream inFile("mp7input.txt"); //open input file

    string sentence;         //declare the variable to store line from input file
    string delimiter = " ";  //to search for spaces between words in the input file
    int insertion = 0;       //counters for the amount of errors in total
    int deletion = 0;
    int transposition = 0;
    int substitution = 0;
    int correct = 0;
    int tooManyErrors = 0;


    while(getline(inFile, sentence)){ //outer while loop reads entire line from input file


        int numWords = countNumberOfWords(sentence); //stores the number of words in the sentence read by calling to a function
        string words[numWords]; //declares an array with length of the number of words in the sentence
        size_t pos = 0;
        int i = 0;

        while ((pos = sentence.find(delimiter)) != string::npos && i < 10) { //finds position of where the delimeter is and loops 10 times
        words[i] = sentence.substr(0, pos); // Store the word in the array
        i+=addToCounter; //increments i
        sentence.erase(0, pos + delimiter.length()); // Erase the word from the sentence
        }

        if (!sentence.empty() && i < 10) {
        words[i] = sentence; // Store the last word in the array
        i+=addToCounter;
        }




        string firstWord = words[IndexFirst]; //stores the first(correct) word in the variable


        outFile<<"The word being checked is: "<<firstWord<<endl;
        Sleep(timeSleep); //need sleep functions to allow the buffer to load, without this the other text will not write
        checkLengths(firstWord, words, numWords, insertion, deletion);
        Sleep(timeSleep);
        checkSubstitution(firstWord, words, numWords, substitution, correct, tooManyErrors);
        transpositionCheck(firstWord, words, numWords, transposition);





        outFile<<endl; //puts 2 spaces between each set of text
        outFile<<endl;


    }

    outFile<< "The amount of insertion errors: " << insertion<<endl;  //writes the amount of total errors at the end
    outFile<< "The amount of deletion errors: " << deletion<<endl;
    outFile<< "The amount of substitution errors: " << substitution<<endl;
    outFile<< "The amount of transposition errors: " << transposition<<endl;
    outFile<< "The amount of really bad errors: " << tooManyErrors<<endl;
    outFile<< "The amount of correct words: " << correct<<endl;



    inFile.close(); // Close the input file
    outFile.close(); //close the output file



return 0;
}

