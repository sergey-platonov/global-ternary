#include "calculation.h"
#include "constructed_ternary.h"

bool add_to_db_impl(sequences::fixed_weigt_t &results, sequences::ternary_pulse t);

namespace sequences
{

void calculation_t::print_seq(const ternary_pulse &t)
{
    int m0 = t.size() - t.weight();
    if ( ((t.weight() == show_options.weight) || (show_options.weight == show_options_t::ALL))
       && ((m0 == show_options.zero_count) || (show_options.zero_count == show_options_t::ALL)))
    {
        out->width(2);
        if (out == &std::cout)
            *out << ++out_count << ") ";
        else
            std::cout << t.weight() << "/" << t.size() << std::endl;

        *out << t << std::endl << std::flush;
    }
}

bool calculation_t::check_seq(constructed_ternary_pulse c)
{
#ifdef VERBOSE_DEBUG
    std::cout << "checking: " << (ternary_pulse)c << std::endl;
#endif
    bool success = false;
    if ((c.half_cf().max() < 2) && (c.half_cf().min() > -2))
    {
        auto t = (ternary_pulse)c;
        float pf = (float)t.size() / t.weight();
        max_pf = 1 + t.weight()  / 10.0f;
        if (pf > max_pf)
            return false;

        //options[c.size()].push_back((ternary_pulse)c);
        if ((t.cf()->max() < 2) && (t.cf()->min() > -2))
        {
            add_to_db(t);
        }

        success = true;
    }
    return success;
}

void calculation_t::add_to_db(ternary_pulse t)
{
    if (::add_to_db_impl(results, t))
    {
        print_seq(t);
    }
}

void calculation_t::calc_impl(ternary_pulse &a, ternary_pulse &b, std::string sym)
{
    for (char a0 : sym)
    {
        auto a1 = a | a0;
        for (char b0 : sym)
        {
            auto b1 = b0 | b;
            if ( check_seq(constructed_ternary_pulse(a1, b1)) )
                calc(a1, b1);

            for (char c1 : sym)
            {
                check_seq(constructed_ternary_pulse(a1, c1, b1));
            }
        }
    }
}


calculation_t::calculation_t() : max_length(15), max_pf(1.3f)
{
    out_count = 0;
    out = &std::cout;
}

void calculation_t::calc(ternary_pulse &a, ternary_pulse &b)
{
    if ((a.size() + b.size() + 2) > max_length)
        return;

    calc_impl(a, b, "+-0");
}

void calculation_t::set_show_options(show_options_t &options)
{
    show_options = options;
}

void calculation_t::set_stream(std::ostream &os)
{
    out = &os;
}

}

bool add_to_db_impl(sequences::fixed_weigt_t &results, sequences::ternary_pulse t)
{
    sequences::ternary_pulse i = -t;
    sequences::ternary_pulse r = ~t;
    sequences::ternary_pulse ir = -r;
    auto it = std::find_if(results.begin(), results.end(),
                           [&](const sequences::ternary_pulse &s){
                                return (s == t) || (s == i) || (s == r) || (s == ir);
    });
    if (it == results.end())
    {
        results.push_back(t);
        return true;
    }
    return false;
}
