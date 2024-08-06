#ifndef DYNAMIC_MATRIX_H
#define DYNAMIC_MATRIX_H

#include <cassert>
#include <stdexcept>
#include <memory>
#include <algorithm>
#include <iterator>
//remove
#include <vector>
std::vector<int>::const_iterator it;
//remove

namespace algo
{   
    template<typename Matrix>
    struct DynamicMatrixConstIterator
    {
        using iterator_category = std::random_access_iterator_tag;
        using value_type        = typename Matrix::value_type;
        using difference_type   = typename Matrix::difference_type;
        using pointer           = typename Matrix::const_pointer;
        using reference         = const value_type&;

        constexpr DynamicMatrixConstIterator() noexcept
            : pos{nullptr}
        {
        }

        constexpr DynamicMatrixConstIterator(typename Matrix::pointer pos) noexcept
            : pos{pos}
        {
        }

        constexpr reference operator*() const noexcept
        {
            return *pos;
        }

        constexpr pointer operator->() const noexcept
        {
            return pos;
        }

        constexpr DynamicMatrixConstIterator& operator++() noexcept
        {
            pos += 1;
            return *this;
        }

        constexpr DynamicMatrixConstIterator operator++(int) noexcept 
        {   
            auto copy{*this};
            ++(*this);
            return copy;
        } 
        
        constexpr DynamicMatrixConstIterator& operator--() noexcept
        {
            pos -= 1;
            return *this;
        }

        constexpr DynamicMatrixConstIterator operator--(int) noexcept 
        {   
            auto copy{*this};
            --(*this);
            return copy;
        }
        
        constexpr DynamicMatrixConstIterator& operator+=(const difference_type offset) noexcept
        {
            pos += offset;
            return *this;
        }

        constexpr DynamicMatrixConstIterator operator+(const difference_type offset) const noexcept
        {
            auto copy{*this};
            copy += offset;
            return copy;
        }

        constexpr friend DynamicMatrixConstIterator operator+(const difference_type offset, DynamicMatrixConstIterator next)
        {
            next += offset;
            return next;
        }
        
        constexpr DynamicMatrixConstIterator& operator-=(const difference_type offset) noexcept
        {
            pos -= offset;
            return *this;
        }
        
        constexpr DynamicMatrixConstIterator operator-(const difference_type offset) const noexcept
        {
            auto copy{*this};
            copy -= offset;
            return copy;
        }

        constexpr friend DynamicMatrixConstIterator operator-(const difference_type offset, DynamicMatrixConstIterator next) noexcept
        {
            next -= offset;
            return next;
        }

        constexpr reference operator[](const difference_type offset) const noexcept
        {
            return *(*this + offset);
        }

        constexpr std::strong_ordering operator<=>(const DynamicMatrixConstIterator& that) const noexcept
        {
            return this->pos <=> that.pos;
        }

        constexpr bool operator==(const DynamicMatrixConstIterator& that) const noexcept
        {
            return this->pos == that.pos;
        }
        
        constexpr bool operator!=(const DynamicMatrixConstIterator& that) const noexcept
        {
            return !(*this == that);
        }

        constexpr bool operator<(const DynamicMatrixConstIterator& that) const noexcept
        {
            return this->pos < that.pos;
        }
        
        constexpr bool operator>(const DynamicMatrixConstIterator& that) const noexcept
        {
            return that < *this;
        }
        
        constexpr bool operator<=(const DynamicMatrixConstIterator& that) const noexcept
        {
            return !(that > *this);
        }
        
        constexpr bool operator>=(const DynamicMatrixConstIterator& that) const noexcept
        {
            return !(that < *this);
        }

        typename Matrix::pointer pos;
    };
    
    template<typename Matrix>
    struct DynamicMatrixIterator : DynamicMatrixConstIterator<Matrix>
    {
        using iterator_category = std::random_access_iterator_tag;
        using value_type        = typename Matrix::value_type;
        using difference_type   = typename Matrix::difference_type;
        using pointer           = typename Matrix::pointer;
        using reference         = value_type&;

