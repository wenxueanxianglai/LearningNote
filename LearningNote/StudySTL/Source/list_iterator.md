# list_iterator
---
## 大致结构
```C++
template <class Mylist>
class list_iterator : public List_const_iterator<Mylist>
{};

template <class Mylist>
class List_const_iterator : public List_unchecked_const_iterator<Mylist, Iterator_base>
{};

template <class Mylist, class Base = Iterator_base0>
class List_unchecked_const_iterator : public Iterator012<
bindirectional_iterator_tag,
typename Mylist::value_type,
typename Mylist::difference_type,
typename Mylist::const_pointer,
typename Mylist::const_reference,
Base
>
{};

template <
  class Category,
  class Ty,
  class Diff,
  class Pointer,
  class Reference,
  class Base
>
struct Iterator012 : public Base
{};
```
