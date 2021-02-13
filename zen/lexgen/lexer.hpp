#ifndef ZEN_LEXGEN_LEXER_HPP
#define ZEN_LEXGEN_LEXER_HPP

#include <functional>

#include "zen/byte.hpp"
#include "zen/string.hpp"
#include "zen/variant.hpp"
#include "zen/stream.hpp"
#include "zen/lexgen/common.hpp"

namespace zen {

  namespace lexgen {

    using TokenValue = Maybe<Variant<String, Glyph>>;

    enum class TokenType {
      eof,
      pub_keyword,
      identifier,
      semi,
      vbar,
      open_bracket,
      close_bracket,
      open_paren,
      close_paren,
      string,
      character,
    };

    class Token {

      TokenType type;
      TokenValue value;

    public:

      inline Token(TokenType type):
        type(type), value() {}

      inline Token(TokenType type, TokenValue value):
        type(type), value(value) {}

      Token(const Token& token) = default;
      Token(Token&& token) = default;

      inline TokenType get_type() const {
        return type;
      }

      inline bool has_value() const {
        return value.is_some();
      }

      inline TokenValue get_value() const {
        return value;
      }

    };

    using BytePeekStream = PeekStream<Byte>;

    class Lexer {

      BytePeekStream& bytes;

      std::size_t offset;

      inline Result<Glyph> get_char() {
        auto ch = bytes.get();
        if (ch.is_empty()) {
          return right(eof);
        }
        offset++;
        return right(*ch);
      }

      inline Result<Glyph> peek_char() {
        auto ch = bytes.peek(1);
        if (ch.is_empty()) {
          return right(eof);
        }
        return right(*ch);
      }

      Result<void> take_while(String& str, std::function<bool(Glyph)> pred);

      Result<Maybe<Token>> try_keyword(String name, TokenType type);

      Result<Glyph> lex_escape_sequence();

    public:

      inline Lexer(BytePeekStream& bytes, std::size_t offset = 0):
        bytes(bytes), offset(offset) {}

      Result<Token> lex();

    };

  }

}

#endif // of #ifndef ZEN_LEXGEN_LEXER_HPP
