#ifndef ZEN_STREAM_HPP
#define ZEN_STREAM_HPP

#include <deque>

#include "zen/maybe.hpp"

namespace zen {

  template<typename T, typename SizeT = std::size_t>
  class stream {
  public:

    /// @brief Get the next token in the stream
    virtual maybe<T> get() = 0;

    /// @brief Skip over a fixed amount of tokens
    inline virtual void skip(SizeT count = 1) {
      for (SizeT i = 0; i < count; i++) {
        get();
      }
    }

    inline virtual ~stream() {}

  };

  template<typename T, typename SizeT = std::size_t>
  class peek_stream : public stream<T> {
  public:

    /// @brief Get some token in the stream without consuming any
    virtual maybe<T> peek(SizeT offset = 0) = 0;

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
        return some(token);
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
      return some(buffer[offset-1]);
    }

  };


  template<typename ContainerT>
  class stream_wrapper : public peek_stream<typename ContainerT::value_type> {
  public:

    using size_type = typename ContainerT::size_type;
    using value_type = typename ContainerT::value_type;

  private:

    ContainerT& data;
    size_type offset;

  public:

    stream_wrapper(ContainerT& data, size_type offset = 0):
      data(data), offset(offset) {}

    maybe<value_type> get() override {
      if (offset < data.size()) {
        return data[offset++];
      } else {
        return {};
      }
    }

    maybe<value_type> peek(size_type lookahead_offset) override {
      auto real_offset = offset + lookahead_offset;
      if (real_offset < data.size()) {
        return data[real_offset];
      } else {
        return {};
      }

    }

  };

}

#endif // of #ifndef ZEN_STREAM_HPP
