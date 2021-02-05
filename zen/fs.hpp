#ifndef INFERA_FS_HPP
#define INFERA_FS_HPP

#include <string>
#include <memory>

#include "zen/config.h"
#include "zen/either.hpp"

namespace zen {

  namespace fs {

    template<typename T>
    using result = either<int, T>;

    using path = std::string;

    class file;

    struct file_handle_t;
    struct file_contents_handle_t;

    /// @brief Represents the contents of an open file
    ///
    /// This class efficiently shares resources with its clones so that the file
    /// needs to be mapped into memory only once.
    class file_contents {

      friend class file;

      std::shared_ptr<file_contents_handle_t> handle;

      inline file_contents(std::shared_ptr<file_contents_handle_t> handle):
        handle(handle) {}

    public:

      /// Create a freshly allocated std::string that will contain the entire
      /// file contents.
      std::string as_string();

      /// Convert the contents of the associated file to a string
      std::string_view as_string_view();

    };

    /// @brief A reference to a single regular file on the file system
    ///
    /// This class cannot be directly constructed. Instead, you should obtain a
    /// copy from a function such as `path::open`.
    class file {

      friend result<file> file_from_path(path p);

      std::shared_ptr<file_handle_t> handle;

      inline file(std::shared_ptr<file_handle_t> handle):
        handle(handle) {}

    public:

      /// @brief Get a structure for querying the contents of this file
      ///
      /// This method will try to use the operating system's best available APIs
      /// to map the file into memory, falling back to a full scan if no
      /// specialised functions exist.
      result<file_contents> get_contents();

    };

    result<file> file_from_path(path p);

  }

}

#endif // of #ifndef INFERA_FS_HPP
