#include <sstream>
#include "prompt.hh"
#include "svlm_scanner.hh"
#include "svlm_lang.hh"
#include "svlm_parser.hh"

class SvlmInteractive : public Prompt {
private:
  SvlmLang svlm_lang;
  vslast::SvlmScanner svlm_scanner { std::cin, std::cerr };
  vslast::SvlmParser svlm_parser { &svlm_scanner , &svlm_lang };
public:
  SvlmInteractive(const std::string&hf, const std::string&ps)
    : Prompt(hf, ps) {};
  void accept_prompt(const std::string&l) override; // readyline prompt
  void parse(const std::string &line); // parse readline line
  void interact(const std::string &line); // parse readline line
  void load(const std::string &filename); // load files from command line

  static std::vector<std::string> commands;
};