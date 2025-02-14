#include <cassert>
#include <iostream>
#include <catch2/catch_all.hpp>
#include <gnu/lib-names.h>

#include "../svlm_dyn_loader.cc"

TEST_CASE("dynamic loader test 1") {
  SvlmDynLoader loader_math(LIBM_SO);
  //ModuleRegistry registry_math(loader_math, "Math");

  //registry_math.register_function<double(double)>("sin", nullptr);
  //auto sin_function = registry_math.get_function<double(double)>("sin");
  double value = 0.5;

  SvlmLibLoader trig;
  trig.load_func(LIBM_SO, "cos");
  trig.load_func(LIBM_SO, "tan");
  auto cos_function = trig.get_function<double(double)>(LIBM_SO, "cos");
  auto sin_function = trig.get_function<double(double)>(LIBM_SO, "sin");
  auto tan_function = trig.get_function<double(double)>(LIBM_SO, "tan");
  auto blah_function = trig.get_function<double(double)>(LIBM_SO, "blah");
  cout << "sin: " << sin_function(value) << "\n";
  cout << "cos: " << cos_function(value) << "\n";
  cout << "tan: " << tan_function(value) << "\n";
  CHECK(blah_function==nullptr); //cout << "blah: " << blah_function(value) << "\n";


}