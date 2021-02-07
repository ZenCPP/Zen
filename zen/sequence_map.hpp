#ifndef ZEN_SEQUENCE_MAP_HPP
#define ZEN_SEQUENCE_MAP_HPP

#include <memory>
#include <unordered_map>
#include <list>

namespace zen {

  template<
    typename Key,
    typename Value,
    typename Hash = std::hash<Key>,
    typename KeyEqual = std::equal_to<Key>,
    typename Allocator = std::allocator<std::pair<const Key, Value>>
  >
  class sequence_map {
  public:

    using key_type = Key;
    using mapped_type = Value;
    using value_type = std::pair<const Key, Value>;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using hasher = Hash;
    using key_equal = KeyEqual;
    using allocator_type = Allocator;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = typename std::allocator_traits<Allocator>::pointer;
    using const_pointer = typename std::allocator_traits<Allocator>::const_pointer;

  private:
    using sequence_type = typename std::list<value_type, Allocator>;
    using index_type = typename std::unordered_map<Key, Value*, Hash, KeyEqual>;

  public:
    using iterator = typename sequence_type::iterator;
    using const_iterator = typename sequence_type::const_iterator;

  private:

    sequence_type sequence;
    index_type index;

  public:

    inline sequence_map(std::initializer_list<value_type> init):
      sequence(init.begin(), init.end()) {
      for (auto& [key, value]: sequence) {
        index.emplace(key, &value);
      }
    }

    inline sequence_map() {};

    sequence_map(const sequence_map& other) = default;
    sequence_map(sequence_map&& other) = default;

    template<typename ...ForwardArgs>
    value_type& emplace(ForwardArgs&& ...args) {
      auto to_insert = value_type(std::forward<ForwardArgs>(args)...);
      sequence.push_back(to_insert);
      auto& inserted = sequence.back();
      auto& [key, value] = inserted;
      index.emplace(key, &value);
      return inserted;
    }

    sequence_map& operator=(sequence_map&& other) {
      sequence = std::move(other.sequence);
      index = std::move(other.index);
      return *this;
    };

    sequence_map& operator=(const sequence_map& other)  {
      std::copy(other.sequence.cbegin(), other.sequence.cend(), std::back_inserter(sequence));
      std::copy(other.index.cbegin(), other.index.cend(), std::inserter(index, index.end()));
      return *this;
    }

    inline size_type size() {
      return sequence.size();
    }

    reference operator[](const key_type& key) {
      return index[key];
    }

    reference operator[](key_type&& key) {
      return index[std::move(key)];
    }

    iterator begin() {
      return sequence.begin();
    }

    iterator end() {
      return sequence.end();
    }

  };

}

#endif // ZEN_SEQUENCE_MAP_HPP
