#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <vector>
#include <map>

#include <toolFunction.h>

using namespace std;

struct Transition{
    string oldStates;
    string oldSymbols;
    string newSymbols;
    string directions;
    string newStates;
};

bool verbose = false;
vector<string> Q;
vector<string> S;
vector<string> G;
string q0;
string B;
vector<string> F;
int N;
vector<Transition> delta;

void parse(char *turingFile);

void simulate(char *input);

int main(int argc, char *argv[])
{
    //-h在命令行参数里优先级比较高，只要命令中有-h，自动进入手册页面
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
        {
            cout << "usage: turing [-v|--verbose] [-h|--help] <tm> <input>" << endl;
            exit(0);
        }
    }
    char *turingFile = NULL;
    char *input = NULL;
    for (int i = 1; i < argc; i++)
        if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--verbose") == 0)
            verbose = true;
    // 程序传入参数有误
    if ((verbose && argc != 4) || (!verbose && argc != 3))
    {
        cerr << "syntax error" << endl
            << "usage: turing [-v|--verbose] [-h|--help] <tm> <input>" << endl;
        exit(1);
    }

    input = argv[argc - 1];
    if ((string(argv[argc - 2])).length() < 3 || ((string(argv[argc - 2])).substr(string(argv[argc - 2]).length() - 3) != ".tm"))
    {
        cerr << "syntax error" << endl
            << "usage: turing [-v|--verbose] [-h|--help] <tm> <input>" << endl;
        exit(1);
    }
    else
        turingFile = argv[argc - 2];

    parse(turingFile);
    simulate(input);
}

