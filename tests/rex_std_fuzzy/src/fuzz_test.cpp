#include <algorithm>
#include <cstdint>
#include <cstring>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <iostream>

// to do: use bit_cast, span if you have C++20
using fuzz_span = std::basic_string_view<std::uint8>;

template <typename ToMake>
std::pair<ToMake, fuzz_span> make_fuzzed_object(fuzz_span input) 
{
  static_assert(std::is_trivial_v<ToMake>);

  // intentionally default initialize object,
  // 0 out trivial members
  ToMake result{};

  auto bytes_used = std::min(input.size(), sizeof(ToMake));

  std::memcpy(&result, input.data(), bytes_used);

  input.remove_prefix(bytes_used);

  return {result, input};
}

template <typename... ToMake, std::size_t... Index>
std::pair<std::tuple<ToMake...>, fuzz_span> make_fuzzed_objects(fuzz_span input, std::index_sequence<Index...>) 
{
  std::pair<std::tuple<ToMake...>, fuzz_span> result;

  (
      [&]() {
        const auto [value, remaining] = make_fuzzed_object<ToMake>(input);
        std::get<Index>(result.first) = value;
        input = remaining;
      }(),
      ...);

  result.second = input;
  return result;
}

template <typename... ToMake>
std::pair<std::tuple<ToMake...>, fuzz_span> make_fuzzed_objects(fuzz_span input) 
{
  return make_fuzzed_objects<ToMake...>(input, std::make_index_sequence<sizeof...(ToMake)>());
}

extern "C" int LLVMFuzzerTestOneInput(const char *Data, size_t Size) {

  // ++iteration_count;

  // auto [args, remaining] = make_fuzzed_objects<int>(input);

  // std::apply(crash, args);

  return 0;  // Values other than 0 and -1 are reserved for future use.
}
