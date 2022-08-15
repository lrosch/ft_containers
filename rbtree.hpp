#ifndef RBTREE_H
# define RBTREE_H

#include <iostream>
#include <queue>
#include "utils.hpp"
#include "iterator_traits.hpp"
#include "map_iterator.hpp"
#include "r_map_iterator.hpp"

enum color {
	BLACK,
	RED,
};

namespace ft {

	template<class T>
	class node {

		public:
			typedef		T	value_type;

		public:
			value_type		val;
			color			colour;
			node			*left;
			node			*right;
			node			*parent;

			node(value_type val): val(val)
			{
				parent = left = right = NULL;
				colour = RED;
			}

			node & operator=(const node &in) 
			{
				val = in.val;
				colour = in.colour;
				left = in.left;
				right = in.right;
				parent = in.parent;
				return (*this);
			}

			node()
			{
				parent = NULL;
				left = NULL;
				right = NULL;
				colour = RED;
			}

			node	*uncle()
			{
				if (parent == NULL || parent->parent == NULL)
					return NULL;
				if (parent->isOnLeft())
					return parent->parent->right;
				else
					return parent->parent->left;
			}

			bool	isOnLeft()
			{
				return (this == parent->left);
			}

			node	*sibling()
			{
				if (parent == NULL)
					return NULL;
				if (isOnLeft())
					return parent->right;
				return parent->left;
			}

			void	moveDown( node *nParent )
			{
				if (this->parent != NULL) {
					if (isOnLeft())
						parent->left = nParent;
					else
						parent->right = nParent;
				}
				nParent->parent = this->parent;
				this->parent = nParent;
			}

			bool	hasRedChild()
			{
				return ((left != NULL && left->colour == RED) || (right != NULL && right->colour == RED));
			}

	};

	template< class Key, class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
	class RBTree {
		public:
			typedef				Key														key;
			typedef				T														value;
			typedef				ft::pair<const Key, T>									value_type;
			typedef				node<value_type>										Node;
			typedef				node<value_type> *										node_pointer;
			typedef				std::allocator<value_type>								allocator_type;
			typedef typename	Alloc::template rebind<Node>::other						node_allocator_type;
			typedef				Compare													value_compare;
			typedef				ft::map_iterator<Node, value_type>						iterator;
			typedef				ft::map_iterator<Node, const value_type, value_type>	const_iterator;
			typedef				ft::r_map_iterator<iterator>							reverse_iterator;
			typedef				ft::r_map_iterator<const_iterator>						const_reverse_iterator;
			typedef				std::size_t												size_type;
			typedef 			Compare													key_compare;

		private:
			node_pointer		_root;
			Node				_end;
			key_compare			_compare;
			node_allocator_type	_alloc_node;
			allocator_type		_alloc;

			void	leftRotate(node_pointer x)
			{
				node_pointer	nParent = x->right;
				if (x == _root)
					_root = nParent;
				x->moveDown(nParent);
				x->right = nParent->left;
				if (nParent->left != NULL)
					nParent->left->parent = x;
				nParent->left = x;
			}

			void	rightRotate(node_pointer x)
			{
				node_pointer	nParent = x->left;
				if (x == _root)
					_root = nParent;
				x->moveDown(nParent);
				x->left = nParent->right;
				if (nParent->right != NULL)
					nParent->right->parent = x;
				nParent->right = x;
			}

			void	swapColors(node_pointer x1, node_pointer x2)
			{
				color	temp;
				temp = x1->colour;
				x1->colour = x2->colour;
				x2->colour = temp;
			}

			void	swapNodes(node_pointer u, node_pointer v)
			{
				Node tmp_v;
				tmp_v.parent = v->parent;
				tmp_v.left = v->left;
				tmp_v.right = v->right;
				v->left = u->left;
				v->right = u->right;
				v->parent = u->parent;
				if (tmp_v.left == u)
					u->left = v;
				else
					u->left = tmp_v.left;
				if (tmp_v.right == u)
					u->right = v;
				else
					u->right = tmp_v.right;
				u->parent = tmp_v.parent;

				if (v->left != NULL)
					v->left->parent = v;
				if (v->right != NULL)
					v->right->parent = v;
				if (u->left != NULL)
					u->left->parent = u;
				if (u->right != NULL)
					u->right->parent = u;

				if (u->parent != NULL && u->parent->left == v)
					u->parent->left = u;
				if (u->parent != NULL && u->parent->right == v)
					u->parent->right = u;
				if (v->parent != NULL && v->parent->left == u)
					v->parent->left = v;
				if (v->parent != NULL && v->parent->right == u)
					v->parent->right = v;

				if (v == getRoot())
					_root = u;
				else if (u == getRoot())
					_root = v;
			}

