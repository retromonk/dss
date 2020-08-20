#include "text.h"

#include <ft2build.h>
#include FT_FREETYPE_H
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <FTGL/ftgl.h>

#include <map>
#include <iostream>

namespace ui
{
    class TextImpl : public IRenderable
    {
    public:
        TextImpl(const std::string &text, int posX, int posY, int fontSize) : text_(text), pos_x_(posX), pos_y_(posY),
                                                                              font_("arial.ttf")
        {
            font_.FaceSize(fontSize);
            layout_.SetFont(&font_);
            layout_.SetAlignment(FTGL::TextAlignment::ALIGN_RIGHT);
        }

        void Init() override
        {
        }

        void Render() override
        {
            auto bb = font_.BBox(text_.c_str(), text_.size());
            auto posX = static_cast<float>(pos_x_) - (bb.Upper().X() - bb.Lower().X()) / 2.0f;
            auto posY = static_cast<float>(pos_y_) + (bb.Upper().Y() - bb.Lower().Y()) / 2.0f;
            font_.Render(text_.c_str(), text_.size(), FTPoint(posX, posY));
        }

    private:
        std::string text_;
        int pos_x_;
        int pos_y_;
        FTGLPixmapFont font_;
        FTSimpleLayout layout_;
    };

    Text::Text(const std::string &text, int posX, int posY, int fontSize) : impl_(std::make_unique<TextImpl>(text, posX, posY, fontSize))
    {
    }

    void Text::Init()
    {
        impl_->Init();
    }

    void Text::Render()
    {
        impl_->Render();
    }
} // namespace ui