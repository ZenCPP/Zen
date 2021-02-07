#ifndef ZEN_PO_HPP
#define ZEN_PO_HPP

#include <initializer_list>
#include <string>
#include <any>
#include <list>
#include <iostream>
#include <unordered_map>

#include "zen/config.h"
#include "zen/maybe.hpp"
#include "zen/sequence_map.hpp"

#define ZEN_FLAGTYPE_STRING 1
#define ZEN_FLAGTYPE_BOOL   2

namespace zen {

  namespace po {

    enum class flag_type {
      boolean,
      string,
    };

    class flag {
    public:

      std::list<std::string> patterns;
      maybe<std::string> description;
      std::size_t min_count = 0;
      std::size_t max_count = 1;
      maybe<std::string> metavar;
      flag_type type = flag_type::string;

      inline flag(std::initializer_list<std::string> patterns):
        patterns(patterns) {}

      flag& set_description(std::string new_description) {
        description = new_description;
        return *this;
      }

      flag& set_nary(bool is_nary) {
        if (is_nary) {
          max_count = ZEN_AUTO_SIZE;
        } else {
          max_count = 1;
        }
        return *this;
      }

      flag& set_is_bool(bool is_bool) {
        if (is_bool) {
          type = flag_type::boolean;
        } else if (type == flag_type::boolean) {
          type = flag_type::string;
        }
        return *this;
      }

      flag& set_metavar(std::string new_metavar) {
        metavar = new_metavar;
        return *this;
      }

    };

    class subcommand {
    public:

      std::string name;
      std::string description;
      std::list<flag> flags;

      subcommand(std::string name): name(name) {}

      subcommand& set_description(std::string new_description) {
        description = new_description;
        return *this;
      }

      subcommand& add_flag(flag f) {
          flags.push_back(f);
          return *this;
      }

    };

    using parsed_options = std::unordered_map<std::string, std::any>;

    class program {
    public:

      std::string name;
      std::string description;
      std::string author;
      sequence_map<std::string, subcommand> subcommands;
      std::list<flag> flags;

      inline program(std::string name): name(name) {}

      program& set_description(std::string new_description) {
        description = new_description;
        return *this;
      }

      program& set_author(std::string new_author) {
        author = new_author;
        return *this;
      }

      program& add_subcommand(subcommand s) {
        subcommands.emplace(s.name, s);
        return *this;
      }

      template<typename ...StringTs>
      program& add_flag(flag f) {
        flags.push_back(f);
        return *this;
      }

      parsed_options parse(int argc, const char* argv) {
        parsed_options result;
        for (flag f: flags) {
          for (auto pattern: f.patterns) {
            std::size_t k = 0;
            if (pattern.size() > 0 && pattern[0] == '-') {
              k++;
              if (pattern.size() > 1 && pattern[1] == '-') {
                k++;
              }
            }
          }
        }
        return result;
      }

      void print_help(std::ostream& out = std::cerr) {
        out << "Usage:\n  " << name << "\n\n";
        out << "Commands:\n";
        for (auto& [k, s]: subcommands) {
          out << "  " << s.name << "  " << s.description << "\n";
        }
      }

    };

  }

}

#endif // of #ifndef ZEN_PO_HPP
