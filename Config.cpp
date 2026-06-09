#include "Config.hpp"
#include <fstream>
#include <regex>
#include <sstream>
#include <stdexcept>
// #include <algorithm>
#include <cctype>
#include "json.h"

namespace plotter
{
    PlotterConfig Config::LoadFromFile(const std::string& filename) {
        std::ifstream fin(filename);
        return LoadFromString(fin);
    }

    PlotterConfig Config::LoadFromString(std::istream& json_str) {
        Document doc = Load(json_str);
        auto& root = doc.GetRoot().AsMap();
        PlotterConfig conf = {
            .height = root.at("height").AsInt(),
            .width = root.at("width").AsInt(),
            .background_char = ' ',
            .plotter_type = "basic",
        };
        if (root.contains("background_char") && root.at("background_char").AsString().size() > 0) {
            conf.background_char = root.at("background_char").AsString()[0];
        }
        if (root.contains("plotter_type")) {
            conf.plotter_type = root.at("plotter_type").AsString();
        }
        if (conf.plotter_type == "grayscale" && root.contains("palette")) {
            conf.palette = ParsePalette(root.at("palette").AsString());
        }
        return conf;
    }

    // inline bool ValidatePalette(const std::vector<char>& palette) {
    //     return std::ranges::all_of(palette, [](const char c){return c != ' ' && !isgraph(c);});
    // }

    bool ValidatePalette(const std::vector<char>& palette) {
        for (char c : palette) {
            if (c != ' ' && !isgraph(c)) {
                return false;
            }
        }
        return true;
    }

    bool Config::ValidateConfig(const PlotterConfig& config) {
        const bool is_size_valid = config.width >= 0 && config.height >= 0;
        const bool is_background_char_valid = config.background_char == ' ' || isgraph(config.background_char);
        const bool is_plotter_type_valid = config.plotter_type == "grayscale" || config.plotter_type == "basic";
        const bool is_palette_valid = config.plotter_type != "grayscale" || ValidatePalette(config.palette);

        return is_size_valid && is_background_char_valid
            && is_plotter_type_valid && is_palette_valid;
    }

    PlotterConfig Config::DefaultConfig() {
        return LoadFromFile("config.json");
    }

    std::vector<char> Config::ParsePalette(const std::string& palette_str) {
        std::vector<char> vec;
        vec.reserve(palette_str.size());
        for (char c : palette_str) {
            vec.push_back(c);
        }
        return vec;
    }

} // namespace plotter