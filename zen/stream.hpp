#ifndef ZEN_STREAM_HPP
#define ZEN_STREAM_HPP

#include "zen/maybe.hpp"
#include <deque>

namespace zen {

  template<typename T>
  class stream {
  public:

    /// @brief Get the next token in the stream
    virtual maybe<T> get() = 0;

    /// @brief Skip over a fixed amount of tokens
    inline virtual void skip(std::size_t count = 1) {
      for (std::size_t i = 0; i < count; i++) {
        get();
      }
    }

    inline virtual ~stream() {}

  };

  template<typename T, typename SizeT = std::size_t>
  class peek_stream {
  public:

    /// @brief Get some token in the stream without consuming any
    virtual maybe<T> peek(SizeT offset = 0);

  };


  template<typename T, typename SizeT = std::size_t>
  class buffered_stream : public peek_stream<T, SizeT> {

    std::deque<T> buffer;

  public:

    /// @brief Get the next token in the underlying stream
    ///
    /// This method should be implemented by users deriving from this class.
    virtual maybe<T> read();

    inline maybe<T> get() override {
      if (buffer.empty()) {
        return read();
      } else {
        auto token = buffer.front();
        buffer.pop_front();
        return right(token);
      }
    }

    inline maybe<T> peek(SizeT offset) override {
      while (buffer.size() < offset) {
        auto token = read();
        if (is_empty(token)) {
          return {};
        }
        buffer.push_back(token);
      }
      return buffer[offset-1];
    }

  };

}

#endif // of #ifndef ZEN_STREAM_HPP
