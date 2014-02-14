// Jan 2008
// Type representation for T language
//
// NOTE: Don't use Type methods directly. Rather use indirectly via
//       TypeModule. See Type.h for more information.

#include "stdio.h"
#include "Type.h"
#include <cstring>
#include <string>
#include <iostream>
#include <sstream>

#define DEBUG 1
//#define NDEBUG
#include <cassert>

static int ht_size = 100;

Type::Type()
{
}

Type::~Type()
{
}

// No type
TypeNone::TypeNone()
{
}

TypeNone::~TypeNone()
{
}

char* TypeNone::toString()
{
  return (char *) "<no type>";
}

// Error type
TypeError::TypeError()
{
}

TypeError::~TypeError()
{
}

char* TypeError::toString()
{
  return (char *) "<error type>";
}

// Int type
TypeInt::TypeInt()
{
}

TypeInt::~TypeInt()
{
}

char* TypeInt::toString()
{
  return (char *) "int";
}

/* Class Type.
 * className is the name of the class; "A" of "class A"
 * superName is the parent class; "B" of "class A extends B"
 * fieldList is a linked list of field structs
 * methodList is a linked list of method structs
 */
TypeClass::TypeClass(char* cName, char* sName){
    className = cName;

    if( sName )
        superName = sName;
    else
        superName = (char*)"Object";   // Default parent class of Object

    // fields not implemented at this time
}

TypeClass::~TypeClass(){

}

char* TypeClass::toString(){
  return className;
}

const char* TypeClass::getClassName(){
  return (const char*) className;
}

const char* TypeClass::getSuperName(){
  return (const char*) superName;
}

// Float type - Not used!
TypeFloat::TypeFloat()
{
}

TypeFloat::~TypeFloat()
{
}

char* TypeFloat::toString()
{
  return (char *) "float";
}

/**********************
    Type Module
**********************/
TypeModule::TypeModule()
{
  intTypeInternal = (Type*) new TypeInt();
  floatTypeInternal = (Type*) new TypeFloat();
  errorTypeInternal = (Type*) new TypeError();
  noTypeInternal = (Type*) new TypeNone();

  classMap = new ClassMap();
}

TypeModule::~TypeModule()
{
  delete intTypeInternal;
  delete floatTypeInternal;
  delete errorTypeInternal;
  delete noTypeInternal;
}

Type* TypeModule::intType()
{
  return intTypeInternal;
}

Type* TypeModule::floatType()
{
  return floatTypeInternal;
}

Type* TypeModule::errorType()
{
  return errorTypeInternal;
}

Type* TypeModule::noType()
{
  return noTypeInternal;
}

Type* TypeModule::classType(){
  return (Type*)classMap->getObject();
}

/* ClassMap*/
ClassMap::ClassMap(){
  //Construct hash table
  classMap = new HashNode*[ht_size]; // the c++ way
  for( int i = 0; i < ht_size; i++ ){   // NULL EVERYTHING!!!
    classMap[i] = NULL;
  }

  TypeClass* object = new TypeClass((char*)"Object",NULL);
  objectNode = new HashNode;
  objectNode->classDef = object;            // Add the default object class
  objectNode->next = objectNode->parent = NULL; // Object links to nothing
  classMap[hash(objectNode->classDef->getClassName())] = objectNode;   // link object in at hashed index
}

ClassMap::~ClassMap(){
  //Delete everything
  HashNode* p, *old;
  for( int i = 0; i < ht_size; i++ ){
    if( classMap[i] ){
      p = classMap[i]; // Grab head of list at hash index
      while( p ){
        old = p;
        p = p->next;
        delete old->classDef;   // delete TypeClass object
        delete old;             // delete HashNode
        old = NULL;             // just in case.
      }
    }
  }
  delete classMap;
}

/* Installs TypeClass object into table
 * Returns 0 on success
 * Returns 1 on name conflicts
 * Returns 2 on illegitimate superclass name
 */
