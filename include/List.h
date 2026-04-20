#ifndef LIST_H
#define LIST_H
#include <iostream>
#include<string>
using namespace std;

struct DNode
{
        string data;
        DNode *next;
};

//functions and attributes of List Class
typedef DNode* Nodeptr ;
class List
{
    public:
        List();
        virtual ~List();
        List(const List& other);
        bool empty()const;
        string headElement()const;
        void addHead(string newdata);
        void delHead();
        int length()const;
        void print()const;
        DNode*& headPtr();

    private:
      Nodeptr head;//we need it to locate our memory in heap
};

#endif // LIST_H
