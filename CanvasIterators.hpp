#pragma once
#include "Canvas.hpp"

namespace plotter
{

class Canvas::RowIterator
{
    friend class Canvas;

    explicit RowIterator(Canvas* canvas, int row, int col)
        : canvas_(canvas)
        , row_(row)
        , col_(col) {
    }

public:
    // Категория итератора
    using iterator_category = std::forward_iterator_tag;
    // Тип элементов, по которым перемещается итератор
    using value_type = char;
    // Тип, используемый для хранения смещения между итераторами
    using difference_type = std::ptrdiff_t;
    // Тип указателя на итерируемое значение
    using pointer = char*;
    // Тип ссылки на итерируемое значение
    using reference = char&;

    /**
     * @brief Конвертирующий / копирующий конструктор.
     */
    RowIterator(const RowIterator& other) noexcept
        : RowIterator(other.canvas_, other.row_, other.col_) {}

    RowIterator& operator=(const RowIterator& rhs) = default;

    /**
     * @brief Сравнение с константным итератором.
     */
    [[nodiscard]] bool operator==(const RowIterator& rhs) const noexcept {
        return canvas_ == rhs.canvas_ && row_ == rhs.row_ && col_ == rhs.col_;
    }

    /**
     * @brief Проверка неравенства с константным итератором.
     */
    [[nodiscard]] bool operator!=(const RowIterator& rhs) const noexcept {
        return canvas_ != rhs.canvas_ || row_ != rhs.row_ || col_ != rhs.col_;
    }

    /**
     * @brief Сравнение с обычным итератором.
     */
    [[nodiscard]] bool operator==(const RowIterator& rhs) noexcept {
        return canvas_ == rhs.canvas_ && row_ == rhs.row_ && col_ == rhs.col_;
    }

    /**
     * @brief Проверка неравенства с обычным итератором.
     */
    [[nodiscard]] bool operator!=(const RowIterator& rhs) noexcept {
        return canvas_ != rhs.canvas_ || row_ != rhs.row_ || col_ != rhs.col_;
    }

    /**
     * @brief Преинкремент.
     */
    RowIterator& operator++() noexcept {
        ++col_;
        return *this;
    }

    /**
     * @brief Постинкремент.
     */
    RowIterator operator++(int) noexcept {
        auto old_value(*this);
        ++(*this);
        return old_value;
    }

    /**
     * @brief Предекремент.
     */
    RowIterator& operator--() noexcept {
        --col_;
        return *this;
    }

    /**
     * @brief Постдекремент.
     */
    RowIterator operator--(int) noexcept {
        auto old_value(*this);
        --(*this);
        return old_value;
    }

    RowIterator& operator+=(int shift) noexcept {
        col_ += shift;
        return *this;
    }

    RowIterator& operator-=(int shift) noexcept {
        col_ -= shift;
        return *this;
    }

    /**
     * @brief Разыменование итератора.
     * Возвращает ссылку на текущий элемент.
     */
    [[nodiscard]] reference operator*() const noexcept {
        return canvas_->canvas_[row_*canvas_->width_ + col_];
    }

    /**
     * @brief Доступ к членам текущего элемента.
     */
    [[nodiscard]] pointer operator->() const noexcept {
        return &canvas_->canvas_[row_*canvas_->width_ + col_];
    }

private:
    Canvas* canvas_;
    int row_;
    int col_;
};

class Canvas::ColumnIterator
{

    friend class Canvas;

    explicit ColumnIterator(Canvas* canvas, int row, int col)
        : canvas_(canvas)
        , col_(col)
        , row_(row) {
    }

public:
    // Категория итератора
    using iterator_category = std::forward_iterator_tag;
    // Тип элементов, по которым перемещается итератор
    using value_type = char;
    // Тип, используемый для хранения смещения между итераторами
    using difference_type = std::ptrdiff_t;
    // Тип указателя на итерируемое значение
    using pointer = char*;
    // Тип ссылки на итерируемое значение
    using reference = char&;

    /**
     * @brief Конвертирующий / копирующий конструктор.
     */
    ColumnIterator(const ColumnIterator& other) noexcept
        : ColumnIterator(other.canvas_, other.row_, other.col_) {}

    ColumnIterator& operator=(const ColumnIterator& rhs) = default;

    /**
     * @brief Сравнение с константным итератором.
     */
    [[nodiscard]] bool operator==(const ColumnIterator& rhs) const noexcept {
        return canvas_ == rhs.canvas_ && row_ == rhs.row_ && col_ == rhs.col_;
    }

    /**
     * @brief Проверка неравенства с константным итератором.
     */
    [[nodiscard]] bool operator!=(const ColumnIterator& rhs) const noexcept {
        return canvas_ != rhs.canvas_ || row_ != rhs.row_ || col_ != rhs.col_;
    }

