/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_integral_enable_if.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrosch <lrosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 14:32:09 by lrosch            #+#    #+#             */
/*   Updated: 2022/07/18 14:13:25 by lrosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IS_INTEGRAL_ENABLE_IF_HPP
#define IS_INTEGRAL_ENABLE_IF_HPP

namespace ft
{

	template <class T> 
	struct remove_const
	{
		typedef T type;
	};

	template <class T> 
	struct remove_const <const T>
	{
		typedef T type;
	};

	template <class T, T v>
	struct is_integral_const
	{
		static const T val = v;
	};

	typedef is_integral_const<bool, true> true_type;
	typedef is_integral_const<bool, false> false_type;

	template <class T>
	struct is_integral_base : public false_type{};
	
	template <> struct is_integral_base <bool> : public true_type{};

	template <> struct is_integral_base <char> : public true_type{};

	template <> struct is_integral_base <char16_t> : public true_type{};

	template <> struct is_integral_base <char32_t> : public true_type{};

	template <> struct is_integral_base <wchar_t> : public true_type{};

	template <> struct is_integral_base <signed char> : public true_type{};

	template <> struct is_integral_base <short int> : public true_type{};

	template <> struct is_integral_base <int> : public true_type{};

	template <> struct is_integral_base <long int> : public true_type{};

	template <> struct is_integral_base <long long int> : public true_type{};

	template <> struct is_integral_base <unsigned char> : public true_type{};

	template <> struct is_integral_base <unsigned short int> : public true_type{};

	template <> struct is_integral_base <unsigned int> : public true_type{};

	template <> struct is_integral_base <unsigned long int> : public true_type{};

	template <> struct is_integral_base <unsigned long long int> : public true_type{};

	template <class T>
	struct is_integral : public is_integral_base <typename remove_const<T>::type> {};

	template<bool Cond, class T = void>
	struct enable_if
	{
	};

	template<class T>
	struct enable_if<true, T> 
	{
		typedef T type; 
	};

}

#endif