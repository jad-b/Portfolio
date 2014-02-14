#ifndef _TYPE_H
#define _TYPE_H

// Jan 2008
// Type representation for Simp language
//
// NOTE: don't construct Type objects directly! Use a TypeModule.
//
// A TypeModule is simply a mechanism for managing the memory used
// to represent types. The strategy is to only allocate memory for
// a distinct type once and re-use that memory for subsequent calls
// to construct that type. A TypeModule keeps track of all the
// allocated types so that memory can be reclaimed when the types
// are no longer needed.
//
// So, to obtain a type, access the appropriate member function for
// the global type module object, which is created in main.cxx.


// abstract base class
class Type
{
  public:

    virtual ~Type();
    
    virtual char* toString() = 0;

  protected:
    Type();
};

class TypeNone: public Type
{
  public:
    TypeNone();
    ~TypeNone();

    char* toString();
};

class TypeError: public Type
{
  public:
    TypeError();
    ~TypeError();

    char* toString();
};

class TypeInt: public Type
{
  public:
    TypeInt();
    ~TypeInt();

    char* toString();
};

class TypeFloat: public Type
{
  public:
    TypeFloat();
    ~TypeFloat();

    char* toString();
};

class TypeModule
{
  protected:
     Type* intTypeInternal;
     Type* floatTypeInternal;
     Type* errorTypeInternal;
     Type* noTypeInternal;
    
  public:
    TypeModule();
    ~TypeModule();
    Type* intType();
    Type* floatType();
    Type* errorType();
    Type* noType();
};

#endif
