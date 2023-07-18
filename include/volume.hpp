#ifndef VOLUME_HPP
#define VOLUME_HPP


#include <cstddef>
#include <vector>
#include <cstdint>
#include <cmath>
#include <tuple>
#include <iostream>
#include <type_traits>
#include <algorithm>

template < typename lengthT, std::enable_if_t< std::is_floating_point< lengthT >::value, bool > = true >
class point
{
public:
    lengthT x_;
    lengthT y_;
    lengthT z_;

    point( lengthT X = 0.0, lengthT Y = 0.0, lengthT Z = 0.0 )
        : x_( X ), y_( Y ), z_( Z )
    {
    }

    bool operator==( const point& RHS ) const = default;
};

template < typename lengthT, std::enable_if_t< std::is_floating_point< lengthT >::value, bool > = true >
class vertice
{
public:
    using point_t = point<lengthT>;

    point_t P1_;
    point_t P2_;

    vertice( point_t P1, point_t P2 )
        : P1_( P1 ), P2_( P2 )
    {
        if( P1 != P2 )
        {
            P1_ = P1;
            P2_ = P2;
        }
        else
        {
            // TODO: compile time error
        }
    }

    bool operator==( const vertice& R ) const
    {
        return ( P1_ == R.P1_ && P2_ == R.P2_ )
            || ( P1_ == R.P2_ && P2_ == R.P1_ );
    }

    const point_t getmaxX() const
    {
        return P1_.x_ > P2_.x_ ? P1_ : P2_;
    }

    const point_t getmaxY() const
    {
        return P1_.y_ > P2_.y_ ? P1_ : P2_;
    }

    const point_t getmaxZ() const
    {
        return P1_.z_ > P2_.z_ ? P1_ : P2_;
    }
    
};

template < typename lengthT, std::enable_if_t< std::is_floating_point< lengthT >::value, bool > = true >
class volume
{
public:

    using volume_t = lengthT;
    using vertice_t = vertice<lengthT>;
    using point_t = typename vertice_t::point_t;

    struct max_dimensions
    {
        lengthT X;
        lengthT Y;
        lengthT Z;
    };

    const std::vector<vertice_t> Vertices_;
    std::vector<std::vector<std::vector<point_t>>> Matrix_;

