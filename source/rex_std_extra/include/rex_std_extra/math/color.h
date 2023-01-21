// ============================================
//
// REX - STANDARD LIBRARY IMPLEMENTATION
//
// Author: Nick De Breuck
// Twitter: @nick_debreuck
//
// File: color.h
// Copyright (c) Nick De Breuck 2023
//
// ============================================

#pragma once

#include "rex_std/array.h"
#include "rex_std/bonus/types.h"
#include "rex_std/ostream.h"

namespace rsl { inline namespace v1 {

template <typename T>
struct Color3
{
  static_assert(rsl::is_arithmetic_v<T>, "T must be of arithemetic type");

  constexpr Color3()
      : red(T())
      , green(T())
      , blue(T())
  {
  }

  constexpr Color3(T r, T g, T b)
      : red(r)
      , green(g)
      , blue(b)
  {
  }

  constexpr T* getData()
  {
    return color_data.data();
  }
  constexpr const T* getData() const
  {
    return color_data.data();
  }

  constexpr Color3& clamp(T min, T max)
  {
    *this = clamped();

    return *this;
  }
  constexpr Color3& clamped(T min, T max)
  {
    Color3 temp = *this;

    temp.red   = clamp(red, min, max);
    temp.green = clamp(green, min, max);
    temp.blue  = clamp(blue, min, max);

    return temp;
  }

  constexpr Color3 operator*(T brightness) const
  {
    Color3 tmp = *this;
    tmp.red *= brightness;
    tmp.green *= brightness;
    tmp.blue *= brightness;

    return tmp;
  }
  constexpr Color3 operator/(T brightness) const
  {
    Color3 tmp = *this;
    tmp.red /= brightness;
    tmp.green /= brightness;
    tmp.blue /= brightness;

    return tmp;
  }
  constexpr Color3& operator*(T brightness)
  {
    red *= brightness;
    green *= brightness;
    blue *= brightness;

    return *this;
  }
  constexpr Color3& operator/(T brightness)
  {
    red /= brightness;
    green /= brightness;
    blue /= brightness;

    return *this;
  }

  union
  {
    // Disabling this warning because it has to be nameless.
#pragma warning(push)
#pragma warning(disable : 4201)
    struct
    {
      T red, green, blue;
    };
#pragma warning(pop)
    Array<T, 3> color_data;
  };
};

template <typename T, typename T2>
T to_custom_color3(const Color3<T2>& color)
{
  static_assert(sizeof(T) == sizeof(Color3<T2>), "sizeof custom color must be equal to Color3");
  T custom_color;
  memcpy(&custom_color, &color, sizeof(color));
  return custom_color;
}

template <typename T, typename T2>
Color3<T> to_rex_color3(const T2& custom_color)
{
  static_assert(sizeof(T) == sizeof(Color3<T2>), "sizeof custom color must be equal to Color3");
  Color3<T> color;
  memcpy(&color, &custom_color, sizeof(custom_color));
  return color;
}

template <typename T>
ostream& operator<<(ostream& os, const Color3<T>& color)
{
  os << "(r: " << color.red << ", g: " << color.green << ", b: " << color.blue << ")";
  return os;
}

template <typename T>
struct Color4
{
  constexpr Color4()
      : red(T())
      , green(T())
      , blue(T())
      , alpha(T(1))
  {
  }

  constexpr Color4(T r, T g, T b, T a = 1.0f)
      : red(r)
      , green(g)
      , blue(b)
      , alpha(a)
  {
  }

  T* getData()
  {
    return color_data.data();
  }
  const T* getData() const
  {
    return color_data.data();
  }

  constexpr Color4& clamp(T min, T max)
  {
    *this = clamped();

    return *this;
  }
  constexpr Color4& clamped(T min, T max)
  {
    Color4 temp = *this;

    temp.red   = clamp(red, min, max);
    temp.green = clamp(green, min, max);
    temp.blue  = clamp(blue, min, max);

    return temp;
  }

  constexpr Color4 operator*(T brightness) const
  {
    Color4 tmp = *this;
    tmp.red *= brightness;
    tmp.green *= brightness;
    tmp.blue *= brightness;

    return tmp;
  }
  constexpr Color4 operator/(T brightness) const
  {
    Color4 tmp = *this;
    tmp.red /= brightness;
    tmp.green /= brightness;
    tmp.blue /= brightness;

    return tmp;
  }
  constexpr Color4& operator*(T brightness)
  {
    red *= brightness;
    green *= brightness;
    blue *= brightness;

    return *this;
  }
  constexpr Color4& operator/(T brightness)
  {
    red /= brightness;
    green /= brightness;
    blue /= brightness;

    return *this;
  }

