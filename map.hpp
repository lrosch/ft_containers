#ifndef MAP_H
# define MAP_H

# include <iostream>
# include "rbtree.hpp"


namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
	class map
	{
		//typedef member types
		public:

		typedef Key												key_type;
		typedef T												mapped_type;
		typedef ft::pair<const Key, T>							value_type;
		typedef Compare											key_compare;
		typedef Alloc											allocator_type;
		typedef value_type &									reference;
		typedef const value_type &								const_reference;
		typedef value_type *									pointer;
		typedef const value_type *								const_pointer;
		typedef ft::RBTree<Key,T,Compare,Alloc>					RBTree;
		typedef typename RBTree::iterator						iterator;
		typedef typename RBTree::const_iterator					const_iterator;
		typedef typename RBTree::reverse_iterator				reverse_iterator;
		typedef typename RBTree::const_reverse_iterator			const_reverse_iterator;
		typedef typename std::ptrdiff_t							difference_type;
		typedef std::size_t										size_type;

		class value_compare
		{
			friend class map;
		protected:
			key_compare comp;
			value_compare (key_compare c) : comp(c) {}
			value_compare () {}
		public:
			bool operator() (const value_type& x, const value_type& y) const
			{
				return comp(x.first, y.first);
			}
		};

		private:
			key_compare		_comp;
			value_compare	_v_comp;
			allocator_type	_alloc;
			size_type		_size;
			RBTree			_tree;

		public:
			explicit map (const key_compare & comp = key_compare(), const allocator_type & alloc = allocator_type())
			{
				this->_alloc = alloc;
				this->_comp = comp;
				this->_size = 0;
			}

			template <class InputIterator>
			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type & alloc = allocator_type())
			{
				this->_alloc = alloc;
				this->_comp = comp;
				this->_size = 0;
				for (; first != last; first++)
					insert(ft::make_pair(first->first, first->second));
			}

			map (const map &x) : _size(0)
			{
				*this = x;
			}


			map &operator=(const map &x)
			{
				if (*this != x)
				{
					if (this->_size != 0)
						this->clear();
					if (x.size() > 0)
						insert(x.begin(), x.end());
					this->_alloc = x.get_allocator();
					this->_comp = x.key_comp();
					this->_size = x.size();
					this->_v_comp = x.value_comp();
				}
				return (*this);
			}

			~map()
			{
				clear();
			}


			iterator	begin() 
			{ 
				return (_tree.begin());
			}

			const_iterator begin() const 
			{ 
				return (_tree.begin());
			}

			iterator	end() 
			{
				return (_tree.end());
			}

			const_iterator end() const 
			{
				return (_tree.end());
			}

			reverse_iterator rbegin() 
			{
				return (_tree.rbegin());
			}

			const_reverse_iterator	rbegin() const
			{
				return (_tree.rbegin());
			}

			reverse_iterator	rend()
			{
				return (_tree.rend());
			}

			const_reverse_iterator	rend() const
			{
				return (_tree.rend());
			}


			ft::pair<iterator,bool> insert (const value_type &val)
			{
				ft::pair<iterator,bool> tmp = _tree.insert(val);
				if (tmp.second == true)
					_size++;
				return (tmp);
			}

			iterator insert (iterator position, const value_type &val)
			{
				ft::pair<iterator,bool> tmp = _tree.insert(position, val);
				if (tmp.second == true)
					_size++;
				return (tmp.first);
			}

			template <class InputIterator>
			void insert (InputIterator first, InputIterator last)
			{
				ft::pair<iterator, bool> tmp;
				for (;first != last; first++)
				{
					tmp = _tree.insert(ft::make_pair(first->first, first->second));
					if (tmp.second == true)
						_size++;
				}
			}

			size_type size() const
			{
				return (this->_size);
			}

			size_type max_size() const
			{
				return (_tree.max_size());
			}

			bool empty() const
			{
				return (!size());
			}

			mapped_type & operator[] (const key_type &k)
			{
				return ((*((this->insert(ft::make_pair(k,mapped_type()))).first)).second);
			}

			value_compare value_comp() const
			{
				return (this->_v_comp);
			}

			key_compare key_comp() const
			{
				return (this->_comp);
			}

			allocator_type get_allocator() const
			{
				return (this->_alloc);
			}

			void clear()
			{
				if (this->_size > 0)
					erase(begin(), end());
			}

			void swap (map &x)
			{
				RBTree temp_tree = this->_tree;
				key_compare	tmp_cmp = this->_comp;
				allocator_type tmp_alloc = this->_alloc;
				size_type tmp_size = this->_size;
				this->_tree = x._tree;
				this->_comp = x.key_comp();
				this->_alloc = x.get_allocator();
				this->_size = x.size();
				x._tree = temp_tree;
				x._comp = tmp_cmp;
				x._alloc = tmp_alloc;
				x._size = tmp_size;
			}

			size_type count (const key_type &k) const
			{
				return (_tree.count(k));
			}

			iterator find (const key_type &k)
			{
				return (_tree.find(k));
			}

			const_iterator find (const key_type &k) const
			{
				return (_tree.find(k));
			}

			iterator lower_bound (const key_type &k)
			{
				return (_tree.lower_bound(k));
			}

			const_iterator lower_bound (const key_type &k) const
			{
				return (_tree.lower_bound(k));
			}

			iterator upper_bound (const key_type &k)
			{
				return (_tree.upper_bound(k));
			}

			const_iterator upper_bound (const key_type &k) const
			{
				return (_tree.upper_bound(k));
			}

			ft::pair<const_iterator,const_iterator> equal_range (const key_type &k) const
			{
				return (_tree.equal_range(k));
			}

			ft::pair<iterator,iterator> equal_range (const key_type &k)
			{
				return (_tree.equal_range(k));
			}

			void erase (iterator position)
			{
				_tree.erase(position);
				_size--;
			}

			size_type erase (const key_type & k)
			{
				iterator tmp = find(k);
				if (tmp != end())
				{
					erase(tmp);
					return (1);
				}
				return (0);
			}

			void erase(iterator first, iterator last)
			{
				key_type next = first->first;
				key_type curr;
				while (first != last)
				{
					first = find(next);
					curr = first->first;
					first++;
					if (first == NULL)
						break;
					next = first->first;
					erase(curr);
				}
			}
	};

	template <class T, class U>
	bool	operator==(const map<T,U> &lhs, const map<T,U> &rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class T, class U>
	bool	operator!=(const map<T,U> &lhs, const map<T,U> &rhs)
	{
		if (lhs.size() != rhs.size())
			return (true);
		return (!ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class T, class U>
	bool	operator<(const map<T,U> &lhs, const map<T,U> &rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class U>
	bool	operator<=(const map<T,U> &lhs, const map<T,U> &rhs)
	{
		if (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()))
			return (true);
		if (ft::equal(lhs.begin(), lhs.end(), rhs.begin()) && (lhs.size() <= rhs.size()))
			return (true);
		return (false);
	}

	template <class T, class U>
	bool	operator>(const map<T,U> &lhs, const map<T,U> &rhs)
	{
		return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
	}

	template <class T, class U>
	bool	operator>=(const map<T,U> &lhs, const map<T,U> &rhs)
	{
		if (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()))
			return (true);
		if (ft::equal(lhs.begin(), lhs.end(), rhs.begin()) && (lhs.size() >= rhs.size()))
			return (true);
		return (false);
	}

}

#endif
