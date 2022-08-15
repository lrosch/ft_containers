/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrosch <lrosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 15:41:42 by lrosch            #+#    #+#             */
/*   Updated: 2022/08/04 14:38:10 by lrosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

#include "vector_iterator.hpp"
#include <typeinfo>
#include <iostream>

namespace ft
{
	template <class Iterator>
	ptrdiff_t distance(Iterator first, Iterator last)
	{
		ptrdiff_t i = 0;
		while (first != last)
		{
			i++;
			first++;
		}
		return (i);
	}

	template<class InputIt1, class InputIt2>
	bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
	{
		for (; first1 != last1; ++first1, ++first2)
		{
			if (!(*first1 == *first2))
			{
				return false;
			}
		}
		return true;
	}

	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
	while (first1 != last1)
	{
		if (first2 == last2 || *first2 < *first1)
			return (false);
		else if (*first1 < *first2)
			return (true);
		first1++;
		first2++;
	}
	return (first2 != last2);
	}

	template <class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || !comp(*first2, *first1)) 
				return (false);
			else if (!comp(*first1, *first2)) 
				return (true);
			first1++;
			first2++;
		}
		return (first2 != last2);
	}

	template<class T1, class T2>
	struct pair
	{
		public:
			typedef T1							first_type;
			typedef T2							second_type;
		
		private:
			typedef std::allocator<first_type>	allocator_first;
			typedef std::allocator<second_type>	allocator_second;
			allocator_first		_alloc_first;
			allocator_second	_alloc_second;

		public:
			first_type 			first;
			second_type 		second;

		pair() : first(), second()
		{
		}

		template <class T, class U>
		pair(const pair<T, U> &other) : first(other.first), second(other.second)
		{
		}

		pair (const first_type& a, const second_type& b): first(a), second(b)
		{
		}

		pair &operator=(const pair &other)
		{
			_alloc_first.construct(&this->first, other.first);
			_alloc_second.construct(&this->second, other.second);
			return (*this);
		}
	};

	template <class T, class U>
	bool operator== (const ft::pair<T,U>& lhs, const ft::pair<T,U>& rhs)
	{ 
		return lhs.first==rhs.first && lhs.second==rhs.second;
	}

	template <class T, class U>
	bool operator!= (const ft::pair<T,U>& lhs, const ft::pair<T,U>& rhs)
	{ 
		return !(lhs == rhs); 
	}

	template <class T, class U>
	bool operator<  (const ft::pair<T,U>& lhs, const ft::pair<T,U>& rhs)
	{ 
		return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); 
	}

	template <class T, class U>
	bool operator<= (const ft::pair<T,U>& lhs, const ft::pair<T,U>& rhs)
	{
		return !(rhs < lhs); 
	}

	template <class T, class U>
	bool operator>  (const ft::pair<T,U>& lhs, const ft::pair<T,U>& rhs)
	{
		return rhs<lhs;
	}

	template <class T, class U>
	bool operator>= (const ft::pair<T,U>& lhs, const ft::pair<T,U>& rhs)
	{
		return !(lhs<rhs);
	}

	template <class T1,class T2>
	ft::pair<T1,T2> make_pair (T1 x, T2 y)
	{
		return ( ft::pair<T1,T2>(x,y) );
	}
}
#endif
