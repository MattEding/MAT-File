#include "Enums.h"
#include "Macros.h"
#include "MatFile.h"
#include "TypeDefs.h"

#include <array>
#include <fstream>
#include <iomanip>

#include "Utils.hpp"

//template < auto stream = std::cout >
struct [[ nodiscard ]] ScopedFmtFlags
{
    template < typename ... Args >
    ScopedFmtFlags( Args &&... args )
        : fmtflags_( std::cout.flags( ) )
    {
        ( std::cout << ... << args );
    }

    ~ScopedFmtFlags( )
    {
        std::cout.flags( fmtflags_ );
    }

    std::ios::fmtflags const fmtflags_;
};

[[ nodiscard ]]
inline
ScopedFmtFlags hex_fmt( )
{
    return { std::hex,
             std::showbase,
             std::left,
//             std::setw( 40 ),
             std::setfill( '0' ) };
}



int main( )
{
    using namespace mat;

    fs::path const hysi_dir{ "/Users/matteding/HySi" };
    MAT_ASSERT( fs::exists( hysi_dir )
            and fs::is_directory( hysi_dir ) );

    fs::path const complex_mnist_dir{ hysi_dir / "Complex MNIST" };
    fs::path const led_spectrum_mat_file{ complex_mnist_dir / "HS_complex_MNIST_LEDspectrum__60000ims.mat" };
    fs::path const uniform_spectrum_mat_file{ complex_mnist_dir / "HS_complex_MNIST_UniformSpectrum__60000ims.mat" };

    fs::path const uavsar_dir{ hysi_dir / "PolSAR UAVSAR Change Detection Images" };
    fs::path const uavsar_2009{ uavsar_dir / "Dataset#1_2009.mat" };
    fs::path const uavsar_2015{ uavsar_dir / "Dataset#1_2015.mat" };
    fs::path const uavsar_gt{ uavsar_dir / "Dataset#1_GT.mat" };

    fs::path const sar_dir{ hysi_dir / "SAR Sentinel-1 Satellite Imagery in VV & VH polarization" };
    fs::path const sar_feature{ sar_dir / "feature_mat.mat" };

    fs::path const indian_pines_dir{ hysi_dir / "Indian Pines" };
    fs::path const indian_pines_corrected{ indian_pines_dir / "Indian_pines_corrected.mat" };
    fs::path const indian_pines_gt{ indian_pines_dir / "Indian_pines_gt.mat" };
    fs::path const indian_pines{ indian_pines_dir / "Indian_pines.mat" };

    fs::path const lena{ hysi_dir / "lena.mat" };

    fs::path const spectrum_mat_file =
//            led_spectrum_mat_file
//            uniform_spectrum_mat_file
//            uavsar_gt
//            sar_feature
//            indian_pines_gt
            lena
            ;

    MAT_PRINT( spectrum_mat_file );
    MAT_ASSERT( fs::exists( spectrum_mat_file )
            and fs::is_regular_file( spectrum_mat_file ));

    MatFile mat_file{ };

    if ( mat_file.load( spectrum_mat_file ) )
    {
        MAT_PRINT( mat_file.header_text( ) );
        MAT_PRINT( mat_file.subsystem_data_offset( ) );
        MAT_PRINT( mat::swab( mat_file.subsystem_data_offset( ) ) );

        {
            {
                ScopedFmtFlags const fmt{ hex_fmt( ) };
                MAT_PRINT( mat_file.version( ) );
                MAT_PRINT( mat::swab( mat_file.version( ) ) );
            }

            MAT_PRINT( mat_file.endian( ) );
//            MAT_PRINT( mat::swab( mat_file.endian( ) ) );

            MAT_PRINT( Header::magic_number(  ) );

            auto const & data_elements = mat_file.data_elements( );
            if ( not data_elements.empty( ) )
            {

                if ( auto const & data_element = data_elements.front( );
                     data_element.is_small( ) )
                {
                    MAT_PRINT( data_element.small.data_type );
                    MAT_PRINT( data_element.small.number_of_bytes );
                }
                else
                {
                    MAT_PRINT( data_element.tag.data_type );
                    MAT_PRINT( data_element.tag.number_of_bytes );
                }
            }
        }

//        MAT_PRINT( ( mat_file.endian( ) == mat_file.magic_number(  ) ) );

//        u32 data_type;
//        mat_file.read( data_type );
//        MAT_PRINT( data_type );

//        u32 number_of_bytes;
//        mat_file.read( number_of_bytes );
//        MAT_PRINT( number_of_bytes );

        mat_file.close( );
    }
}
