#include "interpretor.hpp"

ClassList classGlob;
int typeerror = 0;
std::vector<std::string> glbStrs;
std::vector<std::string> glbInts;
std::string asmTxt;
std::ofstream asmF;
std::string regs[] = {"r1", "r2", "r3", "r4", "r5", "r6", "r8", "r9", "r10"};
int sp = 0;
int j_ind = 0;
int c_ind = 0;
int l_ind = 0;
std::string oFile;

/** Exp Defs **/

/** Plus Defs (of Exp) **/
void Plus::compute() {
  left->env = env;
  right->env = env;
  left->compute();
  right->compute();
  val = left->val + right->val;
}
void Plus::assemble() {
  left->env = env;
  right->env = env;
  left->assemble();
  sp += 1;
  right->assemble();
  sp -= 1;
  asmF << "\t\tadd " << regs[sp] << ", " << regs[sp] << ", " << regs[sp+1] << '\n' ;
}
int Plus::typeCheck() {
  left->env = env;
  right->env = env;
  type = PrimType::Int;
  if(left->typeCheck() || right->typeCheck()) {
    return 1;
  }
  if(left->type != PrimType::Int || right->type != PrimType::Int) {
    std::cout << "Type Violation in Line " << line << " : " << "op1 + op2 -> op1 or/and op2 not INT" << "\n";
    return 1;
  }
  return 0;
}
void Plus::print() {
  std::cout << "Plus(";
  left->print();
  std::cout << ", ";
  right->print();
  std::cout << ", ";
  switch (type) {
    case PrimType::Int: std::cout << "Int_Type"; break;
    case PrimType::Bool: std::cout << "Bool_Type"; break;
  }
  std::cout << ")";
}
void Plus::addFields(Exp* e1, Exp* e2) {
  left = e1;
  right = e2;
  type = PrimType::Int;
}

/** Minus Defs (of Exp) **/
void Minus::compute() {
  left->env = env;
  right->env = env;
  left->compute();
  right->compute();
  val = left->val - right->val;
}
void Minus::assemble() {
  left->env = env;
  right->env = env;
  left->assemble();
  sp += 1;
  right->assemble();
  sp -= 1;
  asmF << "\t\tsub " << regs[sp] << ", " << regs[sp] << ", " << regs[sp+1] << '\n' ;
}
int Minus::typeCheck() {
  left->env = env;
  right->env = env;
  type = PrimType::Int;
  if(left->typeCheck() || right->typeCheck()) {
    return 1;
  }
  if(left->type != PrimType::Int || right->type != PrimType::Int) {
    std::cout << "Type Violation in Line " << line << " : " << "op1 - op2 -> op1 or/and op2 not INT" << "\n";
    return 1;
  }
  return 0;
}
void Minus::print() {
  std::cout << "Minus(";
  left->print();
  std::cout << ", ";
  right->print();
  std::cout << ", ";
  switch (type) {
    case PrimType::Int: std::cout << "Int_Type"; break;
    case PrimType::Bool: std::cout << "Bool_Type"; break;
  }
  std::cout << ")";
}
void Minus::addFields(Exp* e1, Exp* e2) {
  left = e1;
  right = e2;
  type = PrimType::Int;
}

/** Times Defs (of Exp) **/
void Times::compute() {
  left->env = env;
  right->env = env;
  left->compute();
  right->compute();
  val = left->val * right->val;
}
void Times::assemble() {
  left->env = env;
  right->env = env;
  left->assemble();
  sp += 1;
  right->assemble();
  sp -= 1;
  asmF << "\t\tmul " << regs[sp] << ", " << regs[sp] << ", " << regs[sp+1] << '\n' ;
}
int Times::typeCheck() {
  left->env = env;
  right->env = env;
  type = PrimType::Int;
  if(left->typeCheck() || right->typeCheck()) {
    return 1;
  }
  if(left->type != PrimType::Int || right->type != PrimType::Int) {
    std::cout << "Type Violation in Line " << line << " : " << "op1 * op2 -> op1 or/and op2 not INT" << "\n";
    return 1;
  }
  return 0;
}
void Times::print() {
  std::cout << "Times(";
  left->print();
  std::cout << ", ";
  right->print();
  std::cout << ", ";
  switch (type) {
    case PrimType::Int: std::cout << "Int_Type"; break;
    case PrimType::Bool: std::cout << "Bool_Type"; break;
  }
  std::cout << ")";
}
void Times::addFields(Exp* e1, Exp* e2) {
  left = e1;
  right = e2;
  type = PrimType::Int;
}

