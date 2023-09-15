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

const std::string ARGUMENTS_PROVIDED_ERROR("Error: argument(s) provided for operation");
const std::string STREAM_EXTRACTION_FAILURE_ERROR("Error: line stream extraction failure");

bool addition_operation(system_polynomial& source_polynomial,
                        std::string&& source_line)
{
    std::cout<<"Performing \"addition\" operation...\n";
    std::cout<<"Polynomial BEFORE \"addition\" operation: "
             <<source_polynomial
             <<'\n';

    system_polynomial polynomial;
    std::istringstream source_line_stream(std::move(source_line));
    while(source_line_stream>>
          polynomial)
    {
        if(!source_line_stream)
        {
            std::cerr<<STREAM_EXTRACTION_FAILURE_ERROR
                     <<std::endl;

            return false;
        }

        source_polynomial+=polynomial;
    }

    std::cout<<"Polynomial AFTER \"addition\" operation: "
             <<source_polynomial
             <<'\n';

    return true;
}

bool assign_operation(system_polynomial& source_polynomial,
                      std::string&& source_line)
{
    std::cout<<"Performing \"assign\" operation...\n";
    std::cout<<"Polynomial BEFORE \"assign\" operation: "
             <<source_polynomial
             <<'\n';

    std::istringstream source_line_stream(std::move(source_line));
    source_line_stream>>source_polynomial;
    if(!source_line_stream)
    {
        std::cerr<<STREAM_EXTRACTION_FAILURE_ERROR
                 <<std::endl;

        return false;
    }

    std::cout<<"Polynomial AFTER \"assign\" operation: "
             <<source_polynomial
             <<'\n';

    return true;
}

bool compare_equal_operation(system_polynomial& source_polynomial,
                             std::string&& source_line)
{
    std::cout<<"Performing \"compare_equal\" operation...\n";

    bool equal_to{};
    system_polynomial polynomial;
    std::istringstream source_line_stream(std::move(source_line));
    while(source_line_stream>>
          polynomial)
    {
        if(!source_line_stream)
        {
            std::cerr<<STREAM_EXTRACTION_FAILURE_ERROR
                     <<std::endl;

            return false;
        }

        equal_to=source_polynomial==polynomial;
        std::cout<<source_polynomial
                 <<(equal_to?
                    " EQUAL-TO ":
                    " NOT EQUAL-TO ")
                 <<polynomial
                 <<'\n';
    }

    return true;
}

bool compare_greater_operation(system_polynomial& source_polynomial,
                               std::string&& source_line)
{
    std::cout<<"Performing \"compare_greater\" operation...\n";

    bool greater_than{};
    system_polynomial polynomial;
    std::istringstream source_line_stream(std::move(source_line));
    while(source_line_stream>>
          polynomial)
    {
        if(!source_line_stream)
        {
            std::cerr<<STREAM_EXTRACTION_FAILURE_ERROR
                     <<std::endl;

            return false;
        }

        greater_than=source_polynomial>polynomial;
        std::cout<<source_polynomial
                 <<(greater_than?
                    " GREATER-THAN ":
                    " NOT GREATER-THAN ")
                 <<polynomial
                 <<'\n';
    }

    return true;
}

bool compare_greater_equal_operation(system_polynomial& source_polynomial,
                                     std::string&& source_line)
{
    std::cout<<"Performing \"compare_greater_equal\" operation...\n";

    bool greater_equal{};
    system_polynomial polynomial;
    std::istringstream source_line_stream(std::move(source_line));
    while(source_line_stream>>
          polynomial)
    {
        if(!source_line_stream)
        {
            std::cerr<<STREAM_EXTRACTION_FAILURE_ERROR
                     <<std::endl;

            return false;
        }

        greater_equal=source_polynomial>=polynomial;
        std::cout<<source_polynomial
                 <<(greater_equal?
                    " GREATER-THAN-OR-EQUAL-TO ":
                    " NOT GREATER-THAN-OR-EQUAL-TO ")
                 <<polynomial
                 <<'\n';
    }

    return true;
}

