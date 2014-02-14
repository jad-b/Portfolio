#ifndef _AST_H
#define _AST_H

// Jan 2008
// Abstract methods are for debugging - they display the AST to stderr.
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
/**
 * Statement uses a bitset to keep track of various boolean flags:
 * bit  : meaning
 * --------------
 * 0    : inside the main block
 * 1    : inside a method
 * 2    : inside a constructor/destructor
 * 3    : inside a while loop
 * 4    : ???
 * AST nodes with Statement fields are responsible for updating their
 * bitflags.
 */
class AST_Statement: public AST_Node
{
  public:
    virtual ~AST_Statement();
    unsigned int bitflags;

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

/*********************End of Abstract Classes*********************/
//CompilationUnit
class AST_Program: public AST_List
{
protected:
    AST_List* firstList;    // Class List pre-main

  public:
    ~AST_Program();
    AST_Program(AST_List* firstList, AST_Node* item, AST_List* restOfList);

    void dump();
};

// list of statements
class AST_StatementList: public AST_List
{
public:
  ~AST_StatementList();
  AST_StatementList(AST_Statement* statement, AST_List* restOfList);

  // inherit default behavior for dump, analyze, encode
  AST_Node* analyze(unsigned int);
  void dump();
};

//MainFunction
class AST_MainFunction: public AST_Node
{
  protected:
    AST_StatementList* stmtList;

  public:
    ~AST_MainFunction();
    AST_MainFunction(AST_StatementList* stmtList);

  void dump();
  AST_Node* analyze();
  void encode();
};

// list of variables in a variable declaration
class AST_VarList: public AST_List
{
public:
  ~AST_VarList();
  AST_VarList(AST_Expression* variable, AST_VarList* restOfList);

  //AST_Variable* var;
  //AST_VarList* tail;

  //inherit default dump,analyze,encode
  void dump();
  AST_Node* analyze(Type* t);
  void encode();
};

// declaration statement
class AST_Declaration: public AST_Statement
{
protected:
  Type* type;
  AST_VarList* varList;

public:
  ~AST_Declaration();
  AST_Declaration(Type* t, AST_VarList* list);

  void dump();
  AST_Node* analyze();
  void encode();
};

// variable
class AST_Variable: public AST_Expression
{
protected:


public:
  ~AST_Variable();
  AST_Variable(char *id);

  char* name;

  void dump();
  AST_Node* analyze();
  void encode();
  //void setType(Type* t);
};

// ExpressionStatement
class AST_ExpressionStatement: public AST_Statement
{
  protected:
     AST_Expression* var;

  public:
    ~AST_ExpressionStatement();
    AST_ExpressionStatement(AST_Expression* exp);

    void dump();
    AST_Node* analyze();
    void encode();
};

// OutStatement
class AST_OutStatement: public AST_Statement
{
  protected:
    AST_Expression* var;

  public:
    ~AST_OutStatement();
    AST_OutStatement(AST_Expression* var);

    void dump();
    AST_Node* analyze();
    void encode();
};



// Integer literal
class AST_IntegerLiteral: public AST_Expression
{
  protected:
    int value;


  public:
    ~AST_IntegerLiteral();
    AST_IntegerLiteral(int in);

    bool isChildOfNegate;

    void dump();
    AST_Node* analyze();
    void encode();
};


// assignment statement
class AST_Assignment: public AST_BinaryOperator
{
  public:
    ~AST_Assignment();
    AST_Assignment(AST_Expression* lhs, AST_Expression* rhs);

    void dump();
    AST_Node* analyze();
    void encode();
};

// equality expression
class AST_EqualityExpression: public AST_BinaryOperator
{
  protected:

  public:
    ~AST_EqualityExpression();
    AST_EqualityExpression(AST_Expression* lhs, AST_Expression* rhs);

    void dump();
    AST_Node* analyze();
    void encode();
};

// lessThan
class AST_LessThan: public AST_BinaryOperator
{
public:
  ~AST_LessThan();
  AST_LessThan(AST_Expression* left, AST_Expression* right);

  void dump();
  AST_Node* analyze();
  void encode();
};

// greaterThan
class AST_GreaterThan: public AST_BinaryOperator
{
public:
  ~AST_GreaterThan();
  AST_GreaterThan(AST_Expression* left, AST_Expression* right);

  void dump();
  AST_Node* analyze();
  void encode();
};

// Add
class AST_Add: public AST_BinaryOperator{
public:
  ~AST_Add();
  AST_Add(AST_Expression* left, AST_Expression* right);

