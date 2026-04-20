#include "N_ARY_TREE.h"
#include <iostream>
#include <vector>
#include <string>
#include "List.h"
#include "HashMap.h"
#include "HashingChecking.h"
using namespace std;
N_ARY_TREE::N_ARY_TREE(string path)
{
    //At start the root is pointing to null
    //It first check whether it is a Folder or File
    //It update the root according to the directory status
    //By calling traverse function
    root=NULL;
    //which receive directory or pointer reference of root
    traverse(path,root);
}
void N_ARY_TREE::traverse(string path,Node*& root)
{
    /*-----------Comments----------------
    It is the DFS(Depth First algorithm)
    In DFS we first traverse to the node child again again till the last child
    Then we comes up and then check the Sibling(next)and then again we move to that node child till the child has no further child
    In our project which we are first checking the directory status is it a file or folder or invalid directory
    if it is file first generate the hash and call hash map
    Then update the root pointer and return the function
    if it is a folder then update the root and gets its children in linked list
    after getting children first make the Node pointer(last) which is used to trace the path
    then call the traverse which again but with the temp node which is pointing to null first
    it is used here because if we have the linked list of more than one node (Folder children)
    then we call the traverse function for the second linked list element we override the folder first child
    by passing directly the folder child pointer
    So when we pass the temp and directory as a arguments to the same traverse function it do all the things for that child as i mentioned above
    It goes to the final child(node) then connect the child to its parent if it is first child then the folder first child is that Node
    and the node which we used to trace the path point to that node which is adding to folder child
    To check if the Sibling exist then update the child next node to the new sibling node
    -----------------------------*/

    //calling the function to get the status in integer
    int checkStatus=h.CheckDirectory(path);

    //if the status is negative then the directory is invalid and the function show the message and return
    if(checkStatus==-1)
    {
        cout<<"The Directory you entered is Invalid"<<endl;
        return;
    }
    //if status 1 then it is file first call the Hashgenerate function for generating hashing and
    //then call the mapping.put function for hash mapping by key value and update the root node and return the function
    else if(checkStatus==1)
    {
        string hash = h.CompleteHashing(path);
        mapping.put(hash,path);

        root=new Node(path,checkStatus);
        return;
    }
    else if(checkStatus==0)
    {
        //if it is 0 then update the root

        root=new Node(path,checkStatus);
        //receive a linked list pointer

        DNode* children=h.GiveChildren(path);

        //for trace the path we use pointer last
        Node* last=NULL;
        while(children!=NULL)
        {
            //for behaving the linked list element as a separate node
            Node* curr=NULL;
            traverse(children->data,curr);
            //in this we add the node according to the N-ary tree if it is first child then update the root->child
            //and also update the last node
            if(root->child==NULL)
            {
                root->child=curr;
                last=curr;
            }
            //if not(mean it is sibling of last node) then update the last node next to this node and  update last node to the updated node

            else
            {
                last->next=curr;
                last=curr;
            }
            //go to the next linked list child
            children=children->next;
        }

    }
    else
        return ;
}
void N_ARY_TREE::deleteNode(Node*& root)
{
    //termination condition when the root becomes NULL then return the function
    //If the function is recursively call again and again then it call itself to that
    //point when the pointer not points to the NULL
    if(root==NULL)
      return;
    //It deletes the Node in the DFS(Depth First Form)
    //It first goes to the child of node again and again
    deleteNode(root->child);
    //Then it goes to the Node Sibling(next)
    deleteNode(root->next);
    //When no further Sibling exist
    //Then it start deleting from the right direction to left
    delete root;
}
N_ARY_TREE::~N_ARY_TREE()
{
    //For remove the memory from the heap at the end of Program
    //automatically by calling deleteNode function which receive the reference pointer of root as a argument
    deleteNode(root);

}

void N_ARY_TREE::start(string path)
{
    this->traverse(path,root);
}


void N_ARY_TREE::treePrinting()
{
    this->mapping.printHashMap();
}

void N_ARY_TREE::duplicatesPrinting()
{
    this->mapping.printDuplicates();
}

void N_ARY_TREE::deleteDuplicates()
{
    if(mapping.duplicates.size()>0)
    {
        int answer;
        cout<<endl<<endl<<"Do you want to delete duplicate Files?(1/0)"<<endl;
        cin>>answer;

        if(answer==1)
        {
            mapping.duplicateFilesDeletion();
            mapping.printHashMap();
            mapping.printDuplicates();
        }
        else if(answer==0)
            cout<<endl<<"Duplicates are not deleted!"<<endl;
        else
            cout<<endl<<"Invalid choice..Bye Bye!"<<endl;
    }

}

