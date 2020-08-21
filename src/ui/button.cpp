#include "../data/image_provider.h"
#include "button.h"

#include <SOIL/SOIL.h>
#include <GLFW/glfw3.h>

#include <iostream>

namespace ui
{
    class ButtonImpl : public IButton
    {
    public:
        ButtonImpl(std::unique_ptr<data::IImageProvider> image) : image_(std::move(image))
        {
        }

        void Init() override
        {
            auto data = image_->GetImageData();
            glGenTextures(1, &texture_id_);

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture_id_);

            auto imgWidth = 0;
            auto imgHeight = 0;
            auto image = SOIL_load_image_from_memory(data.data(), data.size(), &imgWidth, &imgHeight, 0, SOIL_LOAD_RGB);
            if (image != nullptr)
            {
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

                SOIL_free_image_data(image);
            }
        }

        void Render() override
        {
            auto left = pos_x_ - width_ / 2;
            auto right = pos_x_ + width_ / 2;
            auto top = pos_y_ + height_ / 2;
            auto bottom = pos_y_ - height_ / 2;

            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, texture_id_);
            glBegin(GL_QUADS);
            glColor3f(1, 1, 1);
            glTexCoord2f(0, 0);
            glVertex2f(left, bottom);
            glTexCoord2f(1, 0);
            glVertex2f(right, bottom);
            glTexCoord2f(1, 1);
            glVertex2f(right, top);
            glTexCoord2f(0, 1);
            glVertex2f(left, top);
            glEnd();
            glDisable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        void SetPosition(int posX, int posY) override
        {
            pos_x_ = posX;
            pos_y_ = posY;
        }

        void SetSize(int width, int height) override
        {
            width_ = width;
            height_ = height;
        }

    private:
        GLuint texture_id_;
        int width_;
        int height_;
        int pos_x_;
        int pos_y_;

        std::unique_ptr<data::IImageProvider> image_;
    };

    Button::Button(std::unique_ptr<data::IImageProvider> image) : impl_(std::make_unique<ButtonImpl>(std::move(image)))
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

    void Button::SetPosition(int posX, int posY)
    {
        impl_->SetPosition(posX, posY);
    }

    void Button::SetSize(int width, int height)
    {
        impl_->SetSize(width, height);
    }
} // namespace ui