/** Div Defs (of Exp) **/
void Div::compute() {
  left->env = env;
  right->env = env;
  left->compute();
  right->compute();
  val = left->val / right->val;
}
void Div::assemble() {
  return;
}
int Div::typeCheck() {
  left->env = env;
  right->env = env;
  type = PrimType::Int;
  if(left->typeCheck() || right->typeCheck()) {
    return 1;
  }
  if(left->type != PrimType::Int || right->type != PrimType::Int) {
    std::cout << "Type Violation in Line " << line << " : " << "op1 / op2 -> op1 or/and op2 not INT" << "\n";
    return 1;
  }
  return 0;
}
void Div::print() {
  std::cout << "Div(";
  left->print();
  std::cout << ", ";
  right->print();
  std::cout << ", ";
  switch (type) {
    case PrimType::Int: std::cout << "Int_Type"; break;
    case PrimType::Bool: std::cout << "Bool_Type"; break;
  }
  std::cout << ")";
}
void Div::addFields(Exp* e1, Exp* e2) {
  left = e1;
  right = e2;
  type = PrimType::Int;
}

/** Less Defs (of Exp) **/
void Less::compute() {
  left->env = env;
  right->env = env;
  left->compute();
  right->compute();
  val = left->val < right->val;
}
void Less::assemble() {
  left->env = env;
  right->env = env;
  left->assemble();
  sp += 1;
  right->assemble();
  sp -= 1;
  asmF << "\t\tmov r0, #1\n";
  asmF << "\t\tcmp " << regs[sp] << ", " << regs[sp+1] << '\n' ;
  asmF << "\t\tblt " << "j" << j_ind << '\n';
  asmF << "\t\tmov r0, #0\n";
  asmF << "j" << j_ind << ":\n";
  j_ind++;
  asmF << "\t\tmov " << regs[sp] << ", r0 \n" ;
}
int Less::typeCheck() {
  left->env = env;
  right->env = env;
  type = PrimType::Bool;
  if(left->typeCheck() || right->typeCheck()) {
    return 1;
  }
  if(left->type != PrimType::Int || right->type != PrimType::Int) {
    std::cout << "Type Violation in Line " << line << " : " << "op1 < op2 -> op1 or/and op2 not INT" << "\n";
    return 1;
  }
  return 0;
}
void Less::print() {
  std::cout << "Less(";
  left->print();
  std::cout << ", ";
  right->print();
  std::cout << ", ";
  switch (type) {
    case PrimType::Int: std::cout << "Int_Type"; break;
    case PrimType::Bool: std::cout << "Bool_Type"; break;
  }
  std::cout << ")";
}
void Less::addFields(Exp* e1, Exp* e2) {
  left = e1;
  right = e2;
  type = PrimType::Bool;
}

/** Greater Defs (of Exp) **/
void Greater::compute() {
  left->env = env;
  right->env = env;
  left->compute();
  right->compute();
  val = left->val > right->val;
}
void Greater::assemble() {
  left->env = env;
  right->env = env;
  left->assemble();
  sp += 1;
  right->assemble();
  sp -= 1;
  asmF << "\t\tmov r0, #1\n";
  asmF << "\t\tcmp " << regs[sp] << ", " << regs[sp+1] << '\n' ;
  asmF << "\t\tbgt " << "j" << j_ind << '\n';
  asmF << "\t\tmov r0, #0\n";
  asmF << "j" << j_ind << ":\n";
  j_ind++;
  asmF << "\t\tmov " << regs[sp] << ", r0 \n" ;
}
int Greater::typeCheck() {
  left->env = env;
  right->env = env;
  type = PrimType::Bool;
  if(left->typeCheck() || right->typeCheck()) {
    return 1;
  }
  if(left->type != PrimType::Int || right->type != PrimType::Int) {
    std::cout << "Type Violation in Line " << line << " : " << "op1 > op2 -> op1 or/and op2 not INT" << "\n";
    return 1;
  }
  return 0;
}
void Greater::print() {
  std::cout << "Greater(";
  left->print();
  std::cout << ", ";
  right->print();
  std::cout << ", ";
  switch (type) {
    case PrimType::Int: std::cout << "Int_Type"; break;
    case PrimType::Bool: std::cout << "Bool_Type"; break;
  }
  std::cout << ")";
}
void Greater::addFields(Exp* e1, Exp* e2) {
  left = e1;
  right = e2;
  type = PrimType::Bool;
}

