#ifndef _AST_H
#define _AST_H

// Jan 2008
// Abstract Syntax Tree for Simp language
//
// the dump methods are for debugging - they display the AST to stderr.
//
// the analyze methods perform semantic analysis
//
// the encode methods perform code generation

#include "Type.h"

// abstract class: all AST nodes derived from this
class AST_Node
{
  protected:
    int line;

  public:
    virtual ~AST_Node();
 
    virtual void dump() = 0;
  
    virtual AST_Node* analyze() = 0;
    virtual void encode() = 0;
  
    // set the line number of the node
    virtual void setLineNumber( int );

    // get the line number of the node
    virtual int getLineNumber();

  protected:
    AST_Node();
};

// abstract class: all list nodes derived from this
class AST_List: public AST_Node
{
  protected:
    AST_Node* item;
    AST_List* restOfList;
    
  public:
    virtual ~AST_List();
 
    // default behavior for lists: recurse left, then recurse right
    virtual void dump();
    virtual AST_Node* analyze();
    virtual void encode();
  
  protected:
    AST_List(AST_Node* newItem, AST_List* list);
};

// abstract class: all statements derived from this
class AST_Statement: public AST_Node
{
  public:
    virtual ~AST_Statement();
 
  protected:
    AST_Statement();
};

// abstract class: all expression nodes dervived from this
class AST_Expression: public AST_Node
{
  public:
    virtual ~AST_Expression();

    Type* type;

  protected:
    AST_Expression();
};

// abstract class: all binary operation expression nodes derived from this
class AST_BinaryOperator: public AST_Expression
{
  public:
    virtual ~AST_BinaryOperator();
    AST_Expression* left;
    AST_Expression* right;

  protected:
    AST_BinaryOperator(AST_Expression* l, AST_Expression* r);
};

// abstract class: all unary operation expression nodes dervived from this
class AST_UnaryOperator: public AST_Expression
{
  public:
    virtual ~AST_UnaryOperator();
    AST_Expression* left;

  protected:
    AST_UnaryOperator(AST_Expression* l);
};

// variable
class AST_Variable: public AST_Expression
{
  protected:
    char* name;

  public:
    ~AST_Variable();
    AST_Variable(char *id);

    void dump();
    AST_Node* analyze();
    void encode();
};

// integer literal
class AST_IntegerLiteral: public AST_Expression
{
  protected:
    int value;
  public:
    ~AST_IntegerLiteral();
    AST_IntegerLiteral(int in);

    void dump();
    AST_Node* analyze();
    void encode();
};

// list of statements
class AST_StatementList: public AST_List
{
  public:
    ~AST_StatementList();
    AST_StatementList(AST_Statement* statement, AST_List* restOfList);
 
    // inherit default behavior for dump, analyze, encode
};

// declaration statement
class AST_Declaration: public AST_Statement
{
  protected:
    Type* type;
    char* name;

  public:
    ~AST_Declaration();
    AST_Declaration(Type* type, char* name);
    
    void dump();
    AST_Node* analyze();
    void encode();
};

// assignment statement
class AST_Assignment: public AST_Statement
{
  protected:
    AST_Expression* lhs;
    AST_Expression* rhs;

  public:
    ~AST_Assignment();
    AST_Assignment(AST_Expression* lhs, AST_Expression* rhs);
    
    void dump();
    AST_Node* analyze();
    void encode();
};

// print statement
class AST_Print: public AST_Statement
{
  protected:
    // represent with a AST_Expression because a Deref will be added
    AST_Expression* var;

  public:
    ~AST_Print();
    AST_Print(AST_Expression* var);
    
    void dump();
    AST_Node* analyze();
    void encode();
};

// divide 
class AST_Divide: public AST_BinaryOperator
{
  public:
    ~AST_Divide();
    AST_Divide(AST_Expression* left, AST_Expression* right);

    void dump();
    AST_Node* analyze();
    void encode();
};

// convert unary operator
class AST_Convert: public AST_UnaryOperator
{
  public:
    ~AST_Convert();
    AST_Convert(AST_Expression* left);

    void dump();
    AST_Node* analyze();
    void encode();
};

// dereference unary operator
class AST_Deref: public AST_UnaryOperator
{
  public:
    ~AST_Deref();
    AST_Deref(AST_Expression* left);

    void dump();
    AST_Node* analyze();
    void encode();
};

#endif
