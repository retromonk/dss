#include "button.h"

#include <GLFW/glfw3.h>

namespace ui
{
    class ButtonImpl : public IRenderable
    {
    public:
        ButtonImpl(int width, int height, int posX, int posY) : width_(width), height_(height), pos_x_(posX), pos_y_(posY)
        {
        }

        void Init() override
        {
        }

        void Render() override
        {
            auto left = pos_x_ - width_ / 2;
            auto right = pos_x_ + width_ / 2;
            auto top = pos_y_ + height_ / 2;
            auto bottom = pos_y_ - height_ / 2;

            glBegin(GL_QUADS);
            glColor3f(0.5f, 0.5f, 0.5f);
            glVertex2f(left, bottom);
            glVertex2f(right, bottom);
            glVertex2f(right, top);
            glVertex2f(left, top);
            glEnd();
        }

    private:
        int width_;
        int height_;
        int pos_x_;
        int pos_y_;
    };

    Button::Button(int width, int height, int posX, int posY) : impl_(std::make_unique<ButtonImpl>(width, height, posX, posY))
    {
    }

    void Button::Init()
    {
        impl_->Init();
    }

    void Button::Render()
    {
        impl_->Render();
    }
} // namespace ui