bool compare_less_operation(system_polynomial& source_polynomial,
                            std::string&& source_line)
{
    std::cout<<"Performing \"compare_less\" operation...\n";

    bool less_than{};
    system_polynomial polynomial;
    std::istringstream source_line_stream(std::move(source_line));
    while(source_line_stream>>
          polynomial)
    {
        if(!source_line_stream)
        {
            std::cerr<<STREAM_EXTRACTION_FAILURE_ERROR
                     <<std::endl;

            return false;
        }

        less_than=source_polynomial<polynomial;
        std::cout<<source_polynomial
                 <<(less_than?
                    " LESS-THAN ":
                    " NOT LESS-THAN ")
                 <<polynomial
                 <<'\n';
    }

    return true;
}

bool compare_less_equal_operation(system_polynomial& source_polynomial,
                                  std::string&& source_line)
{
    std::cout<<"Performing \"compare_less_equal\" operation...\n";

    bool less_equal{};
    system_polynomial polynomial;
    std::istringstream source_line_stream(std::move(source_line));
    while(source_line_stream>>
          polynomial)
    {
        if(!source_line_stream)
        {
            std::cerr<<STREAM_EXTRACTION_FAILURE_ERROR
                     <<std::endl;

            return false;
        }

        less_equal=source_polynomial<=polynomial;
        std::cout<<source_polynomial
                 <<(less_equal?
                    " LESS-THAN-OR-EQUAL-TO ":
                    " NOT LESS-THAN-OR-EQUAL-TO ")
                 <<polynomial
                 <<'\n';
    }

    return true;
}

bool compare_not_equal_operation(system_polynomial& source_polynomial,
                                 std::string&& source_line)
{
    std::cout<<"Performing \"compare_not_equal\" operation...\n";

    bool not_equal_to{};
    system_polynomial polynomial;
    std::istringstream source_line_stream(std::move(source_line));
    while(source_line_stream>>
          polynomial)
    {
        if(!source_line_stream)
        {
            std::cerr<<STREAM_EXTRACTION_FAILURE_ERROR
                     <<std::endl;

            return false;
        }

        not_equal_to=source_polynomial!=polynomial;
        std::cout<<source_polynomial
                 <<(not_equal_to?
                    " NOT-EQUAL-TO ":
                    " NOT NOT-EQUAL-TO ")
                 <<polynomial
                 <<'\n';
    }

    return true;
}

bool division_operation(system_polynomial& source_polynomial,
                        std::string&& source_line)
{
    std::cout<<"Performing \"division\" operation...\n";
    std::cout<<"Polynomial BEFORE \"division\" operation: "
             <<source_polynomial
             <<'\n';

    system_polynomial polynomial;
    std::istringstream source_line_stream(std::move(source_line));
    while(source_line_stream>>
          polynomial)
    {
        if(!source_line_stream)
        {
            std::cerr<<STREAM_EXTRACTION_FAILURE_ERROR
                     <<std::endl;

            return false;
        }

        source_polynomial/=polynomial;
    }

    std::cout<<"Polynomial AFTER \"division\" operation: "
             <<source_polynomial
             <<'\n';

    return true;
}

bool division_constant_operation(system_polynomial& source_polynomial,
                                 std::string&& source_line)
{
    std::cout<<"Performing \"division_constant\" operation...\n";
    std::cout<<"Polynomial BEFORE \"division_constant\" operation: "
             <<source_polynomial
             <<'\n';

    #ifdef DECIMAL_VERSION
        long double division_constant{};
    #else
        std::intmax_t division_constant{};
    #endif

    std::istringstream source_line_stream(std::move(source_line));
    while(source_line_stream>>
          division_constant)
    {
        if(!source_line_stream)
        {
            std::cerr<<STREAM_EXTRACTION_FAILURE_ERROR
                     <<std::endl;

            return false;
        }

        source_polynomial/=division_constant;
    }

    std::cout<<"Polynomial AFTER \"division_constant\" operation: "
             <<source_polynomial
             <<'\n';

    return true;
}