/** Less Equal Defs (of Exp) **/
void LessEqual::compute() {
  left->env = env;
  right->env = env;
  left->compute();
  right->compute();
  val = left->val <= right->val;
}
void LessEqual::assemble() {
  left->env = env;
  right->env = env;
  left->assemble();
  sp += 1;
  right->assemble();
  sp -= 1;
  asmF << "\t\tmov r0, #1\n";
  asmF << "\t\tcmp " << regs[sp] << ", " << regs[sp+1] << '\n' ;
  asmF << "\t\tble " << "j" << j_ind << '\n';
  asmF << "\t\tmov r0, #0\n";
  asmF << "j" << j_ind << ":\n";
  j_ind++;
  asmF << "\t\tmov " << regs[sp] << ", r0 \n" ;
}
int LessEqual::typeCheck() {
  left->env = env;
  right->env = env;
  type = PrimType::Bool;
  if(left->typeCheck() || right->typeCheck()) {
    return 1;
  }
  if(left->type != PrimType::Int || right->type != PrimType::Int) {
    std::cout << "Type Violation in Line " << line << " : " << "op1 <= op2 -> op1 or/and op2 not INT" << "\n";
    return 1;
  }
  return 0;
}
void LessEqual::print() {
  std::cout << "LessEqual(";
  left->print();
  std::cout << ", ";
  right->print();
  std::cout << ", ";
  switch (type) {
    case PrimType::Int: std::cout << "Int_Type"; break;
    case PrimType::Bool: std::cout << "Bool_Type"; break;
  }
  std::cout << ")";
}
void LessEqual::addFields(Exp* e1, Exp* e2) {
  left = e1;
  right = e2;
  type = PrimType::Bool;
}

/** Greater Equal Defs (of Exp) **/
void GreaterEqual::compute() {
  left->env = env;
  right->env = env;
  left->compute();
  right->compute();
  val = left->val >= right->val;
}
void GreaterEqual::assemble() {
  left->env = env;
  right->env = env;
  left->assemble();
  sp += 1;
  right->assemble();
  sp -= 1;
  asmF << "\t\tmov r0, #1\n";
  asmF << "\t\tcmp " << regs[sp] << ", " << regs[sp+1] << '\n' ;
  asmF << "\t\tbge " << "j" << j_ind << '\n';
  asmF << "\t\tmov r0, #0\n";
  asmF << "j" << j_ind << ":\n";
  j_ind++;
  asmF << "\t\tmov " << regs[sp] << ", r0 \n" ;
}
int GreaterEqual::typeCheck() {
  left->env = env;
  right->env = env;
  type = PrimType::Bool;
  if(left->typeCheck() || right->typeCheck()) {
    return 1;
  }
  if(left->type != PrimType::Int || right->type != PrimType::Int) {
    std::cout << "Type Violation in Line " << line << " : " << "op1 >= op2 -> op1 or/and op2 not INT" << "\n";
    return 1;
  }
  return 0;
}
void GreaterEqual::print() {
  std::cout << "GreaterEqual(";
  left->print();
  std::cout << ", ";
  right->print();
  std::cout << ", ";
  switch (type) {
    case PrimType::Int: std::cout << "Int_Type"; break;
    case PrimType::Bool: std::cout << "Bool_Type"; break;
  }
  std::cout << ")";
}
void GreaterEqual::addFields(Exp* e1, Exp* e2) {
  left = e1;
  right = e2;
  type = PrimType::Bool;
}

/** Equal Defs (of Exp) **/
void Equal::compute() {
  left->env = env;
  right->env = env;
  left->compute();
  right->compute();
  val = left->val == right->val;
}
void Equal::assemble() {
  left->env = env;
  right->env = env;
  left->assemble();
  sp += 1;
  right->assemble();
  sp -= 1;
  asmF << "\t\tmov r0, #1\n";
  asmF << "\t\tcmp " << regs[sp] << ", " << regs[sp+1] << '\n' ;
  asmF << "\t\tbeq " << "j" << j_ind << '\n';
  asmF << "\t\tmov r0, #0\n";
  asmF << "j" << j_ind << ":\n";
  j_ind++;
  asmF << "\t\tmov " << regs[sp] << ", r0 \n" ;
}
int Equal::typeCheck() {
  left->env = env;
  right->env = env;
  type = PrimType::Bool;
  if(left->typeCheck() || right->typeCheck()) {
    return 1;
  }
  if(left->type != PrimType::Int || right->type != PrimType::Int) {
    std::cout << "Type Violation in Line " << line << " : " << "op1 == op2 -> op1 or/and op2 not INT" << "\n";
    return 1;
  }
  return 0;
}
void Equal::print() {
  std::cout << "Equal(";
  left->print();
  std::cout << ", ";
  right->print();
  std::cout << ", ";
  switch (type) {
    case PrimType::Int: std::cout << "Int_Type"; break;
    case PrimType::Bool: std::cout << "Bool_Type"; break;
  }
  std::cout << ")";
}
void Equal::addFields(Exp* e1, Exp* e2) {
  left = e1;
  right = e2;
  type = PrimType::Bool;
}

