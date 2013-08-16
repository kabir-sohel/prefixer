#pragma once

#include "Log.h"

//This Function will return a pointer of Log() Object. The only one Object.

Log* Log::getInstance()
{
    if(noOfInstances == 0)
    {
        instance = new Log();
        noOfInstances = 1;
    }
    return instance;
}



void Log::setFileStream(ofstream &stream)
{
    logStream = &stream;
}
//Print the log data to the log stream.
void Log::print(string logString)
{
    if(logStream == NULL)return;
    (*logStream) << logString;
}
//Print current time to help understand which instance produces which log data.
void Log::printCurrentTime()
{
    if(logStream == NULL)return;
    time(&now);
    current = localtime(&now);
    (*logStream) << current->tm_hour <<":"<< current->tm_min <<":"<< current->tm_sec<<endl;
}

int Log::noOfInstances = 0;
Log* Log::instance = NULL;
Log *log = Log::getInstance();
