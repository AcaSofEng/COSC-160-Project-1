#ifndef POLYNOMIAL_H_INCLUDED
#define POLYNOMIAL_H_INCLUDED

#include<cstddef>
#include<cstdlib>
#include<ios>
#include<istream>
#include<ostream>
#include<memory>
#include<utility>

template<typename coefficient_type,
         typename exponent_type=coefficient_type,
         const char variable='x',
         template<typename allocate_type> typename allocator_type=std::allocator>
class polynomial
{
    struct term
    {
        coefficient_type _coefficient;
        exponent_type _exponent;
        term* _next;

        term():_coefficient(),
               _exponent(),
               _next(){}

        template<typename forward_coefficient_type,
                 typename forward_exponent_type>
        term(forward_coefficient_type&& coefficient,
             forward_exponent_type&& exponent):_coefficient(std::forward<forward_coefficient_type>(coefficient)),
                                               _exponent(std::forward<forward_exponent_type>(exponent)),
                                               _next(){}

        template<typename forward_coefficient_type,
                 typename forward_exponent_type>
        term(forward_coefficient_type&& coefficient,
             forward_exponent_type&& exponent,
             term* next):_coefficient(std::forward<forward_coefficient_type>(coefficient)),
                         _exponent(std::forward<forward_exponent_type>(exponent)),
                         _next(next){}
    };

    allocator_type<term> _term_allocator;
    term* _front;
    std::size_t _size;

    void clear_terms()
    {
        for(term* clear_term(_front);
            clear_term;
            clear_term=_front)
        {
            _front=_front->_next;
            std::allocator_traits<allocator_type<term>>::destroy(_term_allocator,
                                                                 clear_term);
            _term_allocator.deallocate(clear_term,
                                       static_cast<std::size_t>(1));
        }
    }

    void copy_terms(const polynomial& copy_polynomial)
    {
        term* copy_term{};
        for(const term* copy_polynomial_term(copy_polynomial._front);
            copy_polynomial_term;
            copy_polynomial_term=copy_polynomial_term->_next)
        {
            if(!_front)
            {
                _front=_term_allocator.allocate(static_cast<std::size_t>(1));
                std::allocator_traits<allocator_type<term>>::construct(_term_allocator,
                                                                       _front,
                                                                       copy_polynomial_term->_coefficient,
                                                                       copy_polynomial_term->_exponent);
                copy_term=_front;
            }

            else
            {
                copy_term->_next=_term_allocator.allocate(static_cast<std::size_t>(1));
                std::allocator_traits<allocator_type<term>>::construct(_term_allocator,
                                                                       copy_term->_next,
                                                                       copy_polynomial_term->_coefficient,
                                                                       copy_polynomial_term->_exponent);
                copy_term=copy_term->_next;
            }
        }
    }

    void copy_terms(const std::initializer_list<std::pair<coefficient_type,
                                                          exponent_type>> initialize_term_list)
    {
        for(const std::pair<coefficient_type,
                            exponent_type>& initialize_term:initialize_term_list)
        {
            insert(initialize_term.first,
                   initialize_term.second);
        }
    }

    public:
        polynomial():_term_allocator(),
                     _front(),
                     _size(){}

        polynomial(const polynomial& copy_polynomial):_term_allocator(copy_polynomial._term_allocator),
                                                      _front(),
                                                      _size(copy_polynomial._size)
        {
            copy_terms(copy_polynomial);
        }

        polynomial(polynomial&& move_polynomial):_term_allocator(std::move(move_polynomial._term_allocator)),
                                                 _front(move_polynomial._front),
                                                 _size(move_polynomial._size)
        {
            move_polynomial._term_allocator=allocator_type<term>();
            move_polynomial._front=nullptr;
            move_polynomial._size=std::size_t();
        }

        polynomial(const std::initializer_list<std::pair<coefficient_type,
                                                         exponent_type>> initialize_term_list):polynomial()
        {
            copy_terms(initialize_term_list);
        }

        ~polynomial()
        {
            clear_terms();
        }

        polynomial& operator=(const polynomial& copy_assign_polynomial)
        {
            clear_terms();
            _term_allocator=copy_assign_polynomial._term_allocator;
            _size=copy_assign_polynomial._size;
            copy_terms(copy_assign_polynomial);

            return *this;
        }

        polynomial& operator=(polynomial&& move_assign_polynomial)
        {
            clear_terms();
            _term_allocator=std::move(move_assign_polynomial._term_allocator);
            _front=move_assign_polynomial._front;
            _size=move_assign_polynomial._size;

            move_assign_polynomial._term_allocator=allocator_type<term>();
            move_assign_polynomial._front=nullptr;
            move_assign_polynomial._size=std::size_t();

            return *this;
        }

