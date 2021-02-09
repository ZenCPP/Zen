#ifndef ZEN_VALUE_HPP
#define ZEN_VALUE_HPP

#include "zen/clone_ptr.hpp"
#include "zen/sequence_map.hpp"
#include "zen/string.hpp"
#include "zen/vector.hpp"

ZEN_NAMESPACE_START

using Decimal = double;
using Integer = int64_t;

class Value;

class Array {

  Vector<Value> elements;

public:

  inline Array(std::initializer_list<Value> elements):
    elements(elements) {};

};

class Object {

  sequence_map<String, Value> properties;

public:

  inline Object() {};

  inline Object(std::initializer_list<std::pair<const String, Value>> properties):
    properties(properties) {};

  void set_property(String key, Value value);


};


enum class ValueType {
  array,
  object,
  string,
  integer,
  decimal,
  boolean,
};

class Value {

  ValueType kind;

  union {
    Array a;
    Object o;
    String s;
    Integer i;
    Decimal d;
    bool b;
  };

public:

  inline Value(Array&& a): a(std::move(a)) {};
  inline Value(Object&& o): o(std::move(o)) {};
  inline Value(String&& s): s(std::move(s)) {};
  inline Value(Integer&& i): i(std::move(i)) {};
  inline Value(Decimal&& d): d(std::move(d)) {};
  inline Value(bool&& b): b(std::move(b)) {};

  inline Value(const Array& a): a(std::move(a)) {};
  inline Value(const Object& o): o(std::move(o)) {};
  inline Value(const String& s): s(std::move(s)) {};
  inline Value(const Integer& i): i(std::move(i)) {};
  inline Value(const Decimal& d): d(std::move(d)) {};
  inline Value(const bool& b): b(std::move(b)) {};

  Value(Value&& other) {
    switch (kind) {
      case ValueType::object:
        o = std::move(other.o);
        break;
      case ValueType::array:
        a = std::move(other.a);
        break;
      case ValueType::integer:
        i = std::move(other.i);
        break;
      case ValueType::string:
        s = std::move(other.s);
        break;
      case ValueType::decimal:
        d = std::move(other.d);
        break;
      case ValueType::boolean:
        b = std::move(other.b);
        break;
    }
  }

  Value(const Value& other) {
    switch (kind) {
      case ValueType::object:
        o = other.o;
        break;
      case ValueType::array:
        a = other.a;
        break;
      case ValueType::integer:
        i = other.i;
        break;
      case ValueType::string:
        s = other.s;
        break;
      case ValueType::decimal:
        d = other.d;
        break;
      case ValueType::boolean:
        b = other.b;
        break;
    }
  }

  Value& operator=(Value&& other) {
    switch (kind) {
      case ValueType::object:
        o = std::move(other.o);
        break;
      case ValueType::array:
        a = std::move(other.a);
        break;
      case ValueType::integer:
        i = std::move(other.i);
        break;
      case ValueType::string:
        s = std::move(other.s);
        break;
      case ValueType::decimal:
        d = std::move(other.d);
        break;
      case ValueType::boolean:
        b = std::move(other.b);
        break;
    }
    return *this;
  }

  Value& operator=(const Value& other) {
    switch (kind) {
      case ValueType::object:
        o = other.o;
        break;
      case ValueType::array:
        a = other.a;
        break;
      case ValueType::integer:
        i = other.i;
        break;
      case ValueType::string:
        s = other.s;
        break;
      case ValueType::decimal:
        d = other.d;
        break;
      case ValueType::boolean:
        b = other.b;
        break;
    }
    return *this;
  }

  ~Value() {
    switch (kind) {
      case ValueType::array:
        a.~Array();
        break;
      case ValueType::object:
        o.~Object();
        break;
      case ValueType::string:
        s.~String();
        break;
      case ValueType::integer:
        break;
      case ValueType::decimal:
        break;
      case ValueType::boolean:
        break;
    }
  }

};

ZEN_NAMESPACE_END

#endif // ZEN_VALUE_HPP
