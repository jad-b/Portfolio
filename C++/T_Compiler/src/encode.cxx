/**
 * Spring 2013
 * Jeremy Dobbins-Bucklad
 *
 * NOTE: Code generation is not set to occur if compile-time errors are found.
 * This is set through the use of the 'errors' extern'd global variable in
 * main.cxx
 */

#include <stdlib.h>
#include <string>
#include <iostream>
#include <stack>
#include <sstream>
using namespace std;

#include "AST.h"
#include "Type.h"

// global type module is in main.cxx
extern TypeModule* types;

// label generation method for unique labels
string generateLabel();
// stack for tracking labels
struct labelPair{
  string label_1;
  string label_2;
};
// std library stack
stack<labelPair> labelStack;

string generateLabel(){
  static int labelCtr = 1;
  string lbl ("L"); // All labels are in the format L#
  stringstream ss;
  ss << labelCtr++;
  lbl += ss.str();

  return lbl;
}

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

void AST_MainFunction::encode(){
  cout << "#\tMainFunction Prologue\n";
  cout << "\t.text\n";
  cout << "\t.align\t4\n";
  cout << "\t.globl\tmain\n";
  cout << "main:\n";
  cout << "\tpushl\t%ebp\n";
  cout << "\tmovl\t%esp, %ebp\n";

  stmtList->encode();

  cout << "#\tMainFunction Epilogue\n";
  cout << "main$exit:\n";
  cout << "\tpopl\t%ebp\n";
  cout << "\tret\n";

}

// Declaration
void AST_Declaration::encode(){

  cout << "#\tDeclaration\n";
  cout << "\t.data\n";
  varList->encode();
  cout << "\t.text\n";
}

//VarList
void AST_VarList::encode(){
  cout << "#\tVariableList\n";
  cout << "mainvar$" << ((AST_Variable*)item)->name << ":\t.long 0\n";
  if (restOfList != NULL) restOfList->encode();
}

//Integer literal
void AST_IntegerLiteral::encode()
{
  cout << "#\tIntegerLiteral\n";
  cout << "\tpushl\t$" << value << endl;
}

// Variable
void AST_Variable::encode()
{
  cout << "#\tMain Variable\n";
  cout << "\tpushl\t$mainvar$" << name << endl;
}

//Out Statement
void AST_OutStatement::encode()
{
  var->encode();

  if (var->type == types->intType())
  {
    cout << "#\tOut Statement\n";
    cout << "\tcall\tRTS_outputInteger\n";
    cout << "\taddl\t$4, %esp\n";
  }else  {
    cerr << "AST_OutStatement:encode:"<<line<<":ERROR: unknown type\n";
    exit(-1);
  }
}

// Expression Statement
void AST_ExpressionStatement::encode(){
  var->encode();
  cout << "#\tExpressionStatement\n";
  cout << "\taddl\t $4, %esp\n";
}

// Assignment
void AST_Assignment::encode()
{
  left->encode();
  right->encode();

  cout << "#\tAssignment (=)\n";
  cout << "\tpopl\t%eax\n";
  cout << "\tpopl\t%edx\n";
  cout << "\tmovl\t%eax, (%edx)\n";
  cout << "\tpushl\t%eax\n";
}

// EqualityExpression
void AST_EqualityExpression::encode(){
  left->encode();
  right->encode();

  if (type == types->intType()){
    cout << "#\tEqualityExpression (==)\n";
    cout << "\tpopl\t%eax\n";
    cout << "\tpopl\t%edx\n";
    cout << "\tcmpl\t%eax,%edx\n";
    cout << "\tsete\t%al\n";
    cout << "\tmovzbl\t%al, %eax\n";
    cout << "\tpushl\t%eax\n";
  }else{
    cerr << "AST_EqualityExpression:encode:" << line << ":ERROR: unexpected type\n";
    exit(-1);
  }
}