/** Not Equal Defs (of Exp) **/
void NotEqual::compute() {
  left->env = env;
  right->env = env;
  left->compute();
  right->compute();
  val = left->val != right->val;
}
void NotEqual::assemble() {
  left->env = env;
  right->env = env;
  left->assemble();
  sp += 1;
  right->assemble();
  sp -= 1;
  asmF << "\t\tmov r0, #1\n";
  asmF << "\t\tcmp " << regs[sp] << ", " << regs[sp+1] << '\n' ;
  asmF << "\t\tbne " << "j" << j_ind << '\n';
  asmF << "\t\tmov r0, #0\n";
  asmF << "j" << j_ind << ":\n";
  j_ind++;
  asmF << "\t\tmov " << regs[sp] << ", r0 \n" ;
}
int NotEqual::typeCheck() {
  left->env = env;
  right->env = env;
  type = PrimType::Bool;
  if(left->typeCheck() || right->typeCheck()) {
    return 1;
  }
  if(left->type != PrimType::Int || right->type != PrimType::Int) {
    std::cout << "Type Violation in Line " << line << " : " << "op1 != op2 -> op1 or/and op2 not INT" << "\n";
    return 1;
  }
  return 0;
}
void NotEqual::print() {
  std::cout << "NotEqual(";
  left->print();
  std::cout << ", ";
  right->print();
  std::cout << ", ";
  switch (type) {
    case PrimType::Int: std::cout << "Int_Type"; break;
    case PrimType::Bool: std::cout << "Bool_Type"; break;
  }
  std::cout << ")";
}
void NotEqual::addFields(Exp* e1, Exp* e2) {
  left = e1;
  right = e2;
  type = PrimType::Bool;
}

/** Or Defs (of Exp) **/
void OrN::compute() {
  left->env = env;
  right->env = env;
  left->compute();
  right->compute();
  val = left->val || right->val;
}
void OrN::assemble() {
  left->env = env;
  right->env = env;
  left->assemble();
  sp += 1;
  right->assemble();
  sp -= 1;
  asmF << "\t\torr " << regs[sp] << ", " << regs[sp] << ", " << regs[sp+1] << '\n' ;
}
int OrN::typeCheck() {
  left->env = env;
  right->env = env;
  type = PrimType::Bool;
  if(left->typeCheck() || right->typeCheck()) {
    return 1;
  }
  if(left->type != PrimType::Bool || right->type != PrimType::Bool) {
    std::cout << "Type Violation in Line " << line << " : " << "op1 || op2 -> op1 or/and op2 not BOOL" << "\n";
    return 1;
  }
  return 0;
}
void OrN::print() {
  std::cout << "OrN(";
  left->print();
  std::cout << ", ";
  right->print();
  std::cout << ", ";
  switch (type) {
    case PrimType::Int: std::cout << "Int_Type"; break;
    case PrimType::Bool: std::cout << "Bool_Type"; break;
  }
  std::cout << ")";
}
void OrN::addFields(Exp* e1, Exp* e2) {
  left = e1;
  right = e2;
  type = PrimType::Bool;
}

/** And Defs (of Exp) **/
void AndN::compute() {
  left->env = env;
  right->env = env;
  left->compute();
  right->compute();
  val = left->val && right->val;
}
void AndN::assemble() {
  left->env = env;
  right->env = env;
  left->assemble();
  sp += 1;
  right->assemble();
  sp -= 1;
  asmF << "\t\tand " << regs[sp] << ", " << regs[sp] << ", " << regs[sp+1] << '\n' ;
}
int AndN::typeCheck() {
  left->env = env;
  right->env = env;
  type = PrimType::Bool;
  if(left->typeCheck() || right->typeCheck()) {
    return 1;
  }
  if(left->type != PrimType::Bool || right->type != PrimType::Bool) {
    std::cout << "Type Violation in Line " << line << " : " << "op1 && op2 -> op1 or/and op2 not BOOL" << "\n";
    return 1;
  }
  return 0;
}
void AndN::print() {
  std::cout << "AndN(";
  left->print();
  std::cout << ", ";
  right->print();
  std::cout << ", ";
  switch (type) {
    case PrimType::Int: std::cout << "Int_Type"; break;
    case PrimType::Bool: std::cout << "Bool_Type"; break;
  }
  std::cout << ")";
}
void AndN::addFields(Exp* e1, Exp* e2) {
  left = e1;
  right = e2;
  type = PrimType::Bool;
}

