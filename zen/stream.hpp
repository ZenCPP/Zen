#ifndef ZEN_STREAM_HPP
#define ZEN_STREAM_HPP

#include <deque>

#include "zen/meta.hpp"
#include "zen/maybe.hpp"

ZEN_NAMESPACE_START

template<typename T, typename SizeT = std::size_t>
class Stream {
public:

  /// @brief Get the next token in the stream
  virtual Maybe<T> get() = 0;

  /// @brief Skip over a fixed amount of tokens
  inline virtual void skip(SizeT count = 1) {
    for (SizeT i = 0; i < count; i++) {
      get();
    }
  }

  inline virtual ~Stream() {}

};

template<typename T, typename SizeT = std::size_t>
class PeekStream : public Stream<T> {
public:

  /// @brief Get some token in the stream without consuming any
  virtual Maybe<T> peek(SizeT offset = 1) = 0;

};

template<typename T, typename SizeT = std::size_t>
class BufferedStream : public PeekStream<T, SizeT> {

  std::deque<T> buffer;

public:

  /// @brief Get the next token in the underlying stream
  ///
  /// This method should be implemented by users deriving from this class.
  virtual Maybe<T> read();

  inline Maybe<T> get() override {
    if (buffer.empty()) {
      return read();
    } else {
      auto token = buffer.front();
      buffer.pop_front();
      return some(token);
    }
  }

  inline Maybe<T> peek(SizeT offset) override {
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

template<typename ContainerT, typename Enabler = void>
class StreamWrapper;

template<typename T>
class StreamWrapper<
  T,
  typename EnableIf<IsContainer<T>::value || IsCollection<T>::value>::Type
> : public PeekStream<typename T::value_type> {
public:

  using Size = typename T::size_type;
  using Value = typename T::value_type;

private:

  T& data;
  Size offset;

public:

  StreamWrapper(T& data, Size offset = 0):
    data(data), offset(offset) {}

  Maybe<Value> get() override {
    if (offset < data.size()) {
      return data[offset++];
    } else {
      return {};
    }
  }

  Maybe<Value> peek(Size lookahead_offset) override {
    auto real_offset = offset + lookahead_offset - 1;
    if (real_offset < data.size()) {
      return data[real_offset];
    } else {
      return {};
    }

  }

};

template<typename T>
inline StreamWrapper<T> make_stream(T& data, typename T::size_type offset = 0) {
  return StreamWrapper<T>(data);
}

ZEN_NAMESPACE_END

#endif // of #ifndef ZEN_STREAM_HPP
