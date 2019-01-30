#include "Fonts.hpp"

Fonts::Fonts(std::shared_ptr<Logger> logPtr)
:
ILoggable(logPtr, "Fonts"),
projection(glm::ortho(0.0f, static_cast<float>(Global::ScreenWidth()), static_cast<float>(Global::ScreenHeight()), 0.0f, -1.0f, 1.0f))
{}

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

    // test start
	if (fonts.empty()){
		// Initialization after OpenGL is ready
		glCall(glGenVertexArrays(1, &VAO));
		glCall(glGenBuffers(1, &VBO));
		glCall(glBindVertexArray(VAO));
		glCall(glBindBuffer(GL_ARRAY_BUFFER, VBO));
		glCall(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW));
		glCall(glEnableVertexAttribArray(0));
		glCall(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0));
		glCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
		glCall(glBindVertexArray(0));

		shader.Init("shader/Text.shader");
		shader.Bind();
		shader.SetUniformMat4f("projection", projection);
	}
    // test end

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

    // test start

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

    for (unsigned char c = 0; c < 128; c++){
		if (FT_Load_Char(newFont, c, FT_LOAD_RENDER)){
			ERROR("Failed to load glyph");
			continue;
		}

		// gen texture
		unsigned int texture;
		glCall(glGenTextures(1, &texture));
		glCall(glBindTexture(GL_TEXTURE_2D, texture));
		glCall(
			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RED,
				newFont->glyph->bitmap.width,
				newFont->glyph->bitmap.rows,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				newFont->glyph->bitmap.buffer
			)
		);
		// set texture options
		glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
		glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		// now store character for later use
		Character character = {
			texture,
			glm::ivec2(newFont->glyph->bitmap.width, newFont->glyph->bitmap.rows),
			glm::ivec2(newFont->glyph->bitmap_left, newFont->glyph->bitmap_top),
			static_cast<unsigned int>(newFont->glyph->advance.x)
		};

		Characters.insert(std::pair<char, Character>(c, character));
    }
	glCall(glBindTexture(GL_TEXTURE_2D, 0));
	//FT_Done_Face(face);
    //FT_Done_FreeType(ft);
    // test end

    return true;
}

FT_Face Fonts::Get(std::string fontKey){
    return fonts[fontKey];
}

void Fonts::Write(std::string& text, float& x, float& y, float& scale, glm::vec3& color)
{
	// Activate render state
	shader.Bind();
	shader.SetUniform3f("textColor", color.x, color.y, color.z);
	glCall(glActiveTexture(GL_TEXTURE0));
	glCall(glBindVertexArray(VAO));

	// Loop all char
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++){
		Character ch = Characters[*c];

		float xpos = x + ch.Bearing.x * scale;
		float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

		float w = ch.Size.x * scale;
		float h = ch.Size.y * scale;

		// update vbo for each char
		float vertices[6][4] = {
            { xpos,     ypos + h,   0.0, 0.0 },
            { xpos,     ypos,       0.0, 1.0 },
            { xpos + w, ypos,       1.0, 1.0 },

            { xpos,     ypos + h,   0.0, 0.0 },
            { xpos + w, ypos,       1.0, 1.0 },
            { xpos + w, ypos + h,   1.0, 0.0 }
        };
        // render char on quad
        glCall(glBindTexture(GL_TEXTURE_2D, ch.TextureID));
        // update vbo
        glCall(glBindBuffer(GL_ARRAY_BUFFER, VBO)); // Bind
        glCall(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices));
        glCall(glBindBuffer(GL_ARRAY_BUFFER, 0)); // Unbind
        // render quad
        glCall(glDrawArrays(GL_TRIANGLES, 0, 6));
        // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
	}
	glCall(glBindVertexArray(0));
	glCall(glBindTexture(GL_TEXTURE_2D, 0));
}

void Fonts::Clear(){
	shader.Close();

    INFO("Clearing");
    INFO(ss << "Font total: " << fonts.size());


    for(std::map<std::string, FT_Face>::iterator iter = fonts.begin(); iter != fonts.end();){
        //delete iter->second;
        INFO(ss << iter->first << " cleared (" << iter->second << ")");
        //fonts.erase(iter);
        FT_Done_Face(iter->second);
        INFO(ss << "Font total: " << fonts.size());
        iter = std::next(iter);
    }

	Characters.clear();
    fonts.clear();
    FT_Done_FreeType(freetypeLib);
}
