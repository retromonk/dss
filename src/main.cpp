#include "ui/display.h"
#include "data/data_provider.h"
#include "data/image_provider.h"

#include <iostream>

int main(int, char **)
{
    data::DataProvider dataProvider("statsapi.mlb.com");
    auto catalog = dataProvider.GetCatalog("2018-06-10");
    
    ui::Display display("1.jpg", 1920, 1080);
    for(const auto& entry : catalog)
    {
        auto imageProvider1 = std::make_unique<data::ImageProvider>(entry.Image_96x72);
        auto imageProvider2 = std::make_unique<data::ImageProvider>(entry.Image_148x112);
        display.AddContent(entry.Headline, entry.Description, std::move(imageProvider1), std::move(imageProvider2));
    }

    display.Show();

    return 0;
}