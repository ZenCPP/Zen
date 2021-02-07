
#include "zen/po.hpp"

using namespace zen::po;

int main(int argc, const char* argv[]) {

  auto p = program("myprog")
    .set_description("A sample program that can manage a code project")
    .set_author("Sam Vervaeck")
    .add_flag(flag { "-C", "--work-dir" }
        .set_description("Act as if run from this directory")
        .set_metavar("DIR"))
    .add_subcommand(subcommand { "build" }
      .set_description("Build a project or some files")
      .add_flag(flag { "files" }
        .set_nary(true)
        .set_metavar("PATH")
        .set_description("Source files to build"))
      .add_flag(flag { "--clean" }
        .set_is_bool(true)
        .set_description("Wether to clean intermediate artifacts before building")));

  p.parse(argc, argv);

  return 0;
}
