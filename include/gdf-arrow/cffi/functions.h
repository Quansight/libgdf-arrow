#pragma once

/* column operations */

gdf_size_type gdf_column_sizeof();

gdf_error gdf_column_view(gdf_column *column, void *data, gdf_valid_type *valid,
				      gdf_size_type size, gdf_dtype dtype);

gdf_error gdf_column_view_augmented(gdf_column *column, void *data, gdf_valid_type *valid,
						gdf_size_type size, gdf_dtype dtype, gdf_size_type null_count);

gdf_error gdf_column_free(gdf_column *column);
/* error handling */

const char * gdf_error_get_name(gdf_error errcode);

int gdf_cuda_last_error();
const char * gdf_cuda_error_string(int cuda_error);
const char * gdf_cuda_error_name(int cuda_error);

/* ipc */

gdf_ipc_parser_type* gdf_ipc_parser_open(const uint8_t *schema, size_t length);
void gdf_ipc_parser_open_recordbatches(gdf_ipc_parser_type *handle,
					     const uint8_t *recordbatches,
					     size_t length);

void gdf_ipc_parser_close(gdf_ipc_parser_type *handle);
int gdf_ipc_parser_failed(gdf_ipc_parser_type *handle);
const char* gdf_arrow_ipc_parser_to_json(gdf_ipc_parser_type *handle);
const char* gdf_ipc_parser_get_error(gdf_ipc_parser_type *handle);
const void* gdf_ipc_parser_get_data(gdf_ipc_parser_type *handle);
int64_t gdf_ipc_parser_get_data_offset(gdf_ipc_parser_type *handle);

const char *gdf_ipc_parser_get_schema_json(gdf_ipc_parser_type *handle) ;
const char *gdf_ipc_parser_get_layout_json(gdf_ipc_parser_type *handle) ;

/*
 * gdf_arrow introspection utlities
 */

gdf_error get_column_byte_width(gdf_column * col, int * width);
