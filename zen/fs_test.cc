
#include "gtest/gtest.h"

#include "zen/fs.hpp"

using namespace ZEN_NAMESPACE;
using namespace ZEN_NAMESPACE::fs;

static constexpr std::string_view LOREM_IPSUM = 
  "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Vivamus vestibulum\n"
  "erat eu arcu ultrices, in auctor erat efficitur. Etiam et eros vulputate,\n"
  "lobortis eros in, rutrum tellus. In urna sem, semper vitae volutpat sit amet,\n"
  "vulputate non diam. Aenean ligula dolor, bibendum non nulla tristique,\n"
  "tristique dapibus eros. Nulla facilisi. Nulla pellentesque aliquam felis, ac\n"
  "condimentum felis venenatis eget. Curabitur sagittis a lectus vel faucibus.\n"
  "Nullam convallis vulputate posuere.\n"
  "\n"
  "Etiam pharetra et tellus sit amet viverra. Interdum et malesuada fames ac ante\n"
  "ipsum primis in faucibus. Curabitur quis lobortis ipsum. Nam ullamcorper\n"
  "vulputate lectus quis aliquam. Vivamus sed finibus diam. Phasellus sem nulla,\n"
  "lobortis et eros eget, lacinia hendrerit eros. Nullam nec eleifend augue, sit\n"
  "amet sagittis nisi. Morbi turpis arcu, condimentum sed posuere a, vehicula\n"
  "gravida libero. Nullam sed dignissim nibh.\n"
  "\n"
  "Praesent elit metus, viverra id lacus id, elementum pellentesque massa.\n"
  "Praesent eget vestibulum ante. Vestibulum interdum ac nulla a elementum.\n"
  "Quisque varius, lorem ac dignissim vestibulum, massa lorem ornare felis, in\n"
  "consectetur est purus eget ante. Vestibulum gravida nisl justo, vitae\n"
  "pellentesque ante imperdiet at. Interdum et malesuada fames ac ante ipsum\n"
  "primis in faucibus. Class aptent taciti sociosqu ad litora torquent per conubia\n"
  "nostra, per inceptos himenaeos.";

TEST(FSTest, OpenFile) {
  auto f = file_from_path("test-data/lorem.txt").unwrap();
  auto contents = f.get_contents().unwrap();
  ASSERT_EQ(contents.as_string_view(), LOREM_IPSUM);
}