        polynomial& operator=(const std::initializer_list<std::pair<coefficient_type,
                                                                    exponent_type>> initialize_term_list)
        {
            clear();
            copy_terms(initialize_term_list);

            return *this;
        }

        coefficient_type operator()(const coefficient_type& input_value) const
        {
            if(!_front)
            {
                return coefficient_type();
            }

            coefficient_type evaluate_value{};
            exponent_type evaluate_exponent{};

            const term* next_evaluate_term{};
            for(const term* evaluate_term(_front);
                evaluate_term;
                evaluate_term=evaluate_term->_next)
            {
                evaluate_value=evaluate_value*
                               input_value+
                               evaluate_term->_coefficient;

                evaluate_exponent=evaluate_term->_exponent;
                next_evaluate_term=evaluate_term->_next;
                while(evaluate_exponent)
                {
                    --evaluate_exponent;
                    if(next_evaluate_term&&
                       evaluate_exponent==next_evaluate_term->_exponent)
                    {
                        break;
                    }

                    evaluate_value*=input_value;
                }
            }

            return evaluate_value;
        }

        friend std::istream& operator>>(std::istream& input_stream,
                                        polynomial& input_polynomial)
        {
            input_polynomial.clear();

            char special_character('\0');
            input_stream>>special_character;
            if(special_character!='[')
            {
                input_stream.setstate(std::ios_base::failbit);

                return input_stream;
            }

            coefficient_type input_coefficient{};
            exponent_type input_exponent{};

            input_stream>>
            input_coefficient>>
            special_character>>
            special_character>>
            input_exponent;
            input_polynomial.insert(input_coefficient,
                                    input_exponent);

            char sign_character('\0');
            while(input_stream>>special_character)
            {
                if(special_character==']')
                {
                    break;
                }

                else if(special_character!='+'&&
                        special_character!='-')
                {
                    input_polynomial.clear();
                    input_stream.setstate(std::ios_base::failbit);

                    return input_stream;
                }

                sign_character=special_character;

                input_stream>>
                input_coefficient>>
                special_character>>
                special_character>>
                input_exponent;
                input_polynomial.insert(sign_character=='+'?
                                        input_coefficient:
                                        -input_coefficient,
                                        input_exponent);
            }

            return input_stream;
        }

        friend std::ostream& operator<<(std::ostream& output_stream,
                                        const polynomial& output_polynomial)
        {
            if(!output_polynomial._front)
            {
                return output_stream<<"[0"
                                    <<variable
                                    <<"^0]";
            }

            output_stream<<'[';

            bool negative_coefficient{};
            const coefficient_type zero_coefficient{};
            for(const term* output_term(output_polynomial._front);
                output_term;
                output_term=output_term->_next)
            {
                if(output_term==output_polynomial._front)
                {
                    output_stream<<output_term->_coefficient;
                }

                else
                {
                    negative_coefficient=output_term->_coefficient<zero_coefficient;
                    output_stream<<' '
                                 <<(negative_coefficient?
                                    '-':
                                    '+')
                                 <<' '
                                 <<(negative_coefficient?
                                    -output_term->_coefficient:
                                    output_term->_coefficient);
                }

                output_stream<<variable
                             <<'^'
                             <<output_term->_exponent;
            }

            return output_stream<<']';
        }

        polynomial operator+() const
        {
            return *this;
        }

        polynomial operator-() const
        {
            polynomial minus_polynomial(*this);
            for(term* minus_term(minus_polynomial._front);
                minus_term;
                minus_term=minus_term->_next)
            {
                minus_term->_coefficient=-minus_term->_coefficient;
            }

            return minus_polynomial;
        }

        polynomial operator+(const polynomial& addend_polynomial) const
        {
            polynomial sum_polynomial(*this);
            for(const term* addend_term(addend_polynomial._front);
                addend_term;
                addend_term=addend_term->_next)
            {
                sum_polynomial.insert(addend_term->_coefficient,
                                      addend_term->_exponent);
            }

            return sum_polynomial;
        }

        polynomial operator-(const polynomial& subtrahend_polynomial) const
        {
            polynomial difference_polynomial(*this);
            for(const term* subtrahend_term(subtrahend_polynomial._front);
                subtrahend_term;
                subtrahend_term=subtrahend_term->_next)
            {
                difference_polynomial.insert(-subtrahend_term->_coefficient,
                                             subtrahend_term->_exponent);
            }

            return difference_polynomial;
        }

