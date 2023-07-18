/*
1. single vertice, result is volume of 0
2. two vertices, result is volume of 0
3. three vertices, result is volume of 0
4. vertices, result is volume of 0
...

6. six vertices, valid points, volume is non-zero
7 six non-connected vertices, volume is zero
8. twelve vertices, valid point, volume is non-zero

*/

#include <include/volume.hpp>

#include <boost/test/unit_test.hpp>

void test_single_vertice_volume_is_zero()
{
    using lengthT = double;
    vertice<lengthT> Vertice1{ point<lengthT>{ 0.0, 0.0, 0.0 }, point<lengthT>{ 1.0, 1.0, 1.0 } };

    auto Vertices = std::vector<vertice<lengthT>>{ Vertice1 };

    volume<lengthT> VolumeSingleVertice{ Vertices };

    BOOST_CHECK_EQUAL( 0.0, VolumeSingleVertice.get_volume_si() );
}

void test_two_vertice_volume_is_zero()
{
    using lengthT = double;
    vertice<lengthT> Vertice1{ point<lengthT>{ 0.0, 0.0, 0.0 }, point<lengthT>{ 1.0, 1.0, 1.0 } };
    vertice<lengthT> Vertice2{ point<lengthT>{ 0.0, 0.0, 0.0 }, point<lengthT>{ 1.0, 1.0, 0.0 } };

    auto Vertices = std::vector<vertice<lengthT>>{ Vertice1, Vertice2 };

    volume<lengthT> VolumeSingleVertice{ Vertices };

    BOOST_CHECK_EQUAL( 0.0, VolumeSingleVertice.get_volume_si() );
}

void test_three_vertice_volume_is_zero()
{
    using lengthT = double;
    vertice<lengthT> Vertice1{ point<lengthT>{ 0.0, 0.0, 0.0 }, point<lengthT>{ 1.0, 1.0, 1.0 } };
    vertice<lengthT> Vertice2{ point<lengthT>{ 0.0, 0.0, 0.0 }, point<lengthT>{ 1.0, 1.0, 0.0 } };
    vertice<lengthT> Vertice3{ point<lengthT>{ 1.0, 1.0, 0.0 }, point<lengthT>{ 1.0, 1.0, 1.0 } };

    auto Vertices = std::vector<vertice<lengthT>>{ Vertice1, Vertice2, Vertice3 };

    volume<lengthT> VolumeSingleVertice{ Vertices };

    BOOST_CHECK_EQUAL( 0.0, VolumeSingleVertice.get_volume_si() );
}

void test_six_valid_vertices_volume_is_non_zero()
{
    using lengthT = double;
    vertice<lengthT> Vertice1{ point<lengthT>{ 0.0, 0.0, 0.0 }, point<lengthT>{ 100.0, 0.0, 0.0 } };
    vertice<lengthT> Vertice2{ point<lengthT>{ 100.0, 0.0, 0.0 }, point<lengthT>{ 0.0, 100.0, 0.0 } };
    vertice<lengthT> Vertice3{ point<lengthT>{ 0.0, 100.0, 0.0 }, point<lengthT>{ 0.0, 0.0, 0.0 } };
    vertice<lengthT> Vertice4{ point<lengthT>{ 0.0, 0.0, 0.0 }, point<lengthT>{ 0.0, 0.0, 100.0 } };
    vertice<lengthT> Vertice5{ point<lengthT>{ 0.0, 100.0, 0.0 }, point<lengthT>{ 0.0, 0.0, 100.0 } };
    vertice<lengthT> Vertice6{ point<lengthT>{ 100.0, 0.0, 0.0 }, point<lengthT>{ 0.0, 0.0, 100.0 } };

    auto Vertices = std::vector<vertice<lengthT>>{ Vertice1, Vertice2, Vertice3, Vertice4, Vertice5, Vertice6 };

    volume<lengthT> VolumeSingleVertice{ Vertices };

    BOOST_CHECK_EQUAL( 1000000, VolumeSingleVertice.get_volume_si() );
}

