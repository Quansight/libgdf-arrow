# TASK: Restructure libgdf-arrow to become more arrow alike

This is temporary document created to implement the given task.

## Overview



## Current state of libraries

### libgdf-arrow

Currently, libgdf-arrow has the following file structure:
```
libgdf-arrow/
  include/
    gdf-arrow/
      gdf-arrow.h
      utils.h
        bool gdf_arrow_is_valid(const gdf_arrow_valid_type *valid, gdf_arrow_index_type pos)
	gdf_arrow_size_type gdf_arrow_get_num_chars_bitmask(gdf_arrow_size_type size)
      errorutils.h
      cffi/
        functions.h
          gdf_arrow_size_type gdf_arrow_column_sizeof()
          gdf_arrow_error gdf_arrow_column_view(gdf_arrow_column *column, void *data, gdf_arrow_valid_type *valid,
                                                gdf_arrow_size_type size, gdf_arrow_dtype dtype);
          gdf_arrow_error gdf_arrow_column_view_augmented(gdf_arrow_column *column, void *data, gdf_arrow_valid_type *valid,
                                                gdf_arrow_size_type size, gdf_arrow_dtype dtype, gdf_arrow_size_type null_count);
          const char * gdf_arrow_error_get_name(gdf_arrow_error errcode)
          int gdf_arrow_cuda_last_error()
          const char * gdf_arrow_cuda_error_string(int cuda_error)
          const char * gdf_arrow_cuda_error_name(int cuda_error)
          gdf_arrow_ipc_parser_type* gdf_arrow_ipc_parser_open(const uint8_t *schema, size_t length)
          void gdf_arrow_ipc_parser_open_recordbatches(gdf_arrow_ipc_parser_type *handle,
                                             const uint8_t *recordbatches,
                                             size_t length)
          void gdf_arrow_ipc_parser_close(gdf_arrow_ipc_parser_type *handle)
          int gdf_arrow_ipc_parser_failed(gdf_arrow_ipc_parser_type *handle)
          const char* gdf_arrow_ipc_parser_to_json(gdf_arrow_ipc_parser_type *handle)
          const char* gdf_arrow_ipc_parser_get_error(gdf_arrow_ipc_parser_type *handle)
          const void* gdf_arrow_ipc_parser_get_data(gdf_arrow_ipc_parser_type *handle)
          int64_t gdf_arrow_ipc_parser_get_data_offset(gdf_arrow_ipc_parser_type *handle)
          const char *gdf_arrow_ipc_parser_get_schema_json(gdf_arrow_ipc_parser_type *handle)
          const char *gdf_arrow_ipc_parser_get_layout_json(gdf_arrow_ipc_parser_type *handle)
        types.h
	  size_t gdf_arrow_size_type gdf_arrow_index_type
	  unsigned char gdf_arrow_valid_type
	  enum gdf_arrow_dtype -> GDF_ARROW_INT8, GDF_ARROW_FLOAT32, GDF_ARROW_DATE32, ..., GDF_ARROW_TIMESTAMP
	  enum gdf_arrow_error -> GDF_ARROW_SUCCESS, ...
	  enum gdf_arrow_hash_func -> GDF_ARROW_HASH_MURMUR3
	  enum gdf_arrow_time_unit -> TIME_UNIT_s, ...
	  gdf_arrow_dtype_extra_info {
            gdf_arrow_time_unit time_unit
          }
	  enum gdf_arrow_method -> GDF_ARROW_SORT, ...
	  enum gdf_arrow_agg_op -> GDF_ARROW_SUM, ...
	  enum order_by_type -> GDF_ARROW_ORDER_ASC, ...
	  enum gdf_arrow_comparison_operator -> GDF_ARROW_EQUALS, ...
	  enum window_function_type -> GDF_ARROW_WINDOW_RANGE, ...
	  enum window_reduction_type -> GDF_ARROW_WINDOW_AVG, ...
	  gdf_arrow_context {
	    int flag_sorted;
	    gdf_arrow_method flag_method;
	    int flag_distinct;
	  }
          gdf_arrow_column {
            void *data;
            gdf_arrow_valid_type *valid;
            gdf_arrow_size_type size;
            gdf_arrow_dtype dtype;
            gdf_arrow_size_type null_count;
            gdf_arrow_dtype_extra_info dtype_info;
          }
	  gdf_arrow_dtype_extra_info {
            gdf_arrow_time_unit time_unit
          }
      ipc/
        api.h
        File_generated.h
        Message_generated.h
        Schema_generated.h
        Tensor_generated.h
  src/
    column.cpp
      gdf_arrow_column_sizeof()
      gdf_arrow_column_view(...)
      gdf_arrow_column_view_augmented(...)
      get_column_byte_width(...)      
    cudautils.cu
      gdf_arrow_cuda_last_error(...)
      gdf_arrow_cuda_error_string(...)
      gdf_arrow_cuda_error_name(...)
    errorhandling.cpp
      gdf_arrow_error_get_name(...)
    ipc.cu
      class IpcParser
        ...
        open(...)
        open_recordbatches(...)
        is_failed()
        get_error()
        get_data()
        get_data_offset()
        get_layout_json()
        get_schema_json()
        jsonify_node(...)
        jsonify_dtype(...)
        jsonify_buffer(...)
        read_schema(...)
        parse_schema(...)
        parse_record_batch(...)
        read_bytes(...)
        read_value(...)
        read_msg_size(...)
      cffi_wrap(...)
      cffi_unwrap(...)
      gdf_arrow_ipc_parser_open(...)
      gdf_arrow_ipc_parser_close(...)
      gdf_arrow_ipc_parser_failed(...)
      gdf_arrow_ipc_parser_get_schema_json(...)
      gdf_arrow_ipc_parser_get_layout_json(...)
      gdf_arrow_ipc_parser_get_error(...)
      gdf_arrow_ipc_parser_get_data(...)
      gdf_arrow_ipc_parser_get_data_offset(...)
      gdf_arrow_ipc_parser_open_recordbatches(...)
    tests/
      join/ - should be removed
  python/
    setup.py - builds 
    libgdf_arrow_cffi/
      __init__.py
        GDFARROWError
        libgdf_arrow - _libgdf_arrow_wrapper instance
        ffi - _cffi_backend.FFI instance
      libgdf_arrow_build.py - generator
      libgdf_arrow_cffi.py - generated, defines ffi
      wrapper.py
        _libgdf_arrow_wrapper - implementation
    tests/
      conftest.py
        rand_seed
      utils.py
        new_column()
        unwrap_devary(devary)
        get_dtype(dtype)
        seed_rand()
        gen_rand(dtype, size, **kwargs)
        fix_zeros(arr, val=1)
        buffer_as_bits(data)
      test_ipc.py
        test_arrow_availability()
        test_ipc()
  thirdparty/
    cub/
    moderngpu/
    
```

