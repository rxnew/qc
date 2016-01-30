/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_DEREFERENCE_HPP
#define SPROUT_FUNCTIONAL_POLYMORPHIC_DEREFERENCE_HPP

#include <sprout/config.hpp>
#include <sprout/functional/dereference.hpp>

namespace sprout {
	//
	// dereference_t
	// dereference_
	//
	typedef sprout::dereference<> dereference_t;
	namespace {
		SPROUT_STATIC_CONSTEXPR sprout::dereference_t dereference_ = {};
	}	// anonymous-namespace
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_DEREFERENCE_HPP