			void	fixRedRed(node_pointer x)
			{
				if (x == _root)
				{
					x->colour = BLACK;
					return;
				}
				node_pointer	parent = x->parent;
				node_pointer	grandparent = parent->parent;
				node_pointer	uncle = x->uncle();

				if (parent->colour == RED)
				{
					if (uncle != NULL && uncle->colour == RED)
					{
						parent->colour = BLACK;
						uncle->colour = BLACK;
						grandparent->colour = RED;
						fixRedRed(grandparent);
					}
					else
					{
						if (parent->isOnLeft())
						{
							if (x->isOnLeft())
							{
								swapColors(parent, grandparent);
							}
							else
							{
								leftRotate(parent);
								swapColors(x, grandparent);
							}
							rightRotate(grandparent);
						}
						else
						{
							if (x->isOnLeft())
							{
								rightRotate(parent);
								swapColors(x, grandparent);
							}
							else
								swapColors(parent, grandparent);
							leftRotate(grandparent);
						}
					}
				}
			}

			node_pointer	successor(node_pointer x)
			{
				node_pointer	temp = x;

				while (temp->left != NULL)
					temp = temp->left;

				return temp;
			}

		
			node_pointer	BSTreplace(node_pointer x)
			{
				if (x->left != NULL && x->right != NULL)
					return successor(x->right);
				if (x->left == NULL && x->right == NULL)
					return NULL;
				if (x->left != NULL)
					return x->left;
				else
					return x->right;
			}


			void	deleteNode(node_pointer v)
			{
				node_pointer	u = BSTreplace(v);
				bool	uvBlack = ((u == NULL || u->colour == BLACK) && (v->colour == BLACK));
				node_pointer	parent = v->parent;
				if (u == NULL)
				{
					if (v == _root)
						_root = NULL;
					else
					{
						if (uvBlack)
							fixDoubleBlack(v);
						else
						{
							if (v->sibling() != NULL)
								v->sibling()->colour = RED;
						}
						if (v->isOnLeft())
							parent->left = NULL;
						else
							parent->right = NULL;
					}
					_alloc_node.deallocate(v, 1);
					return;
				}
				if (v->left == NULL || v->right == NULL)
				{
					if (v == _root)
					{
						v->val = u->val;
						v->left = v->right = NULL;
						_alloc_node.deallocate(u, 1);
					}
					else
					{
						if (v->isOnLeft())
							parent->left = u;
						else
							parent->right = u;
						_alloc_node.deallocate(v, 1);
						u->parent = parent;
						if (uvBlack)
							fixDoubleBlack(u);
						else
							u->colour = BLACK;
					}
					return;
				}
				swapNodes(u, v);
				deleteNode(v);
			}

			void	fixDoubleBlack(node_pointer x)
			{
				if (x == _root)
					return;

				node_pointer	sibling = x->sibling();
				node_pointer	parent = x->parent;
				if (sibling == NULL)
					fixDoubleBlack(parent);
				else {
					if (sibling->colour == RED)
					{
						parent->colour = RED;
						sibling->colour = BLACK;
						if (sibling->isOnLeft())
							rightRotate(parent);
						else
							leftRotate(parent);
						fixDoubleBlack(x);
					}
					else {
						if (sibling->hasRedChild())
						{
							if (sibling->left != NULL && sibling->left->colour == RED)
							{
								if (sibling->isOnLeft())
								{
									sibling->left->colour = sibling->colour;
									sibling->colour = parent->colour;
									rightRotate(parent);
								}
								else
								{
									sibling->left->colour = parent->colour;
									rightRotate(sibling);
									leftRotate(parent);
								}
							}
							else {
								if (sibling->isOnLeft())
								{
									sibling->right->colour = parent->colour;
									leftRotate(sibling);
									rightRotate(parent);
								}
								else
								{
									sibling->right->colour = sibling->colour;
									sibling->colour = parent->colour;
									leftRotate(parent);
								}
							}
							parent->colour = BLACK;
						}
						else {
							sibling->colour = RED;
							if (parent->colour == BLACK)
								fixDoubleBlack(parent);
							else
								parent->colour = BLACK;
						}
					}
				}
			}

