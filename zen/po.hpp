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

    enum class FlagType {
      boolean,
      string,
    };

    class Flag {
    public:

      std::list<std::string> patterns;
      Maybe<std::string> description;
      std::size_t min_count = 0;
      std::size_t max_count = 1;
      Maybe<std::string> metavar;
      FlagType type = FlagType::string;

      inline Flag(std::initializer_list<std::string> patterns):
        patterns(patterns) {}

      Flag& set_description(std::string new_description) {
        description = new_description;
        return *this;
      }

      Flag& set_nary(bool is_nary) {
        if (is_nary) {
          max_count = ZEN_AUTO_SIZE;
        } else {
          max_count = 1;
        }
        return *this;
      }

      Flag& set_is_bool(bool is_bool) {
        if (is_bool) {
          type = FlagType::boolean;
        } else if (type == FlagType::boolean) {
          type = FlagType::string;
        }
        return *this;
      }

      Flag& set_metavar(std::string new_metavar) {
        metavar = new_metavar;
        return *this;
      }

    };

    class Subcommand {
    public:

      std::string name;
      std::string description;
      std::list<Flag> flags;

      Subcommand(std::string name): name(name) {}

      Subcommand& set_description(std::string new_description) {
        description = new_description;
        return *this;
      }

      Subcommand& add_flag(Flag f) {
          flags.push_back(f);
          return *this;
      }

    };

    using ParsedOptions = std::unordered_map<std::string, std::any>;

    class Program {
    public:

      std::string name;
      std::string description;
      std::string author;
      sequence_map<std::string, Subcommand> subcommands;
      std::list<Flag> flags;

      inline Program(std::string name): name(name) {}

      Program& set_description(std::string new_description) {
        description = new_description;
        return *this;
      }

      Program& set_author(std::string new_author) {
        author = new_author;
        return *this;
      }

      Program& add_subcommand(Subcommand s) {
        subcommands.emplace(s.name, s);
        return *this;
      }

      template<typename ...StringTs>
      Program& add_flag(Flag f) {
        flags.push_back(f);
        return *this;
      }

      ParsedOptions parse(int argc, const char* argv) {
        ParsedOptions result;
        for (Flag f: flags) {
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
