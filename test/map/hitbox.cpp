#include "catch.hpp"

#include "hitbox.hpp"

TEST_CASE( "Map::Hitbox::Construction", "[Map][Map::Hitbox]" ) {
   Hitbox hb = { 1, 2, 3, 4 };

   REQUIRE( hb.x == 1 );
   REQUIRE( hb.y == 2 );
   REQUIRE( hb.w == 3 );
   REQUIRE( hb.h == 4 );
}

TEST_CASE( "Map::Hitbox::Copy", "[Map][Map::Hitbox]" ) {
   Hitbox hb = { 1, 2, 3, 4 };

   SECTION( "Copy constructor" ) {
      Hitbox cp( hb );

      REQUIRE( hb.x == cp.x );
      REQUIRE( hb.y == cp.y );
      REQUIRE( hb.w == cp.w );
      REQUIRE( hb.h == cp.h );
   }

   SECTION( "Copy operator" ) {
      Hitbox cp = hb;

      REQUIRE( hb.x == cp.x );
      REQUIRE( hb.y == cp.y );
      REQUIRE( hb.w == cp.w );
      REQUIRE( hb.h == cp.h );
   }
}

TEST_CASE( "Map::Hitbox::collides", "[Map][Map::Hitbox]" ) {
   Hitbox hb_base = { 10, 10, 20, 20 };

   SECTION( "A copy collides with itself" ) {
      Hitbox hb_cp = hb_base;

      REQUIRE( hb_base.collides( hb_cp ) == true );
      REQUIRE( hb_cp.collides( hb_base ) == true );
   }

   SECTION( "Aberrant evasion" ) {
      Hitbox hb_other = { 50, 50, 20, 20 };

      REQUIRE( hb_base.collides( hb_other ) == false );
      REQUIRE( hb_other.collides( hb_base ) == false );
   }

   SECTION( "When 2 boxes touches, bot do not overlap" ) {
      Hitbox hb_x = { 10, 30, 20, 20 };
      Hitbox hb_y = { 30, 10, 20, 20 };

      REQUIRE( hb_base.collides( hb_x ) == false );
      REQUIRE( hb_base.collides( hb_y ) == false );
      REQUIRE( hb_x.collides( hb_base ) == false );
      REQUIRE( hb_y.collides( hb_base ) == false );
   }
}

TEST_CASE( "Map::Hitbox::operator<", "[Map][Map::Hitbox]" ) {
   Hitbox hb_base = { 10, 10, 20, 20 };

   SECTION( "Both x are different" ) {
      Hitbox hb_other = { 15, 0, 20, 20 };

      REQUIRE( ( hb_base < hb_other ) == true );
      REQUIRE( ( hb_other < hb_base ) == false );
   }

   SECTION( "x are equal, but not y" ) {
      Hitbox hb_other = { 10, 15, 20, 20 };

      REQUIRE( ( hb_base < hb_other ) == true );
      REQUIRE( ( hb_other < hb_base ) == false );
   }

   SECTION( "both x are equal, and both y are equal" ) {
      Hitbox cp = hb_base;

      REQUIRE( ( hb_base < cp ) == false );
      REQUIRE( ( cp < hb_base ) == false );
   }
}

SCENARIO( "Map::Hitbox::operator<", "[Map][Map::Hitbox]" ) {

   GIVEN( "a basic hitbox" ) {
      Hitbox hb_base = { 10, 10, 20, 20 };

      WHEN( "both x are different" ) {
         Hitbox hb_other = { 15, 0, 20, 20 };

         THEN( "only x is tested" ) {
            REQUIRE( ( hb_base < hb_other ) == true );
            REQUIRE( ( hb_other < hb_base ) == false );
         }
      }

      WHEN( "both x are equal, but not y" ) {
         Hitbox hb_other = { 10, 15, 20, 20 };

         THEN( "x is ignored and y is tested" ) {
            REQUIRE( ( hb_base < hb_other ) == true );
            REQUIRE( ( hb_other < hb_base ) == false );
         }
      }

      WHEN( "both x are equal, and both y are equal" ) {
         Hitbox cp = hb_base;

         THEN( "it returns false in both ways" ) {
            REQUIRE( ( hb_base < cp ) == false );
            REQUIRE( ( cp < hb_base ) == false );
         }
      }
   }
}
