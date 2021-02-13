#ifndef ZEN_LEXGEN_PARSER_HPP
#define ZEN_LEXGEN_PARSER_HPP

#include "zen/stream.hpp"

#include "zen/lexgen/common.hpp"
#include "zen/lexgen/lexer.hpp"
#include "zen/lexgen/nodes.hpp"

namespace zen {

  namespace lexgen {

    using TokenStream = PeekStream<Token>;

    class Parser {

      TokenStream& tokens;

    public:

      inline Parser(TokenStream& tokens):
        tokens(tokens) {}

      Result<Node> parse_expr();

      Result<Node> parse();

    };

  }

}

#endif // of #ifndef ZEN_LEXGEN_PARSER_HPP
