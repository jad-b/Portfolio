#ifndef _TYPE_H
#define _TYPE_H

// Jan 2008
// Type representation for the T language
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

// class field struct
struct field{
  char* fieldName;  // field name
  Type* type;       // field type
  unsigned int offest;    // byte offset in VMT
  field* next;      // LL ptr
};

class TypeClass: public Type{
    protected:
      char* className;
      char* superName;
      field* fieldList;

    public:
        TypeClass(char* c_name, char* s_name);
        ~TypeClass();

        char* toString();
        const char* getClassName();
        const char* getSuperName();
};

class TypeFloat: public Type
{
  public:
    TypeFloat();
    ~TypeFloat();

    char* toString();
};

/* ClassMap */
struct HashNode{
  TypeClass* classDef;
  HashNode* next;       // Keeps a linked list going
  HashNode* parent;     // superclass parent of the Class
};

class ClassMap{
protected:
  HashNode** classMap; // Catchy!
  HashNode* objectNode;

public:
  ClassMap();
  ~ClassMap();

  const char* toString();
  TypeClass* lookup(const char* name);
  HashNode* nodeLookup( const char* name );
  int insert(TypeClass* newClass);
  unsigned int hash(const char*);
  TypeClass* getObject();
};

/* Type Module */
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
    Type* classType();

    ClassMap* classMap;
};



#endif
