#pragma once
#include <memory>
#include "tree.hh"

class SvlmLang {
  friend class SvlmInteractive;
private:
  std::shared_ptr<Tree> context;
public:
  SvlmLang(std::shared_ptr<Tree> tp) { context = tp; }
};