  union
  {
    // Disabling this warning because it has to be nameless.
#pragma warning(push)
#pragma warning(disable : 4201)
    struct
    {
      T red, green, blue, alpha;
    };
#pragma warning(pop)
    Array<T, 4> color_data;
  };
};

template <typename T, typename T2>
T to_custom_color4(const Color4<T2>& color)
{
  static_assert(sizeof(T) == sizeof(Color4<T2>), "sizeof custom color must be equal to Color4");
  T custom_color;
  memcpy(&custom_color, &color, sizeof(color));
  return custom_color;
}

template <typename T, typename T2>
Color4<T> to_rex_color4(const T2& custom_color)
{
  static_assert(sizeof(T) == sizeof(Color4<T2>), "sizeof custom color must be equal to Color4");
  Color4<T> color;
  memcpy(&color, &custom_color, sizeof(custom_color));
  return color;
}

template <typename T>
ostream& operator<<(ostream& os, const Color3<T>& color)
{
  os << "(r: " << color.red << ", g: " << color.green << ", b: " << color.blue << ", a: " << color.alpha << ")";
  return os;
}

using Rgb  = Color3<uint8>;
using Rgba = Color4<uint8>;

using Color3f = Color3<float32>;
using Color4f = Color4<float32>;

namespace colors
{
  constexpr Color4f AliceBlue(0.941176534f, 0.972549081f, 1.000000000f, 1.000000000f);
  constexpr Color4f AntiqueWhite(0.980392218f, 0.921568692f, 0.843137324f, 1.000000000f);
  constexpr Color4f Aqua(0.000000000f, 1.000000000f, 1.000000000f, 1.000000000f);
  constexpr Color4f Aquamarine(0.498039246f, 1.000000000f, 0.831372619f, 1.000000000f);
  constexpr Color4f Azure(0.941176534f, 1.000000000f, 1.000000000f, 1.000000000f);
  constexpr Color4f Beige(0.960784376f, 0.960784376f, 0.862745166f, 1.000000000f);
  constexpr Color4f Bisque(1.000000000f, 0.894117713f, 0.768627524f, 1.000000000f);
  constexpr Color4f Black(0.000000000f, 0.000000000f, 0.000000000f, 1.000000000f);
  constexpr Color4f BlanchedAlmond(1.000000000f, 0.921568692f, 0.803921640f, 1.000000000f);
  constexpr Color4f Blue(0.000000000f, 0.000000000f, 1.000000000f, 1.000000000f);
  constexpr Color4f BlueViolet(0.541176498f, 0.168627456f, 0.886274576f, 1.000000000f);
  constexpr Color4f Brown(0.647058845f, 0.164705887f, 0.164705887f, 1.000000000f);
  constexpr Color4f BurlyWood(0.870588303f, 0.721568644f, 0.529411793f, 1.000000000f);
  constexpr Color4f CadetBlue(0.372549027f, 0.619607866f, 0.627451003f, 1.000000000f);
  constexpr Color4f Chartreuse(0.498039246f, 1.000000000f, 0.000000000f, 1.000000000f);
  constexpr Color4f Chocolate(0.823529482f, 0.411764741f, 0.117647067f, 1.000000000f);
  constexpr Color4f Coral(1.000000000f, 0.498039246f, 0.313725501f, 1.000000000f);
  constexpr Color4f CornflowerBlue(0.392156899f, 0.584313750f, 0.929411829f, 1.000000000f);
  constexpr Color4f Cornsilk(1.000000000f, 0.972549081f, 0.862745166f, 1.000000000f);
  constexpr Color4f Crimson(0.862745166f, 0.078431375f, 0.235294133f, 1.000000000f);
  constexpr Color4f Cyan(0.000000000f, 1.000000000f, 1.000000000f, 1.000000000f);
  constexpr Color4f DarkBlue(0.000000000f, 0.000000000f, 0.545098066f, 1.000000000f);
  constexpr Color4f DarkCyan(0.000000000f, 0.545098066f, 0.545098066f, 1.000000000f);
  constexpr Color4f DarkGoldenrod(0.721568644f, 0.525490224f, 0.043137256f, 1.000000000f);
  constexpr Color4f DarkGray(0.662745118f, 0.662745118f, 0.662745118f, 1.000000000f);
  constexpr Color4f DarkGreen(0.000000000f, 0.392156899f, 0.000000000f, 1.000000000f);
  constexpr Color4f DarkKhaki(0.741176486f, 0.717647076f, 0.419607878f, 1.000000000f);
  constexpr Color4f DarkMagenta(0.545098066f, 0.000000000f, 0.545098066f, 1.000000000f);
  constexpr Color4f DarkOliveGreen(0.333333343f, 0.419607878f, 0.184313729f, 1.000000000f);
  constexpr Color4f DarkOrange(1.000000000f, 0.549019635f, 0.000000000f, 1.000000000f);
  constexpr Color4f DarkOrchid(0.600000024f, 0.196078449f, 0.800000072f, 1.000000000f);
  constexpr Color4f DarkRed(0.545098066f, 0.000000000f, 0.000000000f, 1.000000000f);
  constexpr Color4f DarkSalmon(0.913725555f, 0.588235319f, 0.478431404f, 1.000000000f);
  constexpr Color4f DarkSeaGreen(0.560784340f, 0.737254918f, 0.545098066f, 1.000000000f);
  constexpr Color4f DarkSlateBlue(0.282352954f, 0.239215702f, 0.545098066f, 1.000000000f);
  constexpr Color4f DarkSlateGray(0.184313729f, 0.309803933f, 0.309803933f, 1.000000000f);
  constexpr Color4f DarkTurquoise(0.000000000f, 0.807843208f, 0.819607913f, 1.000000000f);
  constexpr Color4f DarkViolet(0.580392182f, 0.000000000f, 0.827451050f, 1.000000000f);
  constexpr Color4f DeepPink(1.000000000f, 0.078431375f, 0.576470613f, 1.000000000f);
  constexpr Color4f DeepSkyBlue(0.000000000f, 0.749019623f, 1.000000000f, 1.000000000f);
  constexpr Color4f DimGray(0.411764741f, 0.411764741f, 0.411764741f, 1.000000000f);
  constexpr Color4f DodgerBlue(0.117647067f, 0.564705908f, 1.000000000f, 1.000000000f);
  constexpr Color4f Firebrick(0.698039234f, 0.133333340f, 0.133333340f, 1.000000000f);
  constexpr Color4f FloralWhite(1.000000000f, 0.980392218f, 0.941176534f, 1.000000000f);
  constexpr Color4f ForestGreen(0.133333340f, 0.545098066f, 0.133333340f, 1.000000000f);
  constexpr Color4f Fuchsia(1.000000000f, 0.000000000f, 1.000000000f, 1.000000000f);
  constexpr Color4f Gainsboro(0.862745166f, 0.862745166f, 0.862745166f, 1.000000000f);
  constexpr Color4f GhostWhite(0.972549081f, 0.972549081f, 1.000000000f, 1.000000000f);
  constexpr Color4f Gold(1.000000000f, 0.843137324f, 0.000000000f, 1.000000000f);
  constexpr Color4f Goldenrod(0.854902029f, 0.647058845f, 0.125490203f, 1.000000000f);
  constexpr Color4f Gray(0.501960814f, 0.501960814f, 0.501960814f, 1.000000000f);
  constexpr Color4f Green(0.000000000f, 0.501960814f, 0.000000000f, 1.000000000f);
  constexpr Color4f GreenYellow(0.678431392f, 1.000000000f, 0.184313729f, 1.000000000f);
  constexpr Color4f Honeydew(0.941176534f, 1.000000000f, 0.941176534f, 1.000000000f);
  constexpr Color4f HotPink(1.000000000f, 0.411764741f, 0.705882370f, 1.000000000f);
  constexpr Color4f IndianRed(0.803921640f, 0.360784322f, 0.360784322f, 1.000000000f);
  constexpr Color4f Indigo(0.294117659f, 0.000000000f, 0.509803951f, 1.000000000f);
  constexpr Color4f Ivory(1.000000000f, 1.000000000f, 0.941176534f, 1.000000000f);
  constexpr Color4f Khaki(0.941176534f, 0.901960850f, 0.549019635f, 1.000000000f);
  constexpr Color4f Lavender(0.901960850f, 0.901960850f, 0.980392218f, 1.000000000f);
  constexpr Color4f LavenderBlush(1.000000000f, 0.941176534f, 0.960784376f, 1.000000000f);
  constexpr Color4f LawnGreen(0.486274540f, 0.988235354f, 0.000000000f, 1.000000000f);
  constexpr Color4f LemonChiffon(1.000000000f, 0.980392218f, 0.803921640f, 1.000000000f);
  constexpr Color4f LightBlue(0.678431392f, 0.847058892f, 0.901960850f, 1.000000000f);
  constexpr Color4f LightCoral(0.941176534f, 0.501960814f, 0.501960814f, 1.000000000f);
  constexpr Color4f LightCyan(0.878431439f, 1.000000000f, 1.000000000f, 1.000000000f);
  constexpr Color4f LightGoldenrodYellow(0.980392218f, 0.980392218f, 0.823529482f, 1.000000000f);
  constexpr Color4f LightGreen(0.564705908f, 0.933333397f, 0.564705908f, 1.000000000f);
  constexpr Color4f LightGray(0.827451050f, 0.827451050f, 0.827451050f, 1.000000000f);
  constexpr Color4f LightPink(1.000000000f, 0.713725507f, 0.756862819f, 1.000000000f);
  constexpr Color4f LightSalmon(1.000000000f, 0.627451003f, 0.478431404f, 1.000000000f);
  constexpr Color4f LightSeaGreen(0.125490203f, 0.698039234f, 0.666666687f, 1.000000000f);
  constexpr Color4f LightSkyBlue(0.529411793f, 0.807843208f, 0.980392218f, 1.000000000f);
  constexpr Color4f LightSlateGray(0.466666698f, 0.533333361f, 0.600000024f, 1.000000000f);
  constexpr Color4f LightSteelBlue(0.690196097f, 0.768627524f, 0.870588303f, 1.000000000f);
  constexpr Color4f LightYellow(1.000000000f, 1.000000000f, 0.878431439f, 1.000000000f);
  constexpr Color4f Lime(0.000000000f, 1.000000000f, 0.000000000f, 1.000000000f);
  constexpr Color4f LimeGreen(0.196078449f, 0.803921640f, 0.196078449f, 1.000000000f);
  constexpr Color4f Linen(0.980392218f, 0.941176534f, 0.901960850f, 1.000000000f);
  constexpr Color4f Magenta(1.000000000f, 0.000000000f, 1.000000000f, 1.000000000f);
  constexpr Color4f Maroon(0.501960814f, 0.000000000f, 0.000000000f, 1.000000000f);
  constexpr Color4f MediumAquamarine(0.400000036f, 0.803921640f, 0.666666687f, 1.000000000f);
  constexpr Color4f MediumBlue(0.000000000f, 0.000000000f, 0.803921640f, 1.000000000f);
  constexpr Color4f MediumOrchid(0.729411781f, 0.333333343f, 0.827451050f, 1.000000000f);
  constexpr Color4f MediumPurple(0.576470613f, 0.439215720f, 0.858823597f, 1.000000000f);
  constexpr Color4f MediumSeaGreen(0.235294133f, 0.701960802f, 0.443137288f, 1.000000000f);
  constexpr Color4f MediumSlateBlue(0.482352972f, 0.407843173f, 0.933333397f, 1.000000000f);
  constexpr Color4f MediumSpringGreen(0.000000000f, 0.980392218f, 0.603921592f, 1.000000000f);
  constexpr Color4f MediumTurquoise(0.282352954f, 0.819607913f, 0.800000072f, 1.000000000f);
  constexpr Color4f MediumVioletRed(0.780392230f, 0.082352944f, 0.521568656f, 1.000000000f);
  constexpr Color4f MidnightBlue(0.098039225f, 0.098039225f, 0.439215720f, 1.000000000f);
  constexpr Color4f MintCream(0.960784376f, 1.000000000f, 0.980392218f, 1.000000000f);
  constexpr Color4f MistyRose(1.000000000f, 0.894117713f, 0.882353008f, 1.000000000f);
  constexpr Color4f Moccasin(1.000000000f, 0.894117713f, 0.709803939f, 1.000000000f);
  constexpr Color4f NavajoWhite(1.000000000f, 0.870588303f, 0.678431392f, 1.000000000f);
  constexpr Color4f Navy(0.000000000f, 0.000000000f, 0.501960814f, 1.000000000f);
  constexpr Color4f OldLace(0.992156923f, 0.960784376f, 0.901960850f, 1.000000000f);
  constexpr Color4f Olive(0.501960814f, 0.501960814f, 0.000000000f, 1.000000000f);
  constexpr Color4f OliveDrab(0.419607878f, 0.556862772f, 0.137254909f, 1.000000000f);
  constexpr Color4f Orange(1.000000000f, 0.647058845f, 0.000000000f, 1.000000000f);
  constexpr Color4f OrangeRed(1.000000000f, 0.270588249f, 0.000000000f, 1.000000000f);
  constexpr Color4f Orchid(0.854902029f, 0.439215720f, 0.839215755f, 1.000000000f);
  constexpr Color4f PaleGoldenrod(0.933333397f, 0.909803987f, 0.666666687f, 1.000000000f);
  constexpr Color4f PaleGreen(0.596078455f, 0.984313786f, 0.596078455f, 1.000000000f);
  constexpr Color4f PaleTurquoise(0.686274529f, 0.933333397f, 0.933333397f, 1.000000000f);
  constexpr Color4f PaleVioletRed(0.858823597f, 0.439215720f, 0.576470613f, 1.000000000f);
  constexpr Color4f PapayaWhip(1.000000000f, 0.937254965f, 0.835294187f, 1.000000000f);
  constexpr Color4f PeachPuff(1.000000000f, 0.854902029f, 0.725490212f, 1.000000000f);
  constexpr Color4f Peru(0.803921640f, 0.521568656f, 0.247058839f, 1.000000000f);
  constexpr Color4f Pink(1.000000000f, 0.752941251f, 0.796078503f, 1.000000000f);
  constexpr Color4f Plum(0.866666734f, 0.627451003f, 0.866666734f, 1.000000000f);
  constexpr Color4f PowderBlue(0.690196097f, 0.878431439f, 0.901960850f, 1.000000000f);
  constexpr Color4f Purple(0.501960814f, 0.000000000f, 0.501960814f, 1.000000000f);
  constexpr Color4f Red(1.000000000f, 0.000000000f, 0.000000000f, 1.000000000f);
  constexpr Color4f RosyBrown(0.737254918f, 0.560784340f, 0.560784340f, 1.000000000f);
  constexpr Color4f RoyalBlue(0.254901975f, 0.411764741f, 0.882353008f, 1.000000000f);
  constexpr Color4f SaddleBrown(0.545098066f, 0.270588249f, 0.074509807f, 1.000000000f);
  constexpr Color4f Salmon(0.980392218f, 0.501960814f, 0.447058856f, 1.000000000f);
  constexpr Color4f SandyBrown(0.956862807f, 0.643137276f, 0.376470625f, 1.000000000f);
  constexpr Color4f SeaGreen(0.180392161f, 0.545098066f, 0.341176480f, 1.000000000f);
  constexpr Color4f SeaShell(1.000000000f, 0.960784376f, 0.933333397f, 1.000000000f);
  constexpr Color4f Sienna(0.627451003f, 0.321568638f, 0.176470593f, 1.000000000f);
  constexpr Color4f Silver(0.752941251f, 0.752941251f, 0.752941251f, 1.000000000f);
  constexpr Color4f SkyBlue(0.529411793f, 0.807843208f, 0.921568692f, 1.000000000f);
  constexpr Color4f SlateBlue(0.415686309f, 0.352941185f, 0.803921640f, 1.000000000f);
  constexpr Color4f SlateGray(0.439215720f, 0.501960814f, 0.564705908f, 1.000000000f);
  constexpr Color4f Snow(1.000000000f, 0.980392218f, 0.980392218f, 1.000000000f);
  constexpr Color4f SpringGreen(0.000000000f, 1.000000000f, 0.498039246f, 1.000000000f);
  constexpr Color4f SteelBlue(0.274509817f, 0.509803951f, 0.705882370f, 1.000000000f);
  constexpr Color4f Tan(0.823529482f, 0.705882370f, 0.549019635f, 1.000000000f);
  constexpr Color4f Teal(0.000000000f, 0.501960814f, 0.501960814f, 1.000000000f);
  constexpr Color4f Thistle(0.847058892f, 0.749019623f, 0.847058892f, 1.000000000f);
  constexpr Color4f Tomato(1.000000000f, 0.388235331f, 0.278431386f, 1.000000000f);
  constexpr Color4f Transparent(0.000000000f, 0.000000000f, 0.000000000f, 0.000000000f);
  constexpr Color4f Turquoise(0.250980407f, 0.878431439f, 0.815686345f, 1.000000000f);
  constexpr Color4f Violet(0.933333397f, 0.509803951f, 0.933333397f, 1.000000000f);
  constexpr Color4f Wheat(0.960784376f, 0.870588303f, 0.701960802f, 1.000000000f);
  constexpr Color4f White(1.000000000f, 1.000000000f, 1.000000000f, 1.000000000f);
  constexpr Color4f WhiteSmoke(0.960784376f, 0.960784376f, 0.960784376f, 1.000000000f);
  constexpr Color4f Yellow(1.000000000f, 1.000000000f, 0.000000000f, 1.000000000f);
  constexpr Color4f YellowGreen(0.603921592f, 0.803921640f, 0.196078449f, 1.000000000f);
} // namespace colors

namespace rgba_colors
{
  constexpr Rgba color4f_to_rgba(const Color4f& color)
  {
    Rgba rgba;
    rgba.red   = static_cast<uint8>(255 * color.red);
    rgba.green = static_cast<uint8>(255 * color.green);
    rgba.blue  = static_cast<uint8>(255 * color.blue);
    rgba.alpha = static_cast<uint8>(255 * color.alpha);

    return rgba;
  }

