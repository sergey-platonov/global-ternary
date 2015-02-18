#ifndef CALCULATION_H
#define CALCULATION_H

#include <iostream>
#include <list>
#include <map>
#include "ternary.h"
#include "constructed_ternary.h"

namespace sequences
{

typedef std::list<ternary_pulse> fixed_weigt_t;
typedef std::map<std::size_t, fixed_weigt_t> options_map_t;

struct show_options_t
{
    enum consts {ALL = -1};
    int weight;
    int zero_count;
    show_options_t()
    {
        weight = ALL;
        zero_count = ALL;
    }
};

class calculation_t
{
    //options_map_t options;
    fixed_weigt_t results;
    std::size_t max_length;
    // minimum peak factor
    float max_pf;
    int out_count;
    show_options_t show_options;
    std::ostream *out;
public:
    calculation_t();

    void calc(const ternary_pulse &a, const ternary_pulse &b);

    int get_max_length() const { return max_length; }
    void set_max_length(int value) { max_length = value; }

    float get_max_pf() const { return max_pf; }
    void set_max_pf(float value) { max_pf = value; }

    const fixed_weigt_t& get_results() const { return results; }
    void set_show_options(show_options_t &options);
    void set_stream(std::ostream &os);
private:
    bool check_seq(constructed_ternary_pulse &&c);
    void add_to_db(ternary_pulse t);
    void calc_impl(const ternary_pulse &a, const ternary_pulse &b, std::string sym);
    void calc_impl(const ternary_pulse &a, const ternary_pulse &b, char sym, std::string symbols);

    void print_seq(const ternary_pulse &t);
};

}

#endif // CALCULATION_H
