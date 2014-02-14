#ifndef _STRINGPOOL_H
#define _STRINGPOOL_H

// Jan 2008
// Mechanism for keeping track of all allocated strings.
//
// Strings are allocated in the scanner. By doing the allocation
// via the StringPool object, all allocated strings can be remembered
// and re-claimed later.


// one of these is created for each string in order to chain all strings
// together for deleting later
class StringPoolRecord
{
  public:
    StringPoolRecord(char*, StringPoolRecord*); //Constructor
    ~StringPoolRecord();                        //Destructor
    char* savedPointer;                         //
    StringPoolRecord* next;                     //Next pointer
};

// The StringPool proper. The newString method allocates memory
// in the SringPool and copies the input string to that allocated
// space.
//
class StringPool
{
  protected:
     StringPoolRecord* head;

  public:
    StringPool();
    ~StringPool();
    char* newString(char*);
};

#endif
