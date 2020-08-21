#ifndef DATA_DATA_PROVIDER_H
#define DATA_DATA_PROVIDER_H

#include <memory>
#include <vector>

namespace data
{
    struct Entry
    {
        std::string Headline;
        std::string Description;
        std::string Image_96x72;
        std::string Image_148x112;
    };

    class IDataProvider
    {
    public:
        virtual ~IDataProvider() = default;
        virtual std::vector<Entry> GetCatalog(const std::string& dateString) const = 0;
    };

    class DataProvider : public IDataProvider
    {
    public:
        DataProvider(const std::string& hostname);
        std::vector<Entry> GetCatalog(const std::string& dateString) const override;

    private:
        std::unique_ptr<IDataProvider> impl_;
    };
} // namespace data

#endif