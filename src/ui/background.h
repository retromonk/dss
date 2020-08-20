#ifndef UI_BACKGROUND_H
#define UI_BACKGROUND_H

#include "renderable.h"

#include <memory>

namespace ui
{
    class Background : public IRenderable
    {
    public:
        Background(const std::string &filename, int width, int height);
        void Init() override;
        void Render() override;

    private:
        std::unique_ptr<IRenderable> impl_;
    };
} // namespace ui

#endif