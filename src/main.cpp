#include "ui/display.h"

int main(int, char **)
{
    ui::Display display("dss.tga", 1920, 1080);
    display.AddContent("test1", "test2");
    display.AddContent("test3", "test4");
    display.AddContent("test5", "test6");
    display.Show();

    return 0;
}