void parse(char *turingFile){
    ifstream file(turingFile);
    if(file.is_open()){
        int i = 0;
        string line;
        while(getline(file, line)){
            line = formatLine(line);
            if(line == "")
                continue;
            else if(startwith(line, ";"))
                continue;
            else if(i == 0){
                i++;

                //检查状态集Q的语法
                if(!startwith(line, "#Q = {") || line.at(line.length() - 1) != '}'){
                    cerr << "syntax error" << endl;
                    if (verbose)
                        cerr << "Q: Turing machine program syntax" << endl;
                    exit(1);
                }

                if(checkBraceNum(line)){
                    string Qstr = line.substr(line.find("{"));
                    Q = splitString(Qstr, "{,}");
                    if(!checkStates(Q)){
                        cerr << "syntax error" << endl;
                        if (verbose)
                            cerr << "Q: The state set is illegal." << endl;
                        exit(1);
                    }
                }
                else{
                    cerr << "syntax error" << endl;
                    if (verbose)
                        cerr << "Q: Turing machine program syntax" << endl;
                    exit(1);
                }
            }
            else if(i == 1){
                i++;

                //检查输入符号集合S的语法
                if(!startwith(line, "#S = {") || line.at(line.length() - 1) != '}'){
                    cerr << "syntax error" << endl;
                    if (verbose)
                        cerr << "S: Turing machine program syntax" << endl;
                    exit(1);
                }

                if(checkBraceNum(line)){
                    string Sstr = line.substr(line.find("{"));
                    S = splitString(Sstr, "{,}");
                    if(!checkSymbols(S, " ,;{}*_")){
                        cerr << "syntax error" << endl;
                        if (verbose)
                            cerr << "S: The label character set is illegal." << endl;
                        exit(1);
                    }
                }
                else{
                    cerr << "syntax error" << endl;
                    if (verbose)
                        cerr << "S: Turing machine program syntax" << endl;
                    exit(1);
                }
            }
            else if(i == 2){
                i++;

                //检查纸带符号集G的语法
                if(!startwith(line, "#G = {") || line.at(line.length() - 1) != '}'){
                    cerr << "syntax error" << endl;
                    if (verbose)
                        cerr << "G: Turing machine program syntax" << endl;
                    exit(1);
                }

                if(checkBraceNum(line)){
                    string Gstr = line.substr(line.find("{"));
                    G = splitString(Gstr, "{,}");
                    if(!checkSymbols(G, " ,;{}*")){
                        cerr << "syntax error" << endl;
                        if (verbose)
                            cerr << "G: The label character set is illegal." << endl;
                        exit(1);
                    }
                }
                else{
                    cerr << "syntax error" << endl;
                    if (verbose)
                        cerr << "G: Turing machine program syntax" << endl;
                    exit(1);
                }
            }
            else if(i == 3){
                i++;

                //检查初始状态q0表达式的合法性
                if(!startwith(line, "#q0 = ") || line.at(6) == ' '){
                    cerr << "syntax error" << endl;
                    if (verbose)
                        cerr << "q0: Turing machine program syntax" << endl;
                    exit(1);                    
                }
                q0 = line.substr(6);

                //检查初始状态q0在不在状态集Q中
                if(!checkExistence(q0, Q)){
                    cerr << "syntax error" << endl;
                    if (verbose)
                        cerr << "q0: Turing machine program syntax" << endl;
                    exit(1);  
                }
            }
            else if(i == 4){
                i++;

                //检查空格符号表达式的合法性
                if(!startwith(line, "#B = ") || line.at(5) == ' '){
                    cerr << "syntax error" << endl;
                    if (verbose)
                        cerr << "B: Turing machine program syntax" << endl;
                    exit(1);
                }
                B = line.substr(5);

                //检查B是否为'_'
                if(B != "_"){
                    cerr << "syntax error" << endl;
                    if (verbose)
                        cerr << "B: Turing machine program syntax" << endl;
                    exit(1); 
                }

            }
            else if(i == 5){
                i++;

                //检查终结状态集表达式的合法性
                if(!startwith(line, "#F = {") || line.at(line.length() - 1) != '}'){
                    cerr << "syntax error" << endl;
                    if (verbose)
                        cerr << "F: Turing machine program syntax" << endl;
                    exit(1);
                }

                if(checkBraceNum(line)){
                    string Fstr = line.substr(line.find("{"));
                    F = splitString(Fstr, "{,}");
                    bool flag = true;

                    //检查终止状态集是否在状态集Q中
                    for(auto f : F){
                        if(!checkExistence(f, Q)){
                            cerr << "syntax error" << endl;
                            if (verbose)
                                cerr << "Final state " << f << " not exists in Q" << endl;
                            exit(1);
                        }
                    }
                }
                else{
                    cerr << "syntax error" << endl;
                    if (verbose)
                        cerr << "F: Turing machine program syntax" << endl;
                    exit(1);
                }
            }
            else if(i == 6){
                i++;

                if(!startwith(line, "#N = ") || line.at(5) == ' '){
                    cerr << "syntax error" << endl;
                    if (verbose)
                        cerr << "N: Turing machine program syntax" << endl;
                    exit(1);
                }
                N = stoi(line.substr(5));
            }
            else if(i == 7){
                vector<string> subStr = splitString(line, " ");
                //检查状态转移函数的长度
                if(subStr.size() != 5){
                    cerr << "syntax error" << endl;
                    if (verbose)
                        cerr << "deltaFunction: Turing machine program syntax" << endl;
                    exit(1);
                }
                //检查新老状态集是否在状态集Q中
                if(!checkExistence(subStr.at(0), Q) || !checkExistence(subStr.at(4), Q)){
                    cerr << "syntax error" << endl;
                    if (verbose)
                        cerr << "deltaFunction: Turing machine program syntax" << endl;
                    exit(1);
                }
                //检查字符集长度是否为N
                if(subStr.at(1).length() != N || subStr.at(2).length() != N || subStr.at(3).length() != N){
                    cerr << "syntax error" << endl;
                    if (verbose)
                        cerr << "deltaFunction: Turing machine program syntax" << endl;
                    exit(1);
                }
                //检查新老字符集是否在G中
                for(int i = 0; i < N; i++){
                    if(subStr.at(1).substr(i, 1) != "*"){
                        if(!checkExistence(subStr.at(1).substr(i, 1), G)){
                            cerr << "syntax error" << endl;
                            if (verbose)
                                cerr << "deltaFunction: Turing machine program syntax" << endl;
                            exit(1); 
                        }
                    }
                    if(subStr.at(2).substr(i, 1) != "*"){
                        if(!checkExistence(subStr.at(2).substr(i, 1), G)){
                            cerr << "syntax error" << endl;
                            if (verbose)
                                cerr << "deltaFunction: Turing machine program syntax" << endl;
                            exit(1); 
                        }
                    }
                }
                //检查方向字符是否为l r *其中一个
                for(int i = 0; i < N; i++){
                    string oneDirection = subStr.at(3).substr(i, 1);
                    if(oneDirection != "l" && oneDirection != "r" && oneDirection != "*"){
                            cerr << "syntax error" << endl;
                            if (verbose)
                                cerr << "deltaFunction: Turing machine program syntax" << endl;
                            exit(1); 
                        }
                }
                Transition transition;
                transition.oldStates = subStr.at(0);
                transition.oldSymbols = subStr.at(1);
                transition.newSymbols = subStr.at(2);
                transition.directions = subStr.at(3);
                transition.newStates = subStr.at(4);
                delta.push_back(transition);
            }
        }
        file.close();
    }
    else{
        cerr << turingFile << " no exists" << endl;
        exit(1);
    }
}