  constexpr Rgba AliceBlue            = color4f_to_rgba(colors::AliceBlue);
  constexpr Rgba AntiqueWhite         = color4f_to_rgba(colors::AntiqueWhite);
  constexpr Rgba Aqua                 = color4f_to_rgba(colors::Aqua);
  constexpr Rgba Aquamarine           = color4f_to_rgba(colors::Aquamarine);
  constexpr Rgba Azure                = color4f_to_rgba(colors::Azure);
  constexpr Rgba Beige                = color4f_to_rgba(colors::Beige);
  constexpr Rgba Bisque               = color4f_to_rgba(colors::Bisque);
  constexpr Rgba Black                = color4f_to_rgba(colors::Black);
  constexpr Rgba BlanchedAlmond       = color4f_to_rgba(colors::BlanchedAlmond);
  constexpr Rgba Blue                 = color4f_to_rgba(colors::Blue);
  constexpr Rgba BlueViolet           = color4f_to_rgba(colors::BlueViolet);
  constexpr Rgba Brown                = color4f_to_rgba(colors::Brown);
  constexpr Rgba BurlyWood            = color4f_to_rgba(colors::BurlyWood);
  constexpr Rgba CadetBlue            = color4f_to_rgba(colors::CadetBlue);
  constexpr Rgba Chartreuse           = color4f_to_rgba(colors::Chartreuse);
  constexpr Rgba Chocolate            = color4f_to_rgba(colors::Chocolate);
  constexpr Rgba Coral                = color4f_to_rgba(colors::Coral);
  constexpr Rgba CornflowerBlue       = color4f_to_rgba(colors::CornflowerBlue);
  constexpr Rgba Cornsilk             = color4f_to_rgba(colors::Cornsilk);
  constexpr Rgba Crimson              = color4f_to_rgba(colors::Crimson);
  constexpr Rgba Cyan                 = color4f_to_rgba(colors::Cyan);
  constexpr Rgba DarkBlue             = color4f_to_rgba(colors::DarkBlue);
  constexpr Rgba DarkCyan             = color4f_to_rgba(colors::DarkCyan);
  constexpr Rgba DarkGoldenrod        = color4f_to_rgba(colors::DarkGoldenrod);
  constexpr Rgba DarkGray             = color4f_to_rgba(colors::DarkGray);
  constexpr Rgba DarkGreen            = color4f_to_rgba(colors::DarkGreen);
  constexpr Rgba DarkKhaki            = color4f_to_rgba(colors::DarkKhaki);
  constexpr Rgba DarkMagenta          = color4f_to_rgba(colors::DarkMagenta);
  constexpr Rgba DarkOliveGreen       = color4f_to_rgba(colors::DarkOliveGreen);
  constexpr Rgba DarkOrange           = color4f_to_rgba(colors::DarkOrange);
  constexpr Rgba DarkOrchid           = color4f_to_rgba(colors::DarkOrchid);
  constexpr Rgba DarkRed              = color4f_to_rgba(colors::DarkRed);
  constexpr Rgba DarkSalmon           = color4f_to_rgba(colors::DarkSalmon);
  constexpr Rgba DarkSeaGreen         = color4f_to_rgba(colors::DarkSeaGreen);
  constexpr Rgba DarkSlateBlue        = color4f_to_rgba(colors::DarkSlateBlue);
  constexpr Rgba DarkSlateGray        = color4f_to_rgba(colors::DarkSlateGray);
  constexpr Rgba DarkTurquoise        = color4f_to_rgba(colors::DarkTurquoise);
  constexpr Rgba DarkViolet           = color4f_to_rgba(colors::DarkViolet);
  constexpr Rgba DeepPink             = color4f_to_rgba(colors::DeepPink);
  constexpr Rgba DeepSkyBlue          = color4f_to_rgba(colors::DeepSkyBlue);
  constexpr Rgba DimGray              = color4f_to_rgba(colors::DimGray);
  constexpr Rgba DodgerBlue           = color4f_to_rgba(colors::DodgerBlue);
  constexpr Rgba Firebrick            = color4f_to_rgba(colors::Firebrick);
  constexpr Rgba FloralWhite          = color4f_to_rgba(colors::FloralWhite);
  constexpr Rgba ForestGreen          = color4f_to_rgba(colors::ForestGreen);
  constexpr Rgba Fuchsia              = color4f_to_rgba(colors::Fuchsia);
  constexpr Rgba Gainsboro            = color4f_to_rgba(colors::Gainsboro);
  constexpr Rgba GhostWhite           = color4f_to_rgba(colors::GhostWhite);
  constexpr Rgba Gold                 = color4f_to_rgba(colors::Gold);
  constexpr Rgba Goldenrod            = color4f_to_rgba(colors::Goldenrod);
  constexpr Rgba Gray                 = color4f_to_rgba(colors::Gray);
  constexpr Rgba Green                = color4f_to_rgba(colors::Green);
  constexpr Rgba GreenYellow          = color4f_to_rgba(colors::GreenYellow);
  constexpr Rgba Honeydew             = color4f_to_rgba(colors::Honeydew);
  constexpr Rgba HotPink              = color4f_to_rgba(colors::HotPink);
  constexpr Rgba IndianRed            = color4f_to_rgba(colors::IndianRed);
  constexpr Rgba Indigo               = color4f_to_rgba(colors::Indigo);
  constexpr Rgba Ivory                = color4f_to_rgba(colors::Ivory);
  constexpr Rgba Khaki                = color4f_to_rgba(colors::Khaki);
  constexpr Rgba Lavender             = color4f_to_rgba(colors::Lavender);
  constexpr Rgba LavenderBlush        = color4f_to_rgba(colors::LavenderBlush);
  constexpr Rgba LawnGreen            = color4f_to_rgba(colors::LawnGreen);
  constexpr Rgba LemonChiffon         = color4f_to_rgba(colors::LemonChiffon);
  constexpr Rgba LightBlue            = color4f_to_rgba(colors::LightBlue);
  constexpr Rgba LightCoral           = color4f_to_rgba(colors::LightCoral);
  constexpr Rgba LightCyan            = color4f_to_rgba(colors::LightCyan);
  constexpr Rgba LightGoldenrodYellow = color4f_to_rgba(colors::LightGoldenrodYellow);
  constexpr Rgba LightGreen           = color4f_to_rgba(colors::LightGreen);
  constexpr Rgba LightGray            = color4f_to_rgba(colors::LightGray);
  constexpr Rgba LightPink            = color4f_to_rgba(colors::LightPink);
  constexpr Rgba LightSalmon          = color4f_to_rgba(colors::LightSalmon);
  constexpr Rgba LightSeaGreen        = color4f_to_rgba(colors::LightSeaGreen);
  constexpr Rgba LightSkyBlue         = color4f_to_rgba(colors::LightSkyBlue);
  constexpr Rgba LightSlateGray       = color4f_to_rgba(colors::LightSlateGray);
  constexpr Rgba LightSteelBlue       = color4f_to_rgba(colors::LightSteelBlue);
  constexpr Rgba LightYellow          = color4f_to_rgba(colors::LightYellow);
  constexpr Rgba Lime                 = color4f_to_rgba(colors::Lime);
  constexpr Rgba LimeGreen            = color4f_to_rgba(colors::LimeGreen);
  constexpr Rgba Linen                = color4f_to_rgba(colors::Linen);
  constexpr Rgba Magenta              = color4f_to_rgba(colors::Magenta);
  constexpr Rgba Maroon               = color4f_to_rgba(colors::Maroon);
  constexpr Rgba MediumAquamarine     = color4f_to_rgba(colors::MediumAquamarine);
  constexpr Rgba MediumBlue           = color4f_to_rgba(colors::MediumBlue);
  constexpr Rgba MediumOrchid         = color4f_to_rgba(colors::MediumOrchid);
  constexpr Rgba MediumPurple         = color4f_to_rgba(colors::MediumPurple);
  constexpr Rgba MediumSeaGreen       = color4f_to_rgba(colors::MediumSeaGreen);
  constexpr Rgba MediumSlateBlue      = color4f_to_rgba(colors::MediumSlateBlue);
  constexpr Rgba MediumSpringGreen    = color4f_to_rgba(colors::MediumSpringGreen);
  constexpr Rgba MediumTurquoise      = color4f_to_rgba(colors::MediumTurquoise);
  constexpr Rgba MediumVioletRed      = color4f_to_rgba(colors::MediumVioletRed);
  constexpr Rgba MidnightBlue         = color4f_to_rgba(colors::MidnightBlue);
  constexpr Rgba MintCream            = color4f_to_rgba(colors::MintCream);
  constexpr Rgba MistyRose            = color4f_to_rgba(colors::MistyRose);
  constexpr Rgba Moccasin             = color4f_to_rgba(colors::Moccasin);
  constexpr Rgba NavajoWhite          = color4f_to_rgba(colors::NavajoWhite);
  constexpr Rgba Navy                 = color4f_to_rgba(colors::Navy);
  constexpr Rgba OldLace              = color4f_to_rgba(colors::OldLace);
  constexpr Rgba Olive                = color4f_to_rgba(colors::Olive);
  constexpr Rgba OliveDrab            = color4f_to_rgba(colors::OliveDrab);
  constexpr Rgba Orange               = color4f_to_rgba(colors::Orange);
  constexpr Rgba OrangeRed            = color4f_to_rgba(colors::OrangeRed);
  constexpr Rgba Orchid               = color4f_to_rgba(colors::Orchid);
  constexpr Rgba PaleGoldenrod        = color4f_to_rgba(colors::PaleGoldenrod);
  constexpr Rgba PaleGreen            = color4f_to_rgba(colors::PaleGreen);
  constexpr Rgba PaleTurquoise        = color4f_to_rgba(colors::PaleTurquoise);
  constexpr Rgba PaleVioletRed        = color4f_to_rgba(colors::PaleVioletRed);
  constexpr Rgba PapayaWhip           = color4f_to_rgba(colors::PapayaWhip);
  constexpr Rgba PeachPuff            = color4f_to_rgba(colors::PeachPuff);
  constexpr Rgba Peru                 = color4f_to_rgba(colors::Peru);
  constexpr Rgba Pink                 = color4f_to_rgba(colors::Pink);
  constexpr Rgba Plum                 = color4f_to_rgba(colors::Plum);
  constexpr Rgba PowderBlue           = color4f_to_rgba(colors::PowderBlue);
  constexpr Rgba Purple               = color4f_to_rgba(colors::Purple);
  constexpr Rgba Red                  = color4f_to_rgba(colors::Red);
  constexpr Rgba RosyBrown            = color4f_to_rgba(colors::RosyBrown);
  constexpr Rgba RoyalBlue            = color4f_to_rgba(colors::RoyalBlue);
  constexpr Rgba SaddleBrown          = color4f_to_rgba(colors::SaddleBrown);
  constexpr Rgba Salmon               = color4f_to_rgba(colors::Salmon);
  constexpr Rgba SandyBrown           = color4f_to_rgba(colors::SandyBrown);
  constexpr Rgba SeaGreen             = color4f_to_rgba(colors::SeaGreen);
  constexpr Rgba SeaShell             = color4f_to_rgba(colors::SeaShell);
  constexpr Rgba Sienna               = color4f_to_rgba(colors::Sienna);
  constexpr Rgba Silver               = color4f_to_rgba(colors::Silver);
  constexpr Rgba SkyBlue              = color4f_to_rgba(colors::SkyBlue);
  constexpr Rgba SlateBlue            = color4f_to_rgba(colors::SlateBlue);
  constexpr Rgba SlateGray            = color4f_to_rgba(colors::SlateGray);
  constexpr Rgba Snow                 = color4f_to_rgba(colors::Snow);
  constexpr Rgba SpringGreen          = color4f_to_rgba(colors::SpringGreen);
  constexpr Rgba SteelBlue            = color4f_to_rgba(colors::SteelBlue);
  constexpr Rgba Tan                  = color4f_to_rgba(colors::Tan);
  constexpr Rgba Teal                 = color4f_to_rgba(colors::Teal);
  constexpr Rgba Thistle              = color4f_to_rgba(colors::Thistle);
  constexpr Rgba Tomato               = color4f_to_rgba(colors::Tomato);
  constexpr Rgba Transparent          = color4f_to_rgba(colors::Transparent);
  constexpr Rgba Turquoise            = color4f_to_rgba(colors::Turquoise);
  constexpr Rgba Violet               = color4f_to_rgba(colors::Violet);
  constexpr Rgba Wheat                = color4f_to_rgba(colors::Wheat);
  constexpr Rgba White                = color4f_to_rgba(colors::White);
  constexpr Rgba WhiteSmoke           = color4f_to_rgba(colors::WhiteSmoke);
  constexpr Rgba Yellow               = color4f_to_rgba(colors::Yellow);
  constexpr Rgba YellowGreen          = color4f_to_rgba(colors::YellowGreen);
} // namespace rgba_colors

}}