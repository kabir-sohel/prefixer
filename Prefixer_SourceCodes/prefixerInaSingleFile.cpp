/********************************************************************************************************/
/******Author : Sohel Hossain Kabir *********************************************************************/
/********Date : May 15, 2012 , Tuesday ******************************************************************/
/*****Program : An Expression Tree from a infix Expression and produce Preorder Expression***************/
/*******Input : an infix Expression as command prompt****************************************************/
/**Parameter1 : (mandatory) - [FILE_NAME] The File name from which program will read infix string********/
/**Parameter1 : (optional) - [-r] This flag will be triggered to reduce the expression as much it can be*/
/******output : an prefix Expression in stdout **********************************************************/
/******Client : TwitchTv Interview : Coding Session Problem Solving *************************************/
/********************************************************************************************************/




//Header File Declaration
#include<stdio.h>
#include<iostream>
#include<string>
#include<string.h>
#include<stack>
#include<sstream>
#include<algorithm>
#include<fstream>
#include<time.h>
using namespace std;


//Helper Functions' Prototype.
bool isOperator(string&);
bool isOperator(char op);
bool isNumber(string&);
bool isSingleAlphabet(string&);
int priority(char);
string intToString(int);

//Log class will write the program log data whenever it runs.
//Its a singleton class. So only one object of this class can be initiated.
class Log
{
    static Log* instance ;
    static int noOfInstances;
    ofstream *logStream;
    struct tm *current;
    time_t now;
    Log(){}     //private constructor . it prevents object creation outside of class scope.
    public:

//This Function will return a pointer of Log() Object. The only one Object.
    static Log* getInstance()
    {
        if(noOfInstances == 0)
        {
            instance = new Log();
            noOfInstances = 1;
        }
        return instance;
    }
//Set the log writting output stream
    void setFileStream(ofstream &stream)
    {
        logStream = &stream;
    }
//Print the log data to the log stream.
    void print(string logString)
    {
        if(logStream == NULL)return;
        (*logStream) << logString;
    }
//Print current time to help understand which instance produces which log data.
    void printCurrentTime()
    {
        if(logStream == NULL)return;
        time(&now);
        current = localtime(&now);
        (*logStream) << current->tm_hour <<":"<< current->tm_min <<":"<< current->tm_sec<<endl;
    }
};
//initialization of the noOfInstance variable and getting Log() object.
int Log::noOfInstances = 0;
Log* Log::instance = NULL;
Log *log = Log::getInstance();


//node data can be a single char or an integer.
//a single char holds operatoror single char alphabet.
//a node can have data as either singleChar or int, not both, Hence to save memory union is used.

union nodeData
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
};
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
//Now Comes the Helper Functions. These Function is helpful either to tree or others.
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
