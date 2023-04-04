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
void appendSet(std::set<std::string>& src, std::set<std::string> add);
void fillBlank(std::string temp, std::set<std::string>& dest, const std::set<std::string>& dict);
std::set<int> countDash(std::string str);

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
    std::set<int> dashes = countDash(in);
    std::set<int>::iterator it;
    for(it = dashes.begin();it != dashes.end();++it){
        string str = in; 
        str[*it] = floating[0];
        appendSet(result,wordle(str, floating.substr(1), dict));
    }
    return result;

}

// Define any helper functions here
void appendSet(std::set<std::string>& src, std::set<std::string> add){
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
std::set<int> countDash(std::string str){
    std::set<int> count;
    for(int i = 0;i<str.size();i++){
        if(str[i] == '-'){count.insert(i);}
    }
    return count;
}