%{
  /** Import Libs **/
  #include <stdio.h>

  /** Function Decs **/
  int yylex(void);
  void yyerror(char*);

  /** External Vars **/
  extern FILE *yyin;
  extern int yylineno;
%}

  /** Tokens **/
%token  INTEGER_LITERAL ID STRING_LITERAL CLASS PUBLIC STATIC MAIN EXTENDS RETURN IF ELSE WHILE THIS NEW TRUE FALSE STRING VOID INT BOOLEAN LENGTH PRINT PRINTLN BRACKS EQ NQ LE GE AND OR

  /** Code Block **/
%code requires {
  #include "interpretor.hpp"
  extern ClassList classGlob;
  extern int typeerror;
  extern std::string oFile;
}

/** Union **/
%union {
  Exp* node;
  Statement* statement;
  Block* blk;
  Class* cls;
  Method* method;
  MethodList* methodList;
  Object* obje;
  PrimType typ;
  Var* var;
  VarList* varList;
  int val;
  char* str;
}

  /** Types **/
%type <node> Exp UnOpExp LitExp
%type <statement> Statement MainClass Program
%type <cls> ClassDecl
%type <method> MethodDecl
%type <methodList> MethodDeclList
%type <obje> Object
%type <blk> StatementList
%type <str> STRING_LITERAL ID INTEGER_LITERAL
%type <typ> PrimType Type
%type <var> VarDecl
%type <varList> VarDeclList FormalList

  /** Precedence Operators **/
%left OR  AND
%left EQ  NQ  LE  GE '<' '>'
%left '+' '-'
%left '*' '/'
%right '='

%%
Program   : MainClass ClassDeclList             {if(!($1->typeCheck() || typeerror)) {openFile(); $1->assemble(); closeMain(); classGlob.assemble(); closeFile();}}
          | MainClass                           {if(!($$->typeCheck())) {openFile(); $$->assemble(); closeMain(); closeFile();}}
          ;

MainClass : CLASS ID '{' PUBLIC STATIC VOID MAIN '(' STRING BRACKS ID ')' '{' Statement '}' '}' {$$ = $14;}
          ;

ClassDecl : CLASS ID '{' VarDeclList MethodDeclList '}'             {Class* c = new Class; c->addFields($2, $4, $5); c->line = yylineno; c->typeCheck(); classGlob.addClass(c);}
          | CLASS ID '{' VarDeclList '}'                            {}
          | CLASS ID '{' MethodDeclList '}'                         {Class* c = new Class; c->addFields($2, NULL, $4); c->line = yylineno; c->typeCheck(); classGlob.addClass(c);}
          | CLASS ID '{' '}'                                        {}
          | CLASS ID EXTENDS ID '{' VarDeclList MethodDeclList '}'  {}
          | CLASS ID EXTENDS ID '{' VarDeclList '}'                 {}
          | CLASS ID EXTENDS ID '{' MethodDeclList '}'              {}
          | CLASS ID EXTENDS ID '{' '}'                             {}
          ;

ClassDeclList : ClassDecl                                           {}
              | ClassDeclList ClassDecl                             {}
              ;

VarDecl   : Type ID ';'             {Var* v = new Var; v->id = std::string($2); v->type = $1; $$ = v;}
          ;

VarDeclList : VarDecl               {VarList* vl = new VarList; vl->addVar($1); $$ = vl;}
            | VarDeclList VarDecl   {$$->addVar($2); $$ = $$;}
            ;

