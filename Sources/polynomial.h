#ifndef POLYNOMIAL_H_INCLUDED
#define POLYNOMIAL_H_INCLUDED

#include<cstddef>
#include<cstdlib>
#include<initializer_list>
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

        template<typename forward_coefficient_type,
                 typename forward_exponent_type>
        term(forward_coefficient_type&& source_coefficient,
             forward_exponent_type&& source_exponent):_coefficient(std::forward<forward_coefficient_type>(source_coefficient)),
                                                      _exponent(std::forward<forward_exponent_type>(source_exponent)),
                                                      _next(){}

        template<typename forward_coefficient_type,
                 typename forward_exponent_type>
        term(forward_coefficient_type&& source_coefficient,
             forward_exponent_type&& source_exponent,
             term* const source_next):_coefficient(std::forward<forward_coefficient_type>(source_coefficient)),
                                      _exponent(std::forward<forward_exponent_type>(source_exponent)),
                                      _next(source_next){}
    };

    allocator_type<term> _term_allocator;
    std::size_t _size;
    term* _front;

    void clear_terms(term* source_front)
    {
        for(term* clear_term(source_front);
            clear_term;
            clear_term=source_front)
        {
            source_front=source_front->_next;
            std::allocator_traits<allocator_type<term>>::destroy(_term_allocator,
                                                                 clear_term);
            _term_allocator.deallocate(clear_term,
                                       static_cast<std::size_t>(1));
        }
    }

    term* copy_terms(const term* source_front)
    {
        if(!source_front)
        {
            return nullptr;
        }

        term* copy_front(_term_allocator.allocate(static_cast<std::size_t>(1)));
        std::allocator_traits<allocator_type<term>>::construct(_term_allocator,
                                                               copy_front,
                                                               source_front->_coefficient,
                                                               source_front->_exponent);
        source_front=source_front->_next;

        for(term* copy_term(copy_front);
            source_front;
            copy_term=copy_term->_next,
            source_front=source_front->_next)
        {
            copy_term->_next=_term_allocator.allocate(static_cast<std::size_t>(1));
            std::allocator_traits<allocator_type<term>>::construct(_term_allocator,
                                                                   copy_term->_next,
                                                                   source_front->_coefficient,
                                                                   source_front->_exponent);
        }

        return copy_front;
    }

    void insert_terms(const std::initializer_list<const std::pair<coefficient_type,
                                                                  exponent_type>>& source_initializer_list)
    {
        for(const std::pair<coefficient_type,
                            exponent_type>& source_pair:source_initializer_list)
        {
            insert(source_pair.first,
                   source_pair.second);
        }
    }

    public:
        polynomial():_term_allocator(),
                     _size(),
                     _front(){}

        polynomial(const polynomial& source_polynomial):_term_allocator(source_polynomial._term_allocator),
                                                        _size(source_polynomial._size),
                                                        _front(copy_terms(source_polynomial._front)){}

        polynomial(polynomial&& source_polynomial):polynomial()
        {
            std::swap(_term_allocator,
                      source_polynomial._term_allocator);
            std::swap(_size,
                      source_polynomial._size);
            std::swap(_front,
                      source_polynomial._front);
        }

        polynomial(const std::initializer_list<const std::pair<coefficient_type,
                                                               exponent_type>>& source_initializer_list):polynomial()
        {
            insert_terms(source_initializer_list);
        }

        ~polynomial()
        {
            clear_terms(_front);
        }

        polynomial& operator=(const polynomial& source_polynomial)
        {
            _term_allocator=source_polynomial._term_allocator;
            _size=source_polynomial._size;

            if(!_front)
            {
                _front=copy_terms(source_polynomial._front);
            }

            else if(!source_polynomial._front)
            {
                clear_terms(_front);
                _front=nullptr;
            }

            else
            {
                term* previous_copy_term{};
                term* copy_term(_front);
                const term* source_front(source_polynomial._front);
                for(;
                    copy_term&&
                    source_front;
                    source_front=source_front->_next)
                {
                    copy_term->_coefficient=source_front->_coefficient;
                    copy_term->_exponent=source_front->_exponent;
                    previous_copy_term=copy_term;
                    copy_term=copy_term->_next;
                }

                if(copy_term)
                {
                    previous_copy_term->_next=nullptr;
                    clear_terms(copy_term);
                }

                else if(source_front)
                {
                    previous_copy_term->_next=copy_terms(source_front);
                }
            }

            return *this;
        }

        polynomial& operator=(polynomial&& source_polynomial)
        {
            std::swap(_term_allocator,
                      source_polynomial._term_allocator);
            std::swap(_size,
                      source_polynomial._size);
            std::swap(_front,
                      source_polynomial._front);

            return *this;
        }

        polynomial& operator=(const std::initializer_list<const std::pair<coefficient_type,
                                                                          exponent_type>>& source_initializer_list)
        {
            clear();
            insert_terms(source_initializer_list);

            return *this;
        }

        coefficient_type operator()(const coefficient_type& source_value) const
        {
            if(!_front)
            {
                return coefficient_type();
            }

            coefficient_type evaluate_value{};
            exponent_type evaluate_exponent{};
            for(const term* evaluate_term(_front);
                evaluate_term;
                evaluate_term=evaluate_term->_next)
            {
                evaluate_value=evaluate_value*
                               source_value+
                               evaluate_term->_coefficient;

                evaluate_exponent=evaluate_term->_exponent;
                while(evaluate_exponent)
                {
                    --evaluate_exponent;
                    if(evaluate_term->_next&&
                       evaluate_exponent==evaluate_term->_next->_exponent)
                    {
                        break;
                    }

                    evaluate_value*=source_value;
                }
            }

            return evaluate_value;
        }

        polynomial operator+() const
        {
            return *this;
        }

        polynomial operator-() const
        {
            polynomial unary_minus_polynomial(*this);
            for(term* unary_minus_term(unary_minus_polynomial._front);
                unary_minus_term;
                unary_minus_term=unary_minus_term->_next)
            {
                unary_minus_term->_coefficient=-unary_minus_term->_coefficient;
            }

            return unary_minus_polynomial;
        }

        polynomial operator+(const polynomial& source_polynomial) const
        {
            polynomial sum_polynomial(*this);
            for(const term* source_term(source_polynomial._front);
                source_term;
                source_term=source_term->_next)
            {
                sum_polynomial.insert(source_term->_coefficient,
                                      source_term->_exponent);
            }

            return sum_polynomial;
        }

        polynomial operator-(const polynomial& source_polynomial) const
        {
            polynomial difference_polynomial(*this);
            for(const term* source_term(source_polynomial._front);
                source_term;
                source_term=source_term->_next)
            {
                difference_polynomial.insert(-source_term->_coefficient,
                                             source_term->_exponent);
            }

            return difference_polynomial;
        }

        polynomial operator*(const polynomial& source_polynomial) const
        {
            polynomial product_polynomial;
            for(const term* this_term(_front);
                this_term;
                this_term=this_term->_next)
            {
                for(const term* source_term(source_polynomial._front);
                    source_term;
                    source_term=source_term->_next)
                {
                    product_polynomial.insert(this_term->_coefficient*
                                              source_term->_coefficient,
                                              this_term->_exponent+
                                              source_term->_exponent);
                }
            }

            return product_polynomial;
        }

        polynomial operator*(const coefficient_type& source_constant) const
        {
            if(!source_constant)
            {
                return polynomial();
            }

            polynomial product_polynomial(*this);
            for(term* product_term(product_polynomial._front);
                product_term;
                product_term=product_term->_next)
            {
                product_term->_coefficient*=source_constant;
            }

            return product_polynomial;
        }

        polynomial operator/(const polynomial& source_polynomial) const
        {
            if(!source_polynomial._front)
            {
                return polynomial();
            }

            coefficient_type quotient_coefficient{};
            exponent_type quotient_exponent{};

            polynomial quotient_monomial;
            polynomial quotient_polynomial;
            polynomial dividend_polynomial(*this);
            while(dividend_polynomial._front&&
                  dividend_polynomial._front->_exponent>=source_polynomial._front->_exponent)
            {
                quotient_coefficient=dividend_polynomial._front->_coefficient/
                                     source_polynomial._front->_coefficient;
                if(!quotient_coefficient)
                {
                    break;
                }

                quotient_exponent=dividend_polynomial._front->_exponent-
                                  source_polynomial._front->_exponent;

                quotient_monomial.insert(quotient_coefficient,
                                         quotient_exponent);
                quotient_polynomial.insert(quotient_coefficient,
                                           quotient_exponent);
                dividend_polynomial-=quotient_monomial*
                                     source_polynomial;
                quotient_monomial.clear();
            }

            return quotient_polynomial;
        }

        polynomial operator/(const coefficient_type& source_constant) const
        {
            const polynomial divisor_polynomial{{source_constant,
                                                 exponent_type()}};

            return *this/
                   divisor_polynomial;
        }

        polynomial operator%(const polynomial& source_polynomial) const
        {
            if(!source_polynomial._front)
            {
                return *this;
            }

            coefficient_type quotient_coefficient{};
            exponent_type quotient_exponent{};

            polynomial quotient_polynomial;
            polynomial modulus_polynomial(*this);
            while(modulus_polynomial._front&&
                  modulus_polynomial._front->_exponent>=source_polynomial._front->_exponent)
            {
                quotient_coefficient=modulus_polynomial._front->_coefficient/
                                     source_polynomial._front->_coefficient;
                if(!quotient_coefficient)
                {
                    break;
                }

                quotient_exponent=modulus_polynomial._front->_exponent-
                                  source_polynomial._front->_exponent;

                quotient_polynomial.insert(quotient_coefficient,
                                           quotient_exponent);
                modulus_polynomial-=quotient_polynomial*
                                    source_polynomial;
                quotient_polynomial.clear();
            }

            return modulus_polynomial;
        }

        polynomial operator%(const coefficient_type& source_constant) const
        {
            const polynomial divisor_polynomial{{source_constant,
                                                 exponent_type()}};

            return *this%
                   divisor_polynomial;
        }

        polynomial& operator+=(const polynomial& source_polynomial)
        {
            for(const term* source_term(source_polynomial._front);
                source_term;
                source_term=source_term->_next)
            {
                insert(source_term->_coefficient,
                       source_term->_exponent);
            }

            return *this;
        }

        polynomial& operator-=(const polynomial& source_polynomial)
        {
            for(const term* source_term(source_polynomial._front);
                source_term;
                source_term=source_term->_next)
            {
                insert(-source_term->_coefficient,
                       source_term->_exponent);
            }

            return *this;
        }

        polynomial& operator*=(const polynomial& source_polynomial)
        {
            return *this=(*this)*
                         source_polynomial;
        }

        polynomial& operator*=(const coefficient_type& source_constant)
        {
            if(!source_constant)
            {
                clear();
            }

            else
            {
                for(term* this_term(_front);
                    this_term;
                    this_term=this_term->_next)
                {
                    this_term->_coefficient*=source_constant;
                }
            }

            return *this;
        }

        polynomial& operator/=(const polynomial& source_polynomial)
        {
            return *this=*this/
                         source_polynomial;
        }

        polynomial& operator/=(const coefficient_type& source_constant)
        {
            return *this=*this/
                         source_constant;
        }

        polynomial& operator%=(const polynomial& source_polynomial)
        {
            return *this=*this%
                         source_polynomial;
        }

        polynomial& operator%=(const coefficient_type& source_constant)
        {
            return *this=*this%
                         source_constant;
        }

        bool operator<(const polynomial& source_polynomial) const
        {
            for(const term* this_term(_front),
                *source_term(source_polynomial._front);
                this_term&&
                source_term;
                this_term=this_term->_next,
                source_term=source_term->_next)
            {
                if(this_term->_exponent<source_term->_exponent||
                  (this_term->_coefficient<source_term->_coefficient&&
                   this_term->_exponent==source_term->_exponent))
                {
                    return true;
                }

                else if(this_term->_exponent!=source_term->_exponent||
                        this_term->_coefficient!=source_term->_coefficient)
                {
                    return false;
                }
            }

            return _size<source_polynomial._size;
        }

        bool operator>(const polynomial& source_polynomial) const
        {
            return source_polynomial<*this;
        }

        bool operator<=(const polynomial& source_polynomial) const
        {
            return !(source_polynomial<*this);
        }

        bool operator>=(const polynomial& source_polynomial) const
        {
            return !(*this<source_polynomial);
        }

        bool operator==(const polynomial& source_polynomial) const
        {
            if(_size!=source_polynomial._size)
            {
                return false;
            }

            for(const term* this_term(_front),
                *source_term(source_polynomial._front);
                this_term&&
                source_term;
                this_term=this_term->_next,
                source_term=source_term->_next)
            {
                if(this_term->_exponent!=source_term->_exponent||
                   this_term->_coefficient!=source_term->_coefficient)
                {
                    return false;
                }
            }

            return true;
        }

        bool operator!=(const polynomial& source_polynomial) const
        {
            return !(*this==source_polynomial);
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
            clear_terms(_front);
            _term_allocator=allocator_type<term>();
            _size=std::size_t();
            _front=nullptr;
        }

        template<typename forward_coefficient_type,
                 typename forward_exponent_type>
        bool insert(forward_coefficient_type&& source_coefficient,
                    forward_exponent_type&& source_exponent)
        {
            coefficient_type insert_coefficient(std::forward<forward_coefficient_type>(source_coefficient));
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
                                                                       std::forward<forward_exponent_type>(source_exponent));
                ++_size;

                return true;
            }

            exponent_type insert_exponent(std::forward<forward_exponent_type>(source_exponent));

            term* previous_insert_term{};
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

        bool erase(const coefficient_type& source_coefficient,
                   const exponent_type& source_exponent)
        {
            for(term* previous_erase_term{},
                *erase_term(_front);
                erase_term;
                previous_erase_term=erase_term,
                erase_term=erase_term->_next)
            {
                if(erase_term->_coefficient==source_coefficient&&
                   erase_term->_exponent==source_exponent)
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

        bool erase(const exponent_type& source_exponent)
        {
            for(term* previous_erase_term{},
                *erase_term(_front);
                erase_term;
                previous_erase_term=erase_term,
                erase_term=erase_term->_next)
            {
                if(erase_term->_exponent==source_exponent)
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

        bool find(const coefficient_type& source_coefficient,
                  const exponent_type& source_exponent) const
        {
            for(const term* this_term(_front);
                this_term;
                this_term=this_term->_next)
            {
                if(this_term->_coefficient==source_coefficient&&
                   this_term->_exponent==source_exponent)
                {
                    return true;
                }
            }

            return false;
        }

        coefficient_type find(const exponent_type& source_exponent) const
        {
            for(const term* this_term(_front);
                this_term;
                this_term=this_term->_next)
            {
                if(this_term->_exponent==source_exponent)
                {
                    return this_term->_coefficient;
                }
            }

            return coefficient_type();
        }

        friend std::ostream& operator<<(std::ostream& source_ostream,
                                        const polynomial& source_polynomial)
        {
            if(!source_polynomial._front)
            {
                return source_ostream<<"[0"
                                     <<variable
                                     <<"^0]";
            }

            source_ostream<<'[';

            for(const term* source_term(source_polynomial._front);
                source_term;
                source_term=source_term->_next)
            {
                if(source_term==source_polynomial._front)
                {
                    source_ostream<<source_term->_coefficient;
                }

                else
                {
                    if(source_term->_coefficient<coefficient_type())
                    {
                        source_ostream<<" - "
                                      <<-source_term->_coefficient;
                    }

                    else
                    {
                        source_ostream<<" + "
                                      <<source_term->_coefficient;
                    }
                }

                source_ostream<<variable
                              <<'^'
                              <<source_term->_exponent;
            }

            return source_ostream<<']';
        }
};

template<typename source_coefficient_type,
         typename source_exponent_type,
         const char source_variable,
         template<typename source_allocate_type> typename source_allocator_type>
std::istream& operator>>(std::istream& source_istream,
                         polynomial<source_coefficient_type,
                                    source_exponent_type,
                                    source_variable,
                                    source_allocator_type>& source_polynomial)
{
    source_polynomial.clear();

    char special_character{};
    source_istream>>special_character;
    if(special_character!='[')
    {
        source_istream.setstate(std::ios_base::failbit);

        return source_istream;
    }

    source_coefficient_type input_coefficient{};
    source_exponent_type input_exponent{};

    source_istream>>
    input_coefficient>>
    special_character>>
    special_character>>
    input_exponent;
    source_polynomial.insert(input_coefficient,
                             input_exponent);

    char sign_character{};
    while(source_istream>>special_character)
    {
        if(special_character==']')
        {
            break;
        }

        else if(special_character!='+'&&
                special_character!='-')
        {
            source_polynomial.clear();
            source_istream.setstate(std::ios_base::failbit);

            return source_istream;
        }

        sign_character=special_character;

        source_istream>>
        input_coefficient>>
        special_character>>
        special_character>>
        input_exponent;
        source_polynomial.insert(sign_character=='+'?
                                 input_coefficient:
                                 -input_coefficient,
                                 input_exponent);
    }

    return source_istream;
}

template<typename source_coefficient_type,
         typename source_exponent_type,
         const char source_variable,
         template<typename source_allocate_type> typename source_allocator_type>
polynomial<source_coefficient_type,
           source_exponent_type,
           source_variable,
           source_allocator_type> operator*(const source_coefficient_type& source_constant,
                                            const polynomial<source_coefficient_type,
                                                             source_exponent_type,
                                                             source_variable,
                                                             source_allocator_type>& source_polynomial)
{
    return source_polynomial*
           source_constant;
}

template<typename source_coefficient_type,
         typename source_exponent_type,
         const char source_variable,
         template<typename source_allocate_type> typename source_allocator_type>
polynomial<source_coefficient_type,
           source_exponent_type,
           source_variable,
           source_allocator_type> power(const polynomial<source_coefficient_type,
                                                         source_exponent_type,
                                                         source_variable,
                                                         source_allocator_type>& source_polynomial,
                                        const source_exponent_type& source_exponent)
{
    source_exponent_type power_factor{};
    ++power_factor;

    polynomial<source_coefficient_type,
               source_exponent_type,
               source_variable,
               source_allocator_type> power_polynomial{{static_cast<source_coefficient_type>(power_factor),
                                                        source_exponent_type()}};
    if(!source_exponent)
    {
        return power_polynomial;
    }

    source_exponent_type exponent_factor(source_exponent);
    polynomial<source_coefficient_type,
               source_exponent_type,
               source_variable,
               source_allocator_type> base_polynomial(source_polynomial);
    while(exponent_factor)
    {
        if(exponent_factor&
           power_factor)
        {
            power_polynomial*=base_polynomial;
        }

        base_polynomial*=base_polynomial;
        exponent_factor>>=power_factor;
    }

    return power_polynomial;
}

#endif
