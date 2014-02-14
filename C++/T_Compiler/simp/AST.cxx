// Jan 2008
// Abstract Syntax Tree implementation for Simp language
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

AST_Statement::~AST_Statement()
{
}

AST_Statement::AST_Statement()
{
}

AST_Expression::~AST_Expression()
{
}

AST_Expression::AST_Expression()
{
  type = types->noType();
}

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

AST_UnaryOperator::~AST_UnaryOperator()
{
  delete left;
}

AST_UnaryOperator::AST_UnaryOperator(AST_Expression* l)
{
  left = l;
}

AST_IntegerLiteral::~AST_IntegerLiteral()
{
}

AST_IntegerLiteral::AST_IntegerLiteral(int in)
{
  type = types->intType();
  value = in;
}

void AST_IntegerLiteral::dump()
{
  cerr << "IntegerLiteral " << value << " " << type->toString() << endl;
}

AST_Variable::AST_Variable(char* in)
{
  name = in;
}

AST_Variable::~AST_Variable()
{
}

void AST_Variable::dump()
{
  cerr << "Variable " << name << " " << type->toString() << endl;
}

AST_StatementList::AST_StatementList(AST_Statement* s,
  AST_List* l) : AST_List((AST_Node*) s, l)
{
}

AST_StatementList::~AST_StatementList()
{
}

AST_Declaration::AST_Declaration(Type* t, char* n)
{
  type = t;
  name = n;
}

AST_Declaration::~AST_Declaration()
{
}

void AST_Declaration::dump()
{
  cerr << "Declaration " << type->toString() << " " << name << endl;
}

AST_Assignment::AST_Assignment(AST_Expression* l, AST_Expression* r)
{
  lhs = l;
  rhs = r;
}

AST_Assignment::~AST_Assignment()
{
  delete lhs;
  delete rhs;
}

void AST_Assignment::dump()
{
  cerr << "Assignment" << endl;
  lhs->dump();
  rhs->dump();
}


AST_Print::AST_Print(AST_Expression* v)
{
  var = (AST_Expression*) v;
}

AST_Print::~AST_Print()
{
}

void AST_Print::dump()
{
  cerr << "Print" << endl;
  var->dump();
}

AST_Divide::AST_Divide(AST_Expression* l, AST_Expression* r) :
  AST_BinaryOperator(l, r)
{
}

AST_Divide::~AST_Divide()
{
}

void AST_Divide::dump()
{
  cerr << "Divide " << type->toString() << endl;
  left->dump();
  right->dump();
}

AST_Convert::AST_Convert(AST_Expression* l) : AST_UnaryOperator(l)
{
}

AST_Convert::~AST_Convert()
{
}

void AST_Convert::dump()
{
  cerr << "Convert " << type->toString() << endl;
  left->dump();
}

AST_Deref::AST_Deref(AST_Expression* l) : AST_UnaryOperator(l)
{
}

AST_Deref::~AST_Deref()
{
}

void AST_Deref::dump()
{
  cerr << "Deref " << type->toString() << endl;
  left->dump();
}