        DynamicMatrixIterator() noexcept 
            : pos{nullptr}
        {
        }
        
        DynamicMatrixIterator(pointer pos) noexcept 
            : pos{pos}
        {
        }
        
        constexpr reference operator*() const noexcept
        {
            return *pos;
        }

        constexpr pointer operator->() const noexcept
        {
            return pos;
        }

        constexpr DynamicMatrixIterator& operator++() noexcept
        {
            pos += 1;
            return *this;
        }

        constexpr DynamicMatrixIterator operator++(int) noexcept 
        {   
            auto copy{*this};
            ++(*this);
            return copy;
        } 
        
        constexpr DynamicMatrixIterator& operator--() noexcept
        {
            pos -= 1;
            return *this;
        }

        constexpr DynamicMatrixIterator operator--(int) noexcept 
        {   
            auto copy{*this};
            --(*this);
            return copy;
        }
        
        constexpr DynamicMatrixIterator& operator+=(const difference_type offset) noexcept
        {
            pos += offset;
            return *this;
        }

        constexpr DynamicMatrixIterator operator+(const difference_type offset) const noexcept
        {
            auto copy{*this};
            copy += offset;
            return copy;
        }

        constexpr friend DynamicMatrixIterator operator+(const difference_type offset, DynamicMatrixIterator next)
        {
            next += offset;
            return next;
        }
        
        constexpr DynamicMatrixIterator& operator-=(const difference_type offset) noexcept
        {
            pos -= offset;
            return *this;
        }
        
        constexpr DynamicMatrixIterator operator-(const difference_type offset) const noexcept
        {
            auto copy{*this};
            copy -= offset;
            return copy;
        }

        constexpr friend DynamicMatrixIterator operator-(const difference_type offset, DynamicMatrixIterator next) noexcept
        {
            next -= offset;
            return next;
        }

        constexpr reference operator[](const difference_type offset) const noexcept
        {
            return *(*this + offset);
        }

        typename Matrix::pointer pos;
    };

    template<typename Type, typename Allocator = std::allocator<Type>>
    class DynamicMatrix
    {
    public:
        using value_type = Type;
        using allocator_type = Allocator;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;
        using reference = Type&;
        using const_reference = const value_type&;
        using pointer = std::allocator_traits<allocator_type>::pointer;
        using const_pointer = std::allocator_traits<allocator_type>::const_pointer;
        using iterator = DynamicMatrixIterator<DynamicMatrix>;
        using const_iterator = DynamicMatrixConstIterator<DynamicMatrix>;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        constexpr DynamicMatrix()
            : rowsNumber{0}, colsNumber{0}
            , memory{}, storage{std::allocator_traits<allocator_type>::allocate(memory, 0)}
        {
        }

        constexpr DynamicMatrix(const size_type order)
            : rowsNumber{order}, colsNumber{order}
            , memory{}, storage{std::allocator_traits<allocator_type>::allocate(memory, rows() * cols())}
        {
            initialize_default(storage);
        }

        constexpr DynamicMatrix(const size_type rowsNumber, const size_type colsNumber)
            : rowsNumber{rowsNumber}, colsNumber{colsNumber}
            , memory{}, storage{std::allocator_traits<allocator_type>::allocate(memory, rows() * cols())}
        {
            initialize_default(storage);
        }

        constexpr DynamicMatrix(const DynamicMatrix& that)
            : rowsNumber{that.rowsNumber}, colsNumber{that.colsNumber}
            , memory{that.memory}, storage{std::allocator_traits<allocator_type>::allocate(memory, rows() * cols())}
        {
            for(std::size_t row{0}; row < rows(); ++row)
            {
                for(std::size_t col{0}; col < cols(); ++col)
                {
                    std::allocator_traits<allocator_type>::construct(memory, storage + row * rows() + col, std::move(that.storage[row + col * cols()]));
                }
            }
        }

        constexpr reference operator=(const DynamicMatrix& that)
        {
            DynamicMatrix{that}.swap(*this);
            return *this;
        }

