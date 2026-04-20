#include "HashMap.h"
#include "HashingChecking.h"
#include <iostream>
#include <vector>
using namespace std;

//constructor
HashMap::HashMap(int capacity)
{
    this->capacity = capacity;         //initializing capacity with capacity given in parameter
    buckets.resize(capacity, nullptr);          //initializing buckets vector with size equal to capacity and making all pointers null
    this->size = 0;                     //there is no key value in pair in start
    duplicates.clear();                 //making duplicates clear which mean that it has not even a single object
}

//destructor
HashMap::~HashMap()
{
    freeTable();        //function to delete all the nodes in hashmap
}

//function to delete all the nodes in hashMap
void HashMap::freeTable()
{
    //so we are iterating all the buckets in hashMap
    for (int i = 0; i < capacity; i++) {
        //for each bucket we are traversing each node in it and deleting it
        HashNode* node = buckets[i];
        while (node != nullptr) {
            HashNode* oldNode = node;
            node = node->next;
            delete oldNode;
        }
        //and after deleting all the nodes in that bucket..we are assigning it null pointer
        buckets[i] = nullptr;
    }
    //making size 0
    size = 0;
    //and removing all the duplicate indices
    duplicates.clear();
}

//function that will recieve key and value as string and again call main put func a
void HashMap::put(string key, string filePath)
{
    vector<string> values;
    values.push_back(filePath);
    //calling main put func and passing value as vector<string>
    put(key, values);
}

//main put func which recieves vector<string> as value and string as key
void HashMap::put(string key, vector<string> values)
{
    //so first of all based on key we are calculating the bucket in which we will put this node
    int index = hashFunction(key, capacity);
    //next creating two nodes* to insert node in hashMap cause(LinkedList style)
    HashNode* curr = buckets[index];  //curr has head Node of bucket
    HashNode* prev = nullptr;         //while prev is NULL

    //so checking if curr is not null...curr is not null it means there already exists nodes in that bucket
    //and in that case we will first see if that key already exists there..if so then we will add value as duplicate to that node
    while (curr != nullptr) {
        //so matching key's with key's of all nodes in that bucket
        if (curr->key == key) {
            //if key matched..make its duplicate bool true
            curr->duplicate = true;
            //pass index of bucket to duplicatePutter func so that it can store which bucket have node which have duplicate values
            duplicatePutter(index);
            //appending this/these values to one existing already there
            for (string filePath : values)
                curr->values.push_back(filePath);
            //and returning
            return;
        }
        //if this node's key not found...update prev and curr and try again until we reach the end of that bucket
        prev = curr;
        curr = curr->next;
    }

    //so if we reached this stage..it has two meanings...either the head node of bucket is null or there is no node whose key matched with key given to us
    //no matter ..in both cases we have to add a new node so creating a new node
    //interesting part here is that we are making this node as head node of that bucket and passing curr head Node in its next attribute..so we are not appending
    //we are basically addHead ...just like LinkedList although this is not linked list..just giving example for understanding
    HashNode* newNode = new HashNode(key, values, buckets[index], false);
    buckets[index] = newNode;
    size++;

    //we also call it load factor check..it basically checks if no. of nodes has passed specifc threshold..if so it means that buckets are
    //having more nodes in them which will affect efficiency and speed of code so call rehash..
    if (size > capacity * 0.7)
        callRehash(); //so this func calls rehash(we will talk below about rehash function)
}

//this is nothing but calling rehash functions...
void HashMap::callRehash()
{
    rehash();
}

//so this function basically stores indexes of buckets whose any node have duplicate values...so when it comes to printing or checking which nodes have
//duplicate values....rather than traversing whole tree...we simply traverse buckets mentioned here...which increases efficeincy of code
void HashMap::duplicatePutter(int index)
{
    //ensuring that vector don't have duplicate value..if so we may check same bucket more than once
    for (int x : duplicates) {
        if (x == index)
            return;
    }
    //inserting the index if it was not duplicate
    duplicates.push_back(index);
}

//one of the main function which returns value of specific key
vector<string> HashMap::get(string key)
{
    //calculating bucket index based on key
    int index = hashFunction(key, capacity);
    //making node which we will use to traverse the whole bucket
    HashNode* node = buckets[index];
    //checking all the nodes if their key matches the key given in function..if so return value which is basically vector<array>
    while (node != nullptr)
    {
        if (node->key == key)
            return node->values;
        node = node->next;
    }
    return vector<string>();  // not found
}

