#ifndef GDF_ARROW_GDF_ARROW_H
#define GDF_ARROW_GDF_ARROW_H

#include <cstdlib>
#include <cstdint>
#include "cffi/types.h"

#define GDF_ARROW_VALID_BITSIZE (sizeof(gdf_valid_type) * 8)

extern "C" {
#include "cffi/functions.h"
}

#endif /* GDF_ARROW_GDF_ARROW_H */
