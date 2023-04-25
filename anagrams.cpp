#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include<bits/stdc++.h>
#include<ctime>

using namespace std;

vector<string> loadWordlist(string filename);

vector<string> anagram(string word, vector<string> wordlist);

bool isAnagram(string input, string checkString);

int main()
{
    srand(time(NULL));
    vector<string> words;
    vector<string> anagrams;
    string inputWord;


    words=loadWordlist("wordlist.txt");

    string anagramWord = words[rand()%words.size()/4];
    cout << "Find single-word anagrams for the following word: " << anagramWord <<endl;
    anagrams = anagram(anagramWord, words);
    int remainingAns = anagrams.size()-1;
    cout << "Possible anagrams: " << remainingAns << endl;



    while(remainingAns!= 0){
        cin >> inputWord;
    
        if(find(anagrams.begin(), anagrams.end(), inputWord)!= anagrams.end() || isAnagram(inputWord,anagramWord)){
            remainingAns--;
            cout<< "Correct! ";

        }


        else{
            cout<< "Try again! ";
        }

        cout << remainingAns << " answers remaining" <<endl; 

        
    }

    return 0;
}

/*This function reads in the word list and stores
It in a vector*/
vector<string> loadWordlist(string filename)
{
    vector<string> words;
    ifstream inFile;
    string word;
    inFile.open(filename);
    if(inFile.is_open())
    {
        while(getline(inFile,word))
        {
            if(word.length() > 0)
            {
                words.push_back(word);
            }
        }
        inFile.close();
    }
    return words;
}

/*This function takes in a word and a wordlist that will be searched
It will return a vector on anagrams the word has in the dictionary*/

vector<string> anagram(string word, vector<string> wordlist)
{
    //create an unordered map to hold sorted string keys and the words themselves
    unordered_map<string, vector<string>> anagramMap;
    //create the sorted key for our word parameter
    string sortedWord= word;

    sort(sortedWord.begin(),sortedWord.end());

    //iterate through the word list
    for (int i=0; i<wordlist.size(); i++){
        //create a key for the current word in the list
        string sortedKey = wordlist[i];
        sort(sortedKey.begin(),sortedKey.end());
        

        //if the key is not in the list, add it with a vector containing the word
        if(anagramMap.find(sortedKey)==anagramMap.end()){
            //create the vector to be added as the value in the key value pair
            vector<string> tempVect;
            tempVect.push_back(wordlist[i]);

            //add the key and the key value to the unordered map
            anagramMap.insert({sortedKey,tempVect});
        }

        //if the key is in the list, add the current word to the vector of strings
        else{
            anagramMap.at(sortedKey).push_back(wordlist[i]);

        }



    }

    //return the vector at the sorted word key in the map
    return anagramMap.at(sortedWord);
}

bool isAnagram(string input, string checkString){
    string sortedInput =input;
    sort(sortedInput.begin(), sortedInput.end());

    string sortedCheck = checkString;
    sort(sortedCheck.begin(), sortedCheck.end());

    if(sortedInput.find(sortedCheck)!=string::npos){
        return true;

    }
    return false;
}