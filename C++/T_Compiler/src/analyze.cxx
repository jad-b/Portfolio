/**
 * Spring 2013
 * Jeremy Dobbins-Bucklad
 * The TC Compiler
 */

#include <iostream>
#include <stack>
#include <string>
using namespace std;

#include "AST.h"
#include "SymbolTable.h"
#include "Type.h"

// global symbol table is in main.cxx
extern SymbolTable* symbolTable;

// global type module is in main.cxx
extern TypeModule* types;

// global bool for compile-time errors in main.cxx
extern bool errors;

// global int counter for tracking while loops
static int whileCounter= 0;

// global value for maximum integer value
static long long INT_LIT_MAX = 2147483648;


AST_Node* AST_List::analyze()
{
  item = item->analyze();
  if (restOfList != NULL) restOfList = (AST_List*) restOfList->analyze();
  return (AST_Node*) this;
}

AST_Node* AST_StatementList::analyze(unsigned int bits){
  ((AST_Statement*)item)->bitflags |= bits; // OR bits to existing bitflags

  item = item->analyze();
  if (restOfList != NULL) restOfList = (AST_List*)((AST_StatementList*)
restOfList)->analyze(bits);
  return (AST_Node*) this;
}

AST_Node* AST_MainFunction::analyze(){
  stmtList->analyze(0x1); // inside the main block
  return (AST_Node*) this;
}

AST_Node* AST_Declaration::analyze(){
  //Pass type into VarList through analyze()
  varList->analyze(type);
  return (AST_Node*) this;
}

// VarList
AST_Node* AST_VarList::analyze(Type* t){
  AST_Variable* var = (AST_Variable*) item;

  //install into symbol table
  if (!symbolTable->install(var->name, t)){
    errors = true;
    cerr << line << ": duplicate declaration for " << var->name << endl;
  }

  // Process remainder of list
  var->analyze();
  if (restOfList != NULL)
    //Convert to VarList for analyze(Type), then cast return back to List
    restOfList = (AST_List*)((AST_VarList*) restOfList)->analyze(t);
  return (AST_Node*) this;
}


AST_Node* AST_Variable::analyze()
{
  Type* typeFromSymbolTable;
  //cerr << "Analyze: " << name << endl;
  if (symbolTable->lookup(name, typeFromSymbolTable)){
    type = typeFromSymbolTable;
    //cerr << "\tVariable is " << name << " " << type->toString() << endl;
  }else{
    errors = true;
    cerr << "AST_Variable: " << line << ": error: " << name << " is not declared\n";
    type = types->errorType();
  }

  // always put Deref node on top of a variable
  // make a new Deref node which contains this variable, cast as an expression
  AST_Expression* ret = (AST_Expression*) new AST_Deref(this);
  // Deref node has same type as Variable
  ret->type = type;

  return (AST_Node*) ret;
}


AST_Node* AST_IntegerLiteral::analyze()
{
  // Check for acceptable usage,i.e. INT_MAX only if a child of negate
  if( !isChildOfNegate && value == INT_LIT_MAX ){
    type = types->errorType();
    errors = true;
    cerr << "AST_IntegerLiteral:" << line << ": error: illegal operation using "
         << "maximum integer value; INT_MAX only legal when negated.\n";
  }
  return (AST_Node*) this;
}


AST_Node* AST_Assignment::analyze()
{
  // analyze the left variable - a Deref node will be put on top
  AST_Deref* deref = (AST_Deref*) left->analyze();

  // strip off the Deref node
  left = deref->left;
  deref->left = NULL;
  delete deref;

  // analyze the expression
  right = (AST_Expression*) right->analyze();

  // check if error was detected in one of the subtrees
  // ie avoid a cascade of error messages
  if ((left->type == types->errorType()) || (right->type == types->errorType()))
  {
    return (AST_Node*) this;
  }

  // add a convert node if the types are not the same
  if (left->type != right->type)
  {
    AST_Expression* newNode = new AST_Convert(right);

    newNode->type = left->type;

    right = newNode;
  }

  type = left->type;
  return (AST_Node*) this;
}


