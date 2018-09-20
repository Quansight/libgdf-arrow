#pragma once

typedef size_t gdf_size_type;
typedef gdf_size_type gdf_index_type;
typedef unsigned char gdf_valid_type;

/* --------------------------------------------------------------------------*/
/** 
 * @Synopsis  These enums indicate the possible data types for a gdf_column
 */
/* ----------------------------------------------------------------------------*/

typedef enum {
    GDF_invalid=0,
    GDF_INT8,
    GDF_INT16,
    GDF_INT32,
    GDF_INT64,
    GDF_FLOAT32,
    GDF_FLOAT64,
    GDF_DATE32,   // int32_t days since the UNIX epoch
    GDF_DATE64,   // int64_t milliseconds since the UNIX epoch
    GDF_TIMESTAMP,// Exact timestamp encoded with int64 since UNIX epoch (Default unit millisecond)
    N_GDF_TYPES, /* additional types should go BEFORE N_GDF_TYPES */
} gdf_dtype;


/* --------------------------------------------------------------------------*/
/** 
 * @Synopsis  These are all possible gdf error codes that can be returned from 
 * a libgdf function. ANY NEW ERROR CODE MUST ALSO BE ADDED TO `gdf_error_get_name` 
 * AS WELL
 */
/* ----------------------------------------------------------------------------*/

typedef enum {
    GDF_SUCCESS=0,                
    GDF_CUDA_ERROR,                   /**< Error occured in a CUDA call */ 
    GDF_UNSUPPORTED_DTYPE,            /**< The datatype of the gdf_column is unsupported */ 
    GDF_COLUMN_SIZE_MISMATCH,         /**< Two columns that should be the same size aren't the same size*/        
    GDF_COLUMN_SIZE_TOO_BIG,          /**< Size of column is larger than the max supported size */      
    GDF_DATASET_EMPTY,                /**< Input dataset is either null or has size 0 when it shouldn't */   
    GDF_VALIDITY_MISSING,             /**< gdf_column's validity bitmask is null */  
    GDF_VALIDITY_UNSUPPORTED,         
    GDF_INVALID_API_CALL,             /**< The arguments passed into the function were invalid */   
    GDF_JOIN_DTYPE_MISMATCH,          /**< Datatype mismatch between corresponding columns in  left/right tables in the Join function */   
    GDF_JOIN_TOO_MANY_COLUMNS,        /**< Too many columns were passed in for the requested join operation*/       
    GDF_GROUPBY_TOO_MANY_COLUMNS,
    GDF_DTYPE_MISMATCH,               /**< Type mismatch between columns that should be the same type */
    GDF_UNSUPPORTED_METHOD,           /**< The method requested to perform an operation was invalid or unsupported (e.g., hash vs. sort)*/ 
    GDF_INVALID_AGGREGATOR,           /**< Invalid aggregator was specified for a groupby*/
    GDF_INVALID_HASH_FUNCTION,        /**< Invalid hash function was selected */
    GDF_PARTITION_DTYPE_MISMATCH,     /**< Datatype mismatch between columns of input/output in the hash partition function */
    GDF_HASH_TABLE_INSERT_FAILURE,    /**< Failed to insert to hash table, likely because its full */
    GDF_UNSUPPORTED_JOIN_TYPE,        /**< The type of join requested is unsupported */

} gdf_error;

typedef enum {
    GDF_HASH_MURMUR3=0, /**< Murmur3 hash function */
    GDF_HASH_IDENTITY,  /**< Identity hash function that simply returns the key to be hashed */
} gdf_hash_func;

typedef enum {
	TIME_UNIT_NONE=0, // default (undefined)
	TIME_UNIT_s,   // second
	TIME_UNIT_ms,  // millisecond
	TIME_UNIT_us,  // microsecond
	TIME_UNIT_ns   // nanosecond
} gdf_time_unit;

typedef struct {
	gdf_time_unit time_unit;
	// here we can also hold info for decimal datatype or any other datatype that requires additional information
} gdf_dtype_extra_info;

typedef struct gdf_column_{
    void *data;                       /**< Pointer to the columns data */ 
    gdf_valid_type *valid;            /**< Pointer to the columns validity bit mask where the 'i'th bit indicates if the 'i'th row is NULL */
    gdf_size_type size;               /**< Number of data elements in the columns data buffer*/
    gdf_dtype dtype;                  /**< The datatype of the column's data */
    gdf_size_type null_count;         /**< The number of NULL values in the column's data */
    gdf_dtype_extra_info dtype_info;  
} gdf_column;

struct _OpaqueIpcParser;
typedef struct _OpaqueIpcParser gdf_ipc_parser_type;