bool erase_operation(system_polynomial& source_polynomial,
                     std::string&& source_line)
{
    std::cout<<"Performing \"erase\" operation...\n";
    std::cout<<"Polynomial BEFORE \"erase\" operation: "
             <<source_polynomial
             <<'\n';

    char open_bracket_character{};
    char close_bracket_character{};
    std::uintmax_t erase_exponent{};

    #ifdef DECIMAL_VERSION
        long double erase_coefficient{};
    #else
        std::intmax_t erase_coefficient{};
    #endif

    std::istringstream source_line_stream(std::move(source_line));
    while(source_line_stream>>
          open_bracket_character>>
          erase_coefficient>>
          erase_exponent>>
          close_bracket_character)
    {
        if(open_bracket_character!='['||
           close_bracket_character!=']'||
           !source_line_stream)
        {
            std::cerr<<STREAM_EXTRACTION_FAILURE_ERROR
                     <<std::endl;

            return false;
        }

        source_polynomial.erase(erase_coefficient,
                                erase_exponent);
    }

    std::cout<<"Polynomial AFTER \"erase\" operation: "
             <<source_polynomial
             <<'\n';

    return true;
}

bool erase_exponent_operation(system_polynomial& source_polynomial,
                              std::string&& source_line)
{
    std::cout<<"Performing \"erase_exponent\" operation...\n";
    std::cout<<"Polynomial BEFORE \"erase_exponent\" operation: "
             <<source_polynomial
             <<'\n';

    std::uintmax_t erase_exponent{};
    std::istringstream source_line_stream(std::move(source_line));
    while(source_line_stream>>
          erase_exponent)
    {
        if(!source_line_stream)
        {
            std::cerr<<STREAM_EXTRACTION_FAILURE_ERROR
                     <<std::endl;

            return false;
        }

        source_polynomial.erase(erase_exponent);
    }

    std::cout<<"Polynomial AFTER \"erase_exponent\" operation: "
             <<source_polynomial
             <<'\n';

    return true;
}

bool evaluate_operation(system_polynomial& source_polynomial,
                        std::string&& source_line)
{
    std::cout<<"Performing \"evaluate\" operation...\n";

    #ifdef DECIMAL_VERSION
        long double evaluate_value{};
        long double evaluate_result{};
    #else
        std::intmax_t evaluate_value{};
        std::intmax_t evaluate_result{};
    #endif

    std::istringstream source_line_stream(std::move(source_line));
    while(source_line_stream>>
          evaluate_value)
    {
        if(!source_line_stream)
        {
            std::cerr<<STREAM_EXTRACTION_FAILURE_ERROR
                     <<std::endl;

            return false;
        }

        evaluate_result=source_polynomial(evaluate_value);
        std::cout<<source_polynomial
                 <<'('
                 <<evaluate_value
                 <<") = "
                 <<evaluate_result
                 <<'\n';
    }

    return true;
}

bool find_operation(system_polynomial& source_polynomial,
                    std::string&& source_line)
{
    std::cout<<"Performing \"find\" operation...\n";

    char open_bracket_character{};
    char close_bracket_character{};
    std::uintmax_t find_exponent{};

    #ifdef DECIMAL_VERSION
        long double find_coefficient{};
    #else
        std::intmax_t find_coefficient{};
    #endif

    bool term_found{};
    std::istringstream source_line_stream(std::move(source_line));
    while(source_line_stream>>
          open_bracket_character>>
          find_coefficient>>
          find_exponent>>
          close_bracket_character)
    {
        if(open_bracket_character!='['||
           close_bracket_character!=']'||
           !source_line_stream)
        {
            std::cerr<<STREAM_EXTRACTION_FAILURE_ERROR
                     <<std::endl;

            return false;
        }

        term_found=source_polynomial.find(find_coefficient,
                                          find_exponent);
        std::cout<<"Term \""
                 <<find_coefficient
                 <<source_polynomial.variant()
                 <<'^'
                 <<find_exponent
                 <<"\" "
                 <<(term_found?
                    "FOUND\n":
                    "NOT FOUND\n");
    }

    return true;
}

bool find_exponent_operation(system_polynomial& source_polynomial,
                             std::string&& source_line)
{
    std::cout<<"Performing \"find_exponent\" operation...\n";

    #ifdef DECIMAL_VERSION
        long double find_coefficient{};
    #else
        std::intmax_t find_coefficient{};
    #endif

    std::uintmax_t find_exponent{};
    std::istringstream source_line_stream(std::move(source_line));
    while(source_line_stream>>
          find_exponent)
    {
        if(!source_line_stream)
        {
            std::cerr<<STREAM_EXTRACTION_FAILURE_ERROR
                     <<std::endl;

            return false;
        }

        find_coefficient=source_polynomial.find(find_exponent);
        std::cout<<"Term with exponent \""
                 <<find_exponent
                 <<"\" "
                 <<(find_coefficient?
                    "FOUND\n":
                    "NOT FOUND\n");
    }

    return true;
}

