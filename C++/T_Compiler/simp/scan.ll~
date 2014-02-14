%{

// Jan 2008
// scanner for the Simp language

// If the preprocessor symbol DEBUG is defined then the scanner
// can be built in stand-alone mode, to allow the scanner to be
// tested independently of the parser.
//
// See the Makefile target "lexdbg" for how to build the stand-alone
// scanner.
//
// To run it: % lexdbg <input
//
// It will write the tokens, one per line, to stdout.

#include <iostream>
using namespace std;

#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "AST.h"
#include "StringPool.h"
#include "y.tab.h"

// need to use the global string pool from main.cxx
extern StringPool* stringPool;

// local prototypes
static int a2int(char *);
static char* stashIdentifier(char *);

// scanner tracks the current line number
static int sourceLineNumber = 1;
int getCurrentSourceLineNumber();

// following supports the stand-alone scanner program: lexdbg
#ifdef DEBUG

#define token(x) (displayToken((char *) # x),  x)
YYSTYPE yylval;
int displayToken (char *);

#else

#define token(x) x

#endif

%}

hexdigit        [0-9A-Fa-f]
letter          [A-Za-z]
identifier      {letter}({letter}|[_]|[0-9])*


%%


[ \t]                    {
                           // do nothing: whitespace discarded
                         }

[\n]                     {
                           // just advance the line number then discard newline
                           sourceLineNumber += 1;
                         }

([0-9])+                 {
                           yylval.value = a2int(yytext);
                           return token(INTEGER_LITERAL);
                         }

0x{hexdigit}+            {
                           yylval.value = a2int(yytext);
                           return token(INTEGER_LITERAL);
                         }

int                      {
                           return token(INT);
                         }

float                    {
                           return token(FLOAT);
                         }

print                    {
                           return token(PRINT);
                         }

{identifier}             {
                           yylval.str = stashIdentifier(yytext);
                           return token(IDENTIFIER);
                         }

[/]                      {
                           return token('/');
                         }

[=]                      {
                           return token('=');
                         }

[;]                      {
                           return token(';');
                         }

[(]                      {
                           return token('(');
                         }

[)]                      {
                           return token(')');
                         }

.                        {
                           return token(BAD);
                         }

%%

int yywrap(void) {
  return 1;
}


/*
 * Convert from ascii hex to an integer.
 */
static int a2int(char *tptr)
{
  unsigned long long unsigned_long_long_tmp;
  int int_tmp;
  unsigned long long unsigned_long_long_tmp2;

  // errno used to detect overflow of long long
  errno = 0;
  unsigned_long_long_tmp = strtoull(tptr, NULL, 0);
  if (errno)
  {
    cerr << sourceLineNumber << ": integer literal too large\n";
    return 0;
  }

  // check now if value will fit in int
  int_tmp = unsigned_long_long_tmp;
  unsigned_long_long_tmp2 = int_tmp;
  if (unsigned_long_long_tmp != unsigned_long_long_tmp2)
  {
    cerr << sourceLineNumber << ": integer literal too large\n";
    return 0;
  }

  return int_tmp;
}

// identifier is now in yytext, which will soon be re-used
// so allocate a safe place for the string in the string pool
static char* stashIdentifier(char *str)
{
  char *tmp;

  tmp = stringPool->newString(str);

  return tmp;
}

// provide the AST routines access to the line number
int getCurrentSourceLineNumber()
{
  return sourceLineNumber;
}

// following supports the stand-alone scanner program: lexdbg
#ifdef DEBUG
StringPool* stringPool;

int main()
{
  stringPool = new StringPool();

  while (yylex());

  return 0;
}

int displayToken(char *p)
{
  cout << p << " is " << yytext << '\n';
  return 1;
}
#endif

