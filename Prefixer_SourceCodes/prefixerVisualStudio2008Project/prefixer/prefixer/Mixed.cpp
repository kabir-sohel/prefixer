#pragma once
#include "Mixed.h"
#include "Log.h"



//Use the Log variable (global) to store the program log.
extern Log *log;


//Here Comes the Helper Functions. These Function is helpful either to tree or others.
//These function doesn't need any data of Tree. So they are kept outside of Tree.


//returns true when a string is a an operator. i.e + , - , *, / , ( and ). false otherwise
bool isOperator(string &str)
{
    if(str.size() != 1)return false;
    return isOperator(str[0]);
}
//returns true when a char is a an operator. i.e + , - , *, / , ( and ). false otherwise
bool isOperator(char c)
{
    if(c == '+' || c == '-' || c == '*' || c == '/' || c == ')' || c == '(')
    {
        return true;
    }
    return false;
}
//returns true when a string is an integer number
bool isNumber(string &str)
{
    if(str.empty())return false;
    for(int i = 0; i < str.size(); ++i)
    {
        if(str[i] < '0' || str[i] > '9')return false;
    }
    return true;
}
//returns true when a string is a singleChar variable
bool isSingleAlphabet(string &str)
{
    if(str.size() != 1)return false;
    char c = str[0];
    if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
    {
        return true;
    }
    return false;
}

//returns the priority of each operator according to operator precedence.
int priority(char op)
{
    if(op == '+' || op == '-')return 1;
    if(op == '*' || op == '/' || op == '%')return 2;
    return 0;
}
//convert an integer to a string.
string intToString(int num)
{
    char tem[25];
    sprintf(tem,"%d",num);
    string retString = tem;
    return retString;
}






//Make a node with top element of Operators stack and assign two top elements of Nodes stack as children.
//returns false if there is a problem in infixString string the program takes.
bool updateExpressionTree(stack<Tree *> &Nodes, stack<char> &Operators)
{
    if(Nodes.empty())return false;
    Tree *nodeRight = Nodes.top();
    Nodes.pop();
    if(Nodes.empty())return false;
    Tree *nodeLeft = Nodes.top();
    Nodes.pop();
    if(Operators.empty())return false;
    Tree *node = new Tree(Operators.top());
    Operators.pop();
    node->left = nodeLeft;
    node->right = nodeRight;
    Nodes.push(node);
    return true;
}

//takes a string infixString and makes it a Expression Tree. returns the root of the tree.
//Scan the infix string one by one
//If an operator comes insert into operator stack ,if a variable or value comes ,insert into Nodes stack
//Pops the higher or equal order operators and make them node with two Top Nodes and push into Nodes
//Hence the last node is the root of the Expression Tree.
Tree *buildExpressionTreeFromInfix(string &infixString)
{
	infixString += " )";
    istringstream ist(infixString);
    string str;
    stack<Tree *>Nodes;
    stack<char>Operators;
	Operators.push('(');
    while(ist >> str)
    {
        if(isOperator(str))
        {
            char op = str[0];
            if(op == '(')
            {
                Operators.push(op);
            }
            else if(op == ')')
            {
                //pop each operator and make them node until '(' occurs.
                while(!Operators.empty() && Operators.top() != '(')
                {
                    bool ok = updateExpressionTree(Nodes,Operators);
                    if(false == ok)
                    {
                        log->print("Error in Input format. Operator and operand Mismatched.Please check Again\n");
                        return NULL;
                    }
                }
                //pop the '(', coz its done.
                if(!Operators.empty())
                {
                    Operators.pop();
                }
            }
            else
            {
                //pops all higher or equal order operator than op and insert them to the express tree.
                while(!Operators.empty() && Operators.top() != '(' && priority(op) <= priority(Operators.top()))
                {
                    bool ok = updateExpressionTree(Nodes,Operators);
                    if(false == ok)
                    {
                        log->print("Error in Input format. Operator and operand Mismatched.Please check Again\n");
                        return NULL;
                    }
                }
                //push it for later process.
                Operators.push(op);
            }
        }
        else if(isNumber(str))
        {
            int number = atoi(str.c_str());
            Nodes.push(new Tree(number));
        }
        else if(isSingleAlphabet(str))
        {
            char name = str[0];
            Nodes.push(new Tree(name));
        }
        else
        {
            //There is a problem in the Input dataset.
            log->print("Error in Input formate. Please check Again\n");
            return NULL;
        }
    }
    //Expression Tree can't be built. There is a problem in the expression.
    if(Nodes.empty())return NULL;

    //Top elements of Nodes is the root of Expression Tree.
    return Nodes.top();
}