		public:
			RBTree(const value_type &in)
			{
				_root = NULL;
				insert(in);
				_end.left = &_end;
			}

			RBTree()
			{
				_root = NULL;
				_end.left = &_end;
			}

			RBTree &operator=(RBTree &in)
			{
				this->_root = in._root;
				this->_end = in._end;
				this->_root->parent = &_end;
				return (*this);
			}

			node_pointer	getRoot()
			{
				return (_root);
			}

			node_pointer	search(const value_type &n)
			{
				node_pointer	temp = _root;
				while (temp != NULL)
				{
					if (_compare(n.first , temp->val.first))
					{
						if (temp->left == NULL)
							break;
						else
							temp = temp->left;
					}
					else if (n.first == temp->val.first)
					{
						break;
					}
					else
					{
						if (temp->right == NULL)
							break;
						else
							temp = temp->right;
					}
				}
				return (temp);
			}

			size_t	count ( const key & n ) const{
				node_pointer	temp = _root;
				while (temp != NULL)
				{
					if (_compare(n , temp->val.first))
					{
						if (temp->left == NULL)
							break;
						else
							temp = temp->left;
					}
					else if (n == temp->val.first)
					{
						return (1);
					}
					else
					{
						if (temp->right == NULL)
							break;
						else
							temp = temp->right;
					}
				}
				return (0);
			}

			iterator find (const key &n)
			{
				node_pointer	temp = _root;
				while (temp != NULL)
				{
					if (_compare(n , temp->val.first))
					{
						if (temp->left == NULL)
							break;
						else
							temp = temp->left;
					}
					else if (n == temp->val.first)
						return iterator(temp);
					else
					{
						if (temp->right == NULL)
							break;
						else
							temp = temp->right;
					}
				}
				return (end());
			}

			const_iterator find (const key & n) const
			{
				node_pointer	temp = _root;
				while (temp != NULL)
				{
					if (_compare(n , temp->val.first))
					{
						if (temp->left == NULL)
							break;
						else
							temp = temp->left;
					}
					else if (n == temp->val.first)
					{
						return const_iterator(temp);
					}
					else
					{
						if (temp->right == NULL)
							break;
						else
							temp = temp->right;
					}
				}
				return (end());
			}

			iterator lower_bound (const key & n)
			{
				iterator start = begin();
				iterator ende = end();
				key lower_bound = start->first;
				iterator re = start;
				for (;start != ende; start++)
				{
					if (start->first == n)
						return start;
					else if (lower_bound < start->first)
					{
						if (lower_bound > n)
							return re;
						lower_bound = start->first;
						re = start;
					}
				}
				return ende;
			}

			const_iterator lower_bound (const key & n) const
			{
				const_iterator start = begin();
				const_iterator ende = end();
				key lower_bound = start->first;
				const_iterator re = start;
				for (;start != ende; start++)
				{
					if (start->first == n)
						return start;
					else if (lower_bound < start->first)
					{
						if (lower_bound > n)
							return re;
						lower_bound = start->first;
						re = start;
					}
				}
				return ende;
			}

			iterator upper_bound (const key & n)
			{
				iterator start = begin();
				iterator ende = end();
				for (;start != ende; start++)
					if (start->first > n)
						return start;
				return (end());
			}

			const_iterator upper_bound (const key & n) const
			{
				const_iterator start = begin();
				const_iterator ende = end();
				for (;start != ende; start++)
					if (start->first > n)
						return start;
				return (end());
			}

			ft::pair<iterator,iterator> equal_range (const key & k)
			{
				return (ft::make_pair<iterator,iterator>(lower_bound(k),upper_bound(k)));
			}

