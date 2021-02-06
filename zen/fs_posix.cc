
#include "zen/macros.h"
#include "zen/fs.hpp"

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>

namespace zen {

  namespace fs {

    struct file_handle_t {
      int fd;
      file_handle_t(int fd): fd(fd) {}
      ~file_handle_t();
    };

    file_handle_t::~file_handle_t() {
      if (close(fd) < 0) {
        ZEN_PANIC("close() failed for some reason");
      }
    }

    struct file_contents_handle_t {
      void* ptr;
      size_t sz;
      file_contents_handle_t(void* ptr, size_t sz): ptr(ptr), sz(sz) {}
      ~file_contents_handle_t() {
        if (munmap(ptr, sz) < 0) {
          ZEN_PANIC("munmap() failed for some reason");
        }
      }
    };

    std::string file_contents::as_string() const {
      return std::string((char*)handle->ptr, handle->sz-1);
    }

    std::string_view file_contents::as_string_view() const {
      return std::string_view((char*)handle->ptr, handle->sz-1);
    }

    result<file_contents> file::get_contents() {

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

      return zen::right(file_contents { std::make_shared<file_contents_handle_t>(ptr, stats.st_size) });
    }

    result<file> file_from_path(path p) {
      int fd = open(p.c_str(), O_RDONLY);
      if (fd < 0) {
        return left(errno);
      }
      return right(file { std::make_shared<file_handle_t>(fd) });
    }

  }

}