    /**
     * @brief Сравнение с обычным итератором.
     */
    [[nodiscard]] bool operator==(const ColumnIterator& rhs) noexcept {
        return canvas_ == rhs.canvas_ && row_ == rhs.row_ && col_ == rhs.col_;
    }

    /**
     * @brief Проверка неравенства с обычным итератором.
     */
    [[nodiscard]] bool operator!=(const ColumnIterator& rhs) noexcept {
        return canvas_ != rhs.canvas_ || row_ != rhs.row_ || col_ != rhs.col_;
    }

    /**
     * @brief Преинкремент.
     */
    ColumnIterator& operator++() noexcept {
        ++row_;
        return *this;
    }

    /**
     * @brief Постинкремент.
     */
    ColumnIterator operator++(int) noexcept {
        auto old_value(*this);
        ++(*this);
        return old_value;
    }

    /**
     * @brief Предекремент.
     */
    ColumnIterator& operator--() noexcept {
        --row_;
        return *this;
    }

    /**
     * @brief Постдекремент.
     */
    ColumnIterator operator--(int) noexcept {
        auto old_value(*this);
        --(*this);
        return old_value;
    }

    ColumnIterator& operator+=(int shift) noexcept {
        row_ += shift;
        return *this;
    }

    ColumnIterator& operator-=(int shift) noexcept {
        row_ -= shift;
        return *this;
    }

    /**
     * @brief Разыменование итератора.
     * Возвращает ссылку на текущий элемент.
     */
    [[nodiscard]] reference operator*() const noexcept {
        return canvas_->canvas_[row_*canvas_->width_ + col_];
    }

    /**
     * @brief Доступ к членам текущего элемента.
     */
    [[nodiscard]] pointer operator->() const noexcept {
        return &(canvas_->canvas_[row_*canvas_->width_ + col_]);
    }

private:
    Canvas* canvas_;
    int col_;
    int row_;
};

class Canvas::PixelIterator
{
    friend class Canvas;

    explicit PixelIterator(Canvas* canvas, size_t pos)
        : canvas_(canvas)
        , pos_(pos) {
    }

public:
    // Категория итератора
    using iterator_category = std::forward_iterator_tag;
    // Тип элементов, по которым перемещается итератор
    using value_type = char;
    // Тип, используемый для хранения смещения между итераторами
    using difference_type = std::ptrdiff_t;
    // Тип указателя на итерируемое значение
    using pointer = char*;
    // Тип ссылки на итерируемое значение
    using reference = char&;

    /**
     * @brief Конвертирующий / копирующий конструктор.
     */
    PixelIterator(const PixelIterator& other) noexcept
        : PixelIterator(other.canvas_, other.pos_) {}

    PixelIterator& operator=(const PixelIterator& rhs) = default;

    /**
     * @brief Сравнение с константным итератором.
     */
    [[nodiscard]] bool operator==(const PixelIterator& rhs) const noexcept {
        return canvas_ == rhs.canvas_ && pos_ == rhs.pos_;
    }

    /**
     * @brief Проверка неравенства с константным итератором.
     */
    [[nodiscard]] bool operator!=(const PixelIterator& rhs) const noexcept {
        return canvas_ != rhs.canvas_ || pos_ != rhs.pos_;
    }

    /**
     * @brief Сравнение с обычным итератором.
     */
    [[nodiscard]] bool operator==(const PixelIterator& rhs) noexcept {
        return canvas_ == rhs.canvas_ && pos_ == rhs.pos_;
    }

    /**
     * @brief Проверка неравенства с обычным итератором.
     */
    [[nodiscard]] bool operator!=(const PixelIterator& rhs) noexcept {
        return canvas_ != rhs.canvas_ || pos_ != rhs.pos_;
    }

    /**
     * @brief Преинкремент.
     */
    PixelIterator& operator++() noexcept {
        ++pos_;
        return *this;
    }

    /**
     * @brief Постинкремент.
     */
    PixelIterator operator++(int) noexcept {
        auto old_value(*this);
        ++(*this);
        return old_value;
    }

    /**
     * @brief Предекремент.
     */
    PixelIterator& operator--() noexcept {
        --pos_;
        return *this;
    }

    /**
     * @brief Постдекремент.
     */
    PixelIterator operator--(int) noexcept {
        auto old_value(*this);
        --(*this);
        return old_value;
    }

    PixelIterator& operator+=(int shift) noexcept {
        pos_ += shift;
        return *this;
    }

    PixelIterator& operator-=(int shift) noexcept {
        pos_ -= shift;
        return *this;
    }

    /**
     * @brief Разыменование итератора.
     * Возвращает ссылку на текущий элемент.
     */
    [[nodiscard]] reference operator*() const noexcept {
        return canvas_->canvas_[pos_];
    }

    /**
     * @brief Доступ к членам текущего элемента.
     */
    [[nodiscard]] pointer operator->() const noexcept {
        return &(canvas_->canvas_[pos_]);
    }

private:
    Canvas* canvas_;
    size_t pos_;
};


} // namespace plotter