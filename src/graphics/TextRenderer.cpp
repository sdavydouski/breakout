#include "TextRenderer.h"
#include "../utils/FileManager.h"
#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"
#include <iostream>

TextRenderer::TextRenderer() {}

TextRenderer::~TextRenderer() {
    glDeleteTextures(1, &textureId_);
    glDeleteVertexArrays(1, &VAO_);
    glDeleteBuffers(1, &VBO_);
}

void TextRenderer::init(const std::string& path, ShaderProgram* shaderProgram) {
    shaderProgram_ = shaderProgram;
    this->initFont(path);
    this->initGlyphs();
    this->initVAO();
}

void TextRenderer::renderText(const std::string& text, const glm::vec2& position, const glm::vec3& color, float scale) {
    shaderProgram_->use();
    shaderProgram_->setUniform("textColor", color);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId_);
    glBindVertexArray(VAO_);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_);

    auto x = position.x;
    auto i = 0;
    
    for (auto c : text) {
        auto glyph = glyphs_[c];

        // Update VBO for each character
        auto width = glyph.size.x * scale;
        auto height = glyph.size.y * scale;

        auto xPosition = x;
        auto yPosition = position.y;
        
        GLfloat vertices[] = {
            xPosition,         yPosition - height, glyph.uvs[0].x, glyph.uvs[1].y,
            xPosition,         yPosition,          glyph.uvs[0].x, glyph.uvs[0].y,
            xPosition + width, yPosition - height, glyph.uvs[1].x, glyph.uvs[1].y,
            xPosition + width, yPosition,          glyph.uvs[1].x, glyph.uvs[0].y
        };

        glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices) * i, sizeof(vertices), vertices);
        
        x += width;
        i++;
    }

    // Render quads
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4 * text.length());
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);

    shaderProgram_->end();
}

void TextRenderer::initFont(const std::string& path) {
    auto fontData = FileManager::readAsBinary(path);
    auto atlasData = std::vector<unsigned char>(font_.atlasWidth * font_.atlasHeight);
    font_.charInfo = std::vector<stbtt_packedchar>(font_.charCount);

    stbtt_pack_context context;
    if (!stbtt_PackBegin(&context, &atlasData.front(), font_.atlasWidth, font_.atlasHeight, 0, 1, nullptr)) {
        std::cerr << "Failed to initialize font" << std::endl;
    }

    stbtt_PackSetOversampling(&context, font_.overSampleX, font_.overSampleY);
    if (!stbtt_PackFontRange(&context, &fontData.front(), 0,
        font_.size, font_.firstChar, font_.charCount, &font_.charInfo.front())) {
        std::cerr << "Failed to pack font" << std::endl;
    }

    stbtt_PackEnd(&context);

    stbtt_fontinfo fontInfo;
    stbtt_InitFont(&fontInfo, &fontData.front(), 0);

    glGenTextures(1, &textureId_);
    glBindTexture(GL_TEXTURE_2D, textureId_);
    // Disable byte-alignment restriction
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, font_.atlasWidth, font_.atlasHeight, 0,
        GL_RED, GL_UNSIGNED_BYTE, &atlasData.front());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void TextRenderer::initGlyphs() {
    float offsetX = 0;
    float offsetY = 0;

    for (auto c = font_.firstChar; c < font_.charCount; c++) {
        auto glyphInfo = this->getGlyphInfo(c, offsetX, offsetY);
        offsetX = glyphInfo.offsetX;
        offsetY = glyphInfo.offsetY;

        glyphs_[c] = glyphInfo;
    }

    // add more width to space glyph
    auto aGlyph = glyphs_['A'];
    glyphs_[' '].size.x += aGlyph.size.x;
}

GlyphInfo TextRenderer::getGlyphInfo(char character, float offsetX, float offsetY) {
    stbtt_aligned_quad quad;

    stbtt_GetPackedQuad(&font_.charInfo.front(), font_.atlasWidth, font_.atlasHeight, 
                        character - font_.firstChar, &offsetX, &offsetY, &quad, 1);

    auto info = GlyphInfo();
    info.offsetX = offsetX;
    info.offsetY = offsetY;
    info.size = glm::vec2(quad.x1 - quad.x0, quad.y1 - quad.y0);
    info.uvs[0] = { quad.s0, quad.t1 };
    info.uvs[1] = { quad.s1, quad.t0 };

    return info;
}

void TextRenderer::initVAO() {
    glGenVertexArrays(1, &VAO_);
    glGenBuffers(1, &VBO_);

    glBindVertexArray(VAO_);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_);

    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4 * font_.charCount, nullptr, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*) 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
