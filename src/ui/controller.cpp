#include "controller.h"

#include <chrono>

namespace ui
{
    class ControllerImpl : public IController
    {
    public:
        ControllerImpl()
        {
            last_left_pressed_ = std::chrono::steady_clock::now();
            last_right_pressed_ = std::chrono::steady_clock::now();
        }

        void UpdateInput(bool leftPressed, bool rightPressed) override
        {
            left_pressed_ = leftPressed;
            right_pressed_ = rightPressed;
        }

        bool GetLeftPressed() override
        {
            if (left_pressed_)
            {
                std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
                auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_left_pressed_).count();
                if(elapsed > PressTimeout)
                {
                    last_left_pressed_ = now;
                    return true;
                }
            }

            return false;
        }

        bool GetRightPressed() override
        {
            if (right_pressed_)
            {
                std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
                auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_right_pressed_).count();
                if(elapsed > PressTimeout)
                {
                    last_right_pressed_ = now;
                    return true;
                }
            }

            return false;
        }

    private:
        const int PressTimeout = 250;
        bool left_pressed_ = false;
        bool right_pressed_ = false;
        std::chrono::steady_clock::time_point last_left_pressed_;
        std::chrono::steady_clock::time_point last_right_pressed_;
    };

    Controller::Controller() : impl_(std::make_unique<ControllerImpl>())
    {
    }

    void Controller::UpdateInput(bool leftPressed, bool rightPressed)
    {
        impl_->UpdateInput(leftPressed, rightPressed);
    }

    bool Controller::GetLeftPressed()
    {
        return impl_->GetLeftPressed();
    }

    bool Controller::GetRightPressed()
    {
        return impl_->GetRightPressed();
    }
} // namespace ui