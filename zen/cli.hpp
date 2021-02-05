#ifndef ZEN_CLI_HPP
#define ZEN_CLI_HPP

#include <any>
#include <optional>
#include <vector>
#include <unordered_map>
#include <string_view>

#include "zen/empty.hpp"
#include "zen/meta.hpp"
#include "zen/either.hpp"

namespace zen {

  namespace cli {

    using arg_size_t = int;
    using error_list_t = std::vector<std::string>;
    using arg_list_t = std::vector<std::string_view>;


    using arg_size_t = int;
    using error_list_t = std::vector<std::string>;
    using arg_list_t = std::vector<std::string_view>;

    template<typename T>
    struct get_value_type_ {
      using type = typename T::value_type;
    };

    template<typename ProgramT, typename ArgT, bool IsRequired, bool IsList>
    class flag_t;

    template<typename FlagsT>
    class program_description_t {

      template<typename ProgramT, typename ArgT, bool IsRequired, bool IsList>
      friend class flag_t;

      using init_flag_t = flag_t<program_description_t, std::string, false, false>;

      template<typename Tag>
      using get_flag_index = find_t< std::is_same<Tag, _1>, FlagsT >;

      template<typename FlagT>
      inline constexpr auto insert_flag(FlagT flag) const {
        using new_program_description_t = program_description_t< rcons_t<FlagT, FlagsT> >;
        return new_program_description_t {
            .flags = { rcons(flag, flags) },
            .name = name,
            .description = description
        };
      }

    public:

      FlagsT flags;

      std::string_view name;
      std::optional<std::string_view> description;

      inline constexpr program_description_t describe(std::string_view new_description) {
        return program_description_t {
            .flags = flags,
            .name = name,
            .description = new_description
        };
      }

      template<typename Tag = zen::empty>
      inline constexpr auto add_flag(std::string_view pattern) {
        return init_flag_t {
            .program = *this,
            .description = "",
            .pattern = pattern,
            .min_count = 0,
            .max_count = 1
        };
      }

      class values_t {

        using storage_t = map_t<lift_<get_value_type_>, FlagsT>;

        storage_t storage;

      public:

        template<typename Tag>
        auto get() {
          return std::get<get_flag_index<Tag>::value>(storage);
        }

      };

      std::unordered_map<std::string_view, std::size_t> patterns;

      inline either<error_list_t, values_t> parse(const arg_list_t& args) {
        error_list_t errors;
        values_t out;
        auto args_end = args.cend();
        for (auto arg = args.cbegin(); arg != args_end; arg++) {
          if ((*arg)[0] == '-') {
            if (arg->size() == 1) {
              auto match = patterns.find(arg->substr(1));
              if (match == patterns.end()) {
                errors.push_back("argument not recognised");
                continue;
              }
              auto& flag_index = match->second;
              out.values[flag_index] = parse_flag(flag_index, arg, args_end);
            }
          }
        }
        return right(out);
      }

      inline either<error_list_t, values_t> parse(int argc, const char *argv[]) {
        arg_list_t args { argv, argc + argv };
        return parse(args);
      }

    };

    template<typename ProgramT, typename ArgT, bool IsRequired, bool IsList>
    class flag_t {

#define ZEN_CLONE_FLAG_T(...) \
  return flag_t<__VA_ARGS__> { \
    .program = program, \
    .description = description, \
    .pattern = pattern, \
    .min_count = min_count, \
    .max_count = max_count \
  }

    using element_type = std::conditional_t<IsRequired, ArgT, std::optional<ArgT>>;

    public:

      using value_type = std::conditional_t<IsList, std::vector<element_type>, element_type>;

      const ProgramT program;
      const std::string_view description;
      const std::string_view pattern;
      const arg_size_t min_count;
      const arg_size_t max_count;

      constexpr auto describe(std::string_view text) {
        return flag_t {
          .program = program,
          .description = text,
          .pattern = pattern,
          .min_count = min_count,
          .max_count = max_count
        };
      }

      constexpr auto at_least(arg_size_t count) {
        return flag_t {
          .program = program,
          .description = description,
          .pattern = pattern,
          .min_count = count,
          .max_count = max_count
        };
      }

      constexpr auto at_most(arg_size_t count) {
        return flag_t {
          .program = program,
          .description = description,
          .pattern = pattern,
          .min_count = min_count,
          .max_count = count
        };
      }

      constexpr auto as_bool() { ZEN_CLONE_FLAG_T(ProgramT, bool, IsRequired, IsList); }

      constexpr auto required() { ZEN_CLONE_FLAG_T(ProgramT, ArgT, true, IsList); }

      constexpr auto list() { ZEN_CLONE_FLAG_T(ProgramT, ArgT, IsRequired, true); }

      constexpr auto finish() {
        return program.insert_flag(*this);
      }

    };

    constexpr auto program(std::string_view name) {
      return program_description_t<std::tuple<>> {
        .flags = std::make_tuple(),
        .name = name,
        .description = {}
      };
    }

  } // of namespace cli

} // of namespace zen

#endif // ZEN_CLI_HPP
