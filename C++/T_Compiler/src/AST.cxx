// Spring 13
// Abstract Syntax Tree implementation for T language
//
// semantic analysis methods are in analyze.cxx

#include <iostream>
using namespace std;

#include "AST.h"
#include "Type.h"

// this routine is in scan.ll
int getCurrentSourceLineNumber();

// global type module is in main.cxx
extern TypeModule* types;

/********************AST_Node********************/
AST_Node::AST_Node()
{
  // by default get the current line number in the scanner
  line = getCurrentSourceLineNumber();
}

AST_Node::~AST_Node()
{
}

void AST_Node::setLineNumber(int lineNumber)
{
  line = lineNumber;
}

int AST_Node::getLineNumber()
{
  return line;
}

/********************AST_List********************/
AST_List::AST_List(AST_Node* newItem, AST_List* list)
{
  item = newItem;
  restOfList = list;
}

AST_List::~AST_List()
{
  delete item;
  if (restOfList != NULL) delete restOfList;
}

void AST_List::dump()
{
  cerr << "List Item\n";
  item->dump();
  if (restOfList != NULL) restOfList->dump();
  else cerr << "End of List\n";
}

/********************AST_Statement********************/
AST_Statement::~AST_Statement()
{
}

AST_Statement::AST_Statement()
{
  bitflags = 0;
}

/********************AST_Expression********************/
AST_Expression::~AST_Expression()
{
}

AST_Expression::AST_Expression()
{
  type = types->noType();   //Default no-type constructor
}

/********************AST_BinaryOperator********************/
AST_BinaryOperator::~AST_BinaryOperator()
{
  delete left;
  delete right;
}

AST_BinaryOperator::AST_BinaryOperator(AST_Expression* l, AST_Expression* r)
{
  left = l;
  right = r;
}

/********************AST_UnaryOperator********************/
AST_UnaryOperator::~AST_UnaryOperator()
{
  delete left;
}

AST_UnaryOperator::AST_UnaryOperator(AST_Expression* l)
{
  left = l;
}
/*=============================================================*/
/*===================End of Abstract Classes===================*/
/*=============================================================*/

/********************AST_Program********************/
AST_Program::~AST_Program(){}

AST_Program::AST_Program(AST_Node* item, AST_List* restOfList)
            :AST_List(item,restOfList){}

void AST_Program::dump(){
  cerr << line << ":Program:\n";
  item->dump();
  if (restOfList != NULL) restOfList->dump();
  else cerr << "End of Program\n";
}

/********************AST_StatementList********************/
AST_StatementList::AST_StatementList(AST_Statement* s,AST_List* l)
                  : AST_List((AST_Node*) s, l)
{
}

AST_StatementList::~AST_StatementList()
{
}

void AST_StatementList::dump(){
  cerr << line << ":Statement List:\n";
  item->dump();
  if (restOfList != NULL) restOfList->dump();
  else cerr << "End of Statement List\n";
}

/********************AST_MainFunction********************/
AST_MainFunction::~AST_MainFunction(){
  delete stmtList;
}

AST_MainFunction::AST_MainFunction(AST_StatementList* list){
  stmtList = list;
}

void AST_MainFunction::dump(){
    cerr << line << ":MainFunction" << endl;
    stmtList->dump();
}

/********************AST_Variable********************/
AST_Variable::~AST_Variable(){
  delete name;
}

AST_Variable::AST_Variable(char *id){
  name = id;
}

void AST_Variable::dump(){
  cerr << line << ":Variable " << name << " " << type->toString() <<  endl;
}

/********************AST_VarList********************/
AST_VarList::~AST_VarList(){}

AST_VarList::AST_VarList(AST_Expression* variable, AST_VarList* restOfList):
                        AST_List((AST_Node*) variable, (AST_List*) restOfList){}

void AST_VarList::dump(){
  cerr << line << ":VarList:\n";
  item->dump();
  if (restOfList != NULL) restOfList->dump();
  else cerr << "End of VarList\n";
}

/********************AST_Declaration********************/
AST_Declaration::~AST_Declaration(){
  delete varList;
}

AST_Declaration::AST_Declaration(Type* t, AST_VarList* list){
  type = t;
  varList = list;
  //list->type = type;
}

