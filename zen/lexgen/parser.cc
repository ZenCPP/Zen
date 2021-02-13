
#include "zen/lexgen/parser.hpp"

ZEN_NAMESPACE_START

namespace lexgen {

  Result<Node> Parser::parse_expr() {
    return left(error::failed_to_read_char);
  }

}

ZEN_NAMESPACE_END