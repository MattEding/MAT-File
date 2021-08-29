#pragma once

#include "ArrayDataElement.h"
#include "DataElement.h"
#include "Enums.h"
#include "Header.h"
#include "TypeDefs.h"

#include <fstream>
#include <vector>

namespace mat {

class MatFile
{
public:
    Header header;
    DataElement data_element;

    MatFile( );

    ~MatFile( );

    [[ nodiscard ]]
    auto load( fs::path const & matfile ) -> bool;

    auto close( ) -> void;

private:
    std::unique_ptr< class MatFilePrivate > d_ptr;
};

} /* mat */
