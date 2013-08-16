#pragma once
#include "Tree.h"





//first constructor
Tree::Tree(char name)
{
    left = right = NULL;
    data.singleChar = name;
    if(isOperator(name))
    {
        type = anOperator;
    }
    else
    {
        type = aSingleChar;
    }
}
//second constructor
Tree::Tree(int num)
{
    left = right = NULL;
    type = aNumber;
    data.number = num;
}

//destructor
Tree::~Tree()
{
    if(left != NULL)
    {
        delete left;
    }
    if(right != NULL)
    {
        delete right;
    }
}
string Tree::processData()
{
    string prefixString = "";
    if(type == anOperator)
    {
        prefixString += data.singleChar;
    }
    else
    {
        if(type == aNumber)
        {
            prefixString += " ";
            prefixString += intToString(data.number);
        }
        else
        {
            prefixString += " ";
            prefixString += data.singleChar;
        }
    }
    return prefixString;
}
string Tree::preOrderTreeTraversal()
{
    string prefixString = "";
	if(type == anOperator)prefixString += "(";
    prefixString += processData();                                  //process Root at First
    if(left != NULL)prefixString += left->preOrderTreeTraversal();  //process Left Child
    if(right != NULL)prefixString += right->preOrderTreeTraversal();//Process Right Child
	if(type == anOperator)prefixString += ")";
	return prefixString;
}


//when -r flag is triggered, this function will be called.
//It will reduce the expression as much it can.
//Whenever an operator have two of its children as integer value , only then it will be reduced.
//This function change the tree structure and returns the root of the reduced Expression Tree.
Tree* Tree::reduceExpression()
{

    if(left == NULL || right == NULL)return this;

    Tree *temLeft = left->reduceExpression();   //reduce the left child first.
    Tree *temRight = right->reduceExpression(); //then reduce the right child
    left = temLeft;
    right = temRight;

    if(type != anOperator || left->type != aNumber || right ->type != aNumber)return this;
    int nodeVal = 0;
    // Now it knows this node canbe reduced. nodeVal will contain the reduced value.

    if(data.singleChar == '+')nodeVal = temLeft->data.number + temRight->data.number;
    else if(data.singleChar == '-')nodeVal = temLeft->data.number - temRight->data.number;
    else if(data.singleChar == '*')nodeVal = temLeft->data.number * temRight->data.number;
    else if(data.singleChar == '/')nodeVal = temLeft->data.number / temRight->data.number;
    else return this;


    Tree *temNode = new Tree(nodeVal);
    data = temNode->data;
    type = temNode->type;
    delete left;
    delete right;
    left = right = NULL;
    return this;
}