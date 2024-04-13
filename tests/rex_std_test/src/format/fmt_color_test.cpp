// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
// 
// File: fmt_color_test.cpp
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#include "rex_std_test/catch2/catch.hpp"
#include "rex_std/format.h"
#include "rex_std/internal/format/color.h"

#define REQUIRE_STR(x, y) REQUIRE(rsl::string(x) == rsl::string(y))

TEST_CASE("color_test, format") 
{
  REQUIRE_STR(rsl::format(fg(rsl::rgb(255, 20, 30)), "rgb(255,20,30)"), "\x1b[38;2;255;020;030mrgb(255,20,30)\x1b[0m");
  REQUIRE_STR(rsl::format(fg(rsl::color::blue), "blue"), "\x1b[38;2;000;000;255mblue\x1b[0m");
  REQUIRE_STR(rsl::format(fg(rsl::color::blue) | bg(rsl::color::red), "two color"), "\x1b[38;2;000;000;255m\x1b[48;2;255;000;000mtwo color\x1b[0m");
  REQUIRE_STR(rsl::format(rsl::emphasis::bold, "bold"), "\x1b[1mbold\x1b[0m");
  REQUIRE_STR(rsl::format(rsl::emphasis::faint, "faint"), "\x1b[2mfaint\x1b[0m");
  REQUIRE_STR(rsl::format(rsl::emphasis::italic, "italic"), "\x1b[3mitalic\x1b[0m");
  REQUIRE_STR(rsl::format(rsl::emphasis::underline, "underline"), "\x1b[4munderline\x1b[0m");
  REQUIRE_STR(rsl::format(rsl::emphasis::blink, "blink"), "\x1b[5mblink\x1b[0m");
  REQUIRE_STR(rsl::format(rsl::emphasis::reverse, "reverse"), "\x1b[7mreverse\x1b[0m");
  REQUIRE_STR(rsl::format(rsl::emphasis::conceal, "conceal"), "\x1b[8mconceal\x1b[0m");
  REQUIRE_STR(rsl::format(rsl::emphasis::strikethrough, "strikethrough"), "\x1b[9mstrikethrough\x1b[0m");
  REQUIRE_STR(rsl::format(fg(rsl::color::blue) | rsl::emphasis::bold, "blue/bold"), "\x1b[1m\x1b[38;2;000;000;255mblue/bold\x1b[0m");
  REQUIRE_STR(rsl::format(rsl::emphasis::bold, "bold error"), "\x1b[1mbold error\x1b[0m");
  REQUIRE_STR(rsl::format(fg(rsl::color::blue), "blue log"), "\x1b[38;2;000;000;255mblue log\x1b[0m");
  REQUIRE_STR(rsl::format(rsl::text_style(), "hi"), "hi");
  REQUIRE_STR(rsl::format(fg(rsl::terminal_color::red), "tred"), "\x1b[31mtred\x1b[0m");
  REQUIRE_STR(rsl::format(bg(rsl::terminal_color::cyan), "tcyan"), "\x1b[46mtcyan\x1b[0m");
  REQUIRE_STR(rsl::format(fg(rsl::terminal_color::bright_green), "tbgreen"), "\x1b[92mtbgreen\x1b[0m");
  REQUIRE_STR(rsl::format(bg(rsl::terminal_color::bright_magenta), "tbmagenta"), "\x1b[105mtbmagenta\x1b[0m");
  REQUIRE_STR(rsl::format(fg(rsl::terminal_color::red), "{}", "foo"), "\x1b[31mfoo\x1b[0m");
  REQUIRE_STR(rsl::format("{}{}", rsl::styled("red", fg(rsl::color::red)), rsl::styled("bold", rsl::emphasis::bold)), "\x1b[38;2;255;000;000mred\x1b[0m\x1b[1mbold\x1b[0m");
  REQUIRE_STR(rsl::format("{}", rsl::styled("bar", fg(rsl::color::blue) | rsl::emphasis::underline)), "\x1b[4m\x1b[38;2;000;000;255mbar\x1b[0m");
}

TEST_CASE("color_test, format_to") {
  auto out = rsl::string();
  rsl::format_to(rsl::back_inserter(out), fg(rsl::rgb(255, 20, 30)), "rgb(255,20,30){}{}{}", 1, 2, 3);

  REQUIRE_STR(out, "\x1b[38;2;255;020;030mrgb(255,20,30)123\x1b[0m");
}