MethodDecl: PUBLIC Type ID '(' FormalList ')' '{' VarDeclList StatementList RETURN Exp ';' '}'  {Method* m = new Method; m->addFields(std::string($3), $5, $8, $9, $2, $11); m->line = yylineno; $$ = m;}
          | PUBLIC Type ID '(' FormalList ')' '{' VarDeclList RETURN Exp ';' '}'                {Method* m = new Method; m->addFields(std::string($3), $5, $8, NULL, $2, $10); m->line = yylineno; $$ = m;}
          | PUBLIC Type ID '(' ')' '{' VarDeclList StatementList RETURN Exp ';' '}'             {Method* m = new Method; m->addFields(std::string($3), NULL, $7, $8, $2, $10); m->line = yylineno; $$ = m;}
          | PUBLIC Type ID '(' ')' '{' VarDeclList RETURN Exp ';' '}'                           {Method* m = new Method; m->addFields(std::string($3), NULL, $7, NULL, $2, $9); m->line = yylineno; $$ = m;}
          | PUBLIC Type ID '(' FormalList ')' '{' StatementList RETURN Exp ';' '}'              {Method* m = new Method; m->addFields(std::string($3), $5, NULL, $8, $2, $10); m->line = yylineno; $$ = m;}
          | PUBLIC Type ID '(' FormalList ')' '{' RETURN Exp ';' '}'                            {Method* m = new Method; m->addFields(std::string($3), $5, NULL, NULL, $2, $9); m->line = yylineno; $$ = m;}
          | PUBLIC Type ID '(' ')' '{' StatementList RETURN Exp ';' '}'                         {Method* m = new Method; m->addFields(std::string($3), NULL, NULL, $7, $2, $9); m->line = yylineno; $$ = m;}
          | PUBLIC Type ID '(' ')' '{' RETURN Exp ';' '}'                                       {Method* m = new Method; m->addFields(std::string($3), NULL, NULL, NULL, $2, $8); m->line = yylineno; $$ = m;}
          ;

MethodDeclList : MethodDecl                 {MethodList* ml = new MethodList; ml->addMethod($1); $$ = ml;}
               | MethodDeclList MethodDecl  {$$->addMethod($2); $$ = $$;}
               ;

FormalList: Type ID FormalRestList          {$$ = NULL;}
          | Type ID                         {$$ = NULL;}
          ;

FormalRest: ',' Type ID                     {}
          ;

FormalRestList: FormalRest                  {}
              | FormalRestList FormalRest   {}
              ;

Statement : '{' StatementList '}'                     {$$ = $2;}
          | '{''}'                                    {}
          | PRINT '(' Exp ')' ';'                     {Print* prt = new Print; prt->e = $3; prt->line = yylineno; $$ = prt;}
          | PRINT '(' STRING_LITERAL ')' ';'          {PrintStr* prtStr = new PrintStr; prtStr->setStr($3); prtStr->line = yylineno; $$ = prtStr;}
          | PRINTLN '(' Exp ')' ';'                   {PrintLn* prtLn = new PrintLn; prtLn->e = $3; prtLn->line = yylineno; $$ = prtLn;}
          | PRINTLN '(' STRING_LITERAL ')' ';'        {PrintStrLn* prtStrLn = new PrintStrLn; prtStrLn->setStr($3); prtStrLn->line = yylineno; $$ = prtStrLn;}
          | IF '(' Exp ')' Statement ELSE Statement   {If* ifn = new If; ifn->addFields($3, $5, $7); ifn->line = yylineno; $$ = ifn;}
          | WHILE '(' Exp ')' Statement               {While* whilen = new While; whilen->addFields($3, $5); whilen->line = yylineno; $$ = whilen;}
          | RETURN Exp ';'                            {Return* rtr = new Return; rtr->e = $2; rtr->line = yylineno; $$ = rtr;}
          | ID '=' Exp ';'                            {Assign* a = new Assign; a->addFields($1, $3); a->line = yylineno; $$ = a;}
          | THIS '.' ID '=' Exp ';'                   {Assign* a = new Assign; a->addFields("this." + std::string($3), $5); a->line = yylineno; $$ = a;}
          ;

StatementList : Statement                       {Block* block = new Block; block->addStatement($1); block->line = yylineno; $$ = block;}
              | StatementList Statement         {$$->addStatement($2); $$ = $$;}
              ;

PrimType  : INT               {$$ = PrimType::Int;}
          | BOOLEAN           {$$ = PrimType::Bool;}
          | ID                {}
          ;

Type      : PrimType          {$$ = $1;}
          | Type BRACKS       {}
          ;