  void dump();
  AST_Node* analyze();
  void encode();
};

// subtract
class AST_Subtract: public AST_BinaryOperator
{
public:
  ~AST_Subtract();
  AST_Subtract(AST_Expression* left, AST_Expression* right);

  void dump();
  AST_Node* analyze();
  void encode();
};

// multiply
class AST_Multiply: public AST_BinaryOperator
{
public:
  ~AST_Multiply();
  AST_Multiply(AST_Expression* left, AST_Expression* right);

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

// logical NOT '!' unary operator
class AST_LogicalNot: public AST_UnaryOperator
{
  protected:
    AST_Expression* var;

  public:
    ~AST_LogicalNot();
    AST_LogicalNot(AST_Expression* var);

    void dump();
    AST_Node* analyze();
    void encode();
};

// negate '~' unary operator
class AST_Negate: public AST_UnaryOperator
{
  protected:
    AST_Expression* var;

  public:
    ~AST_Negate();
    AST_Negate(AST_Expression* var);

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

/********************Phase 2********************/
/***********************************************/
// Block
class AST_Block: public AST_Statement{
public:
  ~AST_Block();
  AST_Block(AST_StatementList* sl);

  AST_StatementList* stmtList;

  void dump();
  AST_Node* analyze();
  void encode();
};

class AST_EmptyStatement: public AST_Statement{
public:
  AST_EmptyStatement();
  ~AST_EmptyStatement();

  void dump();
  AST_Node* analyze();
  void encode();
};

class AST_IfThenElseStatement: public AST_Statement{
  protected:
    AST_Expression* ifExp;
    AST_Statement* thenStmt;
    AST_Statement* elseStmt;

  public:
    AST_IfThenElseStatement(AST_Expression* pe, AST_Statement* ts, AST_Statement* es);
    ~AST_IfThenElseStatement();

    void dump();
    AST_Node* analyze();
    void encode();
};

class AST_WhileStatement: public AST_Statement{
protected:
  AST_Expression* ifExp;
  AST_Statement* bodyStmt;

public:
  AST_WhileStatement(AST_Expression* ifExp, AST_Statement* bodyS);
  ~AST_WhileStatement();

  void dump();
  AST_Node* analyze();
  void encode();
};

/*
 */
class AST_ReturnStatement: public AST_Statement{
protected:
  AST_Expression* exp;
  Type* method_return_type;

public:
  AST_ReturnStatement(AST_Expression* e);
  ~AST_ReturnStatement();


  void dump();
  AST_Node* analyze();
  void encode();
};

class AST_BreakStatement: public AST_Statement{
public:
  AST_BreakStatement();
  ~AST_BreakStatement();

  void dump();
  AST_Node* analyze();
  void encode();
};

class AST_ContinueStatement: public AST_Statement{
public:
  AST_ContinueStatement();
  ~AST_ContinueStatement();

  void dump();
  AST_Node* analyze();
  void encode();
};

/********************Phase 3********************/
/**********************************************/
class AST_ClassDeclaration: public AST_Node{
protected:
  AST_Expression* id;
  AST_Expression* classType;
  AST_StatementList* stmtList;

public:
  ~AST_ClassDeclaration();
  AST_ClassDeclaration(AST_Expression* id,
                      AST_Expression* type,
                      AST_StatementList* classBody );

  void dump();
  AST_Node* analyze();
  void encode();
};

class AST_ClassList: public AST_List{

public:
  ~AST_ClassList();
  AST_ClassList(AST_ClassDeclaration* classDecl, AST_ClassList* restOfList);

  void dump();wrong
  AST_Node* analyze();
  void encode();
};

class AST_ClassCreationExp: public AST_Expression{
protected:
  AST_Variable* classID;
  AST_Expression* args;

public:
  ~AST_ClassCreationExp();
  AST_ClassCreationExp(AST_Expression* type, AST_Expression* exp);

  void dump();
  AST_Node* analyze();
  void encode();
};

class AST_FieldAccess: public AST_UnaryOperator{
protected:
  AST_Variable* fieldID; // name of field

public:
  ~AST_FieldAccess();
  AST_FieldAccess(AST_Expression* lhs, AST_Expression* id);

  void dump();
  AST_Node* analyze();
  void encode();
};

class AST_This: public AST_Expression{
public:
  ~AST_This();
  AST_This();

  void dump();
  AST_Node* analyze();
  void encode();
};

class AST_NullLiteral: public AST_Expression{
public:
  ~AST_NullLiteral();
  AST_NullLiteral();

  void dump();
  AST_Node* analyze();
  void encode();
};
/********************Phase 4********************/
/**********************************************/
#endif
