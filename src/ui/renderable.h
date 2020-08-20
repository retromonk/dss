#ifndef UI_RENDERABLE_H
#define UI_RENDERABLE_H

namespace ui
{
    class IRenderable
    {
    public:
        virtual ~IRenderable() = default;
        virtual void Init() = 0;
        virtual void Render() = 0;
    };
} // namespace ui

#endif