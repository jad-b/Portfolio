// Jan 2008
// Type representation for Simp language
//
// NOTE: Don't use Type methods directly. Rather use indirectly via
//       TypeModule. See Type.h for more information.

#include "stdio.h"
#include "Type.h"

Type::Type()
{
}

Type::~Type()
{
}

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

TypeModule::TypeModule()
{
  intTypeInternal = (Type*) new TypeInt();
  floatTypeInternal = (Type*) new TypeFloat();
  errorTypeInternal = (Type*) new TypeError();
  noTypeInternal = (Type*) new TypeNone();
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

