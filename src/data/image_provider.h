#ifndef DATA_IMAGE_PROVIDER_H
#define DATA_IMAGE_PROVIDER_H

#include <vector>
#include <memory>

namespace data
{
    class IImageProvider
    {
    public:
        virtual ~IImageProvider() = default;
        virtual std::vector<unsigned char> GetImageData() = 0;
    };

    class ImageProvider : public IImageProvider
    {
    public:
        ImageProvider(const std::string& url);
        std::vector<unsigned char> GetImageData() override;

    private:
        std::unique_ptr<IImageProvider> impl_;
    };
} // namespace data

#endif