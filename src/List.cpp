#include "List.h"
#include <iostream>
#include <string>

using namespace std;
List::List()
{//at first nothing is present
    head=nullptr;
}
//deleting list
List::~List(){
if(empty())//already deleted
    return;
else//call delete func
   delHead();

}

List::List(const List& other){
    head=nullptr;//creating new list
    //checking if other list is empty
    if(other.empty())
        return;
    else{
        //first node of list
       Nodeptr newnode=new DNode();
         head=newnode;
         //putting first data in this list
         head->data=other.head->data;
          //we will iterate and put value with the help of this pointers
         Nodeptr curr_other=other.head->next;
         Nodeptr curr_this=head;

         while(curr_other!=nullptr){
            Nodeptr newnode=new DNode();//creating new node every time
            newnode->data=curr_other->data;//putting data in new node
            newnode->next=nullptr;//its last node so point null
            curr_this->next=newnode;//updating curr
            curr_this=newnode;
             //otherwiae loop forever currother never become null
            curr_other=curr_other->next;


         }


    }

}
//checking if list is empty and returning bool
bool List::empty()const{
    if(head==nullptr)
        return true;
    else
        return false;

}

string List::headElement()const{
    if(!empty())//simple if not empty we have head then return its data
       return head->data;

}
void List::addHead(string newdata){
    //creating  new node
     Nodeptr newnode=new DNode();
     newnode->data=newdata;//putiing data
   if(empty()){
    head=newnode;//simply point head to node
    newnode->next=nullptr;
   }
   else{
        //updatehead
     newnode->next=head;
     head=newnode;
   }
}

DNode*& List::headPtr()
{
    return this->head;
}

void List::delHead(){
if(empty())
    return;
else{
        //storing deleting element in temp
   Nodeptr temp=head;
   head=head->next;//updating head
   delete temp;//deleting
}

}

int List::length()const{
  int length=0;
  Nodeptr curr=head;
//loop through and increment leng
  while(curr!=nullptr){
    length++;
    curr=curr->next;

  }
  //then return it
  return length;

}
void List::print()const{
    Nodeptr curr=head;
    cout<<"[";
    //just looping through and printing data of each node
 while(curr!=nullptr){
    cout<<curr->data<<" ";
    curr=curr->next;

  }

cout<<"]";
cout<<"\n";
}
