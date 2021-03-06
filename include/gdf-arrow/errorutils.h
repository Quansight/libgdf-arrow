#ifndef GDF_ARROW_ERRORUTILS_H
#define GDF_ARROW_ERRORUTILS_H

#define CUDA_TRY(x) if ((x)!=cudaSuccess) return GDF_ARROW_CUDA_ERROR;

#define CUDA_CHECK_LAST() CUDA_TRY(cudaPeekAtLastError())


#define GDF_ARROW_REQUIRE(F, S) if (!(F)) return (S);

#endif // GDF_ARROW_ERRORUTILS_H