AST_Node* AST_ExpressionStatement::analyze(){
  //Call analyze on assignments
  var->analyze();
  return (AST_Node*) this;
}


AST_Node* AST_OutStatement::analyze()
{
  // analyze the variable - a Deref node will be added
  var = (AST_Expression*) var->analyze();

  if( var->type != types->intType() ){
    errors = true;
    cerr << "AST_OutStatement:analyze:"<<line
         <<": expression is not of type int\n";
  }
  return (AST_Node*) this;
}


AST_Node* AST_EqualityExpression::analyze(){
  // analyze both subtrees
  left = (AST_Expression*) left->analyze();
  right = (AST_Expression*) right->analyze();

  // check for error in either subtree to avoid cascade of errors
  if ((left->type == types->errorType()) || (right->type == types->errorType()))
  {
    type = types->errorType();
    return (AST_Node*) this;
  }

  //Check for int type left, right
  if (left->type != types->intType()){
    errors = true;
    cerr << "AST_EqualityExpression:analyze:" << line << ": left argument not of type int\n";
  }
  if( right->type != types->intType() ){
    errors = true;
    cerr << "AST_EqualityExpression:analyze:" << line << ": right argument not of type int\n";
  }

  type = types->intType();

  return (AST_Node*) this;
}


AST_Node* AST_LessThan::analyze(){
  // analyze both subtrees
  left = (AST_Expression*) left->analyze();
  right = (AST_Expression*) right->analyze();

  // check for error in either subtree to avoid cascade of errors
  if ((left->type == types->errorType()) || (right->type == types->errorType()))
  {
    type = types->errorType();
    return (AST_Node*) this;
  }

  //Check for int type left, right
  if (left->type != types->intType()){
    errors = true;
    cerr << "AST_LessThan:analyze:" << line << ": left argument not of type int\n";
  }
  if( right->type != types->intType() ){
    errors = true;
    cerr << "AST_LessThan:analyze:" << line << ": right argument not of type int\n";
  }

  type = types->intType();

  return (AST_Node*) this;
}


AST_Node* AST_GreaterThan::analyze(){
  // analyze both subtrees
  left = (AST_Expression*) left->analyze();
  right = (AST_Expression*) right->analyze();

  // check for error in either subtree to avoid cascade of errors
  if ((left->type == types->errorType()) || (right->type == types->errorType()))
  {
    type = types->errorType();
    return (AST_Node*) this;
  }

  //Check for int type left, right
  if (left->type != types->intType()){
    errors = true;
    cerr << "AST_GreaterThan:analyze:" << line << ": left argument not of type int\n";
  }
  if( right->type != types->intType() ){
    errors = true;
    cerr << "AST_GreaterThan:analyze:" << line << ": right argument not of type int\n";
  }

  type = types->intType();

  return (AST_Node*) this;
}


AST_Node* AST_Multiply::analyze(){
  // analyze both subtrees
  left = (AST_Expression*) left->analyze();
  right = (AST_Expression*) right->analyze();

  // check for error in either subtree to avoid cascade of errors
  if ((left->type == types->errorType()) || (right->type == types->errorType()))
  {
    type = types->errorType();
    return (AST_Node*) this;
  }

  //Check for int type left, right
  if (left->type != types->intType()){
    errors = true;
    cerr << "AST_Multiply:analyze:" << line << ": left argument not of type int\n";
  }
  if( right->type != types->intType() ){
    errors = true;
    cerr << "AST_Multiply:analyze:" << line << ": right argument not of type int\n";
  }

  type = types->intType();

  return (AST_Node*) this;
}