int ClassMap::insert(TypeClass* newClass){
  int index = hash(newClass->getClassName());  // hash to index
  HashNode* p = classMap[index];              // Retrieve index
  HashNode* prev = NULL;                      // Keeps track of previous node
  // search for end and name conflicts
  while( p && strcmp(p->classDef->getClassName(),newClass->getClassName()) != 0){
    prev = p;
    p = p->next;
  }

  if( p ){ // class with same name exists
#ifdef DEBUG
    std::cerr << "insert: class with same name exists\n";
#endif
    return 1; // return error
  }

  HashNode* sc;  // superclass pointer
  if( newClass->getSuperName() ){                 // if superclass is listed
    sc = nodeLookup(newClass->getSuperName());  // get parent HashNode
    if( !sc ){   // if no superclass by that name exists, error
      #ifdef DEBUG
    std::cerr << "insert: no superclass by the name " << newClass->getSuperName() << " found\n";
    #endif
      return 2;
    }
  }
  //else we're good on error cases, so build the new HashNode

  p = new HashNode;       // Create new HashNode for the TypeClass
  p->classDef = newClass; // Assign TypeClass to HashNode
  p->next = NULL;         // We're adding to the tail
  if( prev )
    prev->next = p;         // Link to previous tail
  // superclass handling
  if( sc )    // if there was a superclass listed AND found
    p->parent = sc;           //Link to superclass HashNode wrapper
  else        // else there was no superclass listed
    p->parent = objectNode;   // Link wrapper HashNode to Object HashNode

  classMap[index] = p;
#ifdef DEBUG
  std::cerr << "insert." << index << " " << p->classDef->getClassName() << "\n";
#endif
  return 0;
}

/* Returns pointer to TypeClass object with given name.
 * Returns NULL on error
 */
TypeClass* ClassMap::lookup( const char* name ){
  if( !name ) // no name provided
    return NULL;

  int index = hash( name );     // retrieve index
  HashNode* p = classMap[index];    // create pointer to HashNode
  // while ( exists && names don't match ), travel through the chain
  while( p && strcmp(p->classDef->getClassName(), name) != 0){
    p = p->next;
  }
  if( !p ) // Class does not exist
    return NULL;
  else{     // Class was found
    // assert name's match
    assert( strcmp(p->classDef->getClassName(),name) == 0);
    return p->classDef;
  }
}

/* Returns pointer to HashNode object with given name.
 * Returns NULL on error
 */
HashNode* ClassMap::nodeLookup( const char* name ){
  int index = hash( name );     // retrieve index
  HashNode* p = classMap[index];    // create pointer to HashNode
  // while ( exists && names don't match ), travel through the chain
  while( p && strcmp(p->classDef->getClassName(), name) != 0){
    p = p->next;
  }
  if( !p ) // Class does not exist
    return NULL;
  else{     // Class was found
    // assert name's match
    assert( strcmp(p->classDef->getClassName(),name) == 0);
    return p;
  }
}

/* hash: compute hash value for a string
 * 1. hash ← 0
 * 2. for each byte of key
 * 3. hash ← ((hash × multiplier ) + byte) mod table-size
 */
unsigned int ClassMap::hash(const char *s)
{
  unsigned int c, h = 0;
  for( c = 0; c < strlen(s); c++ )
    h = (h*127 + s[c]) % ht_size;

  if( h <= 0 )
    fprintf(stderr,"ClassMap:hash = %d\n",h);
  return h;
}

const char* ClassMap::toString(){
  std::ostringstream oss;
  HashNode* p;
  int i;
  for( i = 0; i < ht_size; i++ ){
    if( classMap[i] ){
      oss << i << ": ";
      p = classMap[i];
      while( p ){
        oss << p->classDef->toString() << " ";
        p = p->next;
      }
      oss << "\n";
    }
  }
  return oss.str().c_str();
}

/* Returns the Object class
 */
TypeClass* ClassMap::getObject(){
  return objectNode->classDef;
}


#ifdef DEBUG
int main( int argc, const char* argv[] )
{
    int err;
    TypeModule* types = new TypeModule();
    std::cout << types->classMap->toString();

    TypeClass* classA = new TypeClass((char*)"A",NULL);
    err = types->classMap->insert(classA);


    TypeClass* classB = new TypeClass((char*)"B",(char*)"A");
    err = types->classMap->insert(classB);

    std::cout << types->classMap->toString();

    std::cout << types->classMap->lookup("A")->getSuperName() << "\n";
    std::cout << types->classMap->lookup("B")->getSuperName() << "\n";

}
#endif