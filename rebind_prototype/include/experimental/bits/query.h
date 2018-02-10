#ifndef STD_EXPERIMENTAL_BITS_QUERY_H
#define STD_EXPERIMENTAL_BITS_QUERY_H

#include <experimental/bits/has_query_member.h>
#include <utility>

namespace std {
namespace experimental {
inline namespace executors_v1 {
namespace execution {
namespace query_impl {

struct query_fn
{
  template<class Executor, class Property>
  constexpr auto operator()(Executor&& ex, Property&& p) const
    noexcept(noexcept(std::forward<Executor>(ex).query(std::forward<Property>(p))))
    -> decltype(std::forward<Executor>(ex).query(std::forward<Property>(p)))
  {
    return std::forward<Executor>(ex).query(std::forward<Property>(p));
  }

  template<class Executor, class Property>
  constexpr auto operator()(Executor&& ex, Property&& p) const
    noexcept(noexcept(query(std::forward<Executor>(ex), std::forward<Property>(p))))
    -> typename std::enable_if<!has_query_member_impl::eval<typename std::decay<Executor>::type, typename std::decay<Property>::type>::value,
      decltype(query(std::forward<Executor>(ex), std::forward<Property>(p)))>::type
  {
    return query(std::forward<Executor>(ex), std::forward<Property>(p));
  }
};

template<class T = query_fn> constexpr T customization_point{};

} // namespace query_impl
} // namespace execution
} // inline namespace executors_v1
} // namespace experimental
} // namespace std

#endif // STD_EXPERIMENTAL_BITS_QUERY_H
