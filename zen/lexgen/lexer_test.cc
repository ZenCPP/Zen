
#include "gtest/gtest.h"

#include "zen/lexgen/lexer.hpp"
#include "zen/string.hpp"

using namespace zen;
using namespace zen::lexgen;

TEST(LexgenLexerTest, CanLexStrings) {
  std::basic_string<Byte> test_text = ZEN_BYTE_LITERAL("\"Foo the bar.\"");
  zen::StreamWrapper<std::basic_string<Byte>> wrapper(test_text);
  Lexer l(wrapper);
  auto t0 = l.lex().unwrap();
  ASSERT_EQ(t0.get_type(), TokenType::string);
  ASSERT_TRUE(t0.has_value());
  ASSERT_EQ(std::get<0>(*t0.get_value()), ZEN_STRING_LITERAL("Foo the bar."));
}

TEST(LexgenLexerTest, CanLexIdentifiers) {
  std::basic_string<Byte> test_text = ZEN_BYTE_LITERAL("foo bar bax");
  zen::StreamWrapper<std::basic_string<Byte>> wrapper(test_text);
  Lexer l(wrapper);
  auto t0 = l.lex().unwrap();
  ASSERT_EQ(t0.get_type(), TokenType::identifier);
  ASSERT_TRUE(t0.has_value());
  ASSERT_EQ(std::get<0>(*t0.get_value()), ZEN_STRING_LITERAL("foo"));
}