//checking if key exists or not
bool HashMap::contains(string key)
{
    //calculating bucket index based on key
    int index = hashFunction(key, capacity);
    //creating node to traverse whole bucket
    HashNode* node = buckets[index];
    //checking if node's key matches with key given to us..if yes return true else return false
    while (node != nullptr)
    {
        if (node->key == key)
            return true;
        node = node->next;
    }
    return false;
}

//function to tell us how many key's are their or how many nodes are their in simple cause one node may contain more than one key value pair(duplicate case)
int HashMap::getSize()
{
    return size;
}

//will return true if hashMap is empty...false if not
bool HashMap::isEmpty()
{
    if(size==0)
        return true;
    return false;
}

//one of the most imp function ....it decides the bucket index in which we have to put node
int HashMap::hashFunction(string& key, int capacity)
{
    unsigned long hash = 0;        //making a long unsigned integer..unsigend cause we have to take % of it and long cause no. can be too long
    //just a way to calculate hash or making it unique
    //you may have many questions...like why are multiplying and adding..or what are we doing
    //we are basically converting string into integer but not exactly string into integer but think it like a function which is taking string as input
    //performing some operation on it ..using characters of string and converting it into a no.
    //you may have question like why are multiplying a prime no. ...PRIME no. have no factors so it will map uniquely every time multiplied with it..hash grows in irregular way
    //you may have question like why we are taking modulu and modulu with CAPACITY
    //so answer is simple that purpose of taking moudulu is to keep integer in a specifc limit so that it may not overload its capacity
    //and purpose of taking modulu with capacity is that our hashmap has CAPACITY no. of buckets..so for each bucket there is a seperate index
    //so hash or number or you can even say index generated should cover all the buckets...
    for (char c : key)
        hash = (hash * 31 + c) % capacity;

    //returning the index of bucket based on key
    return hash;
}

//so one of the most important function of hashMap   ( REHASH )..it basically increases the no. of buckets of real HashMap which also increase no. of buckets of hashMap
//and then transfers its previous nodes again to its bucket according to index calculated with respect to new capacity
void HashMap::rehash()
{
    //creating a variable having value double of capacity of real hashMap's capacity
    int newCapacity = capacity * 2;
    //creating a new vector<HashNode*> array to store node's/key value pairs with respect to index calculated by newCapacity and at end will
    //just assign it to real HashMap
    vector<HashNode*> newBuckets(newCapacity, nullptr);

    // Move nodes to new buckets according to index calculated by newCapacity
    for (int i = 0; i < capacity; i++) {
        //so first of all creating new node and assigning it head of bucket[i]
        HashNode* node = buckets[i];
        //checking if node is not null
        while (node != nullptr) {
            //and if node is not null...then first of all preserve next node
            HashNode* nextNode = node->next;
            //after that calculate index for our new vector<HashNode*> from the key of node
            int newIndex = hashFunction(node->key, newCapacity);
            //now modify next pointer of node and assign it head node of newBucket vector which is present at that index
            node->next = newBuckets[newIndex];
            //and now making this node as head node of that newBucket cause it already has pointer to next node of that bucket and we can traverse the whole bucket easily
            newBuckets[newIndex] = node;
            //and now assigning nextNode of real hashMap's bucket to node so that we can put that also in newBucket array
            node = nextNode;
        }
    }

    //the most important step that we are moving newBucket vector into old bucket vector/real bucket vector
    //so what move here does....as bucket and newBucket both are vector so both have head which point to first element of vector
    //so what move does is it swaps both vectors head such that now bucket is pointing to elements of newBucket and newBucket is pointing to elments of old/real bucket
    //and when at last newBucket will get destroyed...elements in newBucket will be of old bucket which are of no use...
    buckets = move(newBuckets);
    //assigning capacity as newCapacity
    capacity = newCapacity;

    // Recompute duplicates as previous duplicates are of no use now because buckets indexes has been changed
    duplicates.clear();
    //traversing whole bucket array to detect duplicates and assign it back to duplicates vector
    for (int i = 0; i < capacity; i++)
    {
        //using a dummy node to traverse whole hash map
        HashNode* node = buckets[i];
        //checking if node is not null
        while (node != nullptr)
        {
            //very interesting but simple check...every node has boolean duplicate which tell's if it has duplicates or not..simply checking this bool and if exists then add this index to duplicates vector
            if (node->duplicate)
            {
                duplicates.push_back(i);
                //we are breaking cause we have identified at this index there are duplicates..no need to traverse again and again
                break;
            }
            node = node->next;
        }
    }
}

