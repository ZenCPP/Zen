#ifndef INFERA_FS_HPP
#define INFERA_FS_HPP

#include <string>
#include <memory>

#include "zen/config.h"
#include "zen/either.hpp"

ZEN_NAMESPACE_START

namespace fs {

  template<typename T>
  using Result = Either<int, T>;

  using Path = std::string;

  class File;

  struct FileHandle;
  struct FileContentsHandle;

  /// @brief Represents the contents of an open file
  ///
  /// This class efficiently shares resources with its clones so that the file
  /// needs to be mapped into memory only once.
  class FileContents {

    friend class File;

    std::shared_ptr<FileContentsHandle> handle;

    inline FileContents(std::shared_ptr<FileContentsHandle> handle):
      handle(handle) {}

  public:

    /// Create a freshly allocated std::string that will contain the entire
    /// file contents.
    std::string as_string() const;

    /// Convert the contents of the associated file to a string
    std::string_view as_string_view() const;

  };

  /// @brief A reference to a single regular file on the file system
  ///
  /// This class cannot be directly constructed. Instead, you should obtain a
  /// copy from a function such as `path::open`.
  class File {

    friend Result<File> file_from_path(Path p);

    std::shared_ptr<FileHandle> handle;

    inline File(std::shared_ptr<FileHandle> handle):
      handle(handle) {}

  public:

    /// @brief Get a structure for querying the contents of this file
    ///
    /// This method will try to use the operating system's best available APIs
    /// to map the file into memory, falling back to a full scan if no
    /// specialised functions exist.
    Result<FileContents> get_contents();

  };

  Result<std::string> read_file(Path p);

  Result<File> file_from_path(Path p);

}

ZEN_NAMESPACE_END

#endif // of #ifndef INFERA_FS_HPP
