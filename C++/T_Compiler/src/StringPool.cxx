// Jan 2008
// Mechanism for keeping track of all allocated strings so they can be
// cleaned up all at once later.

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "StringPool.h"

StringPoolRecord::StringPoolRecord(char* s, StringPoolRecord* n)
{
  savedPointer = s;
  next = n;
}

StringPoolRecord::~StringPoolRecord()
{
  free(savedPointer);
  delete next;
}

StringPool::StringPool()
{
  head = NULL;
}

StringPool::~StringPool()
{
  delete head;
}

char* StringPool::newString(char *in)
{
  char* tmp = (char*) malloc(strlen(in)+1);
  strcpy(tmp, in);
  head = new StringPoolRecord(tmp, head);
  return tmp;
}