//Less Than
void AST_LessThan::encode(){
  left->encode();
  right->encode();

  if (type == types->intType()){
    cout << "#\tLessThan (<) int\n";
    cout << "\tpopl\t%eax\n";
    cout << "\tpopl\t%edx\n";
    cout << "\tcmpl\t%eax,%edx\n";
    cout << "\tsetl\t%al\n";
    cout << "\tmovzbl\t%al, %eax\n";
    cout << "\tpushl\t%eax\n";
  }else{
    cerr << "AST_LessThan:encode:" << line << ":ERROR: unexpected type\n";
    exit(-1);
  }
}

// GreaterThan
void AST_GreaterThan::encode(){
  left->encode();
  right->encode();

  if (type == types->intType()){
    cout << "#\tGreaterThan (>)\n";
    cout << "\tpopl\t%eax\n";
    cout << "\tpopl\t%edx\n";
    cout << "\tcmpl\t%eax,%edx\n";
    cout << "\tsetg\t%al\n";
    cout << "\tmovzbl\t%al, %eax\n";
    cout << "\tpushl\t%eax\n";
  }else{
    cerr << "AST_GreaterThan:encode:" << line << ":ERROR: unexpected type\n";
    exit(-1);
  }
}

void AST_Multiply::encode(){
  left->encode();
  right->encode();

  if (type == types->intType()){
    cout << "#\tMultiply int (*)\n";
    cout << "\tpopl\t%eax\n";
    cout << "\tpopl\t%edx\n";
    cout << "\timull\t%edx, %eax\n";
    cout << "\tpushl\t%eax\n";
  }else{
    cerr << "AST_Multiply:encode:" << line << ":ERROR: unexpected type\n";
    exit(-1);
  }
}

//Divide
void AST_Divide::encode()
{
  left->encode();
  right->encode();

  string l1 = generateLabel();
  string l2 = generateLabel();

  if (type == types->intType()){
    cout << "#\tDivide int\n";
    cout << "\tpopl\t%ecx\n";
    cout << "\tcmpl\t$0, %ecx\n";
    cout << "\tje\t" << l1 << "\n";
    cout << "\tpopl\t%eax\n";
    cout << "\tcltd\n";
    cout << "\tidivl\t%ecx, %eax\n";
    cout << "\tpushl\t%eax\n";
    cout << "\tjmp\t" << l2 << "\n";
    cout << l1 << ":\n";
    cout << "\tpushl $" << line << "\n";
    cout << "\tcall\tRTS_printDivideByZeroError\n";
    cout << l2 << ":\n";
  }else{
    cerr << "AST_Divide:encode:" << line << ":ERROR: unexpected type\n";
    exit(-1);
  }
}

//Add
void AST_Add::encode(){
  left->encode();
  right->encode();

  if (type == types->intType()){
    cout << "#\tAdd (binary +) int\n";
    cout << "\tpopl\t%edx\n";
    cout << "\tpopl\t%eax\n";
    cout << "\taddl\t%edx, %eax\n";
    cout << "\tpushl\t%eax\n";
  }else if (type == types->errorType()){
    // do nothing: there was a semantic error
  }else{
    cerr << "AST_Add:encode:" << line << ":ERROR: unexpected type\n";
    exit(-1);
  }
}

// Subtract
void AST_Subtract::encode(){
  left->encode();
  right->encode();

  if (type == types->intType()){
    cout << "#\tSubtract (binary -) int\n";
    cout << "#\tAdd int\n";
    cout << "\tpopl\t%edx\n";
    cout << "\tpopl\t%eax\n";
    cout << "\tsubl\t%edx, %eax\n";
    cout << "\tpushl\t%eax\n";
  }else if (type == types->errorType()){
    // do nothing: there was a semantic error
  }else{
    cerr << "AST_Subtract:encode:" << line << ":ERROR: unexpected type\n";
    exit(-1);
  }
}

// Logical Not
void AST_LogicalNot::encode(){
  left->encode();

  if (type == types->intType()){
    cout << "#\tLogical Complement (!)  [(!i) --> (i == 0)]\n";
    cout << "\tpopl\t%eax\n";
    cout << "\tcmpl\t$0,%eax\n";
    cout << "\tsete\t%al\n";
    cout << "\tmovzbl\t%al, %eax\n";
    cout << "\tpushl\t%eax\n";
  }else if (type == types->errorType()){
    // do nothing: there was a semantic error
  }else{
    cerr << "AST_LogicalNot:encode:" << line << ":ERROR: unexpected type\n";
    exit(-1);
  }


}

