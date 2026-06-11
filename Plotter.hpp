#pragma once
#include "Canvas.hpp"
#include <map>
#include <memory>

namespace plotter
{

class Plotter
{
public:
    explicit Plotter(std::unique_ptr<Canvas> canvas);
    Plotter(int width, int height, char background_char = ' ');

    void DrawLine(int x1, int y1, int x2, int y2, char brush);
    void DrawRectangle(int x1, int y1, int x2, int y2, char brush, bool fill = false);
    void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, char brush, bool fill = false);
    void DrawCircle(int center_x, int center_y, int radius, char brush, bool fill = false);

    void FloodFill(int x, int y, char fill_brush);
    void ScanlineFill(int x, int y, char fill_brush);

    [[nodiscard]] std::map<char, int> ColorHistogram() const;
    [[nodiscard]] std::map<char, int> ColorHistogram(int x1, int y1, int x2, int y2) const;
    [[nodiscard]] static std::pair<char, char> MinMaxColors(const std::map<char, int>& color_weights);

    [[nodiscard]] std::unique_ptr<Canvas> ExtractRegion(int x1, int y1, int x2, int y2) const;
    void PasteRegion(const Canvas& region, int x, int y);

    [[nodiscard]] const Canvas& GetCanvas() const noexcept { return *canvas_; }
    Canvas& GetCanvas() noexcept { return *canvas_; }

    void Render(std::ostream& os = std::cout) const { canvas_->Render(os); }
    void SaveToFile(const std::filesystem::path& filepath) const { canvas_->SaveToFile(filepath); }
    void SaveToFile(const std::string& filename) const { SaveToFile(std::filesystem::path(filename)); }

private:
    std::unique_ptr<Canvas> canvas_;

    void DrawLineBresenham(int x1, int y1, int x2, int y2, char brush);
    void DrawCircleBresenham(int center_x, int center_y, int radius, char brush);
    void FillTriangle(int x1, int y1, int x2, int y2, int x3, int y3, char brush) const;

    /**
     * @brief Ищет координаты однотонного горизонтального отрезка.
     *
     * @param x Абсцисса точки лежащей на прямой.
     * @param y Ордината точки лежащей на прямой.
     * @return Абсцисса начала отрезка и абсцисса конца отрезка.
     */
    std::pair<int, int> FindMonochromeRow(int x, int y) const;

    struct ScanlineSegment
    {
        int y;
        int x_start;
        int x_end;
    };
};

} // namespace plotter