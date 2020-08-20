#include "ui/display.h"
#include "data/data_provider.h"

#include <iostream>

int main(int, char **)
{
    data::DataProvider dataProvider("statsapi.mlb.com");
    auto catalog = dataProvider.GetCatalog("2018-06-10");
    
    ui::Display display("dss.tga", 1920, 1080);
    for(const auto& entry : catalog)
    {
        display.AddContent(entry.Headline, entry.Description);
    }

    display.Show();

    return 0;
}