        constexpr DynamicMatrix(DynamicMatrix&& that)
            : rowsNumber{that.rowsNumber}, colsNumber{that.colsNumber}
            , memory{that.memory}, storage{that.storage}
        {
            that.rowsNumber = 0;
            that.colsNumber = 0;
            that.storage = std::allocator_traits<allocator_type>::allocate(memory, 0);
        }

        constexpr reference operator=(DynamicMatrix&& that)
        {
            DynamicMatrix{std::move(that)}.swap(*this);
            return *this;
        }

        constexpr ~DynamicMatrix()
        {
            clear();
        }

        constexpr size_type rows() const noexcept
        {
            return rowsNumber;
        }

        constexpr size_type cols() const noexcept
        {
            return colsNumber;
        }

        constexpr reference operator[](const size_type row, const size_type col)
        {
            if(row >= rows())
            {
                throw std::out_of_range{"Error: wrong row number"};
            }
            if(col >= cols())
            {
                throw std::out_of_range{"Error: wrong col number."};
            }
            return storage[row * rows() + col] ;
        }
        
        constexpr const_reference operator[](const size_type row, const size_type col) const
        {   
            if(row >= rows())
            {
                throw std::out_of_range{"Error: wrong row number"};
            }
            if(col >= cols())
            {
                throw std::out_of_range{"Error: wrong col number."};
            }
            return storage[row * rows() + col];
        }

        constexpr reference at(const size_type row, const size_type col)
        {
            return (*this)[row, col];
        }

        constexpr const_reference at(const size_type row, const size_type col) const
        {
            return (*this)[row, col];
        }

        constexpr pointer data() noexcept
        {
            return data;
        }

        constexpr const_pointer data() const noexcept
        {
            return data;
        }

        constexpr void resize(const size_type freshRows, const size_type freshCols, bool preserve = true)
        {
            pointer freshStorage{std::allocator_traits<allocator_type>::allocate(memory, freshRows * freshCols)};
            if(preserve)
            {
                copy_to_fresh_memory(freshStorage, freshRows, freshCols);
                clear();
            }
            else
            {
                clear();
                initialize_default(freshStorage);
            }
            rowsNumber = freshRows;
            colsNumber = freshCols;
            storage = freshStorage;
        }

        constexpr void swap(DynamicMatrix& that)
        {
            std::swap(this->rowsNumber, that.rowsNumber);
            std::swap(this->colsNumber, that.colsNumber);
            std::swap(this->memory, that.memory);
            std::swap(this->storage, that.storage);
        }

        constexpr void clear()
        {
            for(size_type row{0}; row < rows(); ++row)
            {
                for(size_type col{0}; col < cols(); ++col)
                {
                    std::allocator_traits<allocator_type>::destroy(memory, storage + row * rows() + col);
                }
            }
            std::allocator_traits<allocator_type>::deallocate(memory, storage, rows() * cols());
            rowsNumber = 0;
            colsNumber = 0;
            storage = std::allocator_traits<Allocator>::allocate(memory, 0);
        }
    private:
        constexpr void copy_to_fresh_memory(pointer freshStorage, const size_type freshRows, const size_type freshCols)
        {
            size_type minRows{std::min(rows(), freshRows)};
            size_type minCols{std::min(cols(), freshCols)};
            for(size_type row{0}; row < minRows; ++row)
            {
                for(size_type col{0}; col < minCols; ++col)
                {
                    std::allocator_traits<allocator_type>::construct(memory, freshStorage + row * minRows + col, std::move(storage[row * minRows + col]));
                }
            }
        }

        constexpr void initialize_default(pointer storage, value_type default_value = value_type{})
        {
            for(size_type row{0}; row < rows(); ++row)
            {
                for(size_type col{0}; col < cols(); ++col)
                {
                    std::allocator_traits<allocator_type>::construct(memory, storage + row * rows() + col, default_value);
                }
            }
        }

        size_type rowsNumber;
        size_type colsNumber;
        allocator_type memory;
        pointer storage;
    };
}

#endif