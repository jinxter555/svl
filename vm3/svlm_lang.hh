#pragma once
#include <memory>
#include "tree.hh"

class SvlmLang {
private:
  std::shared_ptr<Tree> context;
public:
  SvlmLang() { context = std::make_shared<Tree>();}
};