AST_Node* AST_Divide::analyze()
{
  // analyze both subtrees
  left = (AST_Expression*) left->analyze();
  right = (AST_Expression*) right->analyze();

  // check for error in either subtree to avoid cascade of errors
  if ((left->type == types->errorType()) || (right->type == types->errorType()))
  {
    type = types->errorType();
    return (AST_Node*) this;
  }

  // if types not the same then add a convert node to the int subtree
  // (only two legal types in this language: int and float)
  //Check for int type left, right
  if (left->type != types->intType()){
    errors = true;
    cerr << "AST_Divide:analyze:" << line << ": left argument not of type int\n";
  }
  if( right->type != types->intType() ){
    errors = true;
    cerr << "AST_Divide:analyze:" << line << ": right argument not of type int\n";
  }

  // both types the same at this point
  type = left->type;

  return (AST_Node*) this;
}

AST_Node* AST_Add::analyze(){
  // analyze both subtrees
  left = (AST_Expression*) left->analyze();
  right = (AST_Expression*) right->analyze();

  // check for error in either subtree to avoid cascade of errors
  if ((left->type == types->errorType()) || (right->type == types->errorType()))
  {
    type = types->errorType();
    return (AST_Node*) this;
  }

  //Check for int type left, right
  if (left->type != types->intType()){
    errors = true;
    cerr << line << "AST_Add:analyze:" << line << ": left argument not of type int\n";
  }
  if( right->type != types->intType() ){
    errors = true;
    cerr << line << "AST_Add:analyze:" << line << ": right argument not of type int\n";
  }

  type = types->intType();

  return (AST_Node*) this;
}


AST_Node* AST_Subtract::analyze(){
  // analyze both subtrees
  left = (AST_Expression*) left->analyze();
  right = (AST_Expression*) right->analyze();

  // check for error in either subtree to avoid cascade of errors
  if ((left->type == types->errorType()) || (right->type == types->errorType()))
  {
    type = types->errorType();
    return (AST_Node*) this;
  }

  //Check for int type left, right
  if (left->type != types->intType()){
    errors = true;
    cerr << line << "AST_Subtract:analyze:" << line << ": left argument not of type int\n";
  }
  if( right->type != types->intType() ){
    errors = true;
    cerr << line << "AST_Subtract:analyze:" << line << ": right argument not of type int\n";
  }

  type = types->intType();

  return (AST_Node*) this;
}


AST_Node* AST_LogicalNot::analyze(){
  // analyze both subtrees
  left = (AST_Expression*) left->analyze();

  // check for error in either subtree to avoid cascade of errors
  if ( (left->type == types->errorType()) ){
    type = types->errorType();
    return (AST_Node*) this;
  }

  //Check for int type left, right
  if (left->type != types->intType()){
    errors = true;
    cerr << line << "AST_LogicalNot:analyze:" << line << ": left argument not of type int\n";
    type = types->errorType();
  }else
    type = types->intType();

  return (AST_Node*) this;
}


AST_Node* AST_Negate::analyze(){
  // analyze both subtrees
  left = (AST_Expression*) left->analyze();

  // check for error in either subtree to avoid cascade of errors
  if ( (left->type == types->errorType()) )
  {
    type = types->errorType();
    return (AST_Node*) this;
  }

  //Check for int type left, right
  if (left->type != types->intType()){
    errors = true;
    cerr << line << "AST_Negate:analyze:" << line << ": left argument not of type int\n";
    type = types->errorType();
  }else
    type = types->intType();

  return (AST_Node*) this;
}


AST_Node* AST_Convert::analyze()
{
  // convert node is added in analyze but should never be analyzed itself
  cerr << line << ": BUG in AST_Convert::analyze: should never be called\n";
  errors = true;

  return (AST_Node*) this;
}


AST_Node* AST_Deref::analyze()
{
  // deref node is added in analyze but should never be analyzed itself
  cerr << line << ": BUG in AST_Deref::analyze: should never be called\n";
  errors = true;

  return (AST_Node*) this;
}

/********************Phase 2********************/
/***********************************************/

AST_Node* AST_Block::analyze(){
  if( stmtList )    // Check for null case
    stmtList->analyze(bitflags);

  return (AST_Node*) this;
}

