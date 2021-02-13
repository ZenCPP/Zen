
#include <functional>

#include "zen/macros.h"
#include "zen/lexgen/lexer.hpp"
#include "zen/string.hpp"

namespace zen {

  namespace lexgen {

    static inline bool is_alpha(Glyph ch) {
      return (ch >= 65 && ch <= 90) || (ch >= 96 && ch <= 122);
    }

    static inline bool is_ident_start(Glyph ch) {
      return is_alpha(ch);
    }

    static inline bool is_decimal(Glyph ch) {
      return ch >= 48 && ch <= 57;
    }

    static inline bool is_ident_part(Glyph ch) {
      return is_alpha(ch) || is_decimal(ch);
    }

    static inline bool is_whitespace(Glyph ch) {
      return ch == '\n' || ch == ' ' || ch == '\t' || ch == '\r';
    }

    Result<void> Lexer::take_while(String& str, std::function<bool(Glyph)> pred) {
      for (;;) {
        auto ch = get_char();
        ZEN_TRY(ch);
        if (!pred(*ch)) {
          break;
        }
        str.push_back(*ch);
      }
      return right();
    }

#define ZEN_LEX_CHAR(actual, expected, name) \
  { \
    if (*actual == expected) { \
      get_char(); \
      return right(Token(TokenType::name)); \
    } \
  }

#define ZEN_LEX_KEYWORD(str, name) \
  { \
    auto result = try_keyword(str, TokenType::name); \
    ZEN_TRY(result); \
    if (result->is_some()) { \
      return right(**result); \
    } \
  }

    Result<Maybe<Token>> Lexer::try_keyword(String name, TokenType type) {
      std::size_t i = 0;
      for (;;) {
        auto ch = peek_char();
        ZEN_TRY(ch);
        if (*ch != name[i]) {
          return right(Empty());
        }
        get_char();
      }
      return right(Token(type));
    }

    Result<Glyph> Lexer::lex_escape_sequence() {
      auto c0 = get_char();
      ZEN_TRY(c0);
      switch (*c0) {
        case 'a': return right('\a');
        case 'b': return right('\b');
        case 'f': return right('\f');
        case 'n': return right('\n');
        case 'r': return right('\r');
        case 't': return right('\t');
        case 'v': return right('\v');
        case '0': return right('\0');
        default:  return left(error::unexpected_character);
      }
    }

    Result<Token> Lexer::lex() {

      auto c0 = get_char();
      ZEN_TRY(c0);

      if (*c0 == eof) {
        return right(Token(TokenType::eof, Empty()));
      }

      while (is_whitespace(*c0)) {
        c0 = get_char();
        ZEN_TRY(c0);
      }

      ZEN_LEX_CHAR(c0, '|', vbar)
      ZEN_LEX_CHAR(c0, ';', semi)
      ZEN_LEX_CHAR(c0, '[', open_bracket)
      ZEN_LEX_CHAR(c0, ']', close_bracket)
      ZEN_LEX_CHAR(c0, '(', open_paren)
      ZEN_LEX_CHAR(c0, ')', close_paren)

      ZEN_LEX_KEYWORD(ZEN_STRING_LITERAL("pub"), pub_keyword)

      if (is_ident_start(*c0)) {
        String name { *c0 };
        auto result = take_while(name, is_ident_part);
        if (result.is_left()) {
            return left(result.left());
        }
        return right(Token(TokenType::identifier, some(name)));
      }

      if (*c0 == '\'') {
        Glyph ch;
        auto c1 = get_char();
        ZEN_TRY(c1);
        if (*c1 == '\\') {
          auto c2 = get_char();
          auto unescaped = lex_escape_sequence();
          ZEN_TRY(unescaped);
        } else {
          ch = *c1;
        }
        auto c3 = get_char();
        ZEN_TRY(c3);
        if (*c3 != '\'') {
          return left(error::unexpected_character);
        }
        return right(Token(TokenType::character, some(ch)));
      }

      if (*c0 == '"') {
        String text;
        bool escaping = false;
        for (;;) {
          if (escaping) {
            auto ch = lex_escape_sequence();
            ZEN_TRY(ch);
            escaping = false;
          } else {
            auto c1 = get_char();
            if (*c1 == '"') {
              break;
            } else if (*c1 == '\\') {
              escaping = true;
            } else {
              text.push_back(*c1);
            }
          }
        }
        return right(Token(TokenType::string, some(text)));
      }

      return left(error::unexpected_character);
    }

  }

}

