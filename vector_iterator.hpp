/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrosch <lrosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 15:44:32 by lrosch            #+#    #+#             */
/*   Updated: 2022/08/03 18:12:30 by lrosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft
{
	template <class T>
	class vector_iterator
	{
		public:
			typedef iterator<random_access_iterator_tag, T>							iterator_type;
			typedef typename iterator_traits<iterator_type>::difference_type		difference_type;
			typedef	typename iterator_traits<iterator_type>::value_type				value_type;
			typedef typename iterator_traits<iterator_type>::pointer				pointer;
			typedef typename iterator_traits<iterator_type>::reference				reference;
			typedef typename iterator_traits<iterator_type>::iterator_category		iterator_category;

		private:
			pointer _ptr;

		public:
			vector_iterator()
			{
				this->_ptr = nullptr;
			}
			
			vector_iterator(pointer other)
			{
				this->_ptr = other;
			}

			vector_iterator(const vector_iterator &other)
			{
				this->_ptr = other._ptr;
			}

			~vector_iterator()
			{
			}

			pointer	base() const
			{
				return (this->_ptr);
			}

			reference	operator[](int n)
			{
				return (*(operator+(n)));
			}

			vector_iterator &operator=(const vector_iterator &other)
			{
				this->_ptr = other._ptr;
				return (*this);
			}

			reference operator*()
			{
				return (*this->_ptr);
			}

			pointer operator->()
			{
				return (this->_ptr);
			}

			vector_iterator &operator++()
			{
				++this->_ptr;
				return (*this);
			}

			vector_iterator operator++(int)
			{
				vector_iterator tmp(this->_ptr);
				++this->_ptr;
				return (tmp);
			}

			vector_iterator &operator--()
			{
				this->_ptr--;
				return (*this);
			}

			vector_iterator operator--(int)
			{
				vector_iterator tmp(this->_ptr);
				this->_ptr--;
				return (tmp);
			}

			difference_type operator-(vector_iterator &other)
			{
				return (this->_ptr - other._ptr);
			}

			vector_iterator operator-(int n)
			{
				return (vector_iterator(this->_ptr - n));
			}

			vector_iterator operator+(vector_iterator &other)
			{
				difference_type tmp = this->_ptr - other._ptr;
				this->_ptr += tmp;
				return (*this);
			}

			vector_iterator operator+(int n)
			{
				return (vector_iterator(this->_ptr + n));
			}

			vector_iterator &operator+=(int n)
			{
				this->_ptr = this->_ptr + n;
				return (*this);
			}

			vector_iterator &operator-=(int n)
			{
				this->_ptr = this->_ptr - n;
				return (*this);
			}

			operator	vector_iterator<const T>() const
			{
				return (vector_iterator<const T>(base()));
			}
	};

	template <class T>
	vector_iterator<T>	operator+(const typename vector_iterator<T>::difference_type offset, const vector_iterator<T>& r_it )
	{
		return (vector_iterator<T>(r_it.base() + offset));
	}

	template <class T, class U>
	typename ft::vector_iterator<T>::difference_type	operator-( const vector_iterator<T>& lhs, const vector_iterator<U>& rhs )
	{
		return (lhs.base() - rhs.base());
	}

	template <class T, class U>
	bool operator==(const vector_iterator<T> &lhs, const vector_iterator<U> &rhs)
	{
		if (lhs.base() == rhs.base())
			return (true);
		return (false);
	}

	template <class T, class U>
	bool operator!=(const vector_iterator<T> &lhs, const vector_iterator<U> &rhs)
	{
		if (!(lhs.base() == rhs.base()))
			return (true);
		return (false);
	}

	template <class T, class U>
	bool operator<=(const vector_iterator<T> &lhs, const vector_iterator<U> &rhs)
	{
		if ((lhs.base() < rhs.base()) || (lhs.base() == rhs.base()))
			return (true);
		return (false);
	}

	template <class T, class U>
	bool operator>=(const vector_iterator<T> &lhs, const vector_iterator<U> &rhs)
	{
		if (!(lhs.base() < rhs.base()))
			return (true);
		return (false);
	}

	template <class T, class U>
	bool operator<(const vector_iterator<T> &lhs, const vector_iterator<U> &rhs)
	{
		if (lhs.base() < rhs.base())
			return (true);
		return (false);
	}

	template <class T, class U>
	bool operator>(const vector_iterator<T> &lhs, const vector_iterator<U> &rhs)
	{
		if (rhs.base() < lhs.base())
			return (true);
		return (false);
	}
}

#endif

