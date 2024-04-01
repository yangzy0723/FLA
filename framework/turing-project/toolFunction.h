#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

#define ERR "==================== ERR ===================="
#define RUN "==================== RUN ===================="
#define END "==================== END ===================="
#define LINE "---------------------------------------------"

//检测mainStr是否是以subtr开头的串
bool startwith(string mainStr, string subStr);
//格式化行，删除行内注释
string formatLine(string line);
//将字符串按照指定的分隔符进行分割，delimiter中的每个字符都是分隔符
vector<string> splitString(string mainStr, string delimiter);
//检查状态集中的元素符号是否合法
bool checkStates(vector<string> states);
//检查符号是否合法，包括输入符号和纸带符号
bool checkSymbols(vector<string> states, string illegalChars);
//检查外部输入是否合法
bool checkInput(vector<string> S, string input);
//比较Symbol符号是否相同，需要考虑*
bool compareSymbol(string nowSymbol, string transitionSymbol);
//检查大括号数目是否正确
bool checkBraceNum(string line);
//检查某个串是否在某个容器中
bool checkExistence(string s, vector<string> v);
//处理Index数字串，使符号与Index数字串中数字靠左对齐
vector<int> dealWithIndex(string s);