Exp       : UnOpExp             {$$ = $$;}
          | Exp '+' Exp         {Plus* plus = new Plus; plus->addFields($1, $3); plus->line = yylineno; $$ = plus;}
          | Exp '-' Exp         {Minus* minus = new Minus; minus->addFields($1, $3); minus->line = yylineno; $$ = minus;}
          | Exp '*' Exp         {Times* times = new Times; times->addFields($1, $3); times->line = yylineno; $$ = times;}
          | Exp '/' Exp         {Div* div = new Div; div->addFields($1, $3); div->line = yylineno; $$ = div;}
          | Exp EQ Exp          {Equal* equal = new Equal; equal->addFields($1, $3); equal->line = yylineno; $$ = equal;}
          | Exp NQ Exp          {NotEqual* notEqual = new NotEqual; notEqual->addFields($1, $3); notEqual->line = yylineno; $$ = notEqual;}
          | Exp '<' Exp         {Less* less = new Less; less->addFields($1, $3); less->line = yylineno;; $$ = less;}
          | Exp '>' Exp         {Greater* greater = new Greater; greater->addFields($1, $3); greater->line = yylineno; $$ = greater;}
          | Exp LE Exp          {LessEqual* lessEqual = new LessEqual; lessEqual->addFields($1, $3); lessEqual->line = yylineno; $$ = lessEqual;}
          | Exp GE Exp          {GreaterEqual* greaterEqual = new GreaterEqual; greaterEqual->addFields($1, $3); greaterEqual->line = yylineno; $$ = greaterEqual;}
          | Exp OR Exp          {OrN* orn = new OrN; orn->addFields($1, $3); orn->line = yylineno; $$ = orn;}
          | Exp AND Exp         {AndN* andn = new AndN; andn->addFields($1, $3); andn->line = yylineno; $$ = andn;}
          ;

UnOpExp   : LitExp              {$$ = $$;}
          | '!' LitExp          {NotN* notn = new NotN; notn->addFields($2); notn->line = yylineno; $$ = notn;}
          | '+' LitExp          {$$ = $2;}
          | '-' LitExp          {IntegerLiteral* intLit = new IntegerLiteral; intLit->val = -1; intLit->line = yylineno; Times* times = new Times; times->addFields(intLit, $2); times->line = yylineno; $$ = times;}
          ;

LitExp    : INTEGER_LITERAL       {IntegerLiteral* intLit = new IntegerLiteral; intLit->str = std::string($1); intLit->line = yylineno; $$ = intLit;}
          | TRUE                  {True* t = new True; t->val = 1; t->line = yylineno; $$ = t;}
          | FALSE                 {False* f = new False; f->val = 0; f->line = yylineno; $$ = f;}
          | '(' Exp ')'           {$$ = $2;}
          | Object                {$$ = $1;}
          | Object '.' ID '(' ')' {$1->callFunc($3); $$ = $1;}
          | ID                    {Get* g = new Get; g->id = std::string($1); g->line = yylineno; $$ = g;}
          | THIS '.' ID           {Get* g = new Get; g->id = "this." + std::string($3); g->line = yylineno; $$ = g;}
          ;

Object    : NEW ID '(' ')'        {Object* obj = new Object; obj->instance($2); obj->line = yylineno; $$ = obj;}
          ;

%%

/** Main Function Definitions **/
int main(int argc, char** argv) {
  // Increment to Remove Executable
  ++argv;
  --argc;

  // Check if Args available
  if ( argc > 0 )
    // Use File
    yyin = fopen( argv[0], "r" );
  else
    // Use STDIN
    yyin = stdin;

  // Save File Name
  std::string out = argv[0];
  oFile = out.substr(0, out.find_last_of('.') + 1);
  oFile = oFile + 's';

  // Start Parsing
  yyparse();

  // Return
  return 0;
}

  /** Error Definition **/
void yyerror(char* s) {
  // Print Line Error
  std::cout << "Syntax errors in " << yylineno << ".\n";
}

  /** Wrap Up Definition **/
int yywrap() {
  // Return
  return(1);
}
