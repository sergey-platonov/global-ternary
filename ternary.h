#ifndef TERNARY_H
#define TERNARY_H

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include "correlation.h"

namespace sequences
{ enum TernaryAlphabet { minus = -1, zero = 0, plus = 1 }; }

std::ostream & operator << (std::ostream &os, sequences::TernaryAlphabet a);

template<class T>
std::ostream & operator << (std::ostream &os, const std::vector<T> &s)
{
    for (std::size_t i = 0 ; i < s.size() ; i++)
    {
        if ((s[i] >= 0) && (i > 0))
            os << " ";

        os << s[i] << " ";
    }
//    os << " [" << s.size() << "]";
    return os;
}

namespace sequences
{
TernaryAlphabet operator- (TernaryAlphabet a);

TernaryAlphabet to_ternary(long s);
TernaryAlphabet to_ternary(char s);
TernaryAlphabet to_ternary(std::string s);

class ternary_base : public std::vector<TernaryAlphabet>, public std::enable_shared_from_this<ternary_base>
{
public:
    typedef correlation<ternary_base, int> correlation;

    ternary_base();
    explicit ternary_base(std::string s);
    explicit ternary_base(const std::vector<TernaryAlphabet> &v);
    virtual ~ternary_base();

    void append(const std::vector<TernaryAlphabet> &v);

    std::shared_ptr<ternary_base::correlation> cf();
    virtual ternary_base::value_type operator[] (ternary_base::size_type n) = 0;
    virtual ternary_base::value_type operator[] (ternary_base::size_type n) const = 0;

    virtual std::shared_ptr<ternary_base> ptr();

    std::size_t weight() const;

protected:
    void reset_cf();
private:
    std::shared_ptr<correlation> m_cf;
};
typedef ternary_base::correlation ternary_correlation;

class ternary_pulse : public ternary_base
{
public:
    ternary_pulse() : ternary_base() {}

    explicit ternary_pulse(std::string s) : ternary_base(s) {}
    explicit ternary_pulse(const std::vector<TernaryAlphabet> &v) : ternary_base(v) {}

    ternary_base::value_type operator[] (ternary_base::size_type n);
    ternary_base::value_type operator[] (ternary_base::size_type n) const;
};

class ternary_cycle : public ternary_base
{
public:
    ternary_cycle() : ternary_base() {}
    explicit ternary_cycle(std::string s) : ternary_base(s) {}
    explicit ternary_cycle(const std::vector<TernaryAlphabet> &v) : ternary_base(v) {}

    ternary_base::value_type operator[] (ternary_base::size_type n);
    ternary_base::value_type operator[] (ternary_base::size_type n) const;
};

}

// operator | is for appending sequences
template <class A, class B,
          typename std::enable_if<std::is_convertible<A, std::vector<sequences::TernaryAlphabet>>::value, A>::type* = nullptr,
          typename std::enable_if<std::is_convertible<B, std::vector<sequences::TernaryAlphabet>>::value, B>::type* = nullptr>
auto operator |(const A &a, const B &b) -> typename std::remove_reference< decltype(a) >::type
{
    A c(a);
    c.append(b);
    return c;
}

template <class A,
          typename std::enable_if<std::is_convertible<A, std::vector<sequences::TernaryAlphabet>>::value, A>::type* = nullptr>
auto operator |(const A &a, const std::string &seq) -> typename std::remove_reference< decltype(a) >::type
{
    A c(a);
    A b(seq);
    c.append(b);
    return c;
}

template <class A,
          typename std::enable_if<std::is_convertible<A, std::vector<sequences::TernaryAlphabet>>::value, A>::type* = nullptr>
auto operator |(const std::string &seq, const A &a) -> typename std::remove_reference< decltype(a) >::type
{
    A c(seq);
    c.append(a);
    return c;
}

// add char
template <class A,
          typename std::enable_if<std::is_convertible<A, std::vector<sequences::TernaryAlphabet>>::value, A>::type* = nullptr>
auto operator |(const A &a, char s) -> typename std::remove_reference< decltype(a) >::type
{
    std::string seq(1, s);
    A c(a);
    A b(seq);
    c.append(b);
    return c;
}

template <class A,
          typename std::enable_if<std::is_convertible<A, std::vector<sequences::TernaryAlphabet>>::value, A>::type* = nullptr>
auto operator |(char s, const A &a) -> typename std::remove_reference< decltype(a) >::type
{
    std::string seq(1, s);
    A c(seq);
    c.append(a);
    return c;
}

// add TernaryAlphabet
template <class A,
          typename std::enable_if<std::is_convertible<A, std::vector<sequences::TernaryAlphabet>>::value, A>::type* = nullptr>
auto operator |(const A &a, sequences::TernaryAlphabet s) -> typename std::remove_reference< decltype(a) >::type
{
    std::vector<sequences::TernaryAlphabet> seq(1, s);
    A c(a);
    A b(seq);
    c.append(b);
    return c;
}

template <class A,
          typename std::enable_if<std::is_convertible<A, std::vector<sequences::TernaryAlphabet>>::value, A>::type* = nullptr>
auto operator |(sequences::TernaryAlphabet s, const A &a) -> typename std::remove_reference< decltype(a) >::type
{
    std::vector<sequences::TernaryAlphabet> seq(1, s);
    A c(seq);
    c.append(a);
    return c;
}

// operator + is for element by element addition
template <class A, class B,
          typename std::enable_if<std::is_convertible<A, std::vector<sequences::TernaryAlphabet>>::value, A>::type* = nullptr,
          typename std::enable_if<std::is_convertible<B, std::vector<sequences::TernaryAlphabet>>::value, B>::type* = nullptr>
auto operator +(const A &a, const B &b) -> typename std::remove_reference< decltype(a) >::type
{
    A c;
    std::size_t max_len = std::max(a.size(), b.size());
    c.resize(max_len);
    for ( std::size_t i = 0 ; i < max_len ; i++ )
    {
        c[i] = a[i] + b[i];
    }
    return c;
}

// unary operator -
template <class A,
          typename std::enable_if<std::is_convertible<A, std::vector<sequences::TernaryAlphabet>>::value, A>::type* = nullptr>
auto operator -(const A &a) -> typename std::remove_reference< decltype(a) >::type
{
    A c(a);
    for ( std::size_t i = 0 ; i < c.size() ; i++ )
    {
        c.at(i) = -c[i];
    }
    return c;
}

// reverse sequence
template <class A,
          typename std::enable_if<std::is_convertible<A, std::vector<sequences::TernaryAlphabet>>::value, A>::type* = nullptr>
auto operator ~(const A &a) -> typename std::remove_reference< decltype(a) >::type
{
    A c(a);
    auto n = a.size();
    for ( std::size_t i = 0 ; i < n ; i++ )
    {
        c.at(i) = -a[n - i - 1];
    }
    return c;
}



#endif // TERNARY_H
