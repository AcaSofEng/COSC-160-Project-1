#include<cstddef>
#include<cstdint>
#include<cstdlib>
#include<fstream>
#include<functional>
#include<iostream>
#include<sstream>
#include<string>
#include<unordered_map>
#include"polynomial.h"

#ifdef DECIMAL_VERSION
    using system_polynomial=polynomial<long double,
                                       std::uintmax_t>;
#else
    using system_polynomial=polynomial<std::intmax_t,
                                       std::uintmax_t>;
#endif

bool addition_operation(system_polynomial& chain_polynomial,
                        std::string&& polyt_operation_line)
{
    std::cout<<"Performing \"addition\" operation...\n";
    std::cout<<"Polynomial BEFORE \"addition\" operation: "
             <<chain_polynomial
             <<'\n';

    system_polynomial addend_polynomial;
    std::istringstream addition_operation_stream(std::move(polyt_operation_line));
    while(addition_operation_stream>>
          addend_polynomial)
    {
        if(!addition_operation_stream)
        {
            std::cerr<<"Error: addition stream extraction failure"
                     <<std::endl;

            return false;
        }

        chain_polynomial+=addend_polynomial;
    }

    std::cout<<"Polynomial AFTER \"addition\" operation: "
             <<chain_polynomial
             <<'\n';

    return true;
}

bool compare_equal_operation(system_polynomial& chain_polynomial,
                             std::string&& polyt_operation_line)
{
    std::cout<<"Performing \"compare_equal\" operation...\n";

    bool equal_to{};
    system_polynomial compare_equal_polynomial;
    std::istringstream compare_equal_operation_stream(std::move(polyt_operation_line));
    while(compare_equal_operation_stream>>
          compare_equal_polynomial)
    {
        if(!compare_equal_operation_stream)
        {
            std::cerr<<"Error: compare-equal stream extraction failure"
                     <<std::endl;

            return false;
        }

        equal_to=chain_polynomial==compare_equal_polynomial;
        std::cout<<chain_polynomial
                 <<(equal_to?
                    " EQUAL-TO ":
                    " NOT EQUAL-TO ")
                 <<compare_equal_polynomial
                 <<'\n';
    }

    return true;
}

bool compare_greater_operation(system_polynomial& chain_polynomial,
                               std::string&& polyt_operation_line)
{
    std::cout<<"Performing \"compare_greater\" operation...\n";

    bool greater_than{};
    system_polynomial compare_greater_polynomial;
    std::istringstream compare_greater_operation_stream(std::move(polyt_operation_line));
    while(compare_greater_operation_stream>>
          compare_greater_polynomial)
    {
        if(!compare_greater_operation_stream)
        {
            std::cerr<<"Error: compare-greater stream extraction failure"
                     <<std::endl;

            return false;
        }

        greater_than=chain_polynomial>compare_greater_polynomial;
        std::cout<<chain_polynomial
                 <<(greater_than?
                    " GREATER-THAN ":
                    " NOT GREATER-THAN ")
                 <<compare_greater_polynomial
                 <<'\n';
    }

    return true;
}

bool compare_greater_equal_operation(system_polynomial& chain_polynomial,
                                     std::string&& polyt_operation_line)
{
    std::cout<<"Performing \"compare_greater_equal\" operation...\n";

    bool greater_equal{};
    system_polynomial compare_greater_equal_polynomial;
    std::istringstream compare_greater_equal_operation_stream(std::move(polyt_operation_line));
    while(compare_greater_equal_operation_stream>>
          compare_greater_equal_polynomial)
    {
        if(!compare_greater_equal_operation_stream)
        {
            std::cerr<<"Error: compare-greater-equal stream extraction failure"
                     <<std::endl;

            return false;
        }

        greater_equal=chain_polynomial>=compare_greater_equal_polynomial;
        std::cout<<chain_polynomial
                 <<(greater_equal?
                    " GREATER-THAN-OR-EQUAL-TO ":
                    " NOT GREATER-THAN-OR-EQUAL-TO ")
                 <<compare_greater_equal_polynomial
                 <<'\n';
    }

    return true;
}

