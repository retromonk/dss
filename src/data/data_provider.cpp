#include "data_provider.h"

#include <httplib.h>
#include <nlohmann/json.hpp>

#include <algorithm>
#include <sstream>

namespace data
{
    class DataProviderImpl : public IDataProvider
    {
    public:
        DataProviderImpl(const std::string hostname) : hostname_(std::move(hostname))
        {
        }

        std::vector<Entry> GetCatalog(const std::string& inDate) const override
        {
            std::vector<Entry> results;
            std::stringstream endpoint;
            endpoint << "/api/v1/schedule";
            endpoint << "?hydrate=game(content(editorial(recap))),decisions";
            endpoint << "&date=" << inDate;
            endpoint << "&sportId=1";
            httplib::Client client(hostname_);
            auto res = client.Get(endpoint.str().c_str());
            if (res != nullptr)
            {
                auto json = nlohmann::json::parse(res->body);
                if (json.find("dates") != json.end())
                {
                    auto dates = json["dates"];
                    if (dates.is_array())
                    {
                        for (const auto &date : dates)
                        {
                            if (date.find("games") != date.end())
                            {
                                auto games = date["games"];
                                for (const auto &game : games)
                                {
                                    std::stringstream headline;
                                    std::stringstream description;
                                    if (game.find("officialDate") != game.end())
                                    {
                                        auto dateString = game["officialDate"];
                                        description << dateString << "\n";
                                    }

                                    if (game.find("seriesDescription") != game.end())
                                    {
                                        auto descString = game["seriesDescription"];
                                        description << descString << "\n";
                                    }

                                    if (game.find("venue") != game.end())
                                    {
                                        auto venue = game["venue"];
                                        if (venue.find("name") != venue.end())
                                        {
                                            auto nameString = venue["name"];
                                            description << nameString << "\n";
                                        }
                                    }

                                    if (game.find("teams") != game.end())
                                    {
                                        auto teams = game["teams"];
                                        if (teams.find("home") != teams.end())
                                        {
                                            auto home = teams["home"];
                                            if (home.find("team") != home.end())
                                            {
                                                auto team = home["team"];
                                                if (team.find("name") != team.end())
                                                {
                                                    auto homeTeamString = team["name"];
                                                    headline << homeTeamString << " v. ";
                                                }
                                            }
                                        }
                                    }

                                    if (game.find("teams") != game.end())
                                    {
                                        auto teams = game["teams"];
                                        if (teams.find("away") != teams.end())
                                        {
                                            auto home = teams["away"];
                                            if (home.find("team") != home.end())
                                            {
                                                auto team = home["team"];
                                                if (team.find("name") != team.end())
                                                {
                                                    auto awayTeamString = team["name"];
                                                    headline << awayTeamString;
                                                }
                                            }
                                        }
                                    }

                                    auto headlineString = headline.str();
                                    headlineString.erase(std::remove(headlineString.begin(), headlineString.end(), '"'), headlineString.end());
                                    auto descriptionString = description.str();
                                    descriptionString.erase(std::remove(descriptionString.begin(), descriptionString.end(), '"'), descriptionString.end());
                                    results.push_back({headlineString, descriptionString});
                                }
                            }
                        }
                    }
                }
            }

            return results;
        }

    private:
        std::string hostname_;
    };

    DataProvider::DataProvider(const std::string &hostname) : impl_(std::make_unique<DataProviderImpl>(hostname))
    {
    }

    std::vector<Entry> DataProvider::GetCatalog(const std::string& dateString) const
    {
        return impl_->GetCatalog(dateString);
    }
} // namespace data