#ifndef FONTS_HPP
#define FONTS_HPP
#include <map>
#include <ft2build.h>   // font rendering
#include FT_FREETYPE_H
#include "Logger.hpp"
#include "ILoggable.hpp"
#include <sstream>

class Fonts : public ILoggable{
    FT_Library freetypeLib;
    std::map<std::string, FT_Face> fonts;
public:
    Fonts(Logger* logPtr);
    bool Init();
    bool Add(std::string fontKey, const char* fontPath, int fontSize);
    FT_Face Get(std::string fontKey);
    void Clear();
};

#endif // FONTS_HPP
