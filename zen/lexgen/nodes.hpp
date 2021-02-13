#ifndef ZEN_LEXGEN_NODES_HPP
#define ZEN_LEXGEN_NODES_HPP

#include <list>
#include <memory>

#include "zen/string.hpp"
#include "zen/dllist.hpp"

namespace zen {

  namespace lexgen {

    template<typename T>
    using SPtr = std::shared_ptr<T>;

    enum class NodeType {
      rule,
      ref_expr,
      char_expr,
      string_expr,
      choice_expr,
      seq_expr,
    };

    class Node {

      NodeType type;

    public:

      inline Node(NodeType type):
        type(type) {}

      Node* parent_node = nullptr;

      inline NodeType get_type() const {
        return type;
      }

      template<typename DerivedT>
      inline DerivedT& as() {
        return *static_cast<DerivedT*>(this);
      }

    };

    class Expr;

    class Rule : public Node {

      String name;
      SPtr<Expr> expr;

    public:

      inline Rule(String name):
        Node(NodeType::rule), name(name) {}

      string_view get_name() const {
        return name;
      }

    };

    class Expr : public Node {
    public:
      inline Expr(NodeType type):
        Node(type) {}
    };

    class CharExpr : public Expr {

      Glyph ch;

    public:

      inline CharExpr(Glyph ch):
        Expr(NodeType::char_expr), ch(ch) {}

      inline Glyph get_ch() const {
        return ch;
      }

    };

    class ChoiceExpr : public Expr {

      using Elements = DLList<SPtr<Expr>>;

      Elements elements;

    public:

      template<typename RangeT>
      inline ChoiceExpr(RangeT range):
        Expr(NodeType::choice_expr), elements(range.begin(), range.end()) {}

      Elements::Range get_elements() {
        return elements.range();
      }

    };

    class SeqExpr : public Expr {

      using Elements = DLList<SPtr<Expr>>;

      Elements elements;

    public:

      inline SeqExpr():
        Expr(NodeType::seq_expr) {}

      template<typename RangeT>
      inline SeqExpr(RangeT range):
        Expr(NodeType::seq_expr), elements(range) {}

    };

  }

}

#endif // of #ifndef ZEN_LEXGEN_NODES_HPP