### Apache Arrow

arrow has the following file structure:
```
arrow/
  cpp/
    src/
      arrow/
        api.h
        ...
        adapters/
          ...
        compute/
          ...
        gpu/
          cuda_arrow_ipc.h
            Status SerializeRecordBatch(const RecordBatch& batch, CudaContext* ctx,
                                std::shared_ptr<CudaBuffer>* out)
            Status ReadMessage(CudaBufferReader* reader, MemoryPool* pool,
                                std::unique_ptr<ipc::Message>* message)
            Status ReadRecordBatch(const std::shared_ptr<Schema>& schema,
                                   const std::shared_ptr<CudaBuffer>& buffer, MemoryPool* pool,
                                   std::shared_ptr<RecordBatch>* out)
          cuda_context.h
            CudaDeviceManager
              Status GetInstance(CudaDeviceManager** manager)
              Status GetContext(int gpu_number, std::shared_ptr<CudaContext>* ctx)
              Status CreateNewContext(int gpu_number, std::shared_ptr<CudaContext>* ctx)
              Status AllocateHost(int64_t nbytes, std::shared_ptr<CudaHostBuffer>* buffer)
              Status FreeHost(void* data, int64_t nbytes)
              int num_devices()
            CudaContext : public std::enable_shared_from_this<CudaContext>
              Status Close()
              Status Allocate(int64_t nbytes, std::shared_ptr<CudaBuffer>* out)
              Status OpenIpcBuffer(const CudaIpcMemHandle& ipc_handle, std::shared_ptr<CudaBuffer>* buffer)
              int64_t bytes_allocated()
          cuda_memory.h
            CudaBuffer : Buffer - An Arrow buffer located on a GPU device
              CudaBuffer(uint8_t* data,
                         int64_t size,
                         const std::shared_ptr<CudaContext>& context,
                         bool own_data = false, bool is_ipc = false)
              CudaBuffer(const std::shared_ptr<CudaBuffer>& parent,
                         const int64_t offset, const int64_t size)
              Status FromBuffer(std::shared_ptr<Buffer> buffer, std::shared_ptr<CudaBuffer>* out)
              Status CopyToHost(const int64_t position, const int64_t nbytes, void* out)
              Status CopyFromHost(const int64_t position, const void* data, int64_t nbytes)
              Status ExportForIpc(std::shared_ptr<CudaIpcMemHandle>* handle)
              std::shared_ptr<CudaContext> context()
            CudaHostBuffer : MutableBuffer - Device-accessible CPU memory created using cudaHostAlloc
            CudaIpcMemHandle
              Status FromBuffer(const void* opaque_handle,
                         std::shared_ptr<CudaIpcMemHandle>* handle)
              Status Serialize(MemoryPool* pool, std::shared_ptr<Buffer>* out)
            CudaBufferReader : io::BufferReader
              CudaBufferReader(...)
              Status Read(int64_t nbytes, int64_t* bytes_read, void* buffer)
              Status Read(int64_t nbytes, std::shared_ptr<Buffer>* out)
            CudaBufferWriter : io::WriteableFile
              CudaBufferWriter(const std::shared_ptr<CudaBuffer>& buffer)
              Status Close()
              Status Flush()
              Status Seek(int64_t position)
              Status Write(const void* data, int64_t nbytes)
              Status WriteAt(int64_t position, const void* data, int64_t nbytes)
              Status Tell(int64_t* position)
              Status SetBufferSize(const int64_t buffer_size)
              int64_t buffer_size()
              int64_t num_bytes_buffered()
            Status AllocateCudaHostBuffer(const int64_t size, std::shared_ptr<CudaHostBuffer>* out)
        io/
          ...
        ipc/
          dictionary.h
            DictionaryMemo
              DictionaryMemo(...)
              GetDictionary(...)
              GetId(...)
              HasDictionary(...)
              HasDictionaryId(...)
              AddDictionary(...)
              id_to_dictionary(...)
              size()
          feather.h
            TableReader
              TableReader(...)
              Open(...)
              GetDescription(...)
              HasDescription(...)
              version(...)
              num_rows(...)
              num_columns(...)
              GetColumnName(...)
              GetColumn(...)
          json.h
            JsonWriter
              Open(...)
              WriteRecordBatch(...)
              Finish(...)
            JsonReader
              Open(...)
              schema()
              num_record_batches()
              ReadRecordBatch()
          message.h
            MetadataVersion
            Message
              Type
              Message(...)
              Open(...)
              ReadFrom(...)
              Equals(...)
              metadata()
              body()
              type()
              metadata_version()
              header()
              SerializeTo()
            MessageReader
              Open(...)
              ReadNextMessage(...)
            ReadMessage(...)
          reader.h
            RecordBatchStreamReader
              Open(...)
              schema()
              ReadNext(...)
            RecordBatchFileReader
              Open(...)
              schema()
              num_record_batches()
              version()
              ReadRecordBatch(...)
            ReadSchema(...)
            ReadRecordBatch(...)
            ReadTensor(...)
          writer.h
            RecordBatchWriter
              WriteRecordBatch(...)
              WriteTable(...)
              Close()
              set_memory_pool(...)
            RecordBatchStreamWriter : RecordBatchWriter
              Open(...)
              WriteRecordBatch(...)
              Close(...)
              set_memory_pool(...)
            RecordBatchFileWriter : RecordBatchStreamWriter
              Open(...)
              WriteRecordBatch(...)
              Close(...)
            WriteRecordBatch(...)
            SerializeRecordBatch(...)
            SerializeSchema(...)
            WriteRecordBatchStream(...)
            GetRecordBatchSize(...)
            GetTensorSize(...)
            GetTensorMessage(...)
            WriteTensor(...)
          ...
        python/
          ...
        util/
          ...
      plasma/
        ...
    thirdparty/
      hadoop/
      jemalloc/
  ...
```

