#include <cassert>


#include <catch2/catch_all.hpp>
#include <gnu/lib-names.h>

#include "../svlm_dyn_loader.cc"

TEST_CASE("dynamic loader test 1") {
  SvlmDynLoader loader_math(LIBM_SO);
  ModuleRegistry registry_math(loader_math, "Math");

  registry_math.register_function<double(double)>("sin", nullptr);
  auto sin_function = registry_math.get_function<double(double)>("sin");
  double value = 0.5;
  cout << "sin: " << sin_function(value) << "\n";

  SvlmLibLoader trig;
  trig.load_func(LIBM_SO, "cos");
  auto cos_function = trig.get_function<double(double)>(LIBM_SO, "cos");
  cout << "cos: " << cos_function(value) << "\n";


}