
/*******************************************************************************************************/
/*****Author : Sohel Hossain Kabir *********************************************************************/
/*******Date : May 15, 2012 , Tuesday ******************************************************************/
/****Program : An Expression Tree from a infix Expression and produce Preorder Expression***************/
/******Input : an infix Expression as command prompt****************************************************/
/*Parameter1 : (mandatory) - [FILE_NAME] The File name from which program will read infix string********/
/*Parameter1 : (optional) - [-r] This flag will be triggered to reduce the expression as much it can be*/
/*****output : an prefix Expression in stdout **********************************************************/
/*****Client : TwitchTv Interview : Coding Session Problem Solving *************************************/
/*******************************************************************************************************/


#pragma once
#include "CommonHeaders.h"
#include "Log.h"
#include "Tree.h"
#include "Mixed.h"


extern Log *log;
int main(int argc, char *argv[])
{
    //At first create the Log file. If exists append at the last.
    char fileLocation[105];
    strcpy(fileLocation,"Log.txt");
    ofstream logOutputStream;
    logOutputStream.open(fileLocation, ios::out | ios::app);
    log->setFileStream(logOutputStream);


    //can't open the Log File. Logging will be skipped.
    if(!logOutputStream.is_open())
    {
        cout<<"Error!!!!!!! in opening Log file. Logs will not be stored.\n";
    }

    //Start keeping log.
    log->print("\n\n\n\n\nNew Instance starts running........... at ");
    log->printCurrentTime();

    //Enough argument isn't passed through command prompt.
    if(argc < 2)
    {
        log->print("File Location is missing\n");
        cout<<"Error : File Location is missing"<<endl;
        return -1;
    }


    strcpy(fileLocation,argv[1]);


    ifstream input(fileLocation);
    //Get File opening Exception
    if(!input.is_open())
    {
        log->print("File Opening Error\n");
        cout<<"Error : File Opening Error"<<endl;
        return -2;
    }

    string line = "",infixString = "";

    //Get all lines of the file and build one string by concatanating them.
    while(getline(input,line))
    {
        infixString += line;
    }
    //now build the Expression Tree from the infix Expression.
    //root will be the root of Expression Tree.
    Tree *root = buildExpressionTreeFromInfix(infixString);

    if(root == NULL)    //There is an Error building Expression Tree.
    {
        cout<<"Error : See the Exception_Log.txt file for details\n";
        return -3;
    }
    string prefixString = ""; //This will hold the prefix expression of the infix Expression.
    if(argc == 3 && !strcmp(argv[2],"-r"))  //If -r flag is triggered, then reduce the expression tree as much it can be.
    {
        root = root->reduceExpression();
    }
    //now is the time to inorder tree walk. It produces prefix expression from an Expression Tree.
    prefixString = root->preOrderTreeTraversal();
    cout<<prefixString<<endl;

    //Result is printed to the console. program Exiting....
    log->print("Successfully printed the Result\n...Exiting......\n\n");
    return 0;
}
