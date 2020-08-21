#include "image_provider.h"

#include <curl/curl.h>

#include <thread>
#include <string>
#include <algorithm>

#include <iostream>

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    auto stream = static_cast<std::vector<unsigned char>*>(userdata);
    stream->insert(stream->end(), ptr, ptr + size * nmemb);
    return size * nmemb;
}

namespace data
{
    static bool IsCurlInit = false;

    static void InitCurl()
    {
        if (!IsCurlInit)
        {
            IsCurlInit = true;
            curl_global_init(CURL_GLOBAL_DEFAULT);
        }
    }

    class ImageProviderImpl : public IImageProvider
    {
    public:
        ImageProviderImpl(std::string url) : url_(std::move(url))
        {
            InitCurl();
            curl_ = curl_easy_init();
            curl_easy_setopt(curl_, CURLOPT_URL, url_.c_str());
            curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &cache_);
            curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, write_callback);
            curl_easy_setopt(curl_, CURLOPT_SSL_VERIFYPEER, 0L);
            curl_easy_setopt(curl_, CURLOPT_SSL_VERIFYHOST, 0L);
            curl_easy_setopt(curl_, CURLOPT_FOLLOWLOCATION, 1L);
        }

        ~ImageProviderImpl() override
        {
            curl_easy_cleanup(curl_);
        }

        std::vector<unsigned char> GetImageData() override
        {
            if (cache_.size() == 0)
            {
                cacheImageData();
            }

            return cache_;
        }

    private:
        std::string url_;
        std::vector<unsigned char> cache_;
        CURL* curl_;

        void cacheImageData()
        {

            if (curl_ != nullptr)
            {
                auto res = curl_easy_perform(curl_);
                if (res != CURLE_OK)
                {
                    fprintf(stderr, "curl_easy_perform() failed: %s\n",
                            curl_easy_strerror(res));
                }
            }
        }
    };

    ImageProvider::ImageProvider(const std::string &url) : impl_(std::make_unique<ImageProviderImpl>(url))
    {
    }

    std::vector<unsigned char> ImageProvider::GetImageData()
    {
        return impl_->GetImageData();
    }
} // namespace data