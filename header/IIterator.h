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

    iter() : i(I()) {}

    explicit iter(const I &i) : i(i) {}

    // Forward iterator requirements
    reference operator*() const { return *i; }

    pointer operator->() const { return i; }

    iter &operator++()
    {
        ++i;
        return *this;
    }

    iter operator++(int) { return iter(i++); }

    // Bidirectional iterator requirements
    iter &operator--()
    {
        --i;
        return *this;
    }

    iter operator--(int) { return iter(i--); }

    // Random access iterator requirements
    reference operator[](const difference_type &n) const { return i[n]; }

    iter &operator+=(const difference_type &n)
    {
        i += n;
        return *this;
    }

    iter operator+(const difference_type &n) const { return iter(i + n); }

    iter &operator-=(const difference_type &n)
    {
        i -= n;
        return *this;
    }

    iter operator-(const difference_type &n) const { return iter(i - n); }

    const I &base() const { return i; }
};