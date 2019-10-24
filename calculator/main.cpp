#include <iostream>
#include <map>
#include <sstream>
#include <fstream>
#include <string>
#include <stack>

using Variables = std::map<char, int>;

bool isDigit(char c)
{
    return c >= '0' && c <= '9';
}

bool isAlpha(char c)
{
    return c >= 'a' && c <= 'z';
}

void initVariables(Variables &variables, const std::string &expression)
{
    for (auto c : expression) {
        if (isalpha(c)) {
            variables.emplace(c, 0);
        }
    }
}

void fillVariables(Variables &variables, const std::string values)
{
    std::istringstream stream(values);
    int n;
    auto it = variables.begin();
    while (stream >> n) {
        it->second = n;
        ++it;
    }
}

int processDigit(std::string &expression, int &index, char c)
{
    int digit = int(c) - 48;
    if(++index < expression.length()) {
        c = expression.at(index);
        while (isDigit(c)) {
            digit = digit * 10 + (int(c) - 48);
            if(++index >= expression.length()) {
                break;
            }
            c = expression.at(index);
        }
    }
    --index;
    return digit;
}

int main()
{
    std::ifstream infile("input.txt");
    std::string buffer;

    std::getline(infile, buffer);
    int variableCount = std::stoi(buffer);

    std::string expression;
    std::getline(infile, expression);

    Variables variables;
    initVariables(variables, expression);

    std::getline(infile, buffer);
    int testCount = std::stoi(buffer);;

    std::stack<int> stack;
    bool isNegative = false;
    int op1, op2, op3;
    auto pop2op = [&]() {
        op2 = stack.top();
        stack.pop();
        op1 = stack.top();
        stack.pop();
    };
    auto pop3op = [&]() {
        op3 = stack.top();
        stack.pop();
        pop2op();
    };

    std::string result;
    for (auto i = 0; i < testCount; ++i) {
        std::getline(infile, buffer);
        fillVariables(variables, buffer);

        for (auto position = 0; position < expression.length(); ++position) {
            char c = expression.at(position);
            switch (c) {
                case ' ': break;
                case '+':
                    pop2op();
                    stack.emplace(op1 + op2);
                    break;
                case '-': {
                    bool isDigitNext = (position + 1 < expression.length()) and (expression.at(position + 1) != ' ');
                    if (isDigitNext) {
                        isNegative = true;
                    } else {
                        pop2op();
                        stack.emplace(op1 - op2);
                    }
                    break;
                }
                case '*':
                    pop2op();
                    stack.emplace(op1 * op2);
                    break;
                case '/':
                    pop2op();
                    stack.emplace(op1 / op2);
                    break;
                case '<':
                    pop2op();
                    stack.emplace(op1 < op2);
                    break;
                case '=':
                    pop2op();
                    stack.emplace(op1 == op2);
                    break;
                case '?':
                    pop3op();
                    stack.emplace(op1 ? op2 : op3);
                    break;
                default:
                    if (isDigit(c)) {
                        int digit = processDigit(expression, position, c);
                        if (isNegative) {
                            digit *= -1;
                            isNegative = false;
                        }
                        stack.emplace(digit);
                    } else if (isAlpha(c)) {
                        stack.emplace(variables.at(c));
                    }
            }
        }
        result += std::to_string(stack.top()) + '\n';
        std::stack<int>().swap(stack);
    }
    std::cout << result;
    infile.close();
}

