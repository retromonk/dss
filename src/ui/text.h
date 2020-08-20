#ifndef UI_TEXT_H
#define UI_TEXT_H

#include "renderable.h"

#include <memory>
#include <string>

namespace ui
{
    class Text : public IRenderable
    {
    public:
        Text(const std::string &text, int posX, int posY, int fontSize);
        void Init() override;
        void Render() override;

    private:
        std::unique_ptr<IRenderable> impl_;
    };
} // namespace ui

#endif