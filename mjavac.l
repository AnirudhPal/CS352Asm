%{
  /** Import Libs **/
  #include <stdio.h>  // For printf()
  #include <string.h>
  #include "y.tab.h"  // For TOKENS
%}

  /** Lex Options **/
%option yylineno
%option noyywrap

  /** Regular Definitions **/
DIGITS        [0-9]+
ALPHA         [a-zA-Z]+
ALPHANUM      [a-zA-Z0-9]+
ALPHANUMUND   [a-zA-Z0-9_]+
NO_STAR       [^*]
NO_STAR_DASH  [^"/*"]
ANY           .
COMMENT       ("/*"({NO_STAR}|\*+{NO_STAR_DASH})*\*+"/")|("//"{ANY}*)
OP            "&&"|"||"|"<"|">"|"<="|">="|"=="|"!="|"*"|"/"

%%

  /** Catch and Ignore Comments **/
{COMMENT}                   {}

  /** Error Stuff **/
"++"                        {}
"--"                        {}
("[]")+                     {return BRACKS;}

  /** Catch Keyword Tokens **/
"class"                     {return CLASS;}
"public"                    {return PUBLIC;}
"static"                    {return STATIC;}
"main"                      {return MAIN;}
"extends"                   {return EXTENDS;}
"return"                    {return RETURN;}
"if"                        {return IF;}
"else"                      {return ELSE;}
"while"                     {return WHILE;}
"this"                      {return THIS;}
"new"                       {return NEW;}
"length"                    {return LENGTH;}
"System.out.println"        {return PRINTLN;}
"System.out.print"          {return PRINT;}

  /** Catch Literal Tokens **/
"true"                      {return TRUE;}
"false"                     {return FALSE;}

  /** Catch Type Tokens **/
"String"                    {return STRING;}
"void"                      {return VOID;}
"int"                       {return INT;}
"boolean"                   {return BOOLEAN;}

  /** Catch Deliminator Tokens **/
";"                         {return ';';}
","                         {return ',';}
"("                         {return '(';}
")"                         {return ')';}
"["                         {return '[';}
"]"                         {return ']';}
"{"                         {return '{';}
"}"                         {return '}';}
"="                         {return '=';}
"."                         {return '.';}

  /** Catch Unary Operators Tokens **/
"+"                         {return '+';}
"-"                         {return '-';}
"!"                         {return '!';}

  /** Catch Binary Operator Tokens **/
"*"                        {return '*';}
"/"                        {return '/';}
"=="                       {return EQ;}
"!="                       {return NQ;}
"<"                        {return '<';}
">"                        {return '>';}
"<="                       {return LE;}
">="                       {return GE;}
"||"                       {return OR;}
"&&"                       {return AND;}

  /** Catch Identifier Tokens **/
{ALPHA}({ALPHANUMUND})?     {yylval.str = strdup(yytext); return ID;}

  /** Catch String Tokens **/
\"({ANY})*\"                {yylval.str = strdup(yytext); return STRING_LITERAL;}

  /** Catch Number Tokens (including decimals) **/
{DIGITS}(\.{DIGITS})?       {yylval.str = strdup(yytext); return INTEGER_LITERAL;}

  /** Catch White Spaces **/
[ \t\r\n]                   {}

  /** Unexpected Character (Should never come here) **/
{ANY}                       {}

%%