        polynomial operator*(const polynomial& multiplier_polynomial) const
        {
            polynomial product_polynomial;
            for(const term* multiplicand_term(_front);
                multiplicand_term;
                multiplicand_term=multiplicand_term->_next)
            {
                for(const term* multiplier_term(multiplier_polynomial._front);
                    multiplier_term;
                    multiplier_term=multiplier_term->_next)
                {
                    product_polynomial.insert(multiplicand_term->_coefficient*
                                              multiplier_term->_coefficient,
                                              multiplicand_term->_exponent+
                                              multiplier_term->_exponent);
                }
            }

            return product_polynomial;
        }

        polynomial operator*(const coefficient_type& constant) const
        {
            if(!constant)
            {
                return polynomial();
            }

            polynomial product_polynomial(*this);
            for(term* product_term(product_polynomial._front);
                product_term;
                product_term=product_term->_next)
            {
                product_term->_coefficient*=constant;
            }

            return product_polynomial;
        }

        polynomial operator/(const polynomial& divisor_polynomial) const
        {
            polynomial quotient_polynomial;
            if(!divisor_polynomial._front)
            {
                return quotient_polynomial;
            }

            coefficient_type quotient_coefficient{};
            exponent_type quotient_exponent{};

            polynomial quotient_monomial;
            polynomial dividend_polynomial(*this);
            while(dividend_polynomial._front&&
                  dividend_polynomial._front->_exponent>=divisor_polynomial._front->_exponent)
            {
                quotient_coefficient=dividend_polynomial._front->_coefficient/
                                     divisor_polynomial._front->_coefficient;
                if(!quotient_coefficient)
                {
                    break;
                }

                quotient_exponent=dividend_polynomial._front->_exponent-
                                  divisor_polynomial._front->_exponent;

                quotient_monomial.insert(quotient_coefficient,
                                         quotient_exponent);
                quotient_polynomial.insert(quotient_coefficient,
                                           quotient_exponent);
                dividend_polynomial-=quotient_monomial*
                                     divisor_polynomial;
                quotient_monomial.clear();
            }

            return quotient_polynomial;
        }

        polynomial operator/(const coefficient_type& constant) const
        {
            const polynomial divisor_polynomial{{constant,
                                                 exponent_type()}};

            return *this/
                   divisor_polynomial;
        }

        polynomial operator%(const polynomial& divisor_polynomial) const
        {
            if(!divisor_polynomial._front)
            {
                return *this;
            }

            coefficient_type quotient_coefficient{};
            exponent_type quotient_exponent{};

            polynomial quotient_polynomial;
            polynomial modulus_polynomial(*this);
            while(modulus_polynomial._front&&
                  modulus_polynomial._front->_exponent>=divisor_polynomial._front->_exponent)
            {
                quotient_coefficient=modulus_polynomial._front->_coefficient/
                                     divisor_polynomial._front->_coefficient;
                if(!quotient_coefficient)
                {
                    break;
                }

                quotient_exponent=modulus_polynomial._front->_exponent-
                                  divisor_polynomial._front->_exponent;

                quotient_polynomial.insert(quotient_coefficient,
                                           quotient_exponent);
                modulus_polynomial-=quotient_polynomial*
                                    divisor_polynomial;
                quotient_polynomial.clear();
            }

            return modulus_polynomial;
        }

        polynomial operator%(const coefficient_type& constant) const
        {
            const polynomial divisor_polynomial{{constant,
                                                 exponent_type()}};

            return *this%
                   divisor_polynomial;
        }

        polynomial& operator+=(const polynomial& addend_polynomial)
        {
            for(const term* addend_term(addend_polynomial._front);
                addend_term;
                addend_term=addend_term->_next)
            {
                insert(addend_term->_coefficient,
                       addend_term->_exponent);
            }

            return *this;
        }

        polynomial& operator-=(const polynomial& subtrahend_polynomial)
        {
            for(const term* subtrahend_term(subtrahend_polynomial._front);
                subtrahend_term;
                subtrahend_term=subtrahend_term->_next)
            {
                insert(-subtrahend_term->_coefficient,
                       subtrahend_term->_exponent);
            }

            return *this;
        }

        polynomial& operator*=(const polynomial& multiplier_polynomial)
        {
            polynomial& product_polynomial(*this);

            return product_polynomial=product_polynomial*
                                      multiplier_polynomial;
        }

        polynomial& operator*=(const coefficient_type& constant)
        {
            if(!constant)
            {
                clear();

                return *this;
            }

            for(term* product_term(_front);
                product_term;
                product_term=product_term->_next)
            {
                product_term->_coefficient*=constant;
            }

            return *this;
        }

