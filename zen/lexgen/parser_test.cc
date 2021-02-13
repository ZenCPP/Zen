
#include "gtest/gtest.h"

#include "zen/byte.hpp"
#include "zen/vector.hpp"
#include "zen/lexgen/lexer.hpp"
#include "zen/lexgen/parser.hpp"

using namespace ZEN_NAMESPACE;
using namespace ZEN_NAMESPACE::lexgen;

StreamWrapper<Vector<Token>> lex(ByteString input) {
  zen::StreamWrapper<ByteString> wrapper(input);
  Lexer lexer(wrapper);
  Vector<Token> tokens;
  for (;;) {
    auto token = lexer.lex().unwrap();
    if (token.get_type() == TokenType::eof) {
      break;
    }
  }
  return make_stream(tokens);
}

TEST(LexgenParserTest, CanParseChoiceExpr) {
  auto t1 = lex(ZEN_BYTE_LITERAL("a | b | c"));
  Parser p(t1);
  auto e1 = p.parse_expr();
}