/** Not Defs (of Exp) **/
void NotN::compute() {
  exp->compute();
  val = !exp->val;
}
void NotN::assemble() {
  exp->env = env;
  exp->assemble();
  asmF << "\t\tmov r0, #1\n";
  asmF << "\t\teor " << regs[sp] << ", r0, " << regs[sp] << '\n' ;
}
int NotN::typeCheck() {
  exp->env = env;
  type = PrimType::Bool;
  if(exp->typeCheck()) {
    return 1;
  }
  if(exp->type != PrimType::Bool) {
    std::cout << "Type Violation in Line " << line << " : " << "!op1 -> op1 not BOOL" << "\n";
    return 1;
  }
  return 0;
}
void NotN::print() {
  std::cout << "NotN(";
  exp->print();
  std::cout << ", ";
  switch (type) {
    case PrimType::Int: std::cout << "Int_Type"; break;
    case PrimType::Bool: std::cout << "Bool_Type"; break;
  }
  std::cout << ")";
}
void NotN::addFields(Exp* e1) {
  exp = e1;
  type = PrimType::Bool;
}

/** Integer Literal Defs (of Exp) **/
void IntegerLiteral::compute() {
  val = std::stoi(str);
  return;
}
void IntegerLiteral::assemble() {
  val = std::stoi(str);
  asmF << "\t\tmov " << regs[sp] << ", #" << val << '\n';
}
int IntegerLiteral::typeCheck() {
  try {
    std::stoi(str);
  }
  catch (const std::out_of_range& oor) {
    std::cout << "Type Violation in Line " << line << " : " << "INT Overflow" << "\n";
  }
  type = PrimType::Int;
  return 0;
}
void IntegerLiteral::print() {
  std::cout << "IntegerLiteral(";
  std::cout << val << ", ";
  switch (type) {
    case PrimType::Int: std::cout << "Int_Type"; break;
    case PrimType::Bool: std::cout << "Bool_Type"; break;
  }
  std::cout << ")";
}

/** Boolean Literal Defs (of Exp) **/
void True::compute() {
  return;
}
void True::assemble() {
  asmF << "\t\tmov " << regs[sp] << ", #1\n";
}
int True::typeCheck() {
  type = PrimType::Bool;
  return 0;
}
void True::print() {
  std::cout << "True(";
  switch (type) {
    case PrimType::Int: std::cout << "Int_Type"; break;
    case PrimType::Bool: std::cout << "Bool_Type"; break;
  }
  std::cout << ")";
}
void False::compute() {
  return;
}
void False::assemble() {
  asmF << "\t\tmov " << regs[sp] << ", #0\n";
}
int False::typeCheck() {
  type = PrimType::Bool;
  return 0;
}
void False::print() {
  std::cout << "False(";
  switch (type) {
    case PrimType::Int: std::cout << "Int_Type"; break;
    case PrimType::Bool: std::cout << "Bool_Type"; break;
  }
  std::cout << ")";
}

/** Get Defs (of Expression) **/
void Get::compute() {
  Var* v = env->getVar(id);
  val = v->val;
  type = v->type;
}
void Get::assemble() {
  asmF << "\t\tldr r0, =" << id << '\n';
  asmF << "\t\tldr " << regs[sp] << ", [r0]\n";
}
int Get::typeCheck() {
  if(env == NULL) {
    std::cout << "Type Violation in Line " << line << " : " << id << " not declared" << "\n";
    return 1;
  }
  Var* v = env->getVar(id);
  if(v == NULL) {
    std::cout << "Type Violation in Line " << line << " : " << id << " not declared" << "\n";
    return 1;
  }
  type = v->type;
  return 0;
}
void Get::print() {
  std::cout << "Get(" << id << ")";
}

/** Statement Def **/

/** Block Defs (of Statement) **/
void Block::compute() {
  for(Statement* stm: stms) {
    stm->env = env;
    stm->compute();
    if(stm->e != NULL && stm->isRet) {
      e = stm->e;
      break;
    }
  }
}
void Block::assemble() {
  for(Statement* stm: stms) {
    stm->env = env;
    stm->assemble();
  }
}
int Block::typeCheck() {
  int i = 0;
  for(Statement* stm: stms) {
    stm->env = env;
    if(stm->typeCheck()) {
      return 1;
    }
  }
  return 0;
}
void Block::print() {
  std::cout << "Block(";
  for(Statement* stm: stms) {
    stm->print();
    std::cout << ", ";
  }
  std::cout << "\b \b\b \b)";
}
void Block::addStatement(Statement* stm) {
  stms.push_back(stm);
}

