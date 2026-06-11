#include "Canvas.hpp"
#include "CanvasIterators.hpp"
#include <algorithm>
#include <fstream>

namespace plotter {
    Canvas::Canvas(int width, int height, char background_char) :
        width_(width),
        height_(height),
        background_(background_char),
        canvas_(width*height, background_char) {
    }

    Canvas::Canvas(Canvas&& other) noexcept
        : canvas_(std::move(other.canvas_))
        , width_(other.width_)
        , height_(other.height_)
        , background_(other.background_) {
        other.width_ = 0;
        other.height_ = 0;
        other.background_ = ' ';
    }

    Canvas& Canvas::operator=(const Canvas& other) {
        if (this != &other) {
            Canvas temp(other);
            swap(temp);
        }
        return *this;
    }

    Canvas& Canvas::operator=(Canvas&& other) noexcept {
        if (this != &other) {
            canvas_ = std::move(other.canvas_);
            width_ = other.width_;
            height_ = other.height_;
            background_ = other.background_;

            other.width_ = 0;
            other.height_ = 0;
            other.background_ = ' ';
        }
        return *this;
    }

    void Canvas::swap(Canvas& other) noexcept {
        canvas_.swap(other.canvas_);
        std::swap(width_, other.width_);
        std::swap(height_, other.height_);
        std::swap(background_, other.background_);
    }


    [[nodiscard]] int Canvas::Width() const noexcept {
        return width_;
    }

    [[nodiscard]] int Canvas::Height() const noexcept {
        return height_;
    }

    [[nodiscard]] int Canvas::Size() const noexcept {
        return width_*height_;
    }


    char& Canvas::at(int x, int y) {
        if (!InBounds(x, y)) {
            throw std::out_of_range("Coordinates out of bounds");
        }
        return canvas_[y*width_ + x];
    }

    [[nodiscard]] const char& Canvas::at(int x, int y) const {
        if (!InBounds(x, y)) {
            throw std::out_of_range("Coordinates out of bounds");
        }
        return canvas_[y*width_ + x];
    }

    char& Canvas::operator()(int x, int y) noexcept {
        return canvas_[y*width_ + x];
    }

    [[nodiscard]] const char& Canvas::operator()(int x, int y) const noexcept {
        return canvas_[y*width_ + x];
    }


    void Canvas::Clear(char fill_char) {
        for (char& p : canvas_) {
            p = fill_char;
        }
    }

    void Canvas::FillRegion(int x1, int y1, int x2, int y2, char fill_char) {
        // Однозначно определяем координаты левого верхнего угла и правого нижнего.
        if (x1 > x2) { std::swap(x1, x2); }
        if (y1 > y2) { std::swap(y1, y2); }

        // За границами координатной сетки холста.
        if (!InBounds(x1, y1)) {
            return;
        }

        // Защита от выхода за границы холста
        x1 = std::max(x1, 0);
        y1 = std::max(y1, 0);

        x2 = std::min(x2, width_-1);
        y2 = std::min(y2, height_-1);

        char* const first_line = &canvas_[y1*width_];
        const char* const last_line = &canvas_[y2*width_];

        for (char* line = first_line; line <= last_line; line += width_) {
            std::fill(line + x1, line + x2 + 1, fill_char);
        }
    }

    void Canvas::FillPoint(int x, int y, char fill_char) {
        if (InBounds(x, y)) {
            canvas_[y*width_ + x] = fill_char;
        }
    }

    [[nodiscard]] bool Canvas::InBounds(int x, int y) const noexcept {
        return 0 <= x && x < width_ && 0 <= y && y < height_;
    }

    void Canvas::Render(std::ostream& os) const {
        for (auto it = canvas_.begin(); it < canvas_.end(); it += width_) {
            std::copy_n(it, width_, std::ostream_iterator<char>(os));
            os << '\n';
        }
        os << std::flush;
    }

    void Canvas::SaveToFile(const std::filesystem::path& filepath) const {
        using namespace std::filesystem;
        using std::ofstream;

        path dir = absolute(filepath).parent_path();

        if (!exists(dir)) {
            create_directory(dir);
        }

        ofstream file_out(filepath);

        file_out << "Canvas " << width_ << 'x' << height_ << '\n';
        file_out << "Background: '" << background_ << "'\n";
        file_out << "Content:\n";
        Render(file_out);
    }

    void Canvas::SaveToFile(const std::string& filename) const {
        using std::filesystem::path;
        SaveToFile(path(filename));
    }

    Canvas::RowIterator Canvas::RowBegin(int row) {
        return RowIterator(this, row, 0);
    }

    Canvas::RowIterator Canvas::RowEnd(int row) {
        return RowIterator(this, row, width_);
    }

    Canvas::ColumnIterator Canvas::ColBegin(int col) {
        return ColumnIterator(this, 0, col);
    }

    Canvas::ColumnIterator Canvas::ColEnd(int col) {
        return ColumnIterator(this, height_, col);
    }

    Canvas::PixelIterator Canvas::begin() {
        return PixelIterator(this, 0);
    }

    Canvas::PixelIterator Canvas::end() {
        return PixelIterator(this, Size());
    }


} // namespace plotter