bool compare_less_operation(system_polynomial& chain_polynomial,
                            std::string&& polyt_operation_line)
{
    std::cout<<"Performing \"compare_less\" operation...\n";

    bool less_than{};
    system_polynomial compare_less_polynomial;
    std::istringstream compare_less_operation_stream(std::move(polyt_operation_line));
    while(compare_less_operation_stream>>
          compare_less_polynomial)
    {
        if(!compare_less_operation_stream)
        {
            std::cerr<<"Error: compare-less stream extraction failure"
                     <<std::endl;

            return false;
        }

        less_than=chain_polynomial<compare_less_polynomial;
        std::cout<<chain_polynomial
                 <<(less_than?
                    " LESS-THAN ":
                    " NOT LESS-THAN ")
                 <<compare_less_polynomial
                 <<'\n';
    }

    return true;
}

bool compare_less_equal_operation(system_polynomial& chain_polynomial,
                                  std::string&& polyt_operation_line)
{
    std::cout<<"Performing \"compare_less_equal\" operation...\n";

    bool less_equal{};
    system_polynomial compare_less_equal_polynomial;
    std::istringstream compare_less_equal_operation_stream(std::move(polyt_operation_line));
    while(compare_less_equal_operation_stream>>
          compare_less_equal_polynomial)
    {
        if(!compare_less_equal_operation_stream)
        {
            std::cerr<<"Error: compare-less-equal stream extraction failure"
                     <<std::endl;

            return false;
        }

        less_equal=chain_polynomial<=compare_less_equal_polynomial;
        std::cout<<chain_polynomial
                 <<(less_equal?
                    " LESS-THAN-OR-EQUAL-TO ":
                    " NOT LESS-THAN-OR-EQUAL-TO ")
                 <<compare_less_equal_polynomial
                 <<'\n';
    }

    return true;
}

bool compare_not_equal_operation(system_polynomial& chain_polynomial,
                                 std::string&& polyt_operation_line)
{
    std::cout<<"Performing \"compare_not_equal\" operation...\n";

    bool not_equal_to{};
    system_polynomial compare_not_equal_polynomial;
    std::istringstream compare_not_equal_operation_stream(std::move(polyt_operation_line));
    while(compare_not_equal_operation_stream>>
          compare_not_equal_polynomial)
    {
        if(!compare_not_equal_operation_stream)
        {
            std::cerr<<"Error: compare-not-equal stream extraction failure"
                     <<std::endl;

            return false;
        }

        not_equal_to=chain_polynomial!=compare_not_equal_polynomial;
        std::cout<<chain_polynomial
                 <<(not_equal_to?
                    " NOT-EQUAL-TO ":
                    " NOT NOT-EQUAL-TO ")
                 <<compare_not_equal_polynomial
                 <<'\n';
    }

    return true;
}

bool default_operation(system_polynomial& chain_polynomial,
                       std::string&& polyt_operation_line)
{
    std::cout<<"Performing \"default\" operation...\n";
    std::cout<<"Polynomial BEFORE \"default\" operation: "
             <<chain_polynomial
             <<'\n';

    std::istringstream default_operation_stream(std::move(polyt_operation_line));
    default_operation_stream>>chain_polynomial;
    if(!default_operation_stream)
    {
        std::cerr<<"Error: polynomial stream extraction failure"
                 <<std::endl;

        return false;
    }

    std::cout<<"Polynomial AFTER \"default\" operation: "
             <<chain_polynomial
             <<'\n';

    return true;
}

bool division_operation(system_polynomial& chain_polynomial,
                        std::string&& polyt_operation_line)
{
    std::cout<<"Performing \"division\" operation...\n";
    std::cout<<"Polynomial BEFORE \"division\" operation: "
             <<chain_polynomial
             <<'\n';

    system_polynomial divisor_polynomial;
    std::istringstream division_operation_stream(std::move(polyt_operation_line));
    while(division_operation_stream>>
          divisor_polynomial)
    {
        if(!division_operation_stream)
        {
            std::cerr<<"Error: division stream extraction failure"
                     <<std::endl;

            return false;
        }

        chain_polynomial/=divisor_polynomial;
    }

    std::cout<<"Polynomial AFTER \"division\" operation: "
             <<chain_polynomial
             <<'\n';

    return true;
}

