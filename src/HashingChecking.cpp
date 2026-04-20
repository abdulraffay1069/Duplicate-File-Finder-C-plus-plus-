#include "HashingChecking.h"
#include"List.h"
#include<filesystem> //used to check paths, files, folders, and iterate directories
#include <iostream>
#include<string>
#include <iomanip>       // used for formatting hash output
#include <sstream>      //allows string based operations
#include <sys/stat.h>        //used to get metadata of file/folder
#include <openssl/sha.h>     // provides sha256 hashing function
#include<fstream>       // used to read files in binary mode

namespace fs =std::filesystem;
using namespace std;
HashingChecking::HashingChecking()
{
    //ctor
}

HashingChecking::~HashingChecking()
{
    //dtor
}

int HashingChecking:: CheckDirectory(const std::string & directory)
{
     //giving path to filesystem
    fs::path p =directory;
    //checking if file exist if not return -1
    if(!fs::exists(p)){
        //cout<<p<<"is invalid";
       return -1;
    }
    //path is a file
    if(fs::is_regular_file(p))
    {
        return 1;
    }
    //it is directory
    if(fs::is_directory(p))
    {
     return 0;
    }
}



DNode*  HashingChecking::GiveChildren(const string& directory)
{
     List * list =new List();
    //string path
    string path =directory;
    //struct is defined in library that takes meta data of file in sysstat
    //here variable is declared to store file metadata
    struct stat sb;
    //iterating throwing all subfiles
    for(const auto& entry :fs::directory_iterator(path))
    {

            //storing path in outfilename
            std::filesystem::path outfilename = entry.path();
           //converting into string object
            std::string outfilename_str = outfilename.string();
            //converting to char needed in this form
            const char* path = outfilename_str.c_str();
            //checking validality of file path
            if (stat(path, &sb) == 0)
            {
                list->addHead(path);
              //  std ::cout << path << std::endl;
            }
    }
    DNode* head=list->headPtr();
    return head;
}


std::string HashingChecking::ReadFileBinaryContent(const std::string &filepath)
{
    //creating obj of file with its path and mode of access and permission allowed
    std::ifstream  file(filepath,std::ios::binary|std::ios::in);
    //if cannot open return empty s
    if (!file.is_open()) {
        std::cerr << "Error opening file:" << filepath << std::endl;
        return "";
    }
    //seek get function
    file.seekg(0, std::ios::end);
    std::streamsize fileSize = file.tellg();
    //again same thing
    file.seekg(0, std::ios::beg);

    //checking validality
    if (fileSize <= 0) {
        return "";
    }
    //anything for storing content used string i can use vector no skill issue
    std::string content(fileSize, '\0');

    //read function of fstream
    if (file.read(&content[0], fileSize))
        return content;
    std::cerr << "Error reading file data: " << filepath << std::endl;
    return "";
}

std::string HashingChecking::FileHash(const std::string &directory)
{
    //array of bytes
    unsigned char hash[SHA256_DIGEST_LENGTH];
    //openssl func for calculating hash
    SHA256((unsigned char*)directory.c_str(),directory.length(),hash);
    //will contain result
    std::string result;
    //creating buffer
    char buffer[3];
    //nothing just iterating a accumulating hash for n bytes may be any
    for(int i=0;i<SHA256_DIGEST_LENGTH;i++)
    {
        std:: sprintf(buffer,"%02x",hash[i]);
        result+=buffer;
    }
    return result;
}

std::string HashingChecking::CompleteHashing(const std::string &filepath)
{
    //calling functions to read file in binary format and then pass received string to FileHash function to convert that to hash
    std::string content=ReadFileBinaryContent(filepath);
    std::string hashed=FileHash(content);
    return hashed;
}

//function to deleteFiles
void HashingChecking::deleteFile(const std::string& filePathStr)
 {
     //converted string received in parameter to path object which filesystem understands
    fs::path filePath(filePathStr);
    //and if file exists then delete it
    if (fs::exists(filePath))
    {
        fs::remove(filePath);
    }
}

//function to get file size in kbs
int HashingChecking::getFileSizeKB(const std::string& filePathStr) {
    //converting string received in parameter to path object which filesystem understands
    fs::path filePath(filePathStr);
    //checking if file exists If it exists then calculate size in byte and convert into KB and return that
    if (fs::exists(filePath))
    {
        int sizeKB = fs::file_size(filePath) / 1024;
        return sizeKB;
    }
    return 0;
}




