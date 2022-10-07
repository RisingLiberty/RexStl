// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: keys.h
// Copyright (c) Nick De Breuck 2022
//
// ============================================

#pragma once

#include "rex_std_extra/io/key.h"

REX_RSL_BEGIN_NAMESPACE::keys
{
  constexpr Key Zero  = {KeyCode::Zero, "Zero"};
  constexpr Key One   = {KeyCode::One, "One"};
  constexpr Key Two   = {KeyCode::Two, "Two"};
  constexpr Key Three = {KeyCode::Three, "Three"};
  constexpr Key Four  = {KeyCode::Four, "Four"};
  constexpr Key Five  = {KeyCode::Five, "Five"};
  constexpr Key Six   = {KeyCode::Six, "Six"};
  constexpr Key Seven = {KeyCode::Seven, "Seven"};
  constexpr Key Eight = {KeyCode::Eight, "Eight"};
  constexpr Key Nine  = {KeyCode::Nine, "Nine"};

  constexpr Key A = {KeyCode::A, "A"};
  constexpr Key B = {KeyCode::B, "B"};
  constexpr Key C = {KeyCode::C, "C"};
  constexpr Key D = {KeyCode::D, "D"};
  constexpr Key E = {KeyCode::E, "E"};
  constexpr Key F = {KeyCode::F, "F"};
  constexpr Key G = {KeyCode::G, "G"};
  constexpr Key H = {KeyCode::H, "H"};
  constexpr Key I = {KeyCode::I, "I"};
  constexpr Key J = {KeyCode::J, "J"};
  constexpr Key K = {KeyCode::K, "K"};
  constexpr Key L = {KeyCode::L, "L"};
  constexpr Key M = {KeyCode::M, "M"};
  constexpr Key N = {KeyCode::N, "N"};
  constexpr Key O = {KeyCode::O, "O"};
  constexpr Key P = {KeyCode::P, "P"};
  constexpr Key Q = {KeyCode::Q, "Q"};
  constexpr Key R = {KeyCode::R, "R"};
  constexpr Key S = {KeyCode::S, "S"};
  constexpr Key T = {KeyCode::T, "T"};
  constexpr Key U = {KeyCode::U, "U"};
  constexpr Key V = {KeyCode::V, "V"};
  constexpr Key W = {KeyCode::W, "W"};
  constexpr Key X = {KeyCode::X, "X"};
  constexpr Key Y = {KeyCode::Y, "Y"};
  constexpr Key Z = {KeyCode::Z, "Z"};

  constexpr Key F1  = {KeyCode::F1, "F1"};
  constexpr Key F2  = {KeyCode::F2, "F2"};
  constexpr Key F3  = {KeyCode::F3, "F3"};
  constexpr Key F4  = {KeyCode::F4, "F4"};
  constexpr Key F5  = {KeyCode::F5, "F5"};
  constexpr Key F6  = {KeyCode::F6, "F6"};
  constexpr Key F7  = {KeyCode::F7, "F7"};
  constexpr Key F8  = {KeyCode::F8, "F8"};
  constexpr Key F9  = {KeyCode::F9, "F9"};
  constexpr Key F10 = {KeyCode::F10, "F10"};
  constexpr Key F11 = {KeyCode::F11, "F11"};
  constexpr Key F12 = {KeyCode::F12, "F12"};
  constexpr Key F13 = {KeyCode::F13, "F13"};
  constexpr Key F14 = {KeyCode::F14, "F14"};
  constexpr Key F15 = {KeyCode::F15, "F15"};
  constexpr Key F16 = {KeyCode::F16, "F16"};
  constexpr Key F17 = {KeyCode::F17, "F17"};
  constexpr Key F18 = {KeyCode::F18, "F18"};
  constexpr Key F19 = {KeyCode::F19, "F19"};
  constexpr Key F20 = {KeyCode::F20, "F20"};
  constexpr Key F21 = {KeyCode::F21, "F21"};
  constexpr Key F22 = {KeyCode::F22, "F22"};
  constexpr Key F23 = {KeyCode::F23, "F23"};
  constexpr Key F24 = {KeyCode::F24, "F24"};

  constexpr Key UpArrow          = {KeyCode::UpArrow, "UpArrow"};
  constexpr Key DownArrow        = {KeyCode::DownArrow, "DownArrow"};
  constexpr Key LeftArrow        = {KeyCode::LeftArrow, "LeftArrow"};
  constexpr Key RightArrow       = {KeyCode::RightArrow, "RightArrow"};
  constexpr Key NumPad0          = {KeyCode::NumPad0, "NumPad0"};
  constexpr Key NumPad1          = {KeyCode::NumPad1, "NumPad1"};
  constexpr Key NumPad2          = {KeyCode::NumPad2, "NumPad2"};
  constexpr Key NumPad3          = {KeyCode::NumPad3, "NumPad3"};
  constexpr Key NumPad4          = {KeyCode::NumPad4, "NumPad4"};
  constexpr Key NumPad5          = {KeyCode::NumPad5, "NumPad5"};
  constexpr Key NumPad6          = {KeyCode::NumPad6, "NumPad6"};
  constexpr Key NumPad7          = {KeyCode::NumPad7, "NumPad7"};
  constexpr Key NumPad8          = {KeyCode::NumPad8, "NumPad8"};
  constexpr Key NumPad9          = {KeyCode::NumPad9, "NumPad9"};
  constexpr Key Escape           = {KeyCode::Escape, "Escape"};
  constexpr Key Equal            = {KeyCode::Equal, "Equal"};
  constexpr Key Grave            = {KeyCode::Grave, "Grave"};
  constexpr Key Tilde            = {KeyCode::Tilde, "Tilde"};
  constexpr Key Excalamtion      = {KeyCode::Excalamtion, "Excalamtion"};
  constexpr Key Question         = {KeyCode::Question, "Question"};
  constexpr Key AtSign           = {KeyCode::AtSign, "AtSign"};
  constexpr Key Pound            = {KeyCode::Pound, "Pound"};
  constexpr Key DollarSign       = {KeyCode::DollarSign, "DollarSign"};
  constexpr Key Percent          = {KeyCode::Percent, "Percent"};
  constexpr Key Caret            = {KeyCode::Caret, "Caret"};
  constexpr Key AmperSand        = {KeyCode::AmperSand, "AmperSand"};
  constexpr Key Star             = {KeyCode::Star, "Star"};
  constexpr Key OpenBracket      = {KeyCode::OpenBracket, "OpenBracket"};
  constexpr Key CloseBracket     = {KeyCode::CloseBracket, "CloseBracket"};
  constexpr Key Minus            = {KeyCode::Minus, "Minus"};
  constexpr Key UnderScore       = {KeyCode::UnderScore, "UnderScore"};
  constexpr Key Plus             = {KeyCode::Plus, "Plus"};
  constexpr Key OpenCurly        = {KeyCode::OpenCurly, "OpenCurly"};
  constexpr Key CloseCurly       = {KeyCode::CloseCurly, "CloseCurly"};
  constexpr Key OpenSquare       = {KeyCode::OpenSquare, "OpenSquare"};
  constexpr Key CloseSquare      = {KeyCode::CloseSquare, "CloseSquare"};
  constexpr Key SemiColo         = {KeyCode::SemiColo, "SemiColo"};
  constexpr Key Colon            = {KeyCode::Colon, "Colon"};
  constexpr Key SingleQuote      = {KeyCode::SingleQuote, "SingleQuote"};
  constexpr Key DoubleQuote      = {KeyCode::DoubleQuote, "DoubleQuote"};
  constexpr Key LessThan         = {KeyCode::LessThan, "LessThan"};
  constexpr Key GreaterThan      = {KeyCode::GreaterThan, "GreaterThan"};
  constexpr Key Comma            = {KeyCode::Comma, "Comma"};
  constexpr Key Dot              = {KeyCode::Dot, "Dot"};
  constexpr Key Slash            = {KeyCode::Slash, "Slash"};
  constexpr Key BackSlash        = {KeyCode::BackSlash, "BackSlash"};
  constexpr Key VerticalBar      = {KeyCode::VerticalBar, "VerticalBar"};
  constexpr Key Ctrl             = {KeyCode::Ctrl, " Ctrl"};
  constexpr Key Shift            = {KeyCode::Shift, " Shift"};
  constexpr Key Alt              = {KeyCode::Alt, " Alt"};
  constexpr Key Caps             = {KeyCode::Caps, " Caps"};
  constexpr Key BackSpace        = {KeyCode::BackSpace, " BackSpace"};
  constexpr Key Tab              = {KeyCode::Tab, " Tab"};
  constexpr Key Space            = {KeyCode::Space, " Space"};
  constexpr Key NumLock          = {KeyCode::NumLock, " NumLock"};
  constexpr Key Clear            = {KeyCode::Clear, "Clear"};
  constexpr Key Return           = {KeyCode::Return, "Return"};
  constexpr Key NewLine          = {KeyCode::NewLine, "NewLine"};
  constexpr Key Menu             = {KeyCode::Menu, "Menu"};
  constexpr Key Pause            = {KeyCode::Pause, "Pause"};
  constexpr Key Capital          = {KeyCode::Capital, "Capital"};
  constexpr Key PageUp           = {KeyCode::PageUp, "PageUp"};
  constexpr Key PageDown         = {KeyCode::PageDown, "PageDown"};
  constexpr Key End              = {KeyCode::End, "End"};
  constexpr Key Home             = {KeyCode::Home, "Home"};
  constexpr Key Select           = {KeyCode::Select, "Select"};
  constexpr Key Print            = {KeyCode::Print, "Print"};
  constexpr Key Snapshot         = {KeyCode::Snapshot, "Snapshot"};
  constexpr Key Insert           = {KeyCode::Insert, "Insert"};
  constexpr Key Help             = {KeyCode::Help, "Help"};
  constexpr Key Sleep            = {KeyCode::Sleep, "Sleep"};
  constexpr Key Scroll           = {KeyCode::Scroll, "Scroll"};
  constexpr Key LeftShift        = {KeyCode::LeftShift, "LeftShift"};
  constexpr Key RightShift       = {KeyCode::RightShift, "RightShift"};
  constexpr Key LeftCtrl         = {KeyCode::LeftCtrl, "LeftCtrl"};
  constexpr Key RightCtrl        = {KeyCode::RightCtrl, "RightCtrl"};
  constexpr Key LeftPlatformBtn  = {KeyCode::LeftPlatformBtn, "LeftPlatformBtn"};
  constexpr Key RightPlatformBtn = {KeyCode::RightPlatformBtn, "RightPlatformBtn"};
  constexpr Key Apps             = {KeyCode::Apps, "Apps"};
  constexpr Key Delete           = {KeyCode::Delete, "Delete"};
}