#ifndef SVLM_DYN_LOADER_HH
#define SVLM_DYN_LOADER_HH

#pragma once
#include <string>
#include <memory>
#include <unordered_map>
//#include "ast_map.hh"
//#include "svlm_lang.hh"
//----------------------------------------------------------------------- SvlmBind
// if func doesn't exist in module
// look up symbols func. if it exists
// assign new 

using namespace std;

class SvlmDynLoader {
private:
  void *handle;
  string library_name;
  unordered_map<string, void*> functions;
public:
  SvlmDynLoader(const string& l);
  ~SvlmDynLoader();

  template <typename Func> 
  Func* load_function(const std::string& functionName);

  template <typename Func> 
  Func* get_function(const string& function_name);
};


class SvlmLibLoader {
private:
  unordered_map<string, unique_ptr<SvlmDynLoader>> libs;
public:
  SvlmLibLoader();
  bool load_lib(const string& l);
  bool load_func(const string& l, const string& f);

  template <typename Func> 
  Func* get_function(const string& l, const string& f);

};

#endif