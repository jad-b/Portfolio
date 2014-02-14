// main routine for compiler for the T language

#include "SymbolTable.h"
#include "StringPool.h"
#include "Type.h"
#include <cstring>
#include <iostream>
#include <cstdlib>
using namespace std;

// prototype for bison-generated parser
int yyparse();

// prototypes for code generation functions in encode.cxx
void encodeInitialize();
void encodeFinish();

// to enable bison parse-time debugging
#if YYDEBUG
extern int yydebug;
#endif

//Global Dump commands
bool before = false;
bool after = false;
bool errors = false;
bool dumpTable = false;

// global string pool
StringPool* stringPool;

// global symbol table
SymbolTable* symbolTable;

// global type module
TypeModule* types;

// helper methods
int parseCommand(char* cmd);
void printUsage(void);

int main(int argc, char* argv[])
{
  //Rudimentary command-line parsing goes here
  if( argc > 1){
    for(int i = 1; i < argc; i++ ){
      if( parseCommand(argv[i]) ){
        printUsage();
        //exit(1);
      }
    }
  }
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
  //encodeInitialize();

  // syntax directed compilation!
  yyparse();


  // generate epilogue code
  //encodeFinish();

  if( dumpTable ){
    symbolTable->dump();
  }
  // cleanup symbol table
  delete symbolTable;

  // cleanup the types
  delete types;

  // cleanup the string pool
  delete stringPool;
}

int parseCommand(char* cmd){
  int err = 0;
  if( !strcmp(cmd,"-before") ){
    before = true;
    //std::cerr << "before flag set to true" << endl;
  }else if( !strcmp(cmd,"-after") ){
    after = true;
    //std::cerr << "after flag set to true" << endl;
  }else if( !strcmp(cmd,"-table") ){
    dumpTable = true;
  }else{
    err = 1;
  }
  return err;
}

void printUsage(void){
  cout << "-before: Dump AST pre-analysis\n"
       << "-after: Dump AST post-analysis\n"
       << "-table: Dump Symbol Table" << endl;
}