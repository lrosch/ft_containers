/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_vector_iterator.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrosch <lrosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 19:37:11 by lrosch            #+#    #+#             */
/*   Updated: 2022/07/28 11:49:24 by lrosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef R_VECTOR_ITERATOR
#define R_VECTOR_ITERATOR

#include "vector_iterator.hpp"

namespace ft
{
	template <class iterator>
	class r_vector_iterator
	{
		public:
			typedef typename iterator::difference_type		difference_type;
			typedef	typename iterator::value_type			value_type;
			typedef typename iterator::pointer				pointer;
			typedef typename iterator::reference				reference;
			typedef typename iterator::iterator_category		iterator_category;
		private:
			iterator _iterator;
		
		public:
			r_vector_iterator(): _iterator()
			{
			}
			
			explicit r_vector_iterator(iterator other): _iterator(other)
			{
			}

			template <class iter>
			r_vector_iterator(const r_vector_iterator<iter> &other)
			{
				this->_iterator = other.base();
			}

			iterator	base() const
			{
				return (this->_iterator);
			}

			reference	operator[](int n)
			{
				return (*(base() - n - 1));
			}
			
			r_vector_iterator &operator=(const r_vector_iterator<iterator> &other)
			{
				this->_iterator = other.base();
				return (*this);
			}

			reference operator*()
			{
				iterator tmp(_iterator);
				--tmp;
				return (*tmp);
			}

			pointer operator->()
			{
				iterator tmp(_iterator);
				--tmp;
				return (tmp.operator->());
			}

			r_vector_iterator &operator++()
			{
				this->_iterator--;
				return (*this);
			}

			r_vector_iterator operator++(int)
			{
				r_vector_iterator tmp(this->_iterator);
				this->_iterator--;
				return (tmp);
			}

			r_vector_iterator &operator--()
			{
				this->_iterator++;
				return (*this);
			}

			r_vector_iterator operator--(int)
			{
				r_vector_iterator tmp(this->_iterator);
				this->_iterator++;
				return (tmp);
			}

			r_vector_iterator operator+(int n)
			{
				return (r_vector_iterator(this->_iterator - n));
			}

			r_vector_iterator &operator+=(int n)
			{
				this->_iterator -= n;
				return (*this);
			}

			r_vector_iterator &operator-=(int n)
			{
				this->_iterator += n;
				return (*this);
			}
	};

	template < class T, class U >
	typename r_vector_iterator<T>::difference_type	operator-( const r_vector_iterator<T>& first, const r_vector_iterator<U>& second )
	{
		return (second.base() - first.base());
	}

	template < class T >
	r_vector_iterator<T>	operator-( const r_vector_iterator<T>& rit, const typename r_vector_iterator<T>::difference_type offset )
	{
		return r_vector_iterator<T>(rit.base() + offset);
	}

	template < class T>
	r_vector_iterator<T>	operator+( const typename r_vector_iterator<T>::difference_type offset, const r_vector_iterator<T>& rit )
	{
		return r_vector_iterator<T>(rit.base() - offset);
	}

	template <class T, class U>
	bool operator==(const r_vector_iterator<T> &lhs, const r_vector_iterator<U> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <class T, class U>
	bool operator!=(const r_vector_iterator<T> &lhs, const r_vector_iterator<U> &rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <class T, class U>
	bool operator<=(const r_vector_iterator<T> &lhs, const r_vector_iterator<U> &rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template <class T, class U>
	bool operator>=(const r_vector_iterator<T> &lhs, const r_vector_iterator<U> &rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <class T, class U>
	bool operator<(const r_vector_iterator<T> &lhs, const r_vector_iterator<U> &rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <class T, class U>
	bool operator>(const r_vector_iterator<T> &lhs, const r_vector_iterator<U> &rhs)
	{
		return (lhs.base() < rhs.base());
	}
}

#endif