bool division_constant_operation(system_polynomial& chain_polynomial,
                                 std::string&& polyt_operation_line)
{
    std::cout<<"Performing \"division_constant\" operation...\n";
    std::cout<<"Polynomial BEFORE \"division_constant\" operation: "
             <<chain_polynomial
             <<'\n';

    #ifdef DECIMAL_VERSION
        long double division_constant{};
    #else
        std::intmax_t division_constant{};
    #endif

    std::istringstream division_constant_operation_stream(std::move(polyt_operation_line));
    while(division_constant_operation_stream>>
          division_constant)
    {
        if(!division_constant_operation_stream)
        {
            std::cerr<<"Error: division-constant stream extraction failure"
                     <<std::endl;

            return false;
        }

        chain_polynomial/=division_constant;
    }

    std::cout<<"Polynomial AFTER \"division_constant\" operation: "
             <<chain_polynomial
             <<'\n';

    return true;
}

bool erase_operation(system_polynomial& chain_polynomial,
                     std::string&& polyt_operation_line)
{
    std::cout<<"Performing \"erase\" operation...\n";
    std::cout<<"Polynomial BEFORE \"erase\" operation: "
             <<chain_polynomial
             <<'\n';

    char open_bracket_character('\0');
    char close_bracket_character('\0');
    std::uintmax_t erase_exponent{};

    #ifdef DECIMAL_VERSION
        long double erase_coefficient{};
    #else
        std::intmax_t erase_coefficient{};
    #endif

    std::istringstream erase_operation_stream(std::move(polyt_operation_line));
    while(erase_operation_stream>>
          open_bracket_character>>
          erase_coefficient>>
          erase_exponent>>
          close_bracket_character)
    {
        if(open_bracket_character!='['||
           close_bracket_character!=']')
        {
            std::cerr<<"Error: character stream extraction failure"
                     <<std::endl;

            return false;
        }

        else if(!erase_operation_stream)
        {
            std::cerr<<"Error: coefficient-exponent stream extraction failure"
                     <<std::endl;

            return false;
        }

        chain_polynomial.erase(erase_coefficient,
                               erase_exponent);
    }

    std::cout<<"Polynomial AFTER \"erase\" operation: "
             <<chain_polynomial
             <<'\n';

    return true;
}

bool erase_exponent_operation(system_polynomial& chain_polynomial,
                              std::string&& polyt_operation_line)
{
    std::cout<<"Performing \"erase_exponent\" operation...\n";
    std::cout<<"Polynomial BEFORE \"erase_exponent\" operation: "
             <<chain_polynomial
             <<'\n';

    std::uintmax_t erase_exponent{};
    std::istringstream erase_exponent_operation_stream(std::move(polyt_operation_line));
    while(erase_exponent_operation_stream>>
          erase_exponent)
    {
        if(!erase_exponent_operation_stream)
        {
            std::cerr<<"Error: exponent stream extraction failure"
                     <<std::endl;

            return false;
        }

        chain_polynomial.erase_exponent(erase_exponent);
    }

    std::cout<<"Polynomial AFTER \"erase_exponent\" operation: "
             <<chain_polynomial
             <<'\n';

    return true;
}

bool evaluate_operation(system_polynomial& chain_polynomial,
                        std::string&& polyt_operation_line)
{
    std::cout<<"Performing \"evaluate\" operation...\n";

    #ifdef DECIMAL_VERSION
        long double evaluate_value{};
        long double evaluate_result{};
    #else
        std::intmax_t evaluate_value{};
        std::intmax_t evaluate_result{};
    #endif

    std::istringstream evaluate_operation_stream(std::move(polyt_operation_line));
    while(evaluate_operation_stream>>
          evaluate_value)
    {
        if(!evaluate_operation_stream)
        {
            std::cerr<<"Error: evaluate stream extraction failure"
                     <<std::endl;

            return false;
        }

        evaluate_result=chain_polynomial(evaluate_value);
        std::cout<<chain_polynomial
                 <<'('
                 <<evaluate_value
                 <<") = "
                 <<evaluate_result
                 <<'\n';
    }

    return true;
}