void AST_Declaration::dump(){
  cerr << line << ":Declaration " << type->toString() << " " << endl;
  varList->dump();
}

/********************AST_ExpressionStatement********************/
AST_ExpressionStatement::AST_ExpressionStatement(AST_Expression* exp){
  var = exp;
}

AST_ExpressionStatement::~AST_ExpressionStatement(){
  delete var;
}

void AST_ExpressionStatement::dump()
{
  cerr << line << ":ExpressionStatement " << endl;
  var->dump();
}

/********************AST_OutStatement********************/
AST_OutStatement::~AST_OutStatement()
{
  delete var;
}

AST_OutStatement::AST_OutStatement(AST_Expression* v)
{
  var = (AST_Expression*) v;
}

void AST_OutStatement::dump(){
  cerr << line << ":Out" << endl;
  var->dump();
}

/********************AST_IntegerLiteral********************/
AST_IntegerLiteral::~AST_IntegerLiteral(){}

AST_IntegerLiteral::AST_IntegerLiteral(int in)
{
  type = types->intType();
  value = in;
  isChildOfNegate = false;
}

void AST_IntegerLiteral::dump()
{
  cerr << line << ":IntegerLiteral " << value << " " << type->toString() <<
endl;
}
/********************AST_Assignment********************/
AST_Assignment::~AST_Assignment(){
  //I wonder if the default binary operator dtor will take care of this?
  //AST_Divide would say so. ~AST_BinaryOperator should be called right
  //after this exits
}

AST_Assignment::AST_Assignment(AST_Expression* lhs, AST_Expression* rhs):
                AST_BinaryOperator(lhs,rhs){}
//Call the BinOp ctor do the work

void AST_Assignment::dump()
{
  cerr << line << ":Assignment " << type->toString() << endl;
  left->dump();
  right->dump();
}

/********************AST_EqualityExpression*******************/
AST_EqualityExpression::AST_EqualityExpression(AST_Expression* lhs, AST_Expression* rhs)
                        :AST_BinaryOperator(lhs,rhs){};

AST_EqualityExpression::~AST_EqualityExpression(){};

void AST_EqualityExpression::dump(){
  cerr << line << ":EqualityExp " << type->toString() << endl;
  left->dump();
  right->dump();
}

/********************AST_LessThan*******************/
AST_LessThan::AST_LessThan(AST_Expression* left, AST_Expression* right)
  :AST_BinaryOperator(left,right){};

AST_LessThan::~AST_LessThan(){}

void AST_LessThan::dump(){
  cerr << line << ":LessThan " << type->toString() << endl;
  left->dump();
  right->dump();
}

/********************AST_GreaterThan*******************/
AST_GreaterThan::AST_GreaterThan(AST_Expression* left, AST_Expression* right)
:AST_BinaryOperator(left,right){};

AST_GreaterThan::~AST_GreaterThan(){}

void AST_GreaterThan::dump(){
  cerr << line << ":GreaterThan " << type->toString() << endl;
  left->dump();
  right->dump();
}

/********************AST_Add*******************/
AST_Add::AST_Add(AST_Expression* left, AST_Expression* right)
:AST_BinaryOperator(left,right){};

AST_Add::~AST_Add(){}

void AST_Add::dump(){
  cerr << line << ":Add " << type->toString() << endl;
  left->dump();
  right->dump();
}

/********************AST_Subtract*******************/
AST_Subtract::AST_Subtract(AST_Expression* left, AST_Expression* right)
:AST_BinaryOperator(left,right){};

AST_Subtract::~AST_Subtract(){}

void AST_Subtract::dump(){
  cerr << line << ":Subtract  " << type->toString() << endl;
  left->dump();
  right->dump();
}

/********************AST_Multiply*******************/
AST_Multiply::AST_Multiply(AST_Expression* left, AST_Expression* right)
:AST_BinaryOperator(left,right){};

AST_Multiply::~AST_Multiply(){}

void AST_Multiply::dump(){
  cerr << line << ":Multiply " << type->toString() << endl;
  left->dump();
  right->dump();
}

/********************AST_Divide********************/
AST_Divide::AST_Divide(AST_Expression* l, AST_Expression* r) :
  AST_BinaryOperator(l, r){}

AST_Divide::~AST_Divide(){}

