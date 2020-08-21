#ifndef UI_BUTTON_H
#define UI_BUTTON_H

#include "renderable.h"
#include "../data/image_provider.h"

#include <memory>

namespace ui
{
    class IMoveable
    {
    public:
        virtual ~IMoveable() = default;
        virtual void SetPosition(int posX, int posY) = 0;
    };

    class IResizable
    {
    public:
        virtual ~IResizable() = default;
        virtual void SetSize(int width, int height) = 0;
    };

    class IButton : public IRenderable, public IMoveable, public IResizable
    {
    public:
        virtual ~IButton() = default;
    };

    class Button : IButton
    {
    public:
        Button(std::unique_ptr<data::IImageProvider> image = nullptr);
        void Init() override;
        void Render() override;
        void SetPosition(int posX, int posY) override;
        void SetSize(int width, int height) override;

    private:
        std::unique_ptr<IButton> impl_;
    };
} // namespace ui

#endif