			ft::pair<const_iterator,const_iterator> equal_range (const key & k) const
			{
				return (ft::make_pair<const_iterator,const_iterator>(lower_bound(k),upper_bound(k)));
			}

			void erase (iterator position)
			{
				deleteByVal(*position);
			}

			ft::pair<iterator,bool>	insert(const value_type & n ) {
				node_pointer newNode = _alloc_node.allocate(1);
				_alloc.construct(&newNode->val, n);
				newNode->left = NULL;
				newNode->right = NULL;
				newNode->parent = NULL;
				if (_root == NULL) {
					newNode->colour = BLACK;
					_root = newNode;
					_root->parent = &_end;
					_end.left = _root;
				}
				else
				{
					node_pointer	temp = search(n);
					if (temp->val.first == n.first)
					{
						_alloc_node.deallocate(newNode, 1);
						return (ft::make_pair<iterator,bool>(iterator(temp),false));
					}
					newNode->colour = RED;
					newNode->parent = temp;
					if (_compare(n.first , temp->val.first))
						temp->left = newNode;
					else
						temp->right = newNode;
					fixRedRed(newNode);
				}
				return (ft::make_pair<iterator,bool>(iterator(newNode),true));
			}

			ft::pair<iterator,bool> insert(iterator position, const value_type &n)
			{
				node_pointer newNode = _alloc_node.allocate(1);
				_alloc.construct(&newNode->val, n);
				newNode->left = NULL;
				newNode->right = NULL;
				newNode->parent = NULL;
				ft::pair<iterator,bool> tmp;
				if (_root == NULL)
				{
					newNode->colour = BLACK;
					_root = newNode;
					_root->parent = &_end;
					_end.left = _root;
					tmp = ft::make_pair<iterator,bool>(iterator(newNode),true);
					return (tmp);
				}
				else
				{
					if ((position->first < _root->val.first && n.first > _root->val.first)
						|| (position->first > _root->val.first && n.first < _root->val.first)
						|| (position == end()) || (position.base() == NULL))
					{
						tmp = insert(n);
						_alloc_node.deallocate(newNode, 1);
					}
					else if (position.base()->right != NULL && position.base()->left != NULL)
					{
						tmp = insert(n);
						_alloc_node.deallocate(newNode, 1);
					}
					else
					{
						newNode->colour = RED;
						newNode->parent = position.base();
						if (n.first < position.base()->val.first && position.base()->left == NULL)
							position.base()->left = newNode;
						else if (n.first > position.base()->val.first && position.base()->right == NULL)
							position.base()->right = newNode;
						else
						{
							tmp = insert(n);
							_alloc_node.deallocate(newNode, 1);
						}
						fixRedRed(newNode);
					}
				}
				return (tmp);
			}

			void	deleteByVal(const value_type &n)
			{
				if (_root == NULL)
					return;
				node_pointer	v = search(n);
				if (v->val.first != n.first)
					return;
				deleteNode(v);
			}

			iterator	begin()
			{
				if (_root == NULL)
					return _root;
				Node *tmp = _root;
				while (tmp->left != NULL)
					tmp = tmp->left;
				return (tmp);
			}

			const_iterator begin() const
			{
				if (_root == NULL)
					return _root;
				Node *tmp = _root;
				while (tmp->left != NULL)
					tmp = tmp->left;
				return (tmp);
			}

			iterator	end()
			{
				if (_root == NULL)
					return (iterator(&_end));
				return (iterator(&_end));
			}

			const_iterator end() const
			{
				if (_root == NULL)
					return (const_iterator(_root));
				return (const_iterator(_root->parent));
			}

			reverse_iterator 		rbegin()
			{
				return (reverse_iterator(end()));
			}

			const_reverse_iterator	rbegin() const
			{
				return (const_reverse_iterator(end()));
			}

			reverse_iterator		rend()
			{
				return (reverse_iterator(begin()));
			}

			const_reverse_iterator	rend() const
			{
				return (const_reverse_iterator(begin()));
			}

			value_compare value_comp() const
			{
				return (_compare);
			}

			allocator_type get_allocator() const
			{
				return (_alloc_node);
			}

			size_type max_size() const
			{
				return (_alloc_node.max_size());
			}


	};
};


#endif