bool insert_operation(system_polynomial& source_polynomial,
                      std::string&& source_line)
{
    std::cout<<"Performing \"insert\" operation...\n";
    std::cout<<"Polynomial BEFORE \"insert\" operation: "
             <<source_polynomial
             <<'\n';

    char open_bracket_character{};
    char close_bracket_character{};
    std::uintmax_t insert_exponent{};

    #ifdef DECIMAL_VERSION
        long double insert_coefficient{};
    #else
        std::intmax_t insert_coefficient{};
    #endif

    std::istringstream source_line_stream(std::move(source_line));
    while(source_line_stream>>
          open_bracket_character>>
          insert_coefficient>>
          insert_exponent>>
          close_bracket_character)
    {
        if(open_bracket_character!='['||
           close_bracket_character!=']'||
           !source_line_stream)
        {
            std::cerr<<STREAM_EXTRACTION_FAILURE_ERROR
                     <<std::endl;

            return false;
        }

        source_polynomial.insert(insert_coefficient,
                                 insert_exponent);
    }

    std::cout<<"Polynomial AFTER \"insert\" operation: "
             <<source_polynomial
             <<'\n';

    return true;
}

bool modulus_operation(system_polynomial& source_polynomial,
                       std::string&& source_line)
{
    std::cout<<"Performing \"modulus\" operation...\n";
    std::cout<<"Polynomial BEFORE \"modulus\" operation: "
             <<source_polynomial
             <<'\n';

    system_polynomial polynomial;
    std::istringstream source_line_stream(std::move(source_line));
    while(source_line_stream>>
          polynomial)
    {
        if(!source_line_stream)
        {
            std::cerr<<STREAM_EXTRACTION_FAILURE_ERROR
                     <<std::endl;

            return false;
        }

        source_polynomial%=polynomial;
    }

    std::cout<<"Polynomial AFTER \"modulus\" operation: "
             <<source_polynomial
             <<'\n';

    return true;
}

bool modulus_constant_operation(system_polynomial& source_polynomial,
                                std::string&& source_line)
{
    std::cout<<"Performing \"modulus_constant\" operation...\n";
    std::cout<<"Polynomial BEFORE \"modulus_constant\" operation: "
             <<source_polynomial
             <<'\n';

    #ifdef DECIMAL_VERSION
        long double modulus_constant{};
    #else
        std::intmax_t modulus_constant{};
    #endif

    std::istringstream source_line_stream(std::move(source_line));
    while(source_line_stream>>
          modulus_constant)
    {
        if(!source_line_stream)
        {
            std::cerr<<STREAM_EXTRACTION_FAILURE_ERROR
                     <<std::endl;

            return false;
        }

        source_polynomial%=modulus_constant;
    }

    std::cout<<"Polynomial AFTER \"modulus_constant\" operation: "
             <<source_polynomial
             <<'\n';

    return true;
}

bool multiplication_operation(system_polynomial& source_polynomial,
                              std::string&& source_line)
{
    std::cout<<"Performing \"multiplication\" operation...\n";
    std::cout<<"Polynomial BEFORE \"multiplication\" operation: "
             <<source_polynomial
             <<'\n';

    system_polynomial polynomial;
    std::istringstream source_line_stream(std::move(source_line));
    while(source_line_stream>>
          polynomial)
    {
        if(!source_line_stream)
        {
            std::cerr<<STREAM_EXTRACTION_FAILURE_ERROR
                     <<std::endl;

            return false;
        }

        source_polynomial*=polynomial;
    }

    std::cout<<"Polynomial AFTER \"multiplication\" operation: "
             <<source_polynomial
             <<'\n';

    return true;
}

bool multiplication_constant_operation(system_polynomial& source_polynomial,
                                       std::string&& source_line)
{
    std::cout<<"Performing \"multiplication_constant\" operation...\n";
    std::cout<<"Polynomial BEFORE \"multiplication_constant\" operation: "
             <<source_polynomial
             <<'\n';

    #ifdef DECIMAL_VERSION
        long double multiplication_constant{};
    #else
        std::intmax_t multiplication_constant{};
    #endif

    std::istringstream source_line_stream(std::move(source_line));
    while(source_line_stream>>
          multiplication_constant)
    {
        if(!source_line_stream)
        {
            std::cerr<<STREAM_EXTRACTION_FAILURE_ERROR
                     <<std::endl;

            return false;
        }

        source_polynomial*=multiplication_constant;
    }

    std::cout<<"Polynomial AFTER \"multiplication_constant\" operation: "
             <<source_polynomial
             <<'\n';

    return true;
}

