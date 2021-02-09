
#include "zen/memory.hpp"

using namespace ZEN_NAMESPACE;

static_assert(is_pointer_v<std::shared_ptr<int>>, "a shared_ptr should be a pointer");
static_assert(is_pointer_v<std::unique_ptr<int>>, "a unique_ptr should be a pointer");

static_assert(is_nullable_v<std::shared_ptr<int>>, "a shared_ptr should be nullable");
static_assert(is_nullable_v<std::unique_ptr<int>>, "a unique_ptr should be nullable");

