---
layout: page
title : "API Reference"
prev: /tutorial/
flagsfwd_hdr_id: sec-hdr-flagsfwd
allow_flags_hdr_id: sec-hdr-allow-flags
flags_hdr_id: sec-hdr-flags
iterator_hdr_id: sec-hdr-iterator
---

**Disclaimer: docs are currently quite out of sync!**


<nav class="toc">

### Table of Contents


1. [Header `<flags/flagsfwd.hpp>`](#{{ page.flagsfwd_hdr_id }})
2. [Header `<flags/allow_flags.hpp>`](#{{ page.allow_flags_hdr_id }})
3. [Header `<flags/flags.hpp>`](#{{ page.flags_hdr_id }})
4. [Header `<flags/iterator.hpp>`](#{{ page.iterator_hdr_id }})

</nav>


<section id="{{ page.flagsfwd_hdr_id }}">

## Header `<flags/flagsfwd.hpp>`

{% highlight c++ %}
namespace flags {

template <class E> class flags;

} // namespace flags
{% endhighlight %}

Forward declaration of `flags` template.

</section>


<section id="{{ page.allow_flags_hdr_id }}">

## Header `<flags/allow_flags.hpp>`

Work in progress&hellip;

</section>


<section id="{{ page.flags_hdr_id }}">

## Header `<flags/flags.hpp>`
{: #sec-hdr-flags }

### Synopsis

{% highlight c++ %}
namespace flags {

template <class E> class flags {
/* ... */
};

} // namespace flags
{% endhighlight %}

where `E` is an enum.

#### Member types

Member type    |Definition                                                |Notes
---------------|----------------------------------------------------------|---------------------------------------------
enum_type      |The template parameter (E)                                |
underlying_type|The integer type that is used as representation of `flags`|Equivalent of `std::underlying_type<E>::type`

#### Member functions

##### Constructors and assignment operators

Name                         |Description
-----------------------------|-----------
`flags()`                    |Default contructor, keeps object uninitialized (note: object may contain garbage)
`flags(empty_t)`             |Unsets all flags
`flags(flags::enum_type)`    |Sets flag denoted by the parameter
`flags(const flags&)`        |Copy constructor
`flags(flags&&)`             |Move constructor
`operator=(flags::enum_type)`|Unsets all flags, then sets flag denoted by the parameter
`operator=(const flags&)`    |Copy assignment
`operator=(flags&&)`         |Move assignment

##### Bitwise operators

All functions in this group return reference to `flags`, except for `operator~`
which returns a new `flags` value.

Name                                          |Description
----------------------------------------------|-----------
<code>operator&#124;=(flags::enum_type)</code>|Bitwise OR with flag denoted by the parameter
<code>operator&#124;=(const flags&)</code>    |Bitwise OR with flags in the parameter
`operator&=(flags::enum_type)`                |Bitwise AND with flag denoted by the parameter`
`operator&=(const flags&)`                    |Bitwise AND with flags in the parameter
`operator^=(flags::enum_type)`                |Bitwise XOR with flag denoted by the parameter
`operator^=(const flags&)`                    |Bitwise XOR with flags in the parameter
`operator~()`                                 |Bitwise negation

##### Boolean conversions

Name             |Description
-----------------|-----------
`operator bool()`|Returns `true` if any of the flags is set
`operator!()`    |Returns `true` if none of the flags is set

##### Raw access to integer representation

Name                                          |Description
----------------------------------------------|-----------
`underlying_value()`                          |Returns integer representation
`set_underlying_value(flags::underlying_type)`|Sets integer representation to new value

##### Various functions

Name         |Description
-------------|-----------
`swap(flags)`|Swaps two `flags` values

#### Nonmember functions

##### Bitwise operators
All functions in this group return new `flags` value.

Name                                                           |Description
---------------------------------------------------------------|-----------
<code>operator&#124;(flags, flags)</code>                      |Bitwise OR of two `flags` values
<code>operator&#124;(flags, flags::enum_type)</code>           |Bitwise OR of a `flags` value and a flag denoted by an enum value
<code>operator&#124;(flags::enum_type, flags)</code>           |Bitwise OR of a `flags` value and a flag denoted by an enum value
<code>operator&#124;(flags::enum_type, flags::enum_type)</code>|Bitwise OR of two flags denoted by enum values
`operator&(flags, flags)`                                      |Bitwise AND of two `flags` values
`operator&(flags, flags::enum_type)`                           |Bitwise AND of a `flags` value and a flag denoted by an enum value
`operator&(flags::enum_type, flags)`                           |Bitwise AND of a `flags` value and a flag denoted by an enum value
`operator&(flags::enum_type, flags::enum_type)`                |Bitwise AND of two flags denoted by enum values
`operator^(flags, flags)`                                      |Bitwise XOR of two `flags` values
`operator^(flags, flags::enum_type)`                           |Bitwise XOR of a `flags` value and a flag denoted by an enum value
`operator^(flags::enum_type, flags)`                           |Bitwise XOR of a `flags` value and a flag denoted by an enum value
`operator^(flags::enum_type, flags::enum_type)`                |Bitwise XOR of two flags denoted by enum values

##### Comparison operators
All functions in this group return `bool`.

Name                      |Description
--------------------------|-----------
`operator==(flags, flags)`|Compares if two `flags` values are equal
`operator!=(flags, flags)`|Compares if two `flags` values are not equal

</section>


<section id="{{ page.iterator_hdr_id }}">

## Header `<flags/iterator.hpp>`

Work in progress&hellip;

</section>
