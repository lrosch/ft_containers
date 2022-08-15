#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft {

		template<class T_node, class var_type , class var_type_no_const = var_type>
		class map_iterator {
			public:
				typedef ptrdiff_t						difference_type;
				typedef T_node							value_type;
				typedef T_node *						pointer;
				typedef T_node &						reference;
				typedef ft::bidirectional_iterator_tag	iterator_category;
				typedef var_type						variable_type;

			private:
				pointer	_ptr;

			public:

				map_iterator(pointer ptr = nullptr): _ptr(ptr)
				{
				}

				map_iterator(const map_iterator &in): _ptr(in._ptr)
				{
				}

				map_iterator(map_iterator<value_type, var_type_no_const, var_type_no_const> in): _ptr(in.base())
				{
				}

				~map_iterator()
				{
				}

				map_iterator	&operator=(const map_iterator &in)
				{
					this->_ptr = in.base();
					return *this;
				}

				pointer				base() const
				{ 
					return _ptr;
				}

				variable_type	&operator*()
				{
					return _ptr->val;
				}

				variable_type *operator->()
				{
					return &(operator*());
				}

				variable_type &operator*() const
				{
					return _ptr->val;
				}

				variable_type *operator->() const
				{
					return &(operator*());
				}

				map_iterator &operator++()
				{
					if (!_ptr)
						return *this;
					if (_ptr->right != NULL) {
						_ptr = _ptr->right;
						while (_ptr->left != NULL)
							_ptr = _ptr->left;
					}
					else {
						pointer	cur;
						cur = _ptr->parent;
						while (cur != NULL && cur->right == _ptr) {
							_ptr = cur;
							cur = _ptr->parent;
						}
						_ptr = cur;
					}
					return *this;
				}

				map_iterator &		operator--()
				{
					if (!_ptr)
						return *this;
					if (_ptr->left != NULL) {
						_ptr = _ptr->left;
						while (_ptr->right != NULL)
							_ptr = _ptr->right;
					}
					else {
						pointer	cur;
						cur = _ptr->parent;
						while (cur != NULL && cur->left == _ptr) {
							_ptr = cur;
							cur = _ptr->parent;
						}
						_ptr = cur;
					}
					return *this;
				}

				map_iterator		operator++(int)
				{
					map_iterator	temp = *this;
					++(*this);
					return temp;
				}

				map_iterator		operator--(int)
				{
					map_iterator	temp = *this;
					--(*this);
					return temp;
				}

				bool	operator==(const map_iterator &in)
				{
					return (this->base() == in.base());
				}

				bool	operator!=(const map_iterator &in)
				{
					return (this->base() != in.base());
				}

		};
}

#endif