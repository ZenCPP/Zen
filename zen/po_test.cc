
#include "gtest/gtest.h"
#include <sstream>

#include "zen/po.hpp"

using namespace ZEN_NAMESPACE;
using namespace ZEN_NAMESPACE::po;

TEST(POTest, FullExample) {

  auto p = Program("myprog")
    .set_description("A sample program that can manage a code project")
    .set_author("Sam Vervaeck")
    .add_flag(Flag { "-C", "--work-dir" }
        .set_description("Act as if run from this directory")
        .set_metavar("DIR"))
    .add_subcommand(Subcommand { "build" }
      .set_description("Build a project or some files")
      .add_flag(Flag { "files" }
        .set_nary(true)
        .set_metavar("PATH")
        .set_description("Source files to build"))
      .add_flag(Flag { "--clean" }
        .set_is_bool(true)
        .set_description("Wether to clean intermediate artifacts before building")));

  std::stringstream ss;
  p.print_help(ss);

  // TODO asset that the output is the same as some cached text file

}

