#ifndef STACK_HPP
#define STACK_HPP

# include <iostream>
# include <string>
# include <memory>
# include <cstddef>
# include <algorithm>
#include "iterator_traits.hpp"
#include "vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack 
	{
		public:
			typedef Container							container_type;
			typedef typename Container::value_type		value_type;
			typedef typename Container::size_type		size_type;
			typedef typename Container::reference		reference;
			typedef typename Container::const_reference	const_reference;
		
		private:
			container_type c;

		public:
			explicit stack( const container_type& ctnr = container_type() ) : c(ctnr) {}

			bool				empty() const { return (size() == 0); }

			size_type			size() const { return c.size(); }

			void				push( const value_type& val ) { c.push_back(val); }

			void				pop() { if (size()) {c.pop_back(); } }

			value_type &		top() { return c.back(); }

			const value_type &	top() const { return c.back(); }

			template <class X, class TContainer>
			friend bool	operator==( const stack<X,TContainer>& lhs, const stack<X,TContainer>& rhs );

			template <class X, class TContainer>
			friend bool	operator!=( const stack<X,TContainer>& lhs, const stack<X,TContainer>& rhs );

			template <class X, class TContainer>
			friend bool	operator<( const stack<X,TContainer>& lhs, const stack<X,TContainer>& rhs );

			template <class X, class TContainer>
			friend bool	operator<=( const stack<X,TContainer>& lhs, const stack<X,TContainer>& rhs );

			template <class X, class TContainer>
			friend bool	operator>( const stack<X,TContainer>& lhs, const stack<X,TContainer>& rhs );

			template <class X, class TContainer>
			friend bool	operator>=( const stack<X,TContainer>& lhs, const stack<X,TContainer>& rhs );
	}; // stack

	template< class T, class Container >
	bool operator>=( const stack<T,Container>& lhs, const stack<T,Container>& rhs )
	{
		return lhs.c >= rhs.c;
	}
	
	template< class T, class Container >
	bool operator>( const stack<T,Container>& lhs, const stack<T,Container>& rhs )
	{
		return lhs.c > rhs.c;
	}

	template< class T, class Container >
	bool operator<=( const stack<T,Container>& lhs, const stack<T,Container>& rhs )
	{
		return lhs.c <= rhs.c;
	}

	template< class T, class Container>
	bool operator<( const stack<T,Container>& lhs, const stack<T,Container>& rhs )
	{
		return lhs.c < rhs.c;
	}

	template< class T, class Container >
	bool operator!=( const stack<T,Container>& lhs, const stack<T,Container>& rhs )
	{
		return lhs.c != rhs.c;
	}

	template< class T, class Container >
	bool operator==( const stack<T,Container>& lhs, const stack<T,Container>& rhs )
	{
		return lhs.c == rhs.c;
	}
} // ft
#endif