bool find_operation(system_polynomial& chain_polynomial,
                    std::string&& polyt_operation_line)
{
    std::cout<<"Performing \"find\" operation...\n";

    char open_bracket_character('\0');
    char close_bracket_character('\0');
    std::uintmax_t find_exponent{};

    #ifdef DECIMAL_VERSION
        long double find_coefficient{};
    #else
        std::intmax_t find_coefficient{};
    #endif

    bool term_found{};
    std::istringstream find_operation_stream(std::move(polyt_operation_line));
    while(find_operation_stream>>
          open_bracket_character>>
          find_coefficient>>
          find_exponent>>
          close_bracket_character)
    {
        if(open_bracket_character!='['||
           close_bracket_character!=']')
        {
            std::cerr<<"Error: character stream extraction failure"
                     <<std::endl;

            return false;
        }

        else if(!find_operation_stream)
        {
            std::cerr<<"Error: coefficient-exponent stream extraction failure"
                     <<std::endl;

            return false;
        }

        term_found=chain_polynomial.find(find_coefficient,
                                         find_exponent);
        std::cout<<"Term \""
                 <<find_coefficient
                 <<chain_polynomial.variant()
                 <<'^'
                 <<find_exponent
                 <<"\" "
                 <<(term_found?
                    "FOUND\n":
                    "NOT FOUND\n");
    }

    return true;
}

bool find_exponent_operation(system_polynomial& chain_polynomial,
                             std::string&& polyt_operation_line)
{
    std::cout<<"Performing \"find_exponent\" operation...\n";

    #ifdef DECIMAL_VERSION
        long double find_coefficient{};
    #else
        std::intmax_t find_coefficient{};
    #endif

    std::uintmax_t find_exponent{};
    std::istringstream find_exponent_operation_stream(std::move(polyt_operation_line));
    while(find_exponent_operation_stream>>
          find_exponent)
    {
        if(!find_exponent_operation_stream)
        {
            std::cerr<<"Error: exponent stream extraction failure"
                     <<std::endl;

            return false;
        }

        find_coefficient=chain_polynomial.find_exponent(find_exponent);
        std::cout<<"Term with exponent \""
                 <<find_exponent
                 <<"\" "
                 <<(find_coefficient?
                    "FOUND\n":
                    "NOT FOUND\n");
    }

    return true;
}

bool insert_operation(system_polynomial& chain_polynomial,
                      std::string&& polyt_operation_line)
{
    std::cout<<"Performing \"insert\" operation...\n";
    std::cout<<"Polynomial BEFORE \"insert\" operation: "
             <<chain_polynomial
             <<'\n';

    char open_bracket_character('\0');
    char close_bracket_character('\0');
    std::uintmax_t insert_exponent{};

    #ifdef DECIMAL_VERSION
        long double insert_coefficient{};
    #else
        std::intmax_t insert_coefficient{};
    #endif

    std::istringstream insert_operation_stream(std::move(polyt_operation_line));
    while(insert_operation_stream>>
          open_bracket_character>>
          insert_coefficient>>
          insert_exponent>>
          close_bracket_character)
    {
        if(open_bracket_character!='['||
           close_bracket_character!=']')
        {
            std::cerr<<"Error: character stream extraction failure"
                     <<std::endl;

            return false;
        }

        else if(!insert_operation_stream)
        {
            std::cerr<<"Error: coefficient-exponent stream extraction failure"
                     <<std::endl;

            return false;
        }

        chain_polynomial.insert(insert_coefficient,
                                insert_exponent);
    }

    std::cout<<"Polynomial AFTER \"insert\" operation: "
             <<chain_polynomial
             <<'\n';

    return true;
}

bool modulus_operation(system_polynomial& chain_polynomial,
                       std::string&& polyt_operation_line)
{
    std::cout<<"Performing \"modulus\" operation...\n";
    std::cout<<"Polynomial BEFORE \"modulus\" operation: "
             <<chain_polynomial
             <<'\n';

    system_polynomial divisor_polynomial;
    std::istringstream modulus_operation_stream(std::move(polyt_operation_line));
    while(modulus_operation_stream>>
          divisor_polynomial)
    {
        if(!modulus_operation_stream)
        {
            std::cerr<<"Error: modulus stream extraction failure"
                     <<std::endl;

            return false;
        }

        chain_polynomial%=divisor_polynomial;
    }

    std::cout<<"Polynomial AFTER \"modulus\" operation: "
             <<chain_polynomial
             <<'\n';

    return true;
}

