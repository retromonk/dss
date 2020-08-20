#ifndef UI_BUTTON_H
#define UI_BUTTON_H

#include "renderable.h"

#include <memory>

namespace ui
{
    class Button : IRenderable
    {
    public:
        Button(int width, int height, int posX, int posY);
        void Init() override;
        void Render() override;

    private:
        std::unique_ptr<IRenderable> impl_;
    };
} // namespace ui

#endif