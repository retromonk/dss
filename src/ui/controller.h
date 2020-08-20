#ifndef UI_CONTROLLER_H
#define UI_CONTROLLER_H

#include <memory>

namespace ui
{
    class IController 
    {
        public:
            virtual ~IController() = default;
            virtual void UpdateInput(bool leftPressed, bool rightPressed) = 0;
            virtual bool GetLeftPressed() = 0;
            virtual bool GetRightPressed() = 0;
    };

    class Controller : public IController
    {
        public:
            Controller();
            void UpdateInput(bool leftPressed, bool rightPressed) override;
            bool GetLeftPressed() override;
            bool GetRightPressed() override;

        private:
            std::unique_ptr<IController> impl_;
    };
}

#endif