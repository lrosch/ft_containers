/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrosch <lrosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 15:41:37 by lrosch            #+#    #+#             */
/*   Updated: 2022/08/04 15:37:53 by lrosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP

#include <iostream>
#include <stdexcept>
#include "vector_iterator.hpp"
#include "r_vector_iterator.hpp"
#include "is_integral_enable_if.hpp"
#include "utils.hpp"

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class vector
	{
		public:
			typedef T											value_type;
			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef typename std::ptrdiff_t						difference_type;
			typedef typename allocator_type::size_type			size_type;
			typedef	vector_iterator<value_type>					iterator;
			typedef	vector_iterator<const value_type>			const_iterator;
			typedef	r_vector_iterator<iterator>					reverse_iterator;
			typedef	r_vector_iterator<const_iterator>			const_reverse_iterator;

		private:
			size_type		_size;
			size_type		_capacity;
			pointer			_array;
			allocator_type	_alloc;

		public:
			explicit vector(const allocator_type& alloc = allocator_type())
			{
				_alloc = alloc;
				this->_size = 0;
				this->_capacity = 0;
				this->_array = this->_alloc.allocate(0);
			}

			explicit vector(size_type count, const value_type& value = value_type(), const allocator_type& alloc = allocator_type())
			{
				this->_size = count;
				this->_capacity = this->_size;
				this->_alloc = alloc;
				this->_array = this->_alloc.allocate(count);
				for (size_type i = 0; i < count; i++)
					this->_array[i] = value;
			}

			template <class InputIterator>
			vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename enable_if<!is_integral<InputIterator>::val, InputIterator>::type = InputIterator())
			{
				this->_alloc = alloc;
				ptrdiff_t dis = ft::distance(first, last);
				if (dis < 0)
				{
					_alloc = alloc;
					this->_size = 0;
					this->_capacity = 0;
					this->_array = this->_alloc.allocate(0);
					return ;
				}
				this->_array = this->_alloc.allocate(dis);
				this->_capacity = dis;
				this->_size = dis;
				for (ptrdiff_t i = 0; i < dis; i++, first++)
					this->_alloc.construct((this->_array + i), *first);
			}

			vector(const vector &other)
			{
				this->_alloc = other._alloc;
				this->_capacity = other._capacity;
				this->_size = other._size;
				this->_array = this->_alloc.allocate(this->_size);
				for (size_type i = 0; i < this->_size; i++)
					this->_alloc.construct(this->_array + i, other._array[i]);
			}

			~vector()
			{
				for (size_type i = 0; i < this->_size; i++)
					this->_alloc.destroy(this->_array + i);
				this->_alloc.deallocate(this->_array, this->_capacity);
			}

			vector &operator=(const vector &other)
			{
				for(size_type i = 0; i < this->_size; i++)
					this->_alloc.destroy(this->_array + i);
				if (this->_capacity > 0)
					this->_alloc.deallocate(this->_array, this->_capacity);
				this->_capacity = other._capacity;
				this->_size = other._size;
				this->_array = this->_alloc.allocate(this->_size);
				for (size_type i = 0; i < this->_size; i++)
					this->_alloc.construct(this->_array + i, other._array[i]);
				return (*this);
			}

			reference operator[] (size_type n)
			{
				return (this->_array[n]);
			}

			const_reference operator[] (size_type n) const
			{
				return (this->_array[n]);
			}

			size_type	size(void) const
			{
				return (this->_size);
			}

			size_type	max_size(void) const
			{
				return (this->_alloc.max_size());
			}

			void	reserve(size_type n)
			{
				if (n > this->_alloc.max_size())
					throw length_error();
				if (n >= this->_capacity)
				{
					pointer tmp = this->_alloc.allocate(n * 2);
					for (size_type i = 0; i < this->_size; i++)
						this->_alloc.construct(tmp + i, this->_array[i]);
					for(size_type i = 0; i < this->_size; i++)
						this->_alloc.destroy(this->_array + i);
					this->_alloc.deallocate(this->_array, this->_capacity);
					this->_array = tmp;
					this->_capacity = n * 2;
				}
			}

			void	resize(size_type n, value_type val = value_type())
			{
				if (n < this->_size)
				{
					for (size_type i = this->_size; i > n; i--)
						this->_alloc.destroy(this->_array + i);
					this->_size = n;
					return ;
				}
				if (n > this->_capacity)
					reserve(n);
				if (n > this->_size)
				{
					for (size_type i = this->_size; i < n; i++)
						this->_alloc.construct(this->_array + i, val);
					this->_size = n;
				}
			}

			size_type	capacity() const
			{
				return (this->_capacity);
			}

			bool empty() const
			{
				if (this->_size > 0)
					return (false);
				else
					return (true);
			}

			reference at(size_type n)
			{
				if (n < this->_size)
					return (this->_array[n]);
				else
					throw std::out_of_range("Catch out_of_range exception!");
			}

			const_reference at(size_type n) const
			{
				if (n < this->_size)
					return (this->_array[n]);
				else
					throw std::out_of_range("Catch out_of_range exception!");
			}

			reference front()
			{
				if (this->_size == 0)
					throw empty_container();
				return(this->_array[0]);
			}

			const_reference front() const
			{
				if (this->_size == 0)
					throw empty_container();
				return(this->_array[0]);
			}

			reference back()
			{
				if (this->_size == 0)
					throw empty_container();
				return (this->_array[this->_size - 1]);
			}

			const_reference back() const
			{
				if (this->_size == 0)
					throw empty_container();
				return (this->_array[this->_size - 1]);
			}

			template <class InputIterator>
  			void assign (InputIterator first, InputIterator last,  typename enable_if<!is_integral<InputIterator>::val, InputIterator>::type = InputIterator())
			{
				ptrdiff_t dif = ft::distance(first, last);
				if (dif < 0)
					return ;
				if (dif > (ptrdiff_t)this->_capacity)
				{
					this->_alloc.deallocate(this->_array, this->_capacity);
				this->_array = this->_alloc.allocate(dif);
				for (ptrdiff_t i = 0; i < dif; i++, first++)
					this->_alloc.construct(this->_array + i, *(first));
				this->_capacity = dif;
				this->_size = dif;
				}
				else
				{
					clear();
					for (size_t i = 0; first != last; i++)
					{
						this->_alloc.construct(&this->_array[i], *first);
						first++;
					}
					this->_size = dif;
				}
			}


			void	assign(size_type n, const value_type &val)
			{
				if (n > this->_capacity)
				{
					pointer	tmp = this->_alloc.allocate(n);
					for (size_t i = 0; i < n; i++)
						this->_alloc.construct(&tmp[i], val);
					for (size_t i = 0; i < this->_size; i++)
						this->_alloc.destroy(&this->_array[i]);
					this->_alloc.deallocate(this->_array, this->_capacity);
					this->_array = tmp;
					this->_size = n;
					this->_capacity = n;
				}
				else
				{
					for (size_t i = 0; i < this->_size; i++)
						this->_alloc.destroy(&this->_array[i]);
					for (size_t i = 0; i < n; i++)
						this->_alloc.construct(&this->_array[i], val);
					this->_size = n;
				}
			}


			void	push_back(const value_type &val)
			{
				if (this->_capacity > this->_size) 
				{
					this->_alloc.construct(this->_array + this->_size, val);
					this->_size++;
				}
				else if (this->_capacity == 0 && this->_size == 0) 
				{
					pointer	tmp = this->_alloc.allocate(1);
					this->_alloc.deallocate(this->_array, this->_capacity);
					this->_array = tmp;
					this->_alloc.construct(this->_array + this->_size, val);
					this->_capacity++;
					this->_size++;
				}
				else if (this->_capacity == this->_size) 
				{
					pointer	tmp = this->_alloc.allocate(this->_capacity * 2);
					for (size_t i = 0; i < this->_size; i++)
						this->_alloc.construct(tmp + i, this->_array[i]);
					for (size_t i = 0; i < this->_size; i++)
						this->_alloc.destroy(&this->_array[i]);
					this->_alloc.deallocate(this->_array, this->_capacity);
					this->_array = tmp;
					this->_alloc.construct(this->_array + this->_size, val);
					this->_capacity *= 2;
					this->_size++;
				}
			}

			void	pop_back()
			{
				if (this->_size == 0)
					throw empty_container();
				this->_alloc.destroy(this->_array + this->_size - 1);
				this->_size--;
			}

			iterator insert (iterator position, const value_type& val)
			{
				ptrdiff_t dif;

				dif = ft::distance(begin(), position);
				if (position == end())
				{
					if (this->_capacity < this->_size + 1)
						reserve((this->_capacity + 1) * 2);
					this->_alloc.construct(this->_array + this->_size, val);
					this->_size++;
					return (this->_array + dif);
				}
				else if (dif < 0)
				{
					if (this->_capacity < this->_size + 1)
						reserve((this->_capacity + 1) * 2);
					value_type tmp2;
					value_type tmp = this->_array[0];
					for (size_type i = 0; i < this->_size; i++)
					{
						tmp2 = this->_array[i + 1];
						this->_alloc.construct(this->_array + i + 1, tmp);
						tmp = tmp2;
					}
					this->_array[0] = 0;
					this->_size++;
					return (this->_array);
				}
				else if ((size_type)dif > this->_size)
				{
					while((size_type)dif > this->_capacity)
						reserve((this->_capacity + 1) * 2);
					this->_size = dif;
					dif--;
					this->_alloc.construct(this->_array + dif, val);
				}
				else
				{
					if (this->_capacity < this->_size + 1)
						reserve((this->_capacity + 1) * 2);
					value_type tmp = this->_array[dif];
					this->_array[dif] = val;
					value_type tmp2;
					for (size_type i = dif + 1; i <= this->_size; i++)
					{
						tmp2 = this->_array[i];
						this->_alloc.construct(this->_array + i, tmp);
						tmp = tmp2;
					}
					this->_size++;
				}
				return (this->_array + dif);
			}

			void insert (iterator position, size_type n, const value_type& val)
			{
				ptrdiff_t index = ft::distance(begin(), position);
				if (this->_capacity <= this->_size + n)
					this->reserve(this->_size + n);
				for (ptrdiff_t i = this->_size - 1; i >= index; i--)
					this->_alloc.construct(this->_array + i + n, this->_array[i]);
				for (size_t i = 0; i < n; i++,index++)
					this->_alloc.construct(this->_array + index, val);
				this->_size += n;
				return;
			}

			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last,  typename enable_if<!is_integral<InputIterator>::val, InputIterator>::type = InputIterator())
			{
				if (first == last)
					return ;
				ptrdiff_t n = ft::distance(first, last);
				if (n < 0)
					return ;
				ptrdiff_t dif = ft::distance(begin(), position);
				if (position == end())
				{
					if (n + this->_size > this->_capacity)
						reserve(this->_capacity + n);
					for (ptrdiff_t i = 0; i < n; i++, first++)
						this->_alloc.construct(this->_array + this->_size + i, *first);
					this->_size += n;
					return ;
				}
				else if (dif < 0)
				{
					if (dif + n > 0)
					{
						ptrdiff_t to_insert = dif + n;
						if (to_insert + this->_size > this->_capacity)
							reserve(this->_capacity + to_insert);
						value_type tmp = this->_array[0];
						value_type tmp2;
						for (size_type i = 0; i < this->_size; i++)
						{
							tmp2 = this->_array[i];
							this->_alloc.construct(this->_array + i + n, tmp);
							tmp = tmp2;
						}
						for (ptrdiff_t i = 0; i < to_insert; i++, first++)
							this->_alloc.construct(this->_array + i, *first);
						for (ptrdiff_t i = to_insert; i < n; i++)
							this->_alloc.construct(this->_array + i, 0);
						this->_size += n;
						return ;
					}
				}
				else if ((size_type)dif > this->_size)
				{
					if (this->_size + dif > this->_capacity)
						reserve(this->_capacity + dif);
					this->_size = dif + n;
					for (ptrdiff_t i = 0; i < n; i++, first++)
						this->_alloc.construct(this->_array + i + dif, *first);
				}
				else
				{
					if (this->_capacity <= this->_size + n)
						this->reserve(this->_size + n);
					for (difference_type i = this->_size - 1; i >= dif; i--)
						this->_alloc.construct(this->_array + i + n, this->_array[i]);
					for (; first != last; ++dif, ++first)
						this->_alloc.construct(this->_array + dif, *first);
					this->_size += n;
					return;
				}
			}

			iterator erase(iterator position)
			{
				iterator out(position);
				iterator pos1(position);
				pos1++;
				ptrdiff_t dif = ft::distance(position, end());
				for(ptrdiff_t i = 0; i < dif; i++, position++, pos1++)
					*position = *pos1;
				this->_size--;
				return out;
			}

			iterator erase(iterator first, iterator last)
			{
				iterator out(last);
				while (last != end())
				{
					*first = *last;
					++first;
					++last;
				}
				difference_type range = ft::distance(first, last);
				this->_size -= range;
				return (out - range);
			}

			void	swap(vector &other)
			{
				size_type		tmp_size;
				size_type		tmp_capacity;
				pointer			tmp_array;
				allocator_type	tmp_alloc;

				tmp_size = other._size;
				tmp_capacity = other._capacity;
				tmp_array = other._array;
				tmp_alloc = other._alloc;
				other._size = this->_size;
				other._capacity = this->_capacity;
				other._array = this->_array;
				other._alloc = this->_alloc;
				this->_size = tmp_size;
				this->_capacity = tmp_capacity;
				this->_array = tmp_array;
				this->_alloc = tmp_alloc;
			}

			void	clear()
			{
				for(size_type i = 0; i < this->_size; i++)
					this->_alloc.destroy(this->_array + i);
				this->_size = 0;
			}

			allocator_type get_allocator() const
			{
				return (this->_alloc);
			}

			iterator	begin()
			{
				return (iterator(this->_array));
			}

			const_iterator	begin() const
			{
				return (const_iterator(this->_array));
			}

			iterator end()
			{
				return(iterator(this->_array + this->_size));
			}

			const_iterator end() const
			{
				return(const_iterator(this->_array + this->_size));
			}

			reverse_iterator	rbegin()
			{
				return (reverse_iterator(this->_array + this->_size));
			}

			const_reverse_iterator rbegin() const
			{
				return (const_reverse_iterator(this->_array + this->_size));
			}

			reverse_iterator	rend()
			{
				return (reverse_iterator(this->_array));
			}

			const_reverse_iterator	rend() const
			{
				return (const_reverse_iterator(this->_array));
			}

			class empty_container: public std::exception
			{
				const char * what () const throw ()
				{
					return "error: container is empty";
				}
			};

			class length_error: public std::exception
			{
				const char * what () const throw ()
				{
					return "Length error: n > max_size";
				}
			};
	}; // vector

	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (!(lhs.size() == rhs.size()))
			return (false);
		return (equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (!(lhs == rhs))
			return (true);
		return (false);
	}

	template <class T, class Alloc>
	bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if ((lhs < rhs) || (lhs == rhs))
			return (true);
		return (false);
	}

	template <class T, class Alloc>
	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (rhs < lhs)
			return (true);
		return (false);
	}

	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (!(lhs < rhs))
			return (true);
		return (false);
	}
}; // ft

#endif