    volume( const std::vector<vertice_t> Vertices ) : Vertices_( Vertices )
    {
        // if we say that the maximum useful wavelength is that of 500hz
        // constexpr lengthT LenOf500 = 343.0 / 500;
        // // 2 points per wavelength
        // constexpr lengthT PointsPerMetre = 2 / LenOf500;



        max_dimensions MaxDimensions {};

        for( size_t i{0}; i < Vertices.size(); ++i )
        {

            if ( Vertices[i].getmaxX().x_ > MaxDimensions.X )
            {
                MaxDimensions.X = Vertices[i].getmaxX().x_;
            }
            if ( Vertices[i].getmaxY().y_ > MaxDimensions.Y )
            {
                MaxDimensions.Y = Vertices[i].getmaxY().y_;
            }
            if ( Vertices[i].getmaxZ().z_ > MaxDimensions.Z )
            {
                MaxDimensions.Z = Vertices[i].getmaxZ().z_;
            }
        }

        std::cout << "user defined x = " << MaxDimensions.X << "\n";
        std::cout << "user defined y = " << MaxDimensions.Y << "\n";
        std::cout << "user defined z = " << MaxDimensions.Z << "\n";

       
        
        //get the smallest of the dimensions

        // shouldn't wee calculate the length of a vertice?
        lengthT SmallestMaxDimension = MaxDimensions.X;
        if( MaxDimensions.Y < SmallestMaxDimension )
        {
            SmallestMaxDimension = MaxDimensions.Y;
        }
        if( MaxDimensions.Z < SmallestMaxDimension )
        {
            SmallestMaxDimension = MaxDimensions.Z;
        }

        // if SmallestMaxDimension is equal to 0, we can't calculate matrix
        if ( SmallestMaxDimension <= lengthT{} )
        {
            Matrix_.push_back( std::vector<std::vector<point_t>>{ std::vector<point_t> { point_t{} } } );
        }
        // hack to check if volume can be defined with vertices
        else if( Vertices.size() < 6 )
        {
            Matrix_.push_back( std::vector<std::vector<point_t>>{ std::vector<point_t> { point_t{} } } );
        }
        else if( !congruent_vertices( Vertices ) )
        {
            Matrix_.push_back( std::vector<std::vector<point_t>>{ std::vector<point_t> { point_t{} } } );
        }
        else
        {
            lengthT Tolerance = 0.001 * SmallestMaxDimension;
            // = cbrt( 1/(PointsPerMetre) );

            const lengthT LengthBetweenPoints = SmallestMaxDimension;

            std::cout << "Tolerance = " << Tolerance << "\n";
            std::cout << "LengthBetweenPoints = " << LengthBetweenPoints << "\n";

            // Count represents points in SmallestMaxDimension
            int Count = 2;
            std::cout << "Count = " << Count << "\n";
            lengthT CalculatedDistance = ( Count - 1) * LengthBetweenPoints;

            int PointsInX = 0;
            int PointsInY = 0;
            int PointsInZ = 0;

            point_t CalculatedDimensions{};

            PointsInX = MaxDimensions.X / SmallestMaxDimension + 1;
            PointsInY = MaxDimensions.Y / SmallestMaxDimension + 1;
            PointsInZ = MaxDimensions.Z / SmallestMaxDimension + 1;

            std::cout << "staring PointsInX = " << PointsInX << "\n";
            std::cout << "starting PointsInY = " << PointsInY << "\n";
            std::cout << "starting PointsInZ = " << PointsInZ << "\n";

            while( true )
            {

                CalculatedDimensions.x_ = ( PointsInX - 1 ) * CalculatedDistance;
                CalculatedDimensions.y_ = ( PointsInY - 1 ) * CalculatedDistance;
                CalculatedDimensions.z_ = ( PointsInZ - 1 ) * CalculatedDistance;

                if( ( std::abs( CalculatedDimensions.x_ - MaxDimensions.X ) > Tolerance )
                    || ( std::abs( CalculatedDimensions.y_ - MaxDimensions.Y ) > Tolerance )
                    || ( std::abs( CalculatedDimensions.z_ - MaxDimensions.Z ) > Tolerance ) )
                {
                    CalculatedDistance = SmallestMaxDimension / ( ++Count - 1 );

                    PointsInX = MaxDimensions.X / CalculatedDistance + 1;
                    PointsInY = MaxDimensions.Y / CalculatedDistance + 1;
                    PointsInZ = MaxDimensions.Z / CalculatedDistance + 1;

                    std::cout << "CalculatedDistance = " << CalculatedDistance << "\n";
                    std::cout << "PointsInX = " << PointsInX << "\n";
                    std::cout << "PointsInY = " << PointsInY << "\n";
                    std::cout << "PointInZ = " << PointsInZ << "\n";
                }
                else
                {
                    break;
                }
            }



            // LengthBetweenPoints is the starting length between points in any dimension
            // We will use this to calculate number of points in all dimensions
            // then recalculate total distance in each dimension
            // then compare to each maxDimension
        

            // points are on boundary !!

            std::cout << "increased count" << Count << "\n";
            std::cout << "Length between points " << CalculatedDistance << "\n";

            std::cout << "finished calculating count..." << "\n";

            std::cout <<  "calculating matrix...\n";

            for(int x = 0; x < PointsInX; x++ )
            {
                Matrix_.push_back( std::vector<std::vector<point_t>>{} );
                for(int y = 0; y < PointsInY; y++ )
                {
                    Matrix_[x].push_back( std::vector<point_t>{} );
                    for(int z = 0; z< PointsInZ; z++ )
                    {
                        Matrix_[x][y].push_back( point_t{x*CalculatedDistance, y* CalculatedDistance, z* CalculatedDistance } );
                    }
                }
            }
        }
    }

    // for now this will calculate cuboidal volume
    volume_t get_volume_si() const
    {
        const auto LengthX = Matrix_[ std::max( Matrix_.size() - 1, size_t( 0 ) ) ][ 0 ][ 0 ].x_;
        const auto LengthY = Matrix_[ 0 ][ std::max( Matrix_[ 0 ].size() - 1, size_t( 0 ) ) ][ 0 ].y_;
        const auto LengthZ = Matrix_[ 0 ][ 0 ][ std::max( Matrix_[ 0 ][ 0 ].size() - 1, size_t( 0 ) ) ].z_;

        return LengthX * LengthY * LengthZ;
    }

private:
    static bool congruent_vertices( const std::vector<vertice_t>& Vertices )
    {
        bool Result = true;

        std::for_each( std::begin( Vertices ), std::end( Vertices ),
            [&]( const auto& LHVertice )
            {
                const auto& Point1 = LHVertice.P1_;
                const auto& Point2 = LHVertice.P2_;
                if(
                    !std::any_of( std::begin( Vertices ), std::end( Vertices ),
                        [&]( const auto& RHVertice )
                        {
                            if ( LHVertice != RHVertice )
                            {
                                return  ( Point1 == RHVertice.P1_ 
                                    ||  Point1 == RHVertice.P2_ );
                            }
                            else return false;
                        } )
                    || !std::any_of( std::begin( Vertices ), std::end( Vertices ),
                        [&]( const auto& RHVertice )
                        {
                            if ( LHVertice != RHVertice )
                            {
                                return  ( Point2 == RHVertice.P1_ 
                                    ||  Point2 == RHVertice.P2_ );
                            }
                            else return false;
                        } )
                )
                {
                    Result = false;
                }
            } );

        return Result;
    }
};

#endif //VOLUME_HPP