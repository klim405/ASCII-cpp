#pragma once
#include "Plotter.hpp"
#include <algorithm>
#include <memory>
#include <vector>

namespace plotter
{

class GrayscalePlotter : public Plotter
{
public:
    explicit GrayscalePlotter(std::unique_ptr<Canvas> canvas,
        const std::vector<char>& palette = DefaultPalette());

    GrayscalePlotter(int width, int height, char background_char = ' ',
        const std::vector<char>& palette = DefaultPalette());

    static std::vector<char> DefaultPalette();

    void DrawLine(int x1, int y1, int x2, int y2, double brightness);
    void DrawRectangle(int x1, int y1, int x2, int y2, double brightness, bool fill = false);
    void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, double brightness, bool fill = false);
    void DrawCircle(int center_x, int center_y, int radius, double brightness, bool fill = false);

    void FloodFill(int x, int y, double brightness);
    void ScanlineFill(int x, int y, double brightness);

    void DrawLinearGradient(int x1, int y1, int x2, int y2,
        double start_brightness, double end_brightness);
    void DrawRadialGradient(int center_x, int center_y, int radius,
        double center_brightness, double edge_brightness);

    [[nodiscard]] double CalculateAverageBrightness();
    [[nodiscard]] std::pair<double, double> GetMinMaxBrightness();
    [[nodiscard]] std::vector<std::vector<double>> GetBrightnessMatrix() const;

    void AdjustBrightness(double factor);
    void ApplyThreshold(double threshold);
    void InvertBrightness();

    void ApplyBoxBlur(int kernel_size = 3);
    void ApplyGaussianBlur(int kernel_size = 3);

    void SetPalette(const std::vector<char>& new_palette);
    [[nodiscard]] const std::vector<char>& GetPalette() const noexcept { return palette_; }
    [[nodiscard]] size_t GetPaletteSize() const noexcept { return palette_.size(); }

private:
    std::vector<char> palette_;
    std::map<char, double> char_to_brightness_;

    char BrightnessToChar(double brightness) const;
    void RefreshCharToBrightness();

    double GetPixelBrightness(int x, int y) const;
    void SetPixelBrightness(int x, int y, double brightness);
    std::vector<std::vector<double>> Convolve(const std::vector<std::vector<double>>& kernel) const;
    static std::vector<std::vector<double>> CreateGaussianKernel(int size, double sigma = 1.0);
    static std::vector<std::vector<double>> CreateBoxKernel(int size);
};

} // namespace plotter