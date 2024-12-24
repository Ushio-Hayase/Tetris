#include <iterator>

template <typename I>
class IIterator
{
protected:
    I i;

    using tr = std::iterator_traits<I>;

public:
    using iterator_type = I;
    using iterator_category = typename tr::iterator_category;
    using value_type = typename tr::value_type;
    using difference_type = typename tr::difference_type;
    using reference = typename tr::reference;
    using pointer = typename tr::pointer;

    IIterator() : i(I()) {}

    explicit IIterator(const I &i) : i(i) {}

    // Forward IIteratorator requirements
    reference operator*() const { return *i; }

    pointer operator->() const { return i; }

    IIterator &operator++()
    {
        ++i;
        return *this;
    }

    IIterator operator++(int) { return IIterator(i++); }

    // Bidirectional IIteratorator requirements
    IIterator &operator--()
    {
        --i;
        return *this;
    }

    IIterator operator--(int) { return IIterator(i--); }

    // Random access IIteratorator requirements
    reference operator[](const difference_type &n) const { return i[n]; }

    IIterator &operator+=(const difference_type &n)
    {
        i += n;
        return *this;
    }

    IIterator operator+(const difference_type &n) const { return IIterator(i + n); }

    IIterator &operator-=(const difference_type &n)
    {
        i -= n;
        return *this;
    }

    IIterator operator-(const difference_type &n) const { return IIterator(i - n); }

    const I &base() const { return i; }
};