AST_Node* AST_IfThenElseStatement::analyze(){
  ifExp = (AST_Expression*) ifExp->analyze();

  //Pass down bit flags to sub-statements
  thenStmt->bitflags |= bitflags;
  elseStmt->bitflags |= bitflags;

  //Analyze sub-statements
  thenStmt = (AST_Statement*) thenStmt->analyze();
  elseStmt = (AST_Statement*) elseStmt->analyze();

  if( ifExp->type != types->intType() ){
    cerr << "AST_WhileStatement:analyze:"<<line
        <<": expression not of type int\n";
    errors = true;
  }

  return (AST_Node*) this;
}

AST_Node* AST_EmptyStatement::analyze(){
  //Do nothing
  return (AST_Node*) this;
}

// The Expression must have type int, or a compile-time error occurs.
AST_Node* AST_WhileStatement::analyze(){
  whileCounter++;   // entering while loop

  bodyStmt->bitflags |= bitflags;   // OR bitflag for while loop
  ifExp = (AST_Expression*) ifExp->analyze();
  bodyStmt = (AST_Statement*) bodyStmt->analyze();

  whileCounter--;   // exiting while loop

  if( ifExp->type != types->intType() ){
    cerr << "AST_WhileStatement:analyze:"<<line
        <<": expression not of type int\n";
    ifExp->type = types->errorType(); // Set to error type for later checking
    errors = true;
  }
  return (AST_Node*) this;
}

// A return with an expression in a constructor or destructor is a compile-time error.
// A compile-time error occurs if the type of the return expression is not convertible
// by assignment conversion to the return type of the enclosing method, or to int if
// the return statement is in the main block.
// A return statement with no Expression is not allowed in this context and will
// result in a compile-time error.
AST_Node* AST_ReturnStatement::analyze(){
  exp = (AST_Expression*) exp->analyze();

    //Check if in a ctor or dtor w/ an expression
  if( (bitflags & 0x4) == 0x4 ){
    errors = true;
    cerr << "AST_ReturnStatement:analyze:"<<line
    <<": can't have a constructor/destructor return with an expression\n";
  }
  //Check if it's in the main block; all conditions are false
  if( (bitflags & 0x1) == 0x1 ){
    if( exp->type != types->intType() ){    //Main block must be int type
      errors = true;
      cerr << "AST_ReturnStatement:analyze:"<<line
      <<": main block must return an int\n";
    }
  }
  //Check if return matches the return type of the enclosing method
  if( ((bitflags & 0x2) == 0x2) && exp->type != method_return_type ){
    errors = true;
    cerr << "AST_ReturnStatement:analyze:"<<line
    <<": return type does not match method return type\n";
  }
  return (AST_Node*) this;
}

// If no while statement encloses the break statement, a compile-time error occurs.
AST_Node* AST_BreakStatement::analyze(){
  // Check if inside a while loop
  if( whileCounter < 1 ){
    errors = true;
    cerr << "AST_BreakStatement:analyze:"<<line
    <<": break must be inside a while loop\n";
  }
  if( (bitflags & 0x8 ) != 0x8){
    errors = true;
    cerr << "AST_BreakStatement:analyze:"<<line<<
        ": break statement must be enclosed inside a while loop\n";
  }
  return (AST_Node*) this;
}

// If no while statement encloses the continue statement, a compile-time error
// occurs.
AST_Node* AST_ContinueStatement::analyze(){
  // Check if inside a while loop
  if( whileCounter < 1 ){
    errors = true;
    cerr << "AST_ContinueStatement:analyze:"<<line
    <<": continue must be inside a while loop\n";
  }
  if( (bitflags & 0x8) != 0x8 ){
    errors = true;
    cerr << "AST_Continuetatement:analyze:"<<line<<
    ": continue statement must be enclosed inside a while loop\n";
  }
  return (AST_Node*) this;
}

