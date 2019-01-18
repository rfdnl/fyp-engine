#ifndef FONTS_HPP
#define FONTS_HPP

#include "Helper/ILoggable.hpp"
#include <memory>
#include "Helper/IncludeGL.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Component/Graphics/Shader.hpp"
#include <map>
#include <ft2build.h>
#include FT_FREETYPE_H

struct Character {
	unsigned int TextureID;  // ID handle of the glyph texture
    glm::ivec2 Size;       	// Size of glyph
    glm::ivec2 Bearing;    	// Offset from baseline to left/top of glyph
    unsigned int Advance;    // Offset to advance to next glyph
};

class Fonts : public ILoggable
{
    unsigned int VAO, VBO;
	Shader shader; //
	glm::mat4 projection = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
	FT_Library freetypeLib;
    std::map<char, Character> Characters;
    std::map<std::string, FT_Face> fonts;
public:
    Fonts(std::shared_ptr<Logger> logPtr);
    bool Initialize();
    void InitGraphics();
    bool Add(std::string fontKey, const char* fontPath, int fontSize);
    FT_Face Get(std::string fontKey);
    void Write(std::string& text, float& x, float& y, float& scale, glm::vec3& color);
    void Clear();
};

#endif // FONTS_HPP
