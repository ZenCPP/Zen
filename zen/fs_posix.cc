
#include "zen/macros.h"
#include "zen/fs.hpp"

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>

ZEN_NAMESPACE_START

namespace fs {

  struct FileHandle {
    int fd;
    FileHandle(int fd): fd(fd) {}
    ~FileHandle();
  };

  FileHandle::~FileHandle() {
    if (close(fd) < 0) {
      ZEN_PANIC("close() failed for some reason");
    }
  }

  struct FileContentsHandle {
    void* ptr;
    size_t sz;
    FileContentsHandle(void* ptr, size_t sz): ptr(ptr), sz(sz) {}
    ~FileContentsHandle() {
      if (munmap(ptr, sz) < 0) {
        ZEN_PANIC("munmap() failed for some reason");
      }
    }
  };

  std::string FileContents::as_string() const {
    return std::string((char*)handle->ptr, handle->sz-1);
  }

  std::string_view FileContents::as_string_view() const {
    return std::string_view((char*)handle->ptr, handle->sz-1);
  }

  Result<FileContents> File::get_contents() {

    int status;
    struct stat stats;

    status = fstat(handle->fd, &stats);
    if (status < 0) {
      return zen::left(status);
    }

    void* ptr = mmap(NULL, stats.st_size, PROT_READ, MAP_SHARED, handle->fd, 0);
    if (ptr == MAP_FAILED) {
      return zen::left(status);
    }

    return zen::right(FileContents { std::make_shared<FileContentsHandle>(ptr, stats.st_size) });
  }

  Result<File> file_from_path(Path p) {
    int fd = open(p.c_str(), O_RDONLY);
    if (fd < 0) {
      return left(errno);
    }
    return right(File { std::make_shared<FileHandle>(fd) });
  }

}

ZEN_NAMESPACE_END