bool negative_operation(system_polynomial& source_polynomial,
                        std::string&& source_line)
{
    std::cout<<"Performing \"negative\" operation...\n";
    if(!source_line.empty())
    {
        std::cerr<<"Error: argument(s) provided for operation"
                 <<std::endl;

        return false;
    }

    std::cout<<"Polynomial BEFORE \"negative\" operation: "
             <<source_polynomial
             <<'\n';

    source_polynomial=(-source_polynomial);

    std::cout<<"Polynomial AFTER \"negative\" operation: "
             <<source_polynomial
             <<'\n';

    return true;
}

bool output_operation(system_polynomial& source_polynomial,
                      std::string&& source_line)
{
    std::cout<<"Performing \"output\" operation...\n";
    if(!source_line.empty())
    {
        std::cerr<<ARGUMENTS_PROVIDED_ERROR
                 <<std::endl;

        return false;
    }

    std::cout<<"Polynomial: "
             <<source_polynomial
             <<'\n';

    return true;
}

bool positive_operation(system_polynomial& source_polynomial,
                        std::string&& source_line)
{
    std::cout<<"Performing \"positive\" operation...\n";
    if(!source_line.empty())
    {
        std::cerr<<ARGUMENTS_PROVIDED_ERROR
                 <<std::endl;

        return false;
    }

    std::cout<<"Polynomial BEFORE \"positive\" operation: "
             <<source_polynomial
             <<'\n';

    source_polynomial=(+source_polynomial);

    std::cout<<"Polynomial AFTER \"positive\" operation: "
             <<source_polynomial
             <<'\n';

    return true;
}

bool power_operation(system_polynomial& source_polynomial,
                     std::string&& source_line)
{
    std::cout<<"Performing \"power\" operation...\n";
    std::cout<<"Polynomial BEFORE \"power\" operation: "
             <<source_polynomial
             <<'\n';

    std::uintmax_t power_exponent{};
    std::istringstream source_line_stream(std::move(source_line));
    while(source_line_stream>>
          power_exponent)
    {
        if(!source_line_stream)
        {
            std::cerr<<STREAM_EXTRACTION_FAILURE_ERROR
                     <<std::endl;

            return false;
        }

        source_polynomial=power(source_polynomial,
                                power_exponent);
    }

    std::cout<<"Polynomial AFTER \"power\" operation: "
             <<source_polynomial
             <<'\n';

    return true;
}

bool subtraction_operation(system_polynomial& source_polynomial,
                           std::string&& source_line)
{
    std::cout<<"Performing \"subtraction\" operation...\n";
    std::cout<<"Polynomial BEFORE \"subtraction\" operation: "
             <<source_polynomial
             <<'\n';

    system_polynomial polynomial;
    std::istringstream source_line_stream(std::move(source_line));
    while(source_line_stream>>
          polynomial)
    {
        if(!source_line_stream)
        {
            std::cerr<<STREAM_EXTRACTION_FAILURE_ERROR
                     <<std::endl;

            return false;
        }

        source_polynomial-=polynomial;
    }

    std::cout<<"Polynomial AFTER \"subtraction\" operation: "
             <<source_polynomial
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
        {"assign",
         assign_operation},
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
        {"power",
         power_operation},
        {"subtraction",
         subtraction_operation}
    };

    std::unordered_map<std::string,
                       std::function<bool(system_polynomial&,
                                          std::string&&)>>::const_iterator system_operations_iterator;
    system_polynomial previous_source_polynomial;
    system_polynomial source_polynomial;

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

            continue;
        }

        previous_source_polynomial=source_polynomial;
        std::getline(polyt_operation_line_stream,
                     polyt_operation_line);
        if(!system_operations_iterator->second(source_polynomial,
                                               std::move(polyt_operation_line)))
        {
            source_polynomial=previous_source_polynomial;

            continue;
        }

        polyt_operation_line_stream.clear();
    }

    return EXIT_SUCCESS;
}
