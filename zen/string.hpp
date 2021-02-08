#ifndef ZEN_STRING_HPP
#define ZEN_STRING_HPP

#include <string>

#include "zen/maybe.hpp"

namespace zen {

  // TODO This should be a strong type
  using Glyph = char32_t;

  inline constexpr const Glyph eof = 0xFFFF;

  // TODO The internal representation should be converted to UTF-8
  using String = std::basic_string<Glyph>;

  // TODO The internal representation should be converted to UTF-8
  using string_view = std::basic_string_view<Glyph>;

  template<>
  class Maybe<Glyph> {

    Glyph value;

  public:

    inline Maybe():
      value(eof) {}

    inline Maybe(Glyph value):
      value(value) {}

    Glyph& operator*() {
      ZEN_ASSERT(value != eof);
      return value;
    }

    const Glyph& operator*() const {
      ZEN_ASSERT(value != eof);
      return value;
    }

    bool is_some() const {
      return value != eof;
    }

    bool is_empty() const {
      return value == eof;
    }

  };

  // FIXME Currently only works for ASCII values.
  inline String from_utf8(std::string_view raw) {
    return String { raw.begin(), raw.end() };
  }

  template<std::size_t N>
  inline String from_utf8(const char ptr[N]) {
    return String { ptr, ptr + N };
  }

#define ZEN_STRING_LITERAL(literal) ::zen::from_utf8(literal)

}

#endif // of #ifndef ZEN_STRING_HPP
