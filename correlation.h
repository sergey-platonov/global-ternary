#ifndef ACF_H
#define ACF_H
#include <vector>
#include <algorithm>
namespace sequences
{

template<class Sequence, class Values = int>
class correlation : public std::vector<Values>
{
public:
    typedef Values value_type;
    // autocorrelation
    correlation(const Sequence &seq) : std::vector<Values>(seq.size())
    {
        for ( std::size_t t = 0 ; t < seq.size() ; t++ )
        {
            Values sum = 0;
            for ( std::size_t i = 0 ; i < seq.size() ; i++ )
            {
                Values x_i = seq[i];
                Values x_it = seq[i + t];
                Values prod = x_i * x_it;
                sum +=  prod;
            }
            this->at(t) = sum;
        }
    }

    // cross correlation
    correlation(const Sequence &a, const Sequence &b)
    {
        this->resize( a.size() );
        for ( std::size_t t = 0 ; t < a.size() ; t++ )
        {
            Values sum = 0;
            for ( std::size_t i = 0 ; i < b.size() ; i++ )
            {
                Values x_i = a[i];
                Values y_it = b[i + t];
                Values prod = x_i * y_it;
                sum +=  prod;
            }
            this->at(t) = sum;
        }
    }
    // copy
    correlation(const std::vector<Values> &s) : std::vector<Values>(s) {}

    Values max() const
    {
        return *std::max_element(this->begin() + 1, this->end());
    }

    Values min() const
    {
        return *std::min_element(this->begin() + 1, this->end());
    }
};

}

#endif // ACF_H
