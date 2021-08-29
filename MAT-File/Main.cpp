#include "Enums.h"
#include "Macros.h"
#include "MatFile.h"
#include "Print.h"
#include "TypeDefs.h"
#include "TestFiles.hpp"
#include "Swab.hpp"

#include <QImage>

#include <iostream>

#include <cassert>

namespace fs { using namespace mat::fs; }

auto save_image( fs::path const & png_path,
                 mat::NumericArrayDataElement const & numeric_array_data_element ) -> void
{
    MAT_ASSERT( numeric_array_data_element.real.data_type( ) == mat::DataType::UInt8 );

    QImage const image{
        static_cast< unsigned char const * >( numeric_array_data_element.real.data( ) ),
        numeric_array_data_element.common.dimensions[ 0 ],
        numeric_array_data_element.common.dimensions[ 1 ],
        QImage::Format_Grayscale8
        };

    MAT_ASSERT( not image.isNull( ) );

    auto const png = png_path.generic_string( );
    MAT_PRINT( png_path );
    bool const saved = image.save( QString::fromStdString( png_path ) );
    MAT_PRINT( saved );
}

int main( )
{
    fs::path const spectrum_mat_file =
//            led_spectrum_mat_file
//            uniform_spectrum_mat_file
//            uavsar_gt
//            sar_feature
//            indian_pines_gt
            lena
//            mat_uint8
//            mat_int32
//            mat_multi_dim
            ;

    MAT_PRINT( spectrum_mat_file );
    MAT_ASSERT( fs::exists( spectrum_mat_file )
            and fs::is_regular_file( spectrum_mat_file ));

    mat::MatFile mat_file{ };

    if ( mat_file.load( spectrum_mat_file ) )
    {
        auto const & header = mat_file.header;
        mat::print_header( header );

        auto const & data_element = mat_file.data_element;
        mat::print_data_element_tag( data_element );

        switch ( data_element.data_type( ) )
        {
            case mat::DataType::Matrix:
            {
                auto const & array_common = *reinterpret_cast< mat::ArrayCommon const * >( data_element.data( ) );
                mat::print_array_common( array_common );

                if ( is_numeric_array( array_common.array_class( ) ) )
                {
                    auto const & numeric_array_data_element = *reinterpret_cast< mat::NumericArrayDataElement const * >( data_element.data( ) );
                    mat::print_numeric_array_data_element( numeric_array_data_element );

                    save_image( fs::path{ spectrum_mat_file }.replace_extension( ".png" ),
                                numeric_array_data_element );
                }
            }
        }
    }
}
