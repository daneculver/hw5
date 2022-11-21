// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordSolve(const std::set<std::string>& dict, std::string floating, size_t index, std::set<std::string>& correctSet, std::string wordTemp);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::set<std::string> wordAnswers;
    wordSolve(dict, floating, 0, wordAnswers, in);
    return wordAnswers;
}

// Define any helper functions here
void wordSolve(const std::set<std::string>& dict , std::string floating, size_t index, std::set<std::string>& correctSet, std::string wordTemp){
    int dashCount = 0;
    // base case 
    if(index == wordTemp.size() && floating.empty()){ 
        if(dict.find(wordTemp) != dict.end()){
            correctSet.insert(wordTemp);
        }
        return; 
    }
    // if this point is equal to '-', you must recurse to the next point
    if(wordTemp[index] != '-'){
        wordSolve(dict, floating, index+1, correctSet, wordTemp);
        return;
    }
    for(size_t k = 0; k < wordTemp.size(); k++){
        if(wordTemp[k] == '-'){
            dashCount++;
        }
    }
    string floatTemp = floating; 
    if((int)floatTemp.size() == dashCount){
        for(size_t k = 0; k < floatTemp.size(); k++){
            wordTemp[index] = floatTemp[k];
            string copy = floatTemp;
            copy.erase(k, 1);
            wordSolve(dict, copy, index + 1, correctSet, wordTemp);
        }
    }
    else if((int)floatTemp.size() < dashCount){
        for(char check = 'a'; check<= 'z'; check++){
            if(floatTemp.find(check)!=string::npos){
                wordTemp[index] = check;
                string copy = floatTemp;
                copy.erase(floatTemp.find(check), 1);
                wordSolve(dict, copy, index + 1, correctSet, wordTemp);
            }
            else{
                wordTemp[index] = check;
                wordSolve(dict, floatTemp, index+1, correctSet, wordTemp);
            }
        }
    }
}