#ifndef RECCHECK
// For debugging
//#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordle_recursive(
    std::string whole_input,
    std::string floating,
	unsigned int curr_index,
    const std::set<std::string>& dict,
    std::set<std::string>& words_returned
); 

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string&in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    
    //make copy so u can use in helper
    std::string whole_input = in; 
    std::string floating_copy = floating; 

    //set of all possible words that will be returned 
    std::set<std::string> words_returned;

    //helper to recurse 
    wordle_recursive(whole_input, floating_copy, 0, dict, words_returned);
    return words_returned; 

}

// Define any helper functions here
void wordle_recursive(
    std::string whole_input,
    std::string floating,
	unsigned int curr_index,
    const std::set<std::string>& dict,
    std::set<std::string>& words_returned)
{
    char curr_letter; 
    unsigned int to_be_filled = 0;
    //unsigned int correct_letters = 0; 
    
    // count how many fixed and need to be filled letters 
    for(unsigned int i = 0; i < whole_input.size(); ++i){
        curr_letter = whole_input[i];
        if(curr_letter == '-'){
            to_be_filled++;
        }
        //correct_letters++;
    }

    //BC to END RECURSION 
    if(curr_index == whole_input.size()){ // input is full
        // if the word appears in dictionary 
        if(dict.find(whole_input) != dict.end()){ 
            words_returned.insert(whole_input); // add possible words 
        }
        return; 
    }

// RECURSIVE CASES 
    // if hit a FIXED letter  
    if(whole_input[curr_index] != '-'){
        // go to next index
        wordle_recursive(whole_input, floating, curr_index + 1, dict, words_returned); // recurse again 
        return;
    }
    // else hit a '-' ,, needs to be FILLED 
    else{
    // if number of floating letters = to spaces to be filled
        if(to_be_filled == floating.size()){    
            // make the word combos 
            for(unsigned int x = 0; x < floating.size(); ++x){
                // set curr space to x letter of floating
                whole_input[curr_index] = floating[x]; 

                // remove that space from floating (a copy)
                std::string updated_floating = floating.substr(0,x) + floating.substr(x+1); 
                //recurse w new floating
                wordle_recursive(whole_input, updated_floating, curr_index + 1, dict, words_returned);
            }
        }
    
        else{
         // if MORE spaces to be filled than floating size 
        //if(to_be_filled > floating.size())

            for(int x = 0; x < 26; ++x){
                // index becomes a letter a-z
                whole_input[curr_index] = (char)(x + 97); // convert int to char
                
                // if curr letter (of input index) in a letter floating 
                if(floating.find(whole_input[curr_index]) <= floating.size()){ 
                
                //ERASE that letter out of the floating (a copy)    
                    std::string updated_floating = floating;
				    updated_floating.erase(floating.find(whole_input[curr_index]), 1);
                    //recurse w updated floating 
                    wordle_recursive(whole_input, updated_floating, curr_index + 1, dict, words_returned);
                }
                else{ // if the letter is not in floating, then keep recursing 
                    wordle_recursive(whole_input, floating, curr_index + 1, dict, words_returned);
                }   
            }
        }
    }


}