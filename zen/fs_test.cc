
#include "gtest/gtest.h"

#include "zen/fs.hpp"

using namespace zen::fs;

TEST(FSTest, OpenFile) {
  file_from_path("test-data/lorem.txt").unwrap();
}

