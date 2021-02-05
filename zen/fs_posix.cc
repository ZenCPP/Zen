
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
      char* ptr;
      size_t sz;
      ~file_contents_handle_t() {
        if (munmap(ptr, sz) != 0) {
          ZEN_PANIC("munmap() failed for some reason");
        }
      }
    };

    result<file_contents> file::get_contents() {
      
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

