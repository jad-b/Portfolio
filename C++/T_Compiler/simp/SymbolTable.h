#ifndef _SYMBOLTABLE_H
#define _SYMBOLTABLE_H

#include "Type.h"

// Jan 2008
// Symbol Table for Simp language
//
// It is just an inefficient linked list for now.


// Container for one symbol table entry
class SymbolTableRecord
{
  public:
    ~SymbolTableRecord();
    
    SymbolTableRecord(char*, Type*);

    void dump();

    SymbolTableRecord* next;

    char* name;

    Type* type;
    
};

// The SymbolTable proper
class SymbolTable
{
  protected:
    SymbolTableRecord* head;
    
  public:
    ~SymbolTable();
    
    SymbolTable();

    // returns 1 if name is found and 0 otherwise
    // if found, type returned through the second (reference) parameter
    bool lookup(char* name, Type*& type);

    // returns 1 if successful
    // in this case name and type are stored in a new record in table
    // it only fails if name is already in the list
    // in that case symbol table is not changed
    bool install(char* name, Type* type);

    void dump();
};

#endif
