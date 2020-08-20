#include "selector.h"
#include "button.h"
#include "text.h"

#include <sstream>
#include <vector>
#include <algorithm>

namespace ui
{
    using Data = std::pair<std::string, std::string>;
    class SelectorImpl : public ISelector
    {
    public:
        SelectorImpl(int posX, int posY, int buttonWidth, int buttonHeight) : pos_x_(posX), pos_y_(posY), button_width_(buttonWidth), button_height_(buttonHeight)
        {
        }

        void Init() override
        {
        }

        void Render() override
        {
            if (catalog_.size() == 0)
            {
                return;
            }
            
            const int margin = 60;
            auto startX = pos_x_ - current_index_ * (button_width_ + margin);
            for (auto i = 0UL; i < catalog_.size(); ++i)
            {
                auto posX = startX + (i * (button_width_ + margin));
                auto posY = pos_y_;
                auto width = i == current_index_ ? button_width_ * 1.5f : button_width_;
                auto height = i == current_index_ ? button_height_ * 1.5f : button_height_;
                Button button(width, height, posX, posY);
                button.Render();
            }

            Text headline(catalog_.at(current_index_).first, pos_x_, pos_y_ + button_height_ / 2 + 30, 18);
            headline.Render();

            std::stringstream in(catalog_.at(current_index_).second);
            std::string line;
            auto yOffset = 50;
            for (auto i = 0; i < 3; ++i)
            {
                if (std::getline(in, line, '\n'))
                {
                    Text desc(line, pos_x_, pos_y_ - button_height_ / 2 - yOffset, 15);
                    yOffset += 20;
                    desc.Render();
                }
            }
        }

        void AddItem(const std::string &header, const std::string &description) override
        {
            catalog_.push_back({header, description});
        }

        void Next() override
        {
            if (catalog_.size() > 0 && current_index_ < catalog_.size() - 1)
            {
                ++current_index_;
            }
        }

        void Previous() override
        {
            if (current_index_ > 0UL)
            {
                --current_index_;
            }
        }

    private:
        int pos_x_;
        int pos_y_;
        int button_width_;
        int button_height_;
        std::vector<Data> catalog_;
        size_t current_index_ = 0UL;
    };

    Selector::Selector(int posX, int posY, int buttonWidth, int buttonHeight) : impl_(std::make_unique<SelectorImpl>(posX, posY, buttonWidth, buttonHeight))
    {
    }

    void Selector::Init()
    {
        impl_->Init();
    }

    void Selector::Render()
    {
        impl_->Render();
    }

    void Selector::AddItem(const std::string &header, const std::string &description)
    {
        impl_->AddItem(header, description);
    }

    void Selector::Next()
    {
        impl_->Next();
    }

    void Selector::Previous()
    {
        impl_->Previous();
    }
} // namespace ui
