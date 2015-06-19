---
layout: page
title : "Overview"
prev: /
next: /tutorial/
---

<section>

## Motivation


C++ 11 gives us *scoped enums* or `enum class`es. These are strongly typed
enumerations, they do not cast implicitly to or from the underlying integer
type. They also do not leak enumeration values to enclosing scope (thus the
names of this values do not clash and you no longer need to prefix/suffix them
with something to disambiguate).

But with type safety you lose the ability to use variables of `enum class` types
as sets of bit flags. That is because *enum classes* do not cast to integers and
there are no bitwise operators overloads defined for them. It would be desirable
to combine benefits of both enum kinds leaving their drawbacks behind.

And while we there, it also would  be convenient to treat a set of bit flags as
as just that---a `set`. This wouldn't just give us a richer interface, but it
would automatically enable the use of STL algorithms with our values.

This library is an attempt to satisfy this two needs.

</section>


<section>

## Features

The library provides a `flags` class template which:


* does not convert to or from integer types;
* does implicitly convert from enum it was instantiated by;
* does not convert to that enum;
* supports all bitwise operations except for shifts (since shifts are not very
  reasonable for bit flags);
* explicitly converts to bool (which allows to use it in boolean contexts, like
  in branching or loop conditions);
* provides access to the underlying integer through member functions;
* instantiates only for **enums it was explicitly enabled for**;
* usable as an unordered set of enum values (provides partial interface of
  `std::unordered_set`);
* is usable in `constexpr` contexts;
* can be safely passed to C functions and across module boundaries.

</section>

<section>

## Rationales

### Why create a new class and not just overload bitwise operators for enums?

There are two reasons. The first one comes directly from the
[Motivation](#motivation) section: `flags` instances also provide partial
container interface. Because of that it is possible to use them with STL
algorithms like `std::transform` and `std::accumulate` and special iterators
like `std::insert_iterator`.

The second reason is about semantics of an enumeration. For me personally an
enumeration type declares an invariant that all **valid** objects of that type
have one of the values listed in the enumeration definition. And since separate
bit flag value (an enum object) and a collection of bit flags that were set are
conceptionally different, so I prefer to represent them using different types.

Of course, some people see it differently, so for them using such library
is probably an overkill.


### Why is it required to explicitly enable `flags` for each enum?

Tl;dr: so that bitwise operations only work were you need them.

Not all enums exist for the same reason. Some map specific bits into names and
some are threr just to distinguish between different names. The second kind
usually does not have all of its values equal to a power of two, many of
this values are increments of previous values.

Using such enums as bit flags is pretty much nonsensical, since their values
overlap. Even more, `flags` iterators only work as expected if all values
of enumeration are equal to *different* powers of two.

In the end it was decided, that better to force users to explicitly express
their intention to use `flags` template for a certain enumertion than to force
them to use it for all enumeraions. By the way, the standard library does a
similar thing with `std::error_code` and `std::is_error_code_enum`.


### Why `flags` default constructor does not initialize the object?

Tl;dr: for perfomance reasons.

There is a particular kind of types in C++ called [Plain Old Data][POD] types.
Their most important proprety is that copying *bits* of one value of suhc type
to some other location effectively creates a new *valid* object equal to the
first one. As a result, there are some optimisations that could be employed by
containers of PODs. As this library tries to provide an abstraction that does
not incur perfomance costs, it is only natural to make `flags` a POD.

For a type to be recognised as a POD by compilers, it should follow certain
restrictions, one of which is it should have
[trivial default constructor][TrivialConstr]. Such a constructor does not
initialize any members of the object (that's why it is called trivial). This
means that default-constructed `flags` instances are left with garbage inside,
and you probably shouldn't be using default constructor yourself.

That being said, it is usually simpler to create a `flags` object by bitwise
or-ing several enumeration values. And if you do need to create an empty set
of bit flags, the class has a special constructor for that.

[POD]:           http://en.cppreference.com/w/cpp/concept/PODType
[TrivialConstr]: http://en.cppreference.com/w/cpp/language/default_constructor#Trivial_default_constructor

</section>