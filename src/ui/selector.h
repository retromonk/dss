#ifndef UI_SELECTOR_H
#define UI_SELECTOR_H

#include "../data/image_provider.h"
#include "renderable.h"

#include <memory>

namespace ui
{
    class ISelector : public IRenderable
    {
    public:
        virtual ~ISelector() = default;
        virtual void AddItem(const std::string &header, const std::string &description,
            std::unique_ptr<data::IImageProvider> small, std::unique_ptr<data::IImageProvider> large) = 0;
        virtual void Next() = 0;
        virtual void Previous() = 0;
    };

    class Selector : public ISelector
    {
    public:
        Selector(int posX, int posY, int buttonWidth, int buttonHeight);

        void Init() override;
        void Render() override;
        void AddItem(const std::string &header, const std::string &description,
            std::unique_ptr<data::IImageProvider> small, std::unique_ptr<data::IImageProvider> large) override;
        void Next() override;
        void Previous() override;

    private:
        std::unique_ptr<ISelector> impl_;
    };
} // namespace ui

#endif