bool modulus_constant_operation(system_polynomial& chain_polynomial,
                                std::string&& polyt_operation_line)
{
    std::cout<<"Performing \"modulus_constant\" operation...\n";
    std::cout<<"Polynomial BEFORE \"modulus_constant\" operation: "
             <<chain_polynomial
             <<'\n';

    #ifdef DECIMAL_VERSION
        long double modulus_constant{};
    #else
        std::intmax_t modulus_constant{};
    #endif

    std::istringstream modulus_constant_operation_stream(std::move(polyt_operation_line));
    while(modulus_constant_operation_stream>>
          modulus_constant)
    {
        if(!modulus_constant_operation_stream)
        {
            std::cerr<<"Error: modulus-constant stream extraction failure"
                     <<std::endl;

            return false;
        }

        chain_polynomial%=modulus_constant;
    }

    std::cout<<"Polynomial AFTER \"modulus_constant\" operation: "
             <<chain_polynomial
             <<'\n';

    return true;
}

bool multiplication_operation(system_polynomial& chain_polynomial,
                              std::string&& polyt_operation_line)
{
    std::cout<<"Performing \"multiplication\" operation...\n";
    std::cout<<"Polynomial BEFORE \"multiplication\" operation: "
             <<chain_polynomial
             <<'\n';

    system_polynomial multiplier_polynomial;
    std::istringstream multiplication_operation_stream(std::move(polyt_operation_line));
    while(multiplication_operation_stream>>
          multiplier_polynomial)
    {
        if(!multiplication_operation_stream)
        {
            std::cerr<<"Error: multiplication stream extraction failure"
                     <<std::endl;

            return false;
        }

        chain_polynomial*=multiplier_polynomial;
    }

    std::cout<<"Polynomial AFTER \"multiplication\" operation: "
             <<chain_polynomial
             <<'\n';

    return true;
}

bool multiplication_constant_operation(system_polynomial& chain_polynomial,
                                       std::string&& polyt_operation_line)
{
    std::cout<<"Performing \"multiplication_constant\" operation...\n";
    std::cout<<"Polynomial BEFORE \"multiplication_constant\" operation: "
             <<chain_polynomial
             <<'\n';

    #ifdef DECIMAL_VERSION
        long double multiplication_constant{};
    #else
        std::intmax_t multiplication_constant{};
    #endif

    std::istringstream multiplication_constant_operation_stream(std::move(polyt_operation_line));
    while(multiplication_constant_operation_stream>>
          multiplication_constant)
    {
        if(!multiplication_constant_operation_stream)
        {
            std::cerr<<"Error: multiplication-constant stream extraction failure"
                     <<std::endl;

            return false;
        }

        chain_polynomial*=multiplication_constant;
    }

    std::cout<<"Polynomial AFTER \"multiplication_constant\" operation: "
             <<chain_polynomial
             <<'\n';

    return true;
}

bool negative_operation(system_polynomial& chain_polynomial,
                        std::string&& polyt_operation_line)
{
    std::cout<<"Performing \"negative\" operation...\n";
    if(!polyt_operation_line.empty())
    {
        std::cerr<<"Error: argument(s) provided for operation"<<std::endl;

        return false;
    }

    std::cout<<"Polynomial BEFORE \"negative\" operation: "
             <<chain_polynomial
             <<'\n';

    chain_polynomial=(-chain_polynomial);

    std::cout<<"Polynomial AFTER \"negative\" operation: "
             <<chain_polynomial
             <<'\n';

    return true;
}

bool output_operation(system_polynomial& chain_polynomial,
                      std::string&& polyt_operation_line)
{
    std::cout<<"Performing \"output\" operation...\n";
    if(!polyt_operation_line.empty())
    {
        std::cerr<<"Error: argument(s) provided for operation"<<std::endl;

        return false;
    }

    std::cout<<"Polynomial: "<<chain_polynomial<<'\n';

    return true;
}

bool positive_operation(system_polynomial& chain_polynomial,
                        std::string&& polyt_operation_line)
{
    std::cout<<"Performing \"positive\" operation...\n";
    if(!polyt_operation_line.empty())
    {
        std::cerr<<"Error: argument(s) provided for operation"<<std::endl;

        return false;
    }

    std::cout<<"Polynomial BEFORE \"positive\" operation: "
             <<chain_polynomial
             <<'\n';

    chain_polynomial=(+chain_polynomial);

    std::cout<<"Polynomial AFTER \"positive\" operation: "
             <<chain_polynomial
             <<'\n';

    return true;
}

