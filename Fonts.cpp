#include "Fonts.hpp"

bool Fonts::Initialize(){
    INFO("Initialize()");
    if (FT_Init_FreeType(&freetypeLib)){
        ERROR("Cannot initialize FreeType library");
        return false;
    }
    INFO("Ready!");
    return true;
}

// Add("Arial20", "fonts/arial.ttf", 20);
bool Fonts::Add(std::string fontKey, const char* fontPath, int fontSize){
    INFO(ss << "Add(" << fontKey << ", " << fontPath << ", " << fontSize << ")");
    FT_Face newFont;
    if (FT_New_Face(freetypeLib, fontPath, 0, &newFont)){
        ERROR(ss << "Failed to load font (" << fontKey << ")");
        return false;
    }
    fonts[fontKey] = newFont;
    INFO(ss << "Font added (" << fontKey << ")");

    /*setting one of them to 0 will let this function to
    calculate dynamically the value for the other value.*/
    FT_Set_Pixel_Sizes(fonts[fontKey], 0, fontSize);
    return true;
}

FT_Face Fonts::Get(std::string fontKey){
    return fonts[fontKey];
}

void Fonts::Clear(){
    INFO("Clear()");
    INFO(ss << "Font total: " << fonts.size());
    for(std::map<std::string, FT_Face>::iterator iter = fonts.begin(); iter != fonts.end(); ++iter){
        //delete iter->second;
        INFO(ss << iter->first << " cleared (" << iter->second << ")");
        fonts.erase(iter);
        INFO(ss << "Font total: " << fonts.size());
    }
}
