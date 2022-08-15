#ifndef R_MAP_ITERATOR_HPP
# define R_MAP_ITERATOR_HPP

namespace ft {

	template<class Iterator>
		class r_map_iterator {
			public:
				typedef typename Iterator::difference_type		difference_type;
				typedef typename Iterator::value_type			value_type;
				typedef typename Iterator::pointer				pointer;
				typedef typename Iterator::reference			reference;
				typedef typename Iterator::iterator_category	iterator_category;
				typedef typename Iterator::variable_type		variable_type;

			private:
				Iterator	_iterator;

			public:
				r_map_iterator(Iterator it = NULL): _iterator(it)
				{
				}

				template<class Iter>
				r_map_iterator(const r_map_iterator<Iter> &in) : _iterator(in.base())
				{
				}

				~r_map_iterator()
				{
				}

				r_map_iterator &operator=(const r_map_iterator &in)
				{
					this->_iterator = in.base();
					return (*this);
				}

				Iterator	base() const
				{
					return (_iterator);
				}

				variable_type &operator*()
				{
					Iterator temp(_iterator);
					--temp;
					return (*temp);
				}

				variable_type *operator->()
				{
					Iterator temp(_iterator);
					--temp;
					return (temp.operator->());
				}

				variable_type &operator*() const 
				{
					Iterator temp(_iterator);
					--temp;
					return (*temp);
				}

				variable_type *operator->() const
				{
					Iterator temp(_iterator);
					--temp;
					return (temp.operator->());
				}

				r_map_iterator &operator++()
				{
					--(_iterator);
					return (*this);
				}

				r_map_iterator &operator--()
				{
					++(_iterator);
					return (*this);
				}

				r_map_iterator	operator++(int)
				{
					r_map_iterator	temp = *this;
					++(*this);
					return (temp);
				}

				r_map_iterator	operator--(int)
				{
					r_map_iterator	temp = *this;
					--(*this);
					return (temp);
				}

				bool	operator==(const r_map_iterator &in)
				{
					return (this->base() == in.base());
				}

				bool	operator!=(const r_map_iterator &in)
				{
					return (this->base() != in.base());
				}

		};
}

#endif