#include <iostream>
#include <fstream>
#include <getopt.h>
#include "calculation.h"

template<class T>
void print_with_cf(T c)
{
    std::cout << c << std::endl << *c.cf() << std::endl << std::endl;
}

int main(int argc, char *argv[])
{
    sequences::ternary_pulse a("+");
    sequences::ternary_pulse b("-");
    sequences::ternary_pulse cc = -a;
    int c = 0;
    int max_len = 7;
    float pf = 1.3f;
    std::ofstream out;
    sequences::show_options_t options;
    sequences::calculation_t calc;
    while ((c = getopt (argc, argv, "w:m:z:p:o:")) != -1)
    {
        switch (c) {
        case 'w':
            options.weight = atoi(optarg);
            if (max_len < options.weight * pf)
            {
                max_len = options.weight * pf + 1;
                calc.set_max_length(max_len);
            }
            break;
        case 'm':
            max_len = atoi(optarg);
            calc.set_max_length(max_len);
            break;
        case 'z':
            options.zero_count = atoi(optarg);
            break;
        case 'p':
            pf = atof(optarg);
            calc.set_max_pf(pf);
            break;
        case 'o':
            out.open(optarg, std::ios_base::app | std::ios_base::out);
            if (out.is_open())
                calc.set_stream(out);
            else
                std::cout << "Unable to open file " << optarg << std::endl;
            break;
        default:
            std::cout << "Unknown argument: \"" << (char)c << "\"" << std::endl;
            break;
        }
    }

    calc.set_show_options(options);
    calc.calc(a, a);
    calc.calc(a, b);

    return 0;
}

