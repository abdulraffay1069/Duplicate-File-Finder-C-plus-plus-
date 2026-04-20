#ifndef N_ARY_TREE_H
#define N_ARY_TREE_H
#include <iostream>
#include "HashMap.h"
#include "HashingChecking.h"
#include "List.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;
struct Node
{
    string path;   //string to store path
    bool isFile;    //bool which tells stored path is file or not
    Node* child;     //pointer to store address of its child
    Node* next;     //pointer to store address of its siblings
    Node(string path,bool status)
    {
        this->child=NULL;
        this->path=path;
        this->isFile=status;
        this->next=NULL;
    }
};


class N_ARY_TREE
{
    public:

        N_ARY_TREE(string path); //overloaded constructor
        virtual ~N_ARY_TREE();  //destructor
        void start(string path);
        void treePrinting();     //function to print all the files
        void duplicatesPrinting();  //functions to print all duplicates
        HashMap mapping;         //object of HashMap class
        void deleteDuplicates();    //function to delete duplicate files
    protected:

    private:
        Node* root;                 //private attribute
        HashingChecking h;          //object of HashingChecking class
        void traverse(string path,Node*& root); //mian function which is traversing in whole tree
        void deleteNode(Node*& root);       //function to delete the Node

};

#endif // N_ARY_TREE_H
