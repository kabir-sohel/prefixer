#pragma once

#include "CommonHeaders.h"
#include "Mixed.h"


//node data can be a single char or an integer.
//a single char holds operatoror single char alphabet.
//a node can have data as either singleChar or int, not both, Hence to save memory union is used.

typedef union nodeData
{
    char singleChar;
    int number;
};

//holds the type of a certain node.
typedef enum nodeType
{
    anOperator,     //+ , - , * , / , ( , )
    aNumber,        //an integer value
    aSingleChar     //single char variable - English Alphabet.
};






//Encapsulated data of Each node in Expression Tree

class Tree
{
    Tree *left, *right; //holds pointers to its left child and right child
    nodeType type;
    nodeData data;

    public:
    Tree(char);     //constructor for operator and single char variable node
    Tree(int);      //constructor for int node
    ~Tree();        //frees the memory it allocates as left and right child
    string processData();           //process the rootNode before visiting left , right child(prefix)
    string preOrderTreeTraversal(); //preOrder Tree walk for getting prefix Expression
    Tree* reduceExpression();
    friend bool updateExpressionTree(stack<Tree *>&, stack<char>&); // A function to create node
                //and set its left right.works with buildExpressionTreeFromInfix(string&) function
                //and populates the Expression Tree.

	friend Tree* buildExpressionTreeFromInfix(string&);
};