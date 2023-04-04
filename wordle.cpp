#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void appendSet(std::set<std::string> src, std::set<std::string> add);
void fillBlank(std::string temp, std::set<std::string>& dest, const std::set<std::string>& dict);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict){
    std::set<std::string> result;
    if(floating.size()==0){
        fillBlank(in, result, dict);
        return result;
    }
    for(int i = 0;i<floating.size();i++){
        string str = in; string newf = floating;
        str[in.find("-")] = floating[i];
        newf.erase(i);
        appendSet(result,wordle(str, newf, dict));
    }
    return result;

}

// Define any helper functions here
void appendSet(std::set<std::string> src, std::set<std::string> add){
    std::set<std::string>::iterator it;
    for(it = add.begin();it != add.end();++it){
        src.insert(*it);
    }
}
void fillBlank(std::string temp, std::set<std::string>& dest, const std::set<std::string>& dict){
    if(temp.find('-') == std::string::npos){
        if(dict.find(temp) != dict.end()){
            dest.insert(temp);
        }
    }else{
        for(int i = 0;i<26;i++){
            string in = temp;
            in[temp.find('-')] = 'a' + i;
            fillBlank(in, dest, dict);
        }
    }
}