void simulate(char *input){
    string str = string(input);
    if(checkInput(S, str)){
        if(verbose){
            cout << "Input: " << str << endl;
            cout << RUN << endl;
        }

        string state = q0;

        int step = 0;
        int colonPos = to_string(N - 1).length() + 6;
        string acc = "No";

        vector<int> head;
        vector<int> left;
        vector<int> right;
        for(int i = 0; i < N; i++){
            head.push_back(0);
            left.push_back(0);
            right.push_back(0);
        }

        vector<map<int, char>> tapes(N);
        if(str.length() == 0){
            tapes.at(0)[0] = '_';
            right[0] = 1;
        }
        else{
            for(int i = 0; i < str.length(); i++)
                tapes.at(0)[i] = str.at(i);
            right[0] = str.length();
        }
        for(int i = 1; i < N; i++){
            tapes.at(i)[0] = '_';
            right[i] = 1;
        }
        while(true){
            if(verbose){
                vector<int> indexLeft;
                //Step
                cout << "Step";
                for(int i = 0; i < colonPos - 4; i++)
                    cout << " ";
                cout << ": " << step << endl;
                //State
                cout << "State";
                for(int i = 0; i < colonPos - 5; i++)
                    cout << " ";
                cout << ": " << state << endl;
                //Acc
                cout << "Acc";
                for(int i = 0; i < colonPos - 3; i++)
                    cout << " ";
                cout << ": " << acc << endl;
                for(int i = 0; i < N; i++){
                    //Index
                    string index = "Index" + to_string(i);
                    cout << index;
                    for(int j = 0; j < colonPos - index.length(); j++)
                        cout << " ";
                    cout << ": ";
                    index = "";
                    for(int j = left.at(i); j < right.at(i) ; j++){
                        index += to_string(abs(j));
                        if(j != right.at(i) - 1)
                            index += " ";
                    }
                    indexLeft = dealWithIndex(index);
                    cout << index << endl;
                    //Tape
                    string tape = "Tape" + to_string(i);
                    cout << tape;
                    for(int j = 0; j < colonPos - tape.length(); j++)
                        cout << " ";
                    cout << ": ";
                    int nowPos = 0;
                    for(int j = left.at(i); j < right.at(i); nowPos++){
                        if(nowPos == indexLeft.at(j - left.at(i))){
                            cout << tapes.at(i).at(j);
                            j++;
                        }
                        else
                            cout << " ";
                    }
                    cout << endl;
                    //Head
                    string h = "Head" + to_string(i);
                    cout << h;
                    for(int j = 0; j < colonPos - h.length(); j++)
                        cout << " ";
                    cout << ": ";
                    nowPos = 0;
                    for(int j = left.at(i); j < right.at(i); nowPos++){
                        if(nowPos == indexLeft.at(j - left.at(i))){
                            if(j != head.at(i))
                                cout << " ";
                            else
                                cout << "^";
                            j++;
                        }
                        else
                            cout << " ";
                    }
                    cout << endl;
                }
                cout << LINE << endl;
            }

            string symbol = "";
            for(int i = 0; i < N; i++)
                symbol += tapes.at(i).at(head.at(i));
            int which = 0;
            for(; which < delta.size(); which++)
                if(delta.at(which).oldStates == state && compareSymbol(symbol, delta.at(which).oldSymbols))
                    break;
            //停机了
            if(which == delta.size())
                break;
            state = delta.at(which).newStates;
            for(auto stopState : F)
                if(state == stopState){
                    acc = "Yes";
                    break;
                }
            for(int i = 0; i < N; i++){
                if(delta.at(which).newSymbols.at(i) != '*')
                    tapes.at(i)[head.at(i)] = delta.at(which).newSymbols.at(i);
                if(delta.at(which).directions.at(i) != '*'){
                    if(delta.at(which).directions.at(i) == 'l'){
                        head[i]--;
                        if(head.at(i) < left.at(i)){
                            tapes.at(i)[head.at(i)] = '_';
                            left[i]--;
                        }
                        for(int j = right.at(i) - 1; j > head.at(i); j--){
                            if(tapes.at(i).at(j) == '_')
                                right[i]--;
                            else
                                break;
                        }
                    }
                    else if(delta.at(which).directions.at(i) == 'r'){
                        head[i]++;
                        if(head.at(i) == right.at(i)){
                            tapes.at(i)[head.at(i)] = '_';
                            right[i]++;
                        }
                        for(int j = left.at(i); j < head.at(i); j++){
                            if(tapes.at(i).at(j) == '_')
                                left[i]++;
                            else
                                break;
                        }
                    }
                }
            }
            step++;
        }
        string result = "";
        for(int i = left.at(0); i < right.at(0); i++)
            result += tapes.at(0).at(i);
        if(verbose){
            if(acc == "Yes")
                cout << "ACCEPTED" << endl;
            else if(acc == "No")
                cout << "UNACCEPTED" << endl;
            cout << "Result: " << result << endl;
            cout << END << endl;
        }
        else{
            if(acc == "Yes")
                cout << "(ACCEPTED) " << result << endl;
            else
                cout << "(UNACCEPTED) " << result << endl;
        }
    }
    else{
        if (verbose){
            int where;
            for(where = 0; where < str.length(); where++)
                if(!checkExistence(str.substr(where, 1), S))
                    break;
            cerr << "Input: " << str << endl;
            cerr << ERR << endl;
            cerr << "error: Symbol \"" << str.at(where) <<"\" in input is not defined in the set of input symbols" << endl;
            cerr << "Input: " << str << endl;
            for(int i = 0; i < 7 + where; i++)
                cerr << " ";
            cerr << "^" << endl;
            cerr << END << endl;
        }
        else
            cerr << "illegal input string" << endl;
        exit(1);
    }
}