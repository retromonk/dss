#include "background.h"

#include <SOIL/SOIL.h>
#include <GLFW/glfw3.h>

namespace ui
{
    class BackgroundImpl : public IRenderable
    {
    public:
        BackgroundImpl(const std::string &filename, int width, int height) : file_name_(filename), width_(width), height_(height)
        {
        }

        void Init() override
        {
            glGenTextures(1, &texture_id_);

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture_id_);
            
            auto imgWidth = 0;
            auto imgHeight = 0;
            auto image = SOIL_load_image(file_name_.c_str(), &imgWidth, &imgHeight, 0, SOIL_LOAD_RGB);
            if (image != nullptr)
            {
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

                SOIL_free_image_data(image);
            }
        }

        void Render() override
        {
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, texture_id_);
            glBegin(GL_QUADS);
            glColor3f(1, 1, 1);
            glTexCoord2f(0, 0);
            glVertex2f(0, 0);
            glTexCoord2f(1, 0);
            glVertex2f(width_, 0);
            glTexCoord2f(1, 1);
            glVertex2f(width_, height_);
            glTexCoord2f(0, 1);
            glVertex2f(0, height_);
            glEnd();
            glDisable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, 0);
        }

    private:
        GLuint texture_id_;
        const std::string file_name_;
        int width_ = 0;
        int height_ = 0;
    };

    Background::Background(const std::string &filename, int width, int height) : impl_(std::make_unique<BackgroundImpl>(filename, width, height))
    {
    }

    void Background::Init()
    {
        impl_->Init();
    }

    void Background::Render()
    {
        impl_->Render();
    }
} // namespace ui
