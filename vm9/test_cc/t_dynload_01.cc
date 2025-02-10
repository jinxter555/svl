#include <cassert>


#include <catch2/catch_all.hpp>
#include <gnu/lib-names.h>

#include "../svlm_dyn_loader.cc"

TEST_CASE("dynamic loader test 1") {
  SvlmDynLoader loader_math(LIBM_SO);
  FunctionRegistry registry_math(loader_math);

  registry_math.register_function<double(double)>("sin");
  auto sin_function = registry_math.get_function<double(double)>("sin");
  double value = 0.5;
  cout << sin_function(value) << "\n";

}