#pragma once
#include "CommonHeaders.h"


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
    static Log* getInstance();
//Set the log writting output stream
    void setFileStream(ofstream &stream);
//Print the log data to the log stream.
    void print(string logString);
//Print current time to help understand which instance produces which log data.
    void printCurrentTime();
};


//initialization of the noOfInstance variable and getting Log() object.
