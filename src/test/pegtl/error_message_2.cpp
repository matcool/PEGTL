// Copyright (c) 2021-2022 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#if !defined( __cpp_exceptions )
#include <iostream>
int main()
{
   std::cout << "Exception support disabled, skipping test..." << std::endl;
}
#else

#include "test.hpp"

namespace test2
{
   using namespace tao::pegtl;

   // clang-format off
   struct a : one< 'a' > {};
   struct b : one< 'b' > {};
   struct grammar : sor< a, sor< b, TAO_PEGTL_RAISE_MESSAGE( "test123" ) > > {};
   // clang-format on

}  // namespace test2

namespace tao::pegtl
{
   void unit_test()
   {
      try {
         parse< test2::grammar >( memory_input( "c", __FUNCTION__ ) );
         TAO_PEGTL_TEST_UNREACHABLE;  // LCOV_EXCL_LINE
      }
      catch( const parse_error& e ) {
         TAO_PEGTL_TEST_ASSERT( e.message() == "test123" );
      }
   }

}  // namespace tao::pegtl

#include "main.hpp"

#endif
