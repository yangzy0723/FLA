#include "toolFunction.h"

bool startwith(string mainStr, string subStr){
    if (mainStr.substr(0, subStr.length()) == subStr)
        return true;
    return false;
}

string formatLine(string line){
    int commentPos = line.find(';');
    if (commentPos != string::npos){
        while(commentPos > 0 && line.at(commentPos - 1) == ' ')
            commentPos--;
        return line.substr(0, commentPos);
    }
    return line;
}

vector<string> splitString(string mainStr, string delimiter){
    vector<string> Q;
    Q.empty();
    int startIndex = 0, endIndex = 0;
    for(int i = 0; i <= mainStr.length(); i++){
        if(delimiter.find(mainStr[i]) != string::npos || i == mainStr.length()){
            endIndex = i;
            if(startIndex != endIndex){
                string temp;
                temp.append(mainStr, startIndex, endIndex - startIndex);
                Q.push_back(temp);
            }
            startIndex = endIndex + 1;
        }
    }
    return Q;
}

bool checkStates(vector<string> states){
    for(auto s : states)
        for(auto c : s)
            if(!isalnum(c) && c != '_')
                return false;
    return true;
}

bool checkSymbols(vector<string> symbols, string illegalChars){
    for(auto s : symbols){
        if(s.length() != 1)
            return false;
        for(auto c : s)
            if(illegalChars.find(c) != string::npos)
                return false;
    }
    return true;
}

bool checkInput(vector<string> S, string input){
    bool flag = true;
    for(int i = 0; i < input.length(); i++){
        for(auto s : S)
            if(input.substr(i, 1) == s)
                flag = false;
        if(flag)
            return false;
        flag = true;
    }
    return true;
}

bool compareSymbol(string nowSymbol, string transitionSymbol){
    for(int i = 0; i < nowSymbol.length(); i++){
        if(transitionSymbol[i] == '*' && nowSymbol[i] == '_')
            return false;
        if(transitionSymbol[i] != '*' && nowSymbol[i] != transitionSymbol[i])
            return false;
    }
    return true;
}

bool checkBraceNum(string line){
    int count = 0;
    for(auto c : line)
        if(c == '{' || c == '}')
            count++;
    return count == 2;
}

bool checkExistence(string s, vector<string> v){
    for(auto vvs : v)
        if(vvs == s)
            return true;
    return false;
}

vector<int> dealWithIndex(string s){
    vector<int> res;
    res.empty();
    res.push_back(0);
    for(int i = 1; i < s.length(); i++)
        if(s.at(i - 1) == ' ' && s.at(i) != ' ')
            res.push_back(i);
    return res;
}