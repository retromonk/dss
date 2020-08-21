#ifndef UI_DISPLAY_H
#define UI_DISPLAY_H

#include "../data/image_provider.h"

#include <string>
#include <memory>

namespace ui
{
    class IDisplay
    {
    public:
        virtual ~IDisplay() = default;
        virtual void AddContent(const std::string &header, const std::string &description, 
            std::unique_ptr<data::IImageProvider> image1, std::unique_ptr<data::IImageProvider> image2) = 0;
        virtual void Show() = 0;
    };

    class Display : public IDisplay
    {
    public:
        Display(const std::string &backgroundFile, int width, int height);
        void AddContent(const std::string &header, const std::string &description, 
            std::unique_ptr<data::IImageProvider> image1, std::unique_ptr<data::IImageProvider> image2) override;
        void Show() override;

    private:
        std::unique_ptr<IDisplay> impl_;
    };
} // namespace ui

#endif