//Negate
void AST_Negate::encode(){
  left->encode();

  if (type == types->intType()){
    cout << "#\tNegate (unary -)\n";
    cout << "\tpopl\t%eax\n";
    cout << "\tnegl\t%eax\n";
    cout << "\tpushl\t%eax\n";
  }else if (type == types->errorType()){
    // do nothing: there was a semantic error
  }else{
    cerr << "AST_Negate:encode:" << line << ":ERROR: unexpected type\n";
    exit(-1);
  }
}

//Convert: A relic of a previous language
void AST_Convert::encode()
{
  left->encode();

  if (type == types->intType())
  {
    cout << "#\tConvert to int <---THIS SHOULD NEVER BE CALLED\n";

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

//Deref
void AST_Deref::encode()
{
  left->encode();

  // both types are 32 bits so no need to distinguish types here?
  cout << "#\tDeref\n";
  cout << "\tpopl\t%eax\n";
  cout << "\tmovl\t(%eax), %eax\n";
  cout << "\tpushl\t%eax\n";
}

// Block
void AST_Block::encode(){
  //Recursively call encode on all sub-statements
  cout << "#\tBlock\n";
  if( stmtList )
    stmtList->encode();
}

// emptyStatementT
void AST_EmptyStatement::encode(){/*do nothing*/}

// if (exp) stmt1 else stmt2
void AST_IfThenElseStatement::encode(){
  string l1 = generateLabel();
  string l2 = generateLabel();

  cout << "#\tIf-Then-Else\n";
  ifExp->encode();
  cout << "\tpopl\t%eax\n";
  cout << "\tcmpl\t$0, %eax\n";
  cout << "\tje\t" << l1 << "\n";
  thenStmt->encode();
  cout << "\tjmp\t" << l2 << "\n";
  cout << l1 << ":\n";
  elseStmt->encode();
  cout << l2 << ":\n";
}

// while (exp) stmt
void AST_WhileStatement::encode(){
  string l1 = generateLabel();
  string l2 = generateLabel();
  //Store label names in labelPair struct for organization
  labelPair pair;
  pair.label_1 = l1;
  pair.label_2 = l2;
  //Push struct onto stack
  labelStack.push(pair);

  cout << "#\tWhile Statement\n";
  cout << l1 << ":\n";
  ifExp->encode();
  cout << "\tpopl\t%eax\n";
  cout << "\tcmpl\t$0, %eax\n";
  cout << "\tje\t" << l2 << "\n";
  bodyStmt->encode();
  //cout << "#\t WHILE STATEMENT RETURNED\n";
  labelStack.pop(); // Pop struct from stack
  cout << "\tjmp\t" << l1 << "\n";
  cout << l2 << ":\n";
}

// TODO Replace main$exit with appropriate label
void AST_ReturnStatement::encode(){
  if( exp ){
    cout << "#\tReturn <exp>\n";
    exp->encode();
    cout << "\tpopl\t%eax\n";
    cout << "\tjmp\tmain$exit\n";
  }
  //   where LABEL is a label immediately preceding the epilogue code for the
  //   main function or the enclosing method. (Note: we will not do methods
  //   until later.)
  else{
    cout << "#\tReturn\n";
    cout << "\tjmp\tmain$exit\n";
  }
//   where LABEL is a label immediately preceding the epilogue code for the
//   enclosing constructor or destructor. (Note: we will not do constructors
//   and destructors until later.)
}

void AST_BreakStatement::encode(){
  cout << "#\tBreak\n";
  string jump_label = labelStack.top().label_2;
  cout << "\tjmp\t" << jump_label << "\n";
//   where LABEL is the exit label for the closest enclosing while loop,
//   ie L2 in the above code for while loop.
}

void AST_ContinueStatement::encode(){
  cout << "#\tContinue\n";
  string continue_label = labelStack.top().label_1;
  cout << "\tjmp\t" << continue_label << "\n";
//   where LABEL is the continue label for the closest enclosing while loop,
//   ie L1 in the above code for while loop.
}

