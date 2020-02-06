Zen++ Coding Style Guidelines
==============================

This page tries to list all rules and conventions that are used when working on
parts of the libraries. If you plan to update or extend the Zen++ libraries,
then you are expected to have read this document at least once. Code that does
not follow the guidelines may be rejected at any moment.

## Template metaprogramming

### Metafunctions should be suffixed with `_`

In order to distinguish metafunctions from other types and from plain
functions, the suffix `_` should be added to the name of the metafunction. For
example, a metafunction that calculates the size of a type list should
be called `size_` and not `size`, `size_t`, or `size_type`.

This rule is meant to make a seperate namespace (e.g. `zen::meta`) obsolete,
leading to more concise code. It also redcues name collisions, e.g. when out of
frustration the user would write something like `using namespace zen::meta`.
Above that, the suffix is a reminder that the function operates on the type
level.

The rules for determining whether a given type is a metafunction are simple. If
the template may be used as the argument to another metafunction, then that
template is also a metafunction. If instanciating the template results in a
type that may appear in class members, function arguments or return types, then
that template is **not** a metafunction.

More generally, a metafunction is a template that results in a structure of
which all members can be inspected at compile-time and has no use at run-time.
The members of the resulting type usually hold information about how other
metafunctions should operate on it.

### Don't use non-type template parameters in public template metafunctions

User-facing metafunctions should operate solely on types. The only exception to
this rule are functions that lift a primitive value to a type.

The reason that this rule exists is because it makes the template
metaprogramming API more stable and future-proof. When a certain metafunction
only accepts boolean values, changing it to accept a type requires adjusting
all code that relies on it, whereas a type can in principle hold any value.

The following code is incorrect:

```cpp
template<std::size_t N, typename SeqT>
struct nth_;
```

The previous example should be replaced with the following code:

```
template<typename N, typename SeqT>
struct nth_;
```

When end-users or developers of other components of Zen++ encounter a `_helper`
template metafunction, they should know that the function is not meant to be
used or extended.

### Use `_impl_` as a suffix for metafunctions that may be extended by the end-user

This might sound unproductive, but the extra indirection effectively decouples
the interface from the actual implementation. This allows us to add additional
logic in the public API (such as validity checks) while leaving third-party
code unaffected.