void AST_Divide::dump()
{
  cerr << line << ":Divide " << type->toString() << endl;
  left->dump();
  right->dump();
}

/********************AST_LogicalNot*******************/
AST_LogicalNot::AST_LogicalNot(AST_Expression* left)
                :AST_UnaryOperator(left){};

AST_LogicalNot::~AST_LogicalNot(){}

void AST_LogicalNot::dump(){
  cerr << line << ":LogicalNot " << type->toString() << endl;
  left->dump();
}

/********************AST_Negate*******************/
AST_Negate::AST_Negate(AST_Expression* left)
           :AST_UnaryOperator(left){
  AST_IntegerLiteral* ptr = (AST_IntegerLiteral*) left;
  if( ptr ){ // IF pointer exists, we've got an Int_Literal
    ptr->isChildOfNegate = true; //Flip flag
  }
};

AST_Negate::~AST_Negate(){}

void AST_Negate::dump(){
  cerr << line << ":Negate " << type->toString() << endl;
  left->dump();
}

/********************AST_Convert********************/
AST_Convert::AST_Convert(AST_Expression* l) : AST_UnaryOperator(l)
{
}

AST_Convert::~AST_Convert()
{
}

void AST_Convert::dump()
{
  cerr << line << ":Convert " << type->toString() << endl;
  left->dump();
}

/********************AST_Deref********************/
AST_Deref::AST_Deref(AST_Expression* l) : AST_UnaryOperator(l)
{
}

AST_Deref::~AST_Deref()
{
}

void AST_Deref::dump()
{
  cerr << line << ":Deref " << type->toString() << endl;
  left->dump();
}

/********************Phase 2********************/
/***********************************************/
/********************AST_Block********************/
AST_Block::AST_Block(AST_StatementList* sl){
  stmtList = sl;
}
AST_Block::~AST_Block(){
  delete stmtList;
}

void AST_Block::dump(){
  cerr << line << ":Block" << endl;
  if( stmtList ){
    stmtList->dump();
  }
}


/********************AST_IfThenElseStatement********************/
AST_IfThenElseStatement::AST_IfThenElseStatement(AST_Expression* pe,
  AST_Statement* tS, AST_Statement* eS){
    ifExp = pe;
    thenStmt = tS;
    elseStmt = eS;
  }
AST_IfThenElseStatement::~AST_IfThenElseStatement(){
  delete ifExp;
  delete thenStmt;
  delete elseStmt;
}

void AST_IfThenElseStatement::dump(){
  cerr << line << ":If-then-Else" << endl;
  ifExp->dump();
  thenStmt->dump();
  elseStmt->dump();
}

/********************AST_EmptyStatement********************/
AST_EmptyStatement::AST_EmptyStatement(){}
AST_EmptyStatement::~AST_EmptyStatement(){}

void AST_EmptyStatement::dump(){
  cerr << line << ":EmptyStatement" << endl;
}

/********************AST_WhileStatement********************/
AST_WhileStatement::AST_WhileStatement(AST_Expression* e, AST_Statement* s){
  ifExp = e;
  bodyStmt = s;
  bitflags = 0x8;
}
AST_WhileStatement::~AST_WhileStatement(){
  delete ifExp;
  delete bodyStmt;
}
void AST_WhileStatement::dump(){
  cerr << line << ":While" << endl;
  ifExp->dump();
  bodyStmt->dump();
}

/********************AST_ReturnStatement********************/
AST_ReturnStatement::AST_ReturnStatement(AST_Expression* e){
  exp = e;
}
AST_ReturnStatement::~AST_ReturnStatement(){
  delete exp;
}

void AST_ReturnStatement::dump(){
  cerr << line << ":Return" << endl;
  exp->dump();
}

/********************AST_BreakStatement********************/
AST_BreakStatement::AST_BreakStatement(){}
AST_BreakStatement::~AST_BreakStatement(){}

void AST_BreakStatement::dump(){
  cerr << line << ":Break" << endl;
}

/********************AST_ContinueStatement********************/
AST_ContinueStatement::AST_ContinueStatement(){}
AST_ContinueStatement::~AST_ContinueStatement(){}

void AST_ContinueStatement::dump(){
  cerr << line << ":Continue" << endl;
}

/********************Phase 3********************/
/**********************************************/

/********************Phase 4********************/
/**********************************************/