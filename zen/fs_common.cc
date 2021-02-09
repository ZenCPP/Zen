
#include "zen/fs.hpp"

#include <string>
#include <fstream>
#include <streambuf>

ZEN_NAMESPACE_START

namespace fs {

  Result<std::string> read_file(Path p) {

    std::ifstream input(p);

    if (!input) {
      return left(ZEN_COULD_NOT_OPEN_FILE);
    }

    std::string str;

    input.seekg(0, std::ios::end);
    str.reserve(input.tellg());
    input.seekg(0, std::ios::beg);

    str.assign((std::istreambuf_iterator<char>(input)),
                std::istreambuf_iterator<char>());

    return right(str);

  }

}

ZEN_NAMESPACE_END

