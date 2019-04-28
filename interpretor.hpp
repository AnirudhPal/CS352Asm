#include <iostream>
#include <vector>
#include <stdexcept>
#include <fstream>

/** Primitive Types **/
enum class PrimType {
  Int,
  Bool,
  Ref,
  Obj,
};

/** Variable Declaration **/
class Var {
public:
  // Vars
  std::string id;
  PrimType type;
  int val;
  // Methods
  void print();
};

/** Variable List **/
class VarList {
public:
  // Vars
  std::vector<Var*> vars;
  // Methods
  Var* getVar(std::string);
  void addVar(Var*);
  void print();
  void addClassVars(VarList*);
};

/** Exp **/
// Abstract Exp
class Exp {
public:
  // Vars
  int val;
  int line;
  PrimType type;
  VarList* env;
  // Methods
  virtual void compute() = 0;
  virtual void assemble() = 0;
  virtual int typeCheck() = 0;
  virtual void print() = 0;
};

// Plus
class Plus: public Exp {
protected:
  Exp* left;
  Exp* right;
public:
  void compute();
  void assemble();
  int typeCheck();
  void print();
  void addFields(Exp*, Exp*);
};

// Minus
class Minus: public Exp {
protected:
  Exp* left;
  Exp* right;
public:
  void compute();
  void assemble();
  int typeCheck();
  void print();
  void addFields(Exp*, Exp*);
};

// Times
class Times: public Exp {
protected:
  Exp* left;
  Exp* right;
public:
  void compute();
  void assemble();
  int typeCheck();
  void print();
  void addFields(Exp*, Exp*);
};

// Div
class Div: public Exp {
protected:
  Exp* left;
  Exp* right;
public:
  void compute();
  void assemble();
  int typeCheck();
  void print();
  void addFields(Exp*, Exp*);
};

// Less
class Less: public Exp {
protected:
  Exp* left;
  Exp* right;
public:
  void compute();
  void assemble();
  int typeCheck();
  void print();
  void addFields(Exp*, Exp*);
};

// Greater
class Greater: public Exp {
protected:
  Exp* left;
  Exp* right;
public:
  void compute();
  void assemble();
  int typeCheck();
  void print();
  void addFields(Exp*, Exp*);
};

// Less Equal
class LessEqual: public Exp {
protected:
  Exp* left;
  Exp* right;
public:
  void compute();
  void assemble();
  int typeCheck();
  void print();
  void addFields(Exp*, Exp*);
};

// Greater Equal
class GreaterEqual: public Exp {
protected:
  Exp* left;
  Exp* right;
public:
  void compute();
  void assemble();
  int typeCheck();
  void print();
  void addFields(Exp*, Exp*);
};

// Equal
class Equal: public Exp {
protected:
  Exp* left;
  Exp* right;
public:
  void compute();
  void assemble();
  int typeCheck();
  void print();
  void addFields(Exp*, Exp*);
};

// Not Equal
class NotEqual: public Exp {
protected:
  Exp* left;
  Exp* right;
public:
  void compute();
  void assemble();
  int typeCheck();
  void print();
  void addFields(Exp*, Exp*);
};

// Or
class OrN: public Exp {
protected:
  Exp* left;
  Exp* right;
public:
  void compute();
  void assemble();
  int typeCheck();
  void print();
  void addFields(Exp*, Exp*);
};

// And
class AndN: public Exp {
protected:
  Exp* left;
  Exp* right;
public:
  void compute();
  void assemble();
  int typeCheck();
  void print();
  void addFields(Exp*, Exp*);
};

// Not
class NotN: public Exp {
protected:
  Exp* exp;
public:
  void compute();
  void assemble();
  int typeCheck();
  void print();
  void addFields(Exp*);
};

// IntegerLiteral
class IntegerLiteral: public Exp {
public:
  std::string str;
  void compute();
  void assemble();
  int typeCheck();
  void print();
};

// BooleanLiteral
class True: public Exp {
public:
  void compute();
  void assemble();
  int typeCheck();
  void print();
};
class False: public Exp {
public:
  void compute();
  void assemble();
  int typeCheck();
  void print();
};

// VarLiteral
class Get: public Exp {
public:
  // Vars
  std::string id;
  // Methods
  void compute();
  void assemble();
  int typeCheck();
  void print();
};

/** Statement **/
// Abstract Statement
class Statement {
public:
  // Vars
  int line;
  Exp* e = NULL;
  VarList* env = NULL;
  int isRet = 0;
  // Methods
  virtual void compute() = 0;
  virtual void assemble() = 0;
  virtual int typeCheck() = 0;
  virtual void print() = 0;
};

// Block
class Block: public Statement {
protected:
  std::vector<Statement*> stms;
public:
  void compute();
  void assemble();
  int typeCheck();
  void print();
  void addStatement(Statement*);
};

// Print
class Print: public Statement {
public:
  void compute();
  void assemble();
  int typeCheck();
  void print();
};
class PrintStr: public Statement {
protected:
  std::string str;
  int index;
public:
  void compute();
  void assemble();
  int typeCheck();
  void print();
  void setStr(std::string);
};
class PrintLn: public Statement {
public:
  void compute();
  void assemble();
  int typeCheck();
  void print();
};
class PrintStrLn: public Statement {
protected:
  std::string str;
  int index;
public:
  void compute();
  void assemble();
  int typeCheck();
  void print();
  void setStr(std::string);
};

// If
class If: public Statement {
protected:
  Exp* exp;
  Statement* stm1;
  Statement* stm2;
public:
  void compute();
  void assemble();
  int typeCheck();
  void print();
  void addFields(Exp*, Statement*, Statement*);
};

// While
class While: public Statement {
protected:
  Exp* exp;
  Statement* stm;
public:
  void compute();
  void assemble();
  int typeCheck();
  void print();
  void addFields(Exp*, Statement*);
};

// Return
class Return: public Statement {
public:
  void compute();
  void assemble();
  int typeCheck();
  void print();
};

// Assign
class Assign: public Statement {
  std::string id;
  Exp* e;
public:
  void compute();
  void assemble();
  int typeCheck();
  void print();
  void addFields(std::string, Exp*);
};

/** Main Class **/

/** Method Declaration **/
class Method {
public:
  // Vars
  std::string id;
  VarList* formList;
  VarList* varList;
  Block* blk;
  PrimType type;
  int val;
  Exp* rexp;
  int line;
  // Methods
  void print();
  void compute();
  void assemble();
  void addFields(std::string, VarList*, VarList*, Block*, PrimType, Exp*);
  int typeCheck();
};

/** Method List **/
class MethodList {
public:
  std::vector<Method*> methods;
  Method* getMethod(std::string);
  void addMethod(Method*);
  void print();
  void assemble();
};

/** Class **/
class Class {
public:
  // Vars
  std::string id;
  VarList* varList;
  MethodList* methodList;
  int line;
  // Methods
  void print();
  void addFields(std::string, VarList*, MethodList*);
  int typeCheck();
  void assemble();
};

/** Class List **/
class ClassList {
protected:
  std::vector<Class*> classes;
public:
  void addClass(Class*);
  Class* getClass(std::string s);
  void print();
  void assemble();
};

/** Object **/
class Object: public Exp {
public:
  // Vars
  Class* cls;
  std::string typeClass;
  std::string func;
  // Methods
  void instance(std::string);
  void print();
  int typeCheck();
  void compute();
  void assemble();
  void callFunc(std::string);
};

/** Assembly Helpers **/
void openFile();
void closeFile();
void closeMain();
