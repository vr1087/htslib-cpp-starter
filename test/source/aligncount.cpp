#include <aligncount/aligncount.h>
#include <aligncount/version.h>
#include <doctest/doctest.h>

#include <string>

TEST_CASE("Aligncount") {
  using namespace aligncount;

  Aligncount aligncount("Tests");

  CHECK(aligncount.greet(LanguageCode::EN) == "Hello, Tests!");
  CHECK(aligncount.greet(LanguageCode::DE) == "Hallo Tests!");
  CHECK(aligncount.greet(LanguageCode::ES) == "¡Hola Tests!");
  CHECK(aligncount.greet(LanguageCode::FR) == "Bonjour Tests!");
}

TEST_CASE("Aligncount version") {
  static_assert(std::string_view(ALIGNCOUNT_VERSION) == std::string_view("1.0"));
  CHECK(std::string(ALIGNCOUNT_VERSION) == std::string("1.0"));
}