#ifndef ZEN_LEXGEN_COMMON_HPP
#define ZEN_LEXGEN_COMMON_HPP

#include "zen/either.hpp"
namespace zen {

  namespace lexgen {

    enum class error {
      could_not_open_file,
      failed_to_read_char,
      unexpected_character,
    };

    template<typename T>
    using Result = Either<error, T>;

  }

}

#endif // of #ifndef ZEN_LEXGEN_COMMON_HPP