void test_six_valid_vertices_nonconnected_volume_is_zero()
{
    using lengthT = double;

    // this point is slightly short
    vertice<lengthT> Vertice1{ point<lengthT>{ 0.0, 0.0, 0.0 }, point<lengthT>{ 50.0, 0.0, 0.0 } };
    vertice<lengthT> Vertice2{ point<lengthT>{ 100.0, 0.0, 0.0 }, point<lengthT>{ 0.0, 100.0, 0.0 } };
    vertice<lengthT> Vertice3{ point<lengthT>{ 0.0, 100.0, 0.0 }, point<lengthT>{ 0.0, 0.0, 0.0 } };
    vertice<lengthT> Vertice4{ point<lengthT>{ 0.0, 0.0, 0.0 }, point<lengthT>{ 0.0, 0.0, 100.0 } };
    vertice<lengthT> Vertice5{ point<lengthT>{ 0.0, 100.0, 0.0 }, point<lengthT>{ 0.0, 0.0, 100.0 } };
    vertice<lengthT> Vertice6{ point<lengthT>{ 0.0, 100.0, 0.0 }, point<lengthT>{ 0.0, 0.0, 100.0 } };

    auto Vertices = std::vector<vertice<lengthT>>{ Vertice1, Vertice2, Vertice3, Vertice4, Vertice5, Vertice6 };

    volume<lengthT> VolumeSingleVertice{ Vertices };

    BOOST_CHECK_EQUAL( 0.0, VolumeSingleVertice.get_volume_si() );
}

// fails because only a single vertice is used to convey the volume, here it's trying to use two vertices with the same trajectory


        // void test_twelve_valid_vertices_volume_is_non_zero()
        // {
        //     using lengthT = double;
        //     vertice<lengthT> Vertice1{ point<lengthT>{ 0.0, 0.0, 0.0 }, point<lengthT>{ 100.0, 0.0, 0.0 } };
        //     vertice<lengthT> Vertice2{ point<lengthT>{ 100.0, 0.0, 0.0 }, point<lengthT>{ 0.0, 100.0, 0.0 } };
        //     vertice<lengthT> Vertice3{ point<lengthT>{ 0.0, 100.0, 0.0 }, point<lengthT>{ 0.0, 0.0, 0.0 } };
        //     vertice<lengthT> Vertice4{ point<lengthT>{ 0.0, 0.0, 0.0 }, point<lengthT>{ 0.0, 0.0, 100.0 } };
        //     vertice<lengthT> Vertice5{ point<lengthT>{ 0.0, 100.0, 0.0 }, point<lengthT>{ 0.0, 0.0, 100.0 } };
        //     vertice<lengthT> Vertice6{ point<lengthT>{ 100.0, 0.0, 0.0 }, point<lengthT>{ 0.0, 0.0, 100.0 } };
        //     vertice<lengthT> Vertice7{ point<lengthT>{ 0.0, 0.0, 0.0 }, point<lengthT>{ -100.0, 0.0, 0.0 } };
        //     vertice<lengthT> Vertice8{ point<lengthT>{ -100.0, 0.0, 0.0 }, point<lengthT>{ 0.0, -100.0, 0.0 } };
        //     vertice<lengthT> Vertice9{ point<lengthT>{ 0.0, -100.0, 0.0 }, point<lengthT>{ 0.0, 0.0, 0.0 } };
        //     vertice<lengthT> Vertice10{ point<lengthT>{ 0.0, 0.0, 0.0 }, point<lengthT>{ 0.0, 0.0, -100.0 } };
        //     vertice<lengthT> Vertice11{ point<lengthT>{ 0.0, -100.0, 0.0 }, point<lengthT>{ 0.0, 0.0, -100.0 } };
        //     vertice<lengthT> Vertice12{ point<lengthT>{ -100.0, 0.0, 0.0 }, point<lengthT>{ 0.0, 0.0, -100.0 } };

        //     auto Vertices =
        //         std::vector<vertice<lengthT>>
        //         {
        //             Vertice1,
        //             Vertice2,
        //             Vertice3,
        //             Vertice4,
        //             Vertice5,
        //             Vertice6,
        //             Vertice7,
        //             Vertice8,
        //             Vertice9,
        //             Vertice10,
        //             Vertice11,
        //             Vertice12
        //         };

        //     volume<lengthT> VolumeSingleVertice{ Vertices };

        //     BOOST_CHECK_EQUAL( 1000000.0 * ( 2 * 2 * 2 ), VolumeSingleVertice.get_volume_si() );
        // }

