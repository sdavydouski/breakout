#pragma once

#include <GL/glew.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <string>
#include <map>
#include "ShaderProgram.h"
#include "Font.h"
#include "GlyphInfo.h"
#include "../Singleton.h"

class TextRenderer: public Singleton<TextRenderer> {
public:
    void init(const std::string& path, ShaderProgram* shaderProgram);
    void renderText(const std::string& text, 
                           const glm::vec2& position, 
                           const glm::vec3& color, 
                           float scale = 1.0f);
private:
    ShaderProgram* shaderProgram_;
    GLuint VAO_;
    GLuint VBO_;
    GLuint textureId_;

    Font font_;

    std::map<char, GlyphInfo> glyphs_;
    
    void initFont(const std::string& path);
    void initGlyphs();
    void initVAO();

    GlyphInfo getGlyphInfo(char character, float offsetX, float offsetY);

    TextRenderer();
    ~TextRenderer();

friend Singleton;
};
