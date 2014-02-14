/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IDENTIFIER = 258,
     INT = 259,
     INTEGER_LITERAL = 260,
     MAIN = 261,
     EQ_OP = 262,
     OUT = 263,
     IF = 264,
     ELSE = 265,
     WHILE = 266,
     RETURN = 267,
     BREAK = 268,
     CONTINUE = 269,
     NULL_LITERAL = 270,
     CLASS = 271,
     EXTENDS = 272,
     NEW = 273,
     FIELD_REF = 274,
     THIS = 275,
     SUPER = 276,
     DELETE = 277,
     BAD = 278
   };
#endif
/* Tokens.  */
#define IDENTIFIER 258
#define INT 259
#define INTEGER_LITERAL 260
#define MAIN 261
#define EQ_OP 262
#define OUT 263
#define IF 264
#define ELSE 265
#define WHILE 266
#define RETURN 267
#define BREAK 268
#define CONTINUE 269
#define NULL_LITERAL 270
#define CLASS 271
#define EXTENDS 272
#define NEW 273
#define FIELD_REF 274
#define THIS 275
#define SUPER 276
#define DELETE 277
#define BAD 278




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 33 "parse.yy"
 //types of semantic values
       int value;
       char* str;
       AST_Program* program;
       AST_MainFunction* mainFunction;
       AST_StatementList* statementList;
       AST_VarList* varList;
       AST_Statement* statement;
       AST_Declaration* declaration;
       AST_Block* block;
       AST_OutStatement* outStatement;
       AST_ExpressionStatement* expStatement;
       AST_WhileStatement* whileStatement;
       AST_ReturnStatement* returnStatement;
       AST_IfThenElseStatement* ifThenElseStatement;
       AST_BreakStatement* breakStatement;
       AST_ContinueStatement* continueStatement;
       AST_EmptyStatement* emptyStatement;
       AST_Expression* expression;
       AST_IntegerLiteral* intLiteral;
       Type* type;
       /*Phase 3*/
       AST_ClassList* classList;
       AST_ClassDeclaration* classDeclaration;
       AST_FieldAccess* fieldAccess;
       //AST_This* astThis;
       //AST_NullLiteral* nullLiteral;



/* Line 2068 of yacc.c  */
#line 127 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


