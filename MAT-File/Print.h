#pragma once

#include "Macros.h"
#include "MatFile.h"

#include <string_view>

namespace mat {

#define MAT_PRINT_IMPL( func, param )  func( param, MAT_STR( param ) )

auto _print_header( Header const & header,
                    std::string_view const _ ) -> void;
#define print_header( header )  MAT_PRINT_IMPL( _print_header, header )

auto _print_data_element_tag( DataElement const & data_element,
                              std::string_view const _ ) -> void;
#define print_data_element_tag( data_element )  MAT_PRINT_IMPL( _print_data_element_tag, data_element )

auto _print_array_common( ArrayCommon const & array_common,
                          std::string_view const _ ) -> void;
#define print_array_common( array_common )  MAT_PRINT_IMPL( _print_array_common, array_common )

auto _print_numeric_array_data_element( NumericArrayDataElement const & numeric_array_data_element,
                                        std::string_view const _ ) -> void;
#define print_numeric_array_data_element( numeric_array_data_element )  MAT_PRINT_IMPL( _print_numeric_array_data_element, numeric_array_data_element )

} /* mat */
