#pragma once
#include "assembly.hh"


class Printer {
public:
  virtual void accept_printer(class VisitorPrinter&) = 0;
};

class VisitorPrinter {
public:
  virtual void visit(class Assembly &a) = 0;
 // virtual void visit(class Assembler &a) = 0;
 // virtual void visit(class VM &a) = 0;
};

class AssemblyVistorPrinter : VisitorPrinter {
};