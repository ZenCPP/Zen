
#ifndef ZEN_CONFIG_HPP
#define ZEN_CONFIG_HPP

#include "zen/clone_ptr.hpp"
#include "zen/sequence_map.hpp"

namespace zen {

  using string = std::string;
  using decimal = double;
  using integer = int64_t;

  class value;

  class array {

    std::vector<value> elements;

  public:

    inline array(std::initializer_list<value> elements):
      elements(elements) {};

  };

  class object {

    sequence_map<std::string, value> properties;

  public:

    inline object() {};

    inline object(std::initializer_list<std::pair<const std::string, value>> properties):
      properties(properties) {};

  };


  enum class value_kind {
    array,
    object,
    string,
    integer,
    decimal,
    boolean,
  };

  class value {

    value_kind kind;

    union {
      array a;
      object o;
      string s;
      integer i;
      decimal d;
      bool b;
    };

  public:

    inline value(array&& a): a(std::move(a)) {};
    inline value(object&& o): o(std::move(o)) {};
    inline value(string&& s): s(std::move(s)) {};
    inline value(integer&& i): i(std::move(i)) {};
    inline value(decimal&& d): d(std::move(d)) {};
    inline value(bool&& b): b(std::move(b)) {};

    inline value(const array& a): a(std::move(a)) {};
    inline value(const object& o): o(std::move(o)) {};
    inline value(const string& s): s(std::move(s)) {};
    inline value(const integer& i): i(std::move(i)) {};
    inline value(const decimal& d): d(std::move(d)) {};
    inline value(const bool& b): b(std::move(b)) {};

    value(value&& other) {
      switch (kind) {
        case value_kind::object:
          o = std::move(other.o);
          break;
        case value_kind::array:
          a = std::move(other.a);
          break;
        case value_kind::integer:
          i = std::move(other.i);
          break;
        case value_kind::string:
          s = std::move(other.s);
          break;
        case value_kind::decimal:
          d = std::move(other.d);
          break;
        case value_kind::boolean:
          b = std::move(other.b);
          break;
      }
    }

    value(const value& other) {
      switch (kind) {
        case value_kind::object:
          o = other.o;
          break;
        case value_kind::array:
          a = other.a;
          break;
        case value_kind::integer:
          i = other.i;
          break;
        case value_kind::string:
          s = other.s;
          break;
        case value_kind::decimal:
          d = other.d;
          break;
        case value_kind::boolean:
          b = other.b;
          break;
      }
    }

    value& operator=(value&& other) {
      switch (kind) {
        case value_kind::object:
          o = std::move(other.o);
          break;
        case value_kind::array:
          a = std::move(other.a);
          break;
        case value_kind::integer:
          i = std::move(other.i);
          break;
        case value_kind::string:
          s = std::move(other.s);
          break;
        case value_kind::decimal:
          d = std::move(other.d);
          break;
        case value_kind::boolean:
          b = std::move(other.b);
          break;
      }
      return *this;
    }

    value& operator=(const value& other) {
      switch (kind) {
        case value_kind::object:
          o = other.o;
          break;
        case value_kind::array:
          a = other.a;
          break;
        case value_kind::integer:
          i = other.i;
          break;
        case value_kind::string:
          s = other.s;
          break;
        case value_kind::decimal:
          d = other.d;
          break;
        case value_kind::boolean:
          b = other.b;
          break;
      }
      return *this;
    }

    ~value() {
      switch (kind) {
        case value_kind::array:
          a.~array();
          break;
        case value_kind::object:
          o.~object();
          break;
        case value_kind::string:
          s.~string();
          break;
        case value_kind::integer:
          break;
        case value_kind::decimal:
          break;
        case value_kind::boolean:
          break;
      }
    }

  };

}

#endif // ZEN_CONFIG_HPP