bool subtraction_operation(system_polynomial& chain_polynomial,
                           std::string&& polyt_operation_line)
{
    std::cout<<"Performing \"subtraction\" operation...\n";
    std::cout<<"Polynomial BEFORE \"subtraction\" operation: "
             <<chain_polynomial
             <<'\n';

    system_polynomial subtrahend_polynomial;
    std::istringstream subtraction_operation_stream(std::move(polyt_operation_line));
    while(subtraction_operation_stream>>
          subtrahend_polynomial)
    {
        if(!subtraction_operation_stream)
        {
            std::cerr<<"Error: subtraction stream extraction failure"
                     <<std::endl;

            return false;
        }

        chain_polynomial-=subtrahend_polynomial;
    }

    std::cout<<"Polynomial AFTER \"subtraction\" operation: "
             <<chain_polynomial
             <<'\n';

    return true;
}

int main(const int argc,
         const char* const argv[])
{
    if(argc!=2)
    {
        #ifdef DECIMAL_VERSION
            std::cerr<<"Error: wrong number of command line arguments provided\nUsage: decimal_polynomial_system <polyt file path>"
                     <<std::endl;
        #else
            std::cerr<<"Error: wrong number of command line arguments provided\nUsage: integer_polynomial_system <polyt file path>"
                     <<std::endl;
        #endif

        return EXIT_FAILURE;
    }

    std::ifstream polyt_file(argv[static_cast<std::size_t>(1)]);
    if(!polyt_file.is_open())
    {
        std::cerr<<"Error: polyt file path open failure"
                 <<std::endl;

        return EXIT_FAILURE;
    }

    const std::unordered_map<std::string,
                             std::function<bool(system_polynomial&,
                                                std::string&&)>> system_operations
    {
        {"addition",
         addition_operation},
        {"compare_equal",
         compare_equal_operation},
        {"compare_greater",
         compare_greater_operation},
        {"compare_greater_equal",
         compare_greater_equal_operation},
        {"compare_less",
         compare_less_operation},
        {"compare_less_equal",
         compare_less_equal_operation},
        {"compare_not_equal",
         compare_not_equal_operation},
        {"default",
         default_operation},
        {"division",
         division_operation},
        {"division_constant",
         division_constant_operation},
        {"erase",
         erase_operation},
        {"erase_exponent",
         erase_exponent_operation},
        {"evaluate",
         evaluate_operation},
        {"find",
         find_operation},
        {"find_exponent",
         find_exponent_operation},
        {"insert",
         insert_operation},
        {"modulus",
         modulus_operation},
        {"modulus_constant",
         modulus_constant_operation},
        {"multiplication",
         multiplication_operation},
        {"multiplication_constant",
         multiplication_constant_operation},
        {"negative",
         negative_operation},
        {"output",
         output_operation},
        {"positive",
         positive_operation},
        {"subtraction",
         subtraction_operation}
    };

    std::unordered_map<std::string,
                       std::function<bool(system_polynomial&,
                                          std::string&&)>>::const_iterator system_operations_iterator;

    system_polynomial chain_polynomial;

    std::string polyt_operation_line;
    std::istringstream polyt_operation_line_stream;
    while(std::getline(polyt_file,
                       polyt_operation_line))
    {
        if(polyt_operation_line.empty()||
           polyt_operation_line.front()=='#')
        {
            continue;
        }

        polyt_operation_line_stream.str(polyt_operation_line);
        std::getline(polyt_operation_line_stream,
                     polyt_operation_line,
                     ':');
        system_operations_iterator=system_operations.find(polyt_operation_line);
        if(system_operations_iterator==system_operations.cend())
        {
            std::cerr<<"Error: operation \""
                     <<polyt_operation_line
                     <<"\" not found"
                     <<std::endl;

            return EXIT_FAILURE;
        }

        std::getline(polyt_operation_line_stream,
                     polyt_operation_line);
        if(!system_operations_iterator->second(chain_polynomial,
                                               std::move(polyt_operation_line)))
        {
            return EXIT_FAILURE;
        }

        polyt_operation_line_stream.clear();
    }

    return EXIT_SUCCESS;
}
