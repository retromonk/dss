#include "background.h"
#include "controller.h"
#include "display.h"
#include "selector.h"
#include "text.h"

#include <GLFW/glfw3.h>

namespace ui
{
    class DisplayImpl : public IDisplay
    {
    public:
        DisplayImpl(const std::string &background, int width, int height) : 
            background_(background, width, height),
            selector_(width / 2, height / 2, 120, 70), 
            width_(width), height_(height)
        {
        }

        void AddContent(const std::string& headline, const std::string& description)
        {
            selector_.AddItem(headline, description);
        }

        void Show() override
        {
            /* Initialize the library */
            if (!glfwInit())
            {
                return;
            }

            /* Create a windowed mode window and its OpenGL context */
            auto window = glfwCreateWindow(width_, height_, "DSS - Test", NULL, NULL);
            if (!window)
            {
                glfwTerminate();
                return;
            }

            /* Make the window's context current */
            glfwMakeContextCurrent(window);

            glClearColor(0.0, 0.0, 0.0, 0.0);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glOrtho(0.0, width_, height_, 1.0, -1.0, 1.0);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            background_.Init();

            glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);

            /* Loop until the user closes the window */
            while (!glfwWindowShouldClose(window))
            {
                auto leftPressed = glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS;
                auto rightPressed = glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS;
                controller_.UpdateInput(leftPressed, rightPressed);
                if (controller_.GetLeftPressed())
                {
                    selector_.Previous();
                }

                if (controller_.GetRightPressed())
                {
                    selector_.Next();
                }

                /* Render here */
                glClear(GL_COLOR_BUFFER_BIT);

                background_.Render();
                selector_.Render();

                /* Swap front and back buffers */
                glfwSwapBuffers(window);

                /* Poll for and process events */
                glfwPollEvents();
            }

            glfwTerminate();
        }

    private:
        Background background_;
        Selector selector_;
        int width_;
        int height_;
        Controller controller_;
    };

    Display::Display(const std::string &background, int width, int height) : impl_(std::make_unique<DisplayImpl>(background, width, height))
    {
    }

    void Display::AddContent(const std::string& headline, const std::string& description)
    {
        impl_->AddContent(headline, description);
    }

    void Display::Show()
    {
        impl_->Show();
    }
} // namespace ui