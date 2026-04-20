#ifndef HASHINGCHECKING_H
#define HASHINGCHECKING_H
#include <iostream>
#include <vector>
#include"List.h"
using namespace std;

class HashingChecking
{
    public:
        HashingChecking();   //constructor
        virtual ~HashingChecking();     //destructor
        int CheckDirectory(const std::string & directory);   //function which will check if given path is directory or file or invalid path
        DNode* GiveChildren(const string& directory);       //function which will return a linkedList Node containing all childrens in it of path given in parameter
        std::string CompleteHashing(const std::string &filepath); //function to calculate hash of content of file passed to it
        int getFileSizeKB(const std::string& filePathStr);      //function to return size of file in KB
        void deleteFile(const std::string& filePathStr);        //function to delete the file
    private:
        std::string FileHash(const std::string &directory);     //function used by complete Hash it calculates hash of content passed to it
        std::string ReadFileBinaryContent(const std::string &filepath); //this one reads the content of file in binary mode
};

#endif // HASHING&CHECKING_H