// Print entire hash map in table style
void HashMap::printHashMap()
{
    cout << "\n===========================================================================================================================\n";
    cout << "                                                  HASH MAP CONTENTS\n";
    cout << "===========================================================================================================================\n\n";

    bool foundSomething = false;
    //iterating over the whole hash map
    for (int i = 0; i < capacity; i++)
    {
        HashNode* node = buckets[i];
        //if there is no node in bucket then move to next bucket
        if (node == nullptr)
            continue;  // Skip empty buckets
        foundSomething = true;
        while (node != nullptr)
        {
            // now for each node ..print its key
            cout << node->key;

            // adding spaces to organize the output
            int keyLength = node->key.length();
            int spaces = 80 - keyLength;  // Fixed width for key column
            //now appending spaces after printing key
            for (int s = 0; s < spaces; s++)
                cout << " ";
            cout << " -> ";
            // Print all values of that node...all duplicate or simple values
            for (int j = 0; j < node->values.size(); j++)
            {
                cout << node->values[j];
                //putting seperation between values in case of duplicate values...
                if (j != node->values.size() - 1)
                    cout << "  |  ";
            }
            cout << endl;
            node = node->next;
        }
    }
    //if we reached here..it means our hash map is empty
    if (!foundSomething)
    {
        cout << "       Hash Map is Empty!\n";
    }
}

// Print only duplicate entries
void HashMap::printDuplicates()
{
    cout << "\n\n\n===========================================================================================================================\n";
    cout << "                                                  DUPLICATE ENTRIES\n";
    cout << "===========================================================================================================================\n\n";

    //if duplicates vector is empty then return..
    if (duplicates.empty())
    {
        cout << "   No duplicates found!\n";
        cout << "===========================================================================================================================\n";
        return;
    }
    //iterating over the whole duplicate vector
    for (int index : duplicates)
    {
        //pick that bucket and traverse each node of that bucket
        HashNode* node = buckets[index];
        while (node != nullptr)
        {
            //in case of duplicate value exists
            if (node->duplicate)
            {
                //doing same thing as we did in printing hashMap
                cout << node->key;
                int keyLength = node->key.length();
                int spaces = 80 - keyLength;

                for (int s = 0; s < spaces; s++)
                    cout << " ";

                cout << " -> ";

                // Print values
                for (int j = 0; j < node->values.size(); j++)
                {
                    cout << node->values[j];
                    //printing size of file along with duplicate files..calling getFileSizeKB function using object of HashingChecking class
                    cout<<"( "<<helper.getFileSizeKB(node->values[j])<<" KB)";
                    //in case of duplicate values..insert seperation in them
                    if (j != node->values.size() - 1)
                        cout << "  |  ";
                }
                cout << endl;
            }
            node = node->next;
        }
    }
    //at last ..print total no. of duplicate buckets
    cout<<endl<< "Total duplicate buckets: " << duplicates.size() << endl;
}


//function to delete duplicateFiles
void HashMap::duplicateFilesDeletion()
{
    //iterate over each bucket and check which Node is having duplicate values
    for (int index : duplicates)
    {
        HashNode* node = buckets[index];
        while (node != nullptr)
        {
            //if duplicate is true then it means it is having duplicate values
            if (node->duplicate)
            {
                //so call deleteFile function through HashingChecking and delete all the files whose path is given to it
                for(int i=1;i<node->values.size();i++)
                    helper.deleteFile(node->values[i]); //giving it paths other than first one

                //as we have deleted duplicate values...make its duplicate node false
                node->duplicate=false;
                //create a new vector...assign it first value only of our real values vector and assign this vector to values vector
                vector<string> newValue;
                newValue.push_back(node->values[0]);
                node->values=newValue;
            }
            node=node->next;
        }
    }
    //at last clear duplicate vector as there is no duplicate file now
    duplicates.clear();
    cout<<endl<<"Files deleted successfully!"<<endl;
}