### pygdf

libgdf is used in the following parts of the pygdf:
```
pygdf/
  _gdf.py
    _columnview
      libgdf.gdf_column_view
    columnview_from_devary
      _columnview
    columnview
      _columnview
    apply_mask_and
      libgdf.gdf_validity_and
    np_to_gdf_dtype
      libgdf.GDF_FLOAT64, etc
    apply_reduce
      libgdf.gdf_reduce_optimal_output_size
    apply_prefixsum
      libgdf.gdf_prefixsum_generic
    apply_binaryop, apply_unaryop, apply_mask_and, apply_reduce, apply_sort, apply_join, SegmentedRadixortPlan.sort, hash_columns
      .cffi_view
    ...
  column.py
    class Column(object)
      .cffi_view
        _gdf.columnview
  libgdf_groupby.py
    LibGdfGroupby._apply_agg
      .cffi_view
  cudautils.py
    prefixsum
      _gdf.columnview_from_devary
      _gdf.apply_prefixsum
    mask_assign_slot
      prefixsum
    find_segments
      prefixsum
  gpuarrow.py
    class GpuArrowReader(Sequence)
      __init__, __len__, __getitem__, to_dict
      _open
        _parse_metdata
      _parse_metdata
        ffi.string, ffi.cast
        libgdf.gdf_ipc_parser_open
        libgdf.gdf_ipc_parser_close
        libgdf.gdf_ipc_parser_get_error
        libgdf.gdf_ipc_parser_open_recordbatches
        libgdf.gdf_ipc_parser_get_schema_json
        libgdf.gdf_ipc_parser_get_layout_json
        libgdf.gdf_ipc_parser_get_data_offset
```