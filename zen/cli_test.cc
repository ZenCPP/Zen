
#include "gtest/gtest.h"

#include "zen/cli.hpp"

TEST(CLI, WorksOnSample) {

  constexpr auto P = zen::cli::program("edenc")
      .describe("The Eden compiler")
      .add_flag("--help")
        .describe("Show this help message")
        .finish()
      .add_flag<Files>()
        .describe("A lis of files to compile")
        .list()
        .required()
        .finish()
      .finish();

  static const std::vector<std::string_view> args1 = { "--help" };

  auto result1 = P.parse(args1);

}

