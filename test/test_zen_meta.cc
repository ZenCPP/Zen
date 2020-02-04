
#include <memory>

#include "zen/meta.hpp"

static_assert(zen::is_pointer_v<std::shared_ptr<int>>, "a shared_ptr should be a pointer");
static_assert(zen::is_nullable_v<std::shared_ptr<int>>, "a shared_ptr should be nullable");