void test_twelve_valid_vertices_volume_is_non_zero()
{
    using lengthT = double;
    // cuboid with 'length' in the x dim

    // bottom
    vertice<lengthT> Vertice1{ point<lengthT>{ 0.0, 0.0, 0.0 }, point<lengthT>{ 200.0, 0.0, 0.0 } };
    vertice<lengthT> Vertice2{ point<lengthT>{ 200.0, 0.0, 0.0 }, point<lengthT>{ 200.0, 100.0, 0.0 } };
    vertice<lengthT> Vertice3{ point<lengthT>{ 200.0, 100.0, 0.0 }, point<lengthT>{ 0.0, 100.0, 0.0 } };
    vertice<lengthT> Vertice4{ point<lengthT>{ 0.0, 100.0, 0.0 }, point<lengthT>{ 0.0, 0.0, 0.0 } };
    // top
    vertice<lengthT> Vertice5{ point<lengthT>{ 0.0, 0.0, 100.0 }, point<lengthT>{ 200.0, 0.0, 100.0 } };
    vertice<lengthT> Vertice6{ point<lengthT>{ 200.0, 0.0, 100.0 }, point<lengthT>{ 200.0, 100.0, 100.0 } };
    vertice<lengthT> Vertice7{ point<lengthT>{ 200.0, 100.0, 100.0 }, point<lengthT>{ 0, 100.0, 100.0 } };
    vertice<lengthT> Vertice8{ point<lengthT>{ 0, 100.0, 100.0 }, point<lengthT>{ 0.0, 0.0, 100.0 } };
    // sides
    vertice<lengthT> Vertice9{ point<lengthT>{ 0.0, 0.0, 0.0 }, point<lengthT>{ 0.0, 0.0, 100.0 } };
    vertice<lengthT> Vertice10{ point<lengthT>{ 200.0, 0.0, 0.0 }, point<lengthT>{ 200.0, 0.0, 100.0 } };
    vertice<lengthT> Vertice11{ point<lengthT>{ 200.0, 100.0, 0.0 }, point<lengthT>{ 200.0, 100.0, 100.0 } };
    vertice<lengthT> Vertice12{ point<lengthT>{ 0.0, 100.0, 0.0 }, point<lengthT>{ 0.0, 100.0, 100.0 } };

    auto Vertices =
        std::vector<vertice<lengthT>>
        {
            Vertice1,
            Vertice2,
            Vertice3,
            Vertice4,
            Vertice5,
            Vertice6,
            Vertice7,
            Vertice8,
            Vertice9,
            Vertice10,
            Vertice11,
            Vertice12
        };

    volume<lengthT> VolumeSingleVertice{ Vertices };

    BOOST_CHECK_EQUAL( 1000000.0 * 2, VolumeSingleVertice.get_volume_si() );
}

boost::unit_test::test_suite* volume_test_suite()
{
    boost::unit_test::test_suite* test_suite = BOOST_TEST_SUITE( "volume_test_suite" );
    test_suite->add( BOOST_TEST_CASE( &test_single_vertice_volume_is_zero ) );
    test_suite->add( BOOST_TEST_CASE( &test_two_vertice_volume_is_zero ) );
    test_suite->add( BOOST_TEST_CASE( &test_three_vertice_volume_is_zero ) );
    test_suite->add( BOOST_TEST_CASE( &test_six_valid_vertices_volume_is_non_zero ) );
    test_suite->add( BOOST_TEST_CASE( &test_six_valid_vertices_nonconnected_volume_is_zero ) );
    test_suite->add( BOOST_TEST_CASE( &test_twelve_valid_vertices_volume_is_non_zero ) );
    
    return test_suite;
}

boost::unit_test::test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    boost::unit_test::framework::master_test_suite().add( volume_test_suite() );
    return 0;
}