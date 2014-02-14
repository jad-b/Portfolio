// main routine for compiler for Simp language

#include "SymbolTable.h"
#include "StringPool.h"
#include "Type.h"

// prototype for bison-generated parser
int yyparse();

// prototypes for code generation functions in encode.cxx
void encodeInitialize();
void encodeFinish();

// to enable bison parse-time debugging
#if YYDEBUG
extern int yydebug;
#endif

// global string pool
StringPool* stringPool;

// global symbol table
SymbolTable* symbolTable;

// global type module
TypeModule* types;

int main()
{
  // create a string pool
  stringPool = new StringPool();

  // create a type module
  types = new TypeModule();

  // create a symbol table
  symbolTable = new SymbolTable();

  // set yydebug to 1 to enable bison debugging
  // (preprocessor symbol YYDEBUG must also be 1 here and in parse.yy)
#if YYDEBUG
  yydebug = 1;
#endif

  // generate prologue code
  encodeInitialize();

  // syntax directed compilation!
  yyparse();

  // generate epilogue code
  encodeFinish();

  // cleanup symbol table
  delete symbolTable;

  // cleanup the types
  delete types;

  // cleanup the string pool
  delete stringPool;
}
