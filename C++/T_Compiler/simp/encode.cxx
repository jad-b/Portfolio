// Jan 2008
// AST methods for code generation

#include <stdlib.h>

#include <iostream>
using namespace std;

#include "AST.h"
#include "Type.h"

// global type module is in main.cxx
extern TypeModule* types;

// output the prelude code
void encodeInitialize()
{
  cout << "#\tPrologue\n";
  cout << "\t.text\n";
  cout << "\t.globl\tmain\n";
  cout << "\tmain:\n";
  cout << "\tpushl\t%ebp\n";
  cout << "\tmovl\t%esp, %ebp\n";
}

// output the epilogue code
void encodeFinish()
{
  cout << "#\tEpilogue\n";
  cout << "\tpopl\t%ebp\n";
  cout << "\tret\n";
  cout << "\t.data\n";
}

void AST_List::encode()
{
  item->encode();
  if (restOfList != NULL) restOfList->encode();
}

void AST_IntegerLiteral::encode()
{
  cout << "#\tIntegerLiteral\n";
  cout << "\tpushl\t$" << value << endl;
}

void AST_Variable::encode()
{
  cout << "#\tVariable\n";
  cout << "\tpushl\t$" << name << endl;
}

void AST_Declaration::encode()
{
  cout << "#\tDeclaration\n";
  cout << "\t.data\n";
  cout << "\t.comm\t" << name << ", 4\n";
  cout << "\t.text\n";
}

void AST_Assignment::encode()
{
  lhs->encode();
  rhs->encode();

  cout << "#\tAssignment\n";
  cout << "\tpopl\t%eax\n";
  cout << "\tpopl\t%edx\n";
  cout << "\tmovl\t%eax, (%edx)\n";
}

void AST_Print::encode()
{
  var->encode();

  if (var->type == types->intType())
  {
    cout << "#\tPrint int\n";
    cout << "\tcall\tSIMP_RT_printInt\n";
    cout << "\taddl\t$4, %esp\n";
  }
  else if (var->type == types->floatType())
  {
    cout << "#\tPrint float\n";
    cout << "\tcall\tSIMP_RT_printFloat\n";
    cout << "\taddl\t$4, %esp\n";
  }
  else if (var->type == types->errorType())
  {
    // do nothing: there was a semantic error
  }
  else
  {
    cerr << line << ": BUG in AST_Print::encode: unknown type\n";
    exit(-1);
  }
}

void AST_Divide::encode()
{
  left->encode();
  right->encode();

  if (type == types->intType())
  {
    cout << "#\tDivide int\n";
    cout << "\tpopl\t%ecx\n";
    cout << "\tpopl\t%eax\n";
    cout << "\tcltd\n";
    cout << "\tidivl\t%ecx, %eax\n";
    cout << "\tpushl\t%eax\n";
  }
  else if (type == types->floatType())
  {
    cout << "#\tDivide float\n";
    cout << "\tflds\t(%esp)\n";
    cout << "\taddl\t$4, %esp\n";
    cout << "\tflds\t(%esp)\n";
    cout << "\tfdivp\n";
    cout << "\tfstps\t(%esp)\n";
  }
  else if (type == types->errorType())
  {
    // do nothing: there was a semantic error
  }
  else
  {
    cerr << line << ": BUG in AST_Divide::encode: unexpected type\n";
    exit(-1);
  }
}

void AST_Convert::encode()
{
  left->encode();

  if (type == types->intType())
  {
    cout << "#\tConvert to int\n";

    // load value into fp register
    cout << "\tflds\t(%esp)\n";

    // set rounding mode to truncate
      // store fp control word in first word
      cout << "\tfnstcw\t(%esp)\n";
      // put control word in %ax
      cout << "\tmovw\t(%esp), %ax\n";
      // set RC bits to "truncate"
      cout << "\tmovb\t$12, %ah\n";
      // put modified control word in 2nd slot
      cout << "\tmovw\t%ax, 2(%esp)\n";
      // load modified control word
      cout << "\tfldcw\t2(%esp)\n";
      // put old control word in %ax
      cout << "\tmovw\t(%esp), %ax\n";

    // convert value to signed int
    cout << "\tfistpl\t(%esp)\n";

    // re-establish old fp control word */
      // alloc one word on top of stack
        cout << "\tsubl\t$2, %esp\n";
      // put original cntrl word on stack
        cout << "\tmovw\t%ax, (%esp)\n";
      // re-load original control word
        cout << "\tfldcw\t(%esp)\n";
     // free word on top of stack
        cout << "\taddl\t$2, %esp\n";
  }
  else if (type == types->floatType())
  {
    cout << "#\tConvert to float\n";
    cout << "\tfildl\t(%esp)\n";
    cout << "\tfstps\t(%esp)\n";
  }
  else
  {
    cerr << line << ": BUG in AST_Convert::encode: unexpected type\n";
    exit(-1);
  }
}

void AST_Deref::encode()
{
  left->encode();

  // both types are 32 bits so no need to distinguish types here?
  cout << "#\tDeref\n";
  cout << "\tpopl\t%eax\n";
  cout << "\tmovl\t(%eax), %eax\n";
  cout << "\tpushl\t%eax\n";
}
