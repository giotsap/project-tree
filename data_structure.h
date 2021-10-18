#ifndef DATA_STRUCTURE_H
#define DATA_STRUCTURE_H

#include <string> 

using namespace std;

template <class T> class DataStructure{
    protected:
        T *entry; // a pointer points to a data structure 
    public: 
        /* The basic operations for each data structure - there isn't a common operation for the three data structures*/
        virtual void Insert(string key) = 0; //so, this class is abstract  and these operations have to be implemented 
        virtual void Delete(string key) = 0;
        virtual int Search(string key) = 0;
};

#endif