        polynomial& operator/=(const polynomial& divisor_polynomial)
        {
            polynomial& quotient_polynomial(*this);

            return quotient_polynomial=quotient_polynomial/
                                       divisor_polynomial;
        }

        polynomial& operator/=(const coefficient_type& constant)
        {
            polynomial& quotient_polynomial(*this);

            return quotient_polynomial=quotient_polynomial/
                                       constant;
        }

        polynomial& operator%=(const polynomial& divisor_polynomial)
        {
            polynomial& modulus_polynomial(*this);

            return modulus_polynomial=modulus_polynomial%
                                      divisor_polynomial;
        }

        polynomial& operator%=(const coefficient_type& constant)
        {
            polynomial& modulus_polynomial(*this);

            return modulus_polynomial=modulus_polynomial%
                                      constant;
        }

        bool operator<(const polynomial& comparate_polynomial) const
        {
            bool exponents_equal{};
            for(const term* compare_term(_front),
                *comparate_term(comparate_polynomial._front);
                compare_term&&
                comparate_term;
                compare_term=compare_term->_next,
                comparate_term=comparate_term->_next)
            {
                exponents_equal=compare_term->_exponent==comparate_term->_exponent;
                if(compare_term->_exponent<comparate_term->_exponent||
                  (compare_term->_coefficient<comparate_term->_coefficient&&
                   exponents_equal))
                {
                    return true;
                }

                else if(!exponents_equal||
                        compare_term->_coefficient!=comparate_term->_coefficient)
                {
                    return false;
                }
            }

            return _size<comparate_polynomial._size;
        }

        bool operator>(const polynomial& comparate_polynomial) const
        {
            return comparate_polynomial<*this;
        }

        bool operator<=(const polynomial& comparate_polynomial) const
        {
            return !(comparate_polynomial<*this);
        }

        bool operator>=(const polynomial& comparate_polynomial) const
        {
            return !(*this<comparate_polynomial);
        }

        bool operator==(const polynomial& comparate_polynomial) const
        {
            if(_size!=comparate_polynomial._size)
            {
                return false;
            }

            for(const term* compare_term(_front),
                *comparate_term(comparate_polynomial._front);
                compare_term&&
                comparate_term;
                compare_term=compare_term->_next,
                comparate_term=comparate_term->_next)
            {
                if(compare_term->_exponent!=comparate_term->_exponent||
                   compare_term->_coefficient!=comparate_term->_coefficient)
                {
                    return false;
                }
            }

            return true;
        }

        bool operator!=(const polynomial& comparate_polynomial) const
        {
            return !(*this==comparate_polynomial);
        }

        exponent_type degree() const
        {
            return _front?
                   _front->_exponent:
                   exponent_type();
        }

        std::size_t size() const
        {
            return _size;
        }

        char variant() const
        {
            return variable;
        }

        void clear()
        {
            clear_terms();
            _term_allocator=allocator_type<term>();
            _size=std::size_t();
        }

        template<typename forward_coefficient_type,
                 typename forward_exponent_type>
        bool insert(forward_coefficient_type&& coefficient,
                    forward_exponent_type&& exponent)
        {
            coefficient_type insert_coefficient(std::forward<forward_coefficient_type>(coefficient));
            if(!insert_coefficient)
            {
                return false;
            }

            else if(!_front)
            {
                _front=_term_allocator.allocate(static_cast<std::size_t>(1));
                std::allocator_traits<allocator_type<term>>::construct(_term_allocator,
                                                                       _front,
                                                                       std::move(insert_coefficient),
                                                                       std::forward<forward_exponent_type>(exponent));
                ++_size;

                return true;
            }

            term* previous_insert_term{};
            exponent_type insert_exponent(std::forward<forward_exponent_type>(exponent));
            for(term* insert_term(_front);
                insert_term;
                previous_insert_term=insert_term,
                insert_term=insert_term->_next)
            {
                if(insert_term->_exponent<insert_exponent)
                {
                    insert_term=_term_allocator.allocate(static_cast<std::size_t>(1));
                    std::allocator_traits<allocator_type<term>>::construct(_term_allocator,
                                                                           insert_term,
                                                                           std::move(insert_coefficient),
                                                                           std::move(insert_exponent),
                                                                           previous_insert_term?
                                                                           previous_insert_term->_next:
                                                                           _front);
                    if(previous_insert_term)
                    {
                        previous_insert_term->_next=insert_term;
                    }

                    else
                    {
                        _front=insert_term;
                    }

                    ++_size;

                    return true;
                }

                else if(insert_term->_exponent==insert_exponent)
                {
                    insert_term->_coefficient+=insert_coefficient;
                    if(!insert_term->_coefficient)
                    {
                        if(previous_insert_term)
                        {
                            previous_insert_term->_next=insert_term->_next;
                        }

                        else
                        {
                            _front=_front->_next;
                        }

                        std::allocator_traits<allocator_type<term>>::destroy(_term_allocator,
                                                                             insert_term);
                        _term_allocator.deallocate(insert_term,
                                                   static_cast<std::size_t>(1));
                        --_size;
                    }

                    return true;
                }
            }

            previous_insert_term->_next=_term_allocator.allocate(static_cast<std::size_t>(1));
            std::allocator_traits<allocator_type<term>>::construct(_term_allocator,
                                                                   previous_insert_term->_next,
                                                                   std::move(insert_coefficient),
                                                                   std::move(insert_exponent));
            ++_size;

            return true;
        }

        bool erase(const coefficient_type& coefficient,
                   const exponent_type& exponent)
        {
            for(term* previous_erase_term{},
                *erase_term(_front);
                erase_term;
                previous_erase_term=erase_term,
                erase_term=erase_term->_next)
            {
                if(erase_term->_coefficient==coefficient&&
                   erase_term->_exponent==exponent)
                {
                    if(previous_erase_term)
                    {
                        previous_erase_term->_next=erase_term->_next;
                    }

                    else
                    {
                        _front=_front->_next;
                    }

                    std::allocator_traits<allocator_type<term>>::destroy(_term_allocator,
                                                                         erase_term);
                    _term_allocator.deallocate(erase_term,
                                               static_cast<std::size_t>(1));
                    --_size;

                    return true;
                }
            }

            return false;
        }

        bool erase_exponent(const exponent_type& exponent)
        {
            for(term* previous_erase_term{},
                *erase_term(_front);
                erase_term;
                previous_erase_term=erase_term,
                erase_term=erase_term->_next)
            {
                if(erase_term->_exponent==exponent)
                {
                    if(previous_erase_term)
                    {
                        previous_erase_term->_next=erase_term->_next;
                    }

                    else
                    {
                        _front=_front->_next;
                    }

                    std::allocator_traits<allocator_type<term>>::destroy(_term_allocator,
                                                                         erase_term);
                    _term_allocator.deallocate(erase_term,
                                               static_cast<std::size_t>(1));
                    --_size;

                    return true;
                }
            }

            return false;
        }

        bool find(const coefficient_type& coefficient,
                  const exponent_type& exponent) const
        {
            for(const term* find_term(_front);
                find_term;
                find_term=find_term->_next)
            {
                if(find_term->_coefficient==coefficient&&
                   find_term->_exponent==exponent)
                {
                    return true;
                }
            }

            return false;
        }

        coefficient_type find_exponent(const exponent_type& exponent) const
        {
            for(const term* find_term(_front);
                find_term;
                find_term=find_term->_next)
            {
                if(find_term->_exponent==exponent)
                {
                    return find_term->_coefficient;
                }
            }

            return coefficient_type();
        }
};

template<typename coefficient_type,
         typename exponent_type,
         const char variable,
         template<typename allocate_type> typename allocator_type>
polynomial<coefficient_type,
           exponent_type,
           variable,
           allocator_type> operator*(const coefficient_type& constant,
                                     const polynomial<coefficient_type,
                                                      exponent_type,
                                                      variable,
                                                      allocator_type>& multiplicand_polynomial)
{
    return multiplicand_polynomial*
           constant;
}

template<typename coefficient_type,
         typename exponent_type,
         const char variable,
         template<typename allocate_type> typename allocator_type>
polynomial<coefficient_type,
           exponent_type,
           variable,
           allocator_type> power(const polynomial<coefficient_type,
                                                  exponent_type,
                                                  variable,
                                                  allocator_type>& base_polynomial,
                                 const coefficient_type& exponent)
{
    coefficient_type power_factor{};
    polynomial<coefficient_type,
               exponent_type,
               variable,
               allocator_type> power_polynomial{{++power_factor,
                                                 exponent_type()}};
    if(!exponent)
    {
        return power_polynomial;
    }

    coefficient_type power_exponent(exponent);
    polynomial<coefficient_type,
               exponent_type,
               variable,
               allocator_type> power_base_polynomial(base_polynomial);
    while(power_exponent)
    {
        if(power_exponent&
           power_factor)
        {
            power_polynomial*=power_base_polynomial;
        }

        power_base_polynomial*=power_base_polynomial;
        power_exponent>>=power_factor;
    }

    return power_polynomial;
}

#endif