/** Print Defs (of Statement) **/
void Print::compute() {
  e->env = env;
  e->compute();
  switch (e->type) {
    case PrimType::Int: std::cout << e->val; break;
    case PrimType::Bool:
      if(e->val)
        std::cout << "true";
      else
        std::cout << "false";
    break;
    default: std::cout << e->val; break;
  }
}
void Print::assemble() {
  e->env = env;
  e->assemble();
  asmF << "\t\tldr r0, =d\n";
  asmF << "\t\tbl printf\n";
}
int Print::typeCheck() {
  e->env = env;
  if(e->typeCheck()) {
    return 1;
  }
  if(e->type != PrimType::Int) {
    std::cout << "Type Violation in Line " << line << " : " << "Can only print INT or STR" << "\n";;
    return 1;
  }
  return 0;
}
void Print::print() {
  std::cout << "Print(";
  e->print();
  std::cout << ")";
}
void PrintStr::compute() {
  std::cout << str;
}
void PrintStr::assemble() {
  asmF << "\t\tldr r0, =s" << index << "\n\t\tbl printf\n";
}
int PrintStr::typeCheck() {
  return 0;
}
void PrintStr::print() {
  std::cout << "PrintStr(" << str << ")";
}
void PrintStr::setStr(std::string s) {
  str = s.substr(s.find_first_of('"') + 1, s.find_last_of('"') - 1);
  index = glbStrs.size();
  glbStrs.push_back(str);
}
void PrintLn::compute() {
  e->env = env;
  e->compute();
  switch (e->type) {
    case PrimType::Int: std::cout << e->val << "\n"; break;
    case PrimType::Bool:
      if(e->val)
        std::cout << "true" << "\n";
      else
        std::cout << "false" << "\n";
    break;
    default: std::cout << e->val; break;
  }
}
void PrintLn::assemble() {
  e->env = env;
  e->assemble();
  asmF << "\t\tldr r0, =dn\n";
  asmF << "\t\tbl printf\n";
}
int PrintLn::typeCheck() {
  e->env = env;
  if(e->typeCheck()) {
    return 1;
  }
  if(e->type != PrimType::Int) {
    std::cout << "Type Violation in Line " << line << " : " << "Can only print INT or STR" << "\n";;
    return 1;
  }
  return 0;
}
void PrintLn::print() {
  std::cout << "PrintLn(";
  e->print();
  std::cout << ")";
}
void PrintStrLn::compute() {
  std::cout << str << "\n";
}
void PrintStrLn::assemble() {
  asmF << "\t\tldr r0, =s" << index << "\n\t\tbl printf\n";
}
int PrintStrLn::typeCheck() {
  return 0;
}
void PrintStrLn::print() {
  std::cout << "PrintStrLn(" << str << ")";
}
void PrintStrLn::setStr(std::string s) {
  str = s.substr(s.find_first_of('"') + 1, s.find_last_of('"') - 1);
  index = glbStrs.size();
  glbStrs.push_back(str + "\\n");
}

/** If Defs (of Statement) **/
void If::compute() {
  exp->env = env;
  exp->compute();
  if(exp->val) {
    stm1->env = env;
    stm1->compute();
    if(stm1->e != NULL) {e = stm1->e;}
  }
  else {
    stm2->env = env;
    stm2->compute();
    if(stm2->e != NULL) {e = stm2->e;}
  }
}
void If::assemble() {
  exp->env = env;
  exp->assemble();
  stm2->env = env;
  stm1->env = env;
  asmF << "\t\tcmp " << regs[sp] << ", #0\n";
  asmF << "\t\tbeq els" << c_ind << "\n";
  stm1->assemble();
  asmF << "\t\tb end" << c_ind << "\n";
  asmF << "els" << c_ind << ":\n";
  stm2->assemble();
  asmF << "end" << c_ind << ":\n";
  c_ind++;
}
int If::typeCheck() {
  exp->env = env;
  stm1->env = env;
  stm2->env = env;
  if(exp->typeCheck() || stm1->typeCheck() || stm2->typeCheck()) {
    return 1;
  }
  if(exp->type != PrimType::Bool) {
    std::cout << "Type Violation in Line " << line << " : " << "if(op) op in not BOOL" << "\n";;
    return 1;
  }
  return 0;
}
void If::print() {
  std::cout << "If(";
  exp->print();
  std::cout << ", ";
  stm1->print();
  std::cout << ", ";
  stm2->print();
  std::cout << ")";
}
void If::addFields(Exp* e, Statement* s1, Statement* s2) {
  exp = e;
  stm1 = s1;
  stm2 = s2;
}

