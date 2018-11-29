#ifndef FONTS_HPP
#define FONTS_HPP

#include "Helper/ILoggable.hpp"
#include <map>
#include <ft2build.h>
#include FT_FREETYPE_H

class Fonts : public ILoggable
{
    FT_Library freetypeLib;
    std::map<std::string, FT_Face> fonts;
public:
    Fonts(std::shared_ptr<Logger> logPtr):ILoggable(logPtr, "Fonts"){}

    bool Initialize();
    bool Add(std::string fontKey, const char* fontPath, int fontSize);
    FT_Face Get(std::string fontKey);
    void Clear();
};

#endif // FONTS_HPP