/** While Defs (of Statement) **/
void While::compute() {
  exp->env = env;
  exp->compute();
  while(exp->val) {
    stm->env = env;
    stm->compute();
    if(stm->e != NULL) {e = stm->e;}
    exp->env = env;
    exp->compute();
  }
}
void While::assemble() {
  exp->env = env;
  asmF << "l" << l_ind << ":\n";
  exp->assemble();
  asmF << "\t\tcmp " << regs[sp] << ", #0\n";
  asmF << "\t\tbeq le" << l_ind << '\n';
  stm->assemble();
  asmF << "\t\tb l" << l_ind << '\n';
  asmF << "le" << l_ind << ":\n";
  l_ind++;
}
int While::typeCheck() {
  exp->env = env;
  stm->env = env;
  if(exp->typeCheck() || stm->typeCheck()) {
    return 1;
  }
  if(exp->type != PrimType::Bool) {
    std::cout << "Type Violation in Line " << line << " : " << "while(op) op in not BOOL" << "\n";;
    return 1;
  }
  return 0;
}
void While::print() {
  std::cout << "While(";
  exp->print();
  std::cout << ", ";
  stm->print();
  std::cout << ")";
}
void While::addFields(Exp* e, Statement* s) {
  exp = e;
  stm = s;
}

/** Return Defs (of Statement) **/
void Return::compute() {
  isRet = 1;
  return;
}
void Return::assemble() {
  e->assemble();
  asmF << "\t\tmov r0, " << regs[sp] << '\n';
  asmF << "\t\tbx lr\n";
}
int Return::typeCheck() {
  isRet = 1;
  return 0;
}
void Return::print() {
  std::cout << "Return(";
  e->print();
  std::cout << ")";
}

/** Assign Defs (of Statement) **/
void Assign::compute() {
  e->env = env;
  e->compute();
  Var* v = env->getVar(id);
  v->val = e->val;
}
void Assign::assemble() {
  e->assemble();
  asmF << "\t\tldr r0, =" << id << '\n';
  asmF << "\t\tstr " << regs[sp] << ", [r0]\n";
}
int Assign::typeCheck() {
  e->env = env;
  if(env == NULL) {
    std::cout << "Type Violation in Line " << line << " : " << id << " not declared" << "\n";
    return 1;
  }
  Var* v = env->getVar(id);
  if(e->typeCheck()) {
    return 1;
  }
  if(v == NULL || e->type != v->type) {
    std::cout << "Type Violation in Line " << line << " : " << id << " not declared or exp of wrong type" << "\n";
    return 1;
  }
  return 0;
}
void Assign::print() {
  std::cout << "Assign(" << id << ", ";
  e->print();
  std::cout << ")";
}
void Assign::addFields(std::string s, Exp* ep) {
  id = s;
  e = ep;
}

/** Class Def **/
void Class::print() {
  std::cout << "Class(" << id << ", ";
  methodList->print();
  std::cout << ")";
}
void Class::addFields(std::string s, VarList* v, MethodList* m) {
  id = s;
  varList = v;
  methodList = m;
}
int Class::typeCheck() {
  if(classGlob.getClass(id) != NULL) {
    std::cout << "Type Violation in Line " << line << " : " << id << " class already declared" << "\n";
    typeerror = 1;
    return 1;
  }
  return 0;
}
void Class::assemble() {
  methodList->assemble();
}

/** Class List Defs **/
void ClassList::addClass(Class* c) {
  classes.push_back(c);
}
Class* ClassList::getClass(std::string s) {
  for(Class* c: classes) {
    if(c->id.compare(s) == 0)
      return c;
  }
  return NULL;
}
void ClassList::print() {
  std::cout << "ClassList(";
  for(Class* c: classes) {
    c->print();
    std::cout << ", ";
  }
  std::cout << "\b \b\b \b)";
}
void ClassList::assemble() {
  for(Class* c: classes)
    c->assemble();
}

/** Method Defs **/
void Method::print() {
  std::cout << "Method(" << id << ", ";
  varList->print();
  std::cout << ", ";
  blk->print();
  std::cout << ", ";
  rexp->print();
  std::cout << ")";
}
void Method::compute() {
  Exp* e = NULL;
  if(blk != NULL) {
    blk->env = varList;
    blk->compute();
    e = blk->e;
  }
  if(e != NULL) {
    e->env = varList;
    e->compute();
    val = e->val;
  }
  else {
    rexp->env = varList;
    rexp->compute();
    val = rexp->val;
  }
}
void Method::assemble() {
  // TODO
  asmF << id << ":\n";
  asmF << "\t\tpush {lr}\n";
  blk->assemble();
  rexp->assemble();
  asmF << "\t\tmov r0, " << regs[sp] << '\n';
  asmF << "\t\tpop {pc}\n";
}
void Method::addFields(std::string s, VarList* v1, VarList* v2, Block* b, PrimType t, Exp* e) {
  id = s;
  formList = v1;
  if(v2 == NULL) {
    varList = new VarList;
  }
  else {
    varList = v2;
  }
  blk = b;
  type = t;
  rexp = e;
}
int Method::typeCheck() {
  if(blk != NULL) {
    blk->env = varList;
    if(blk->typeCheck()) {
      return 1;
    }
  }
  rexp->env = varList;
  if(rexp->typeCheck()) {
    return 1;
  }
  if(rexp->type != type) {
    std::cout << "Type Violation in Line " << line << " : " << id << "() method has wrong return type" << "\n";
    return 1;
  }
  return 0;
}

/** Method List Defs **/
Method* MethodList::getMethod(std::string s) {
  for(Method* m: methods) {
    if(m->id.compare(s) == 0)
      return m;
  }
  return NULL;
}
void MethodList::addMethod(Method* m) {
  methods.push_back(m);
}
void MethodList::print() {
  std::cout << "MethodList(";
  for(Method* m: methods) {
    m->print();
    std::cout << ", ";
  }
  std::cout << "\b \b\b \b)";
}
void MethodList::assemble() {
  for(Method* m: methods) {
    asmF << "\n\n";
    m->assemble();
  }
}

/** Var Defs **/
void Var::print() {
  std::cout << "Var(" << id << ", ";
  switch (type) {
    case PrimType::Int: std::cout << "Int_Type"; break;
    case PrimType::Bool: std::cout << "Bool_Type"; break;
    case PrimType::Ref: std::cout << "Ref_Type"; break;
    case PrimType::Obj: std::cout << "Obj_Type"; break;
  }
  std::cout << ")";
}

/** Var List Defs **/
Var* VarList::getVar(std::string s) {
  for(Var* v: vars) {
    if(v->id.compare(s) == 0)
      return v;
  }
  return NULL;
}
void VarList::addVar(Var* v) {
  vars.push_back(v);
  glbInts.push_back(v->id);
}
void VarList::print() {
  std::cout << "VarList(";
  for(Var* v: vars) {
    v->print();
    std::cout << ", ";
  }
  std::cout << ")";
}
void VarList::addClassVars(VarList* cvs) {
  if(cvs == NULL)
    return;
  for(Var* cv: cvs->vars) {
    Var* v = new Var;
    v->id = "this." + cv->id;
    v->type = cv->type;
    vars.push_back(v);
  }
}

/** Object Defs (of Exp) **/
void Object::compute() {
  cls = new Class(*(classGlob.getClass(typeClass)));
  Method* f = new Method(*(cls->methodList->getMethod(func)));
  f->varList->addClassVars(cls->varList);
  f->compute();
  val = f->val;
}
void Object::assemble() {
  cls = new Class(*(classGlob.getClass(typeClass)));
  Method* f = new Method(*(cls->methodList->getMethod(func)));
  asmF << "\t\tbl " << func << '\n';
  asmF << "\t\tmov " << regs[sp] << ",r0 \n";
}
int Object::typeCheck() {
  if(classGlob.getClass(typeClass) == NULL || classGlob.getClass(typeClass)->methodList->getMethod(func) == NULL) {
    std::cout << "Type Violation in Line " << line << " : " << typeClass << " class not declared or " << func << "() method not declared" << "\n";
    return 1;
  }
  Class* c = new Class(*(classGlob.getClass(typeClass)));
  Method* f = new Method(*(c->methodList->getMethod(func)));
  f->varList->addClassVars(c->varList);
  if(f->typeCheck()) {
    //std::cout << "Type Violation in Line " << line << "\n";
    return 1;
  }
  return 0;
}
void Object::print() {
  std::cout << "Object(" << typeClass << ", " << func << ")";
}
void Object::instance(std::string ci) {
  typeClass = ci;
}
void Object::callFunc(std::string f) {
  func = f;
  type = PrimType::Int;
}

/** Assembly Helpers **/
void openFile() {
  // Open
  asmF.open(oFile);

  // Print Text
  asmF << ".section\t.data\n";

  // Print Global Str
  for(int i = 0; i < glbInts.size(); i++) {
    asmF << glbInts[i] << ":\t\t.word\t\t0\n";
  }
  asmF << "\n";

  // Print Text
  asmF << ".section\t.text\nd:\t\t.asciz\t\t\"%d\"\ndn:\t\t.asciz\t\t\"%d\\n\"\n";

  // Print Global Str
  for(int i = 0; i < glbStrs.size(); i++) {
    asmF << "s" << i << ":\t\t.asciz\t\t\"" << glbStrs[i] << "\"\n";
  }
  asmF << "\n";

  // Print Middle
  asmF << ".global\t\tmain\n.balign\t\t4\n\nmain:\n\t\tpush {lr}\n";
}

void closeMain() {
    asmF << "\t\tpop {pc}\n";
}

void closeFile() {
  asmF.close();
}
