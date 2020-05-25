/* (c) 2019 Confio UO. Licensed under Apache-2.0 */

/* Generated with cbindgen:0.14.2 */

/* Warning, this file is autogenerated by cbindgen. Don't modify this manually. */

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

enum ErrnoValue {
  ErrnoValue_Success = 0,
  ErrnoValue_Other = 1,
  ErrnoValue_OutOfGas = 2,
};
typedef int32_t ErrnoValue;

/**
 * This enum gives names to the status codes returned from Go callbacks to Rust.
 *
 * The go code will return one of these variants when returning.
 *
 */
enum GoResult {
  GoResult_Ok = 0,
  /**
   * Go panicked for an unexpected reason.
   */
  GoResult_Panic = 1,
  /**
   * Go received a bad argument from Rust
   */
  GoResult_BadArgument = 2,
  /**
   * Ran out of gas while using the SDK (e.g. storage)
   */
  GoResult_OutOfGas = 3,
  /**
   * An error happened during normal operation of a Go callback
   */
  GoResult_Other = 4,
};
typedef int32_t GoResult;

typedef struct Buffer {
  uint8_t *ptr;
  uintptr_t len;
  uintptr_t cap;
} Buffer;

typedef struct cache_t {

} cache_t;

typedef struct db_t {
  uint8_t _private[0];
} db_t;

typedef struct iterator_t {
  uint8_t _private[0];
} iterator_t;

typedef struct Iterator_vtable {
  int32_t (*next_db)(iterator_t*, Buffer*, Buffer*);
} Iterator_vtable;

typedef struct GoIter {
  iterator_t *state;
  Iterator_vtable vtable;
} GoIter;

typedef struct DB_vtable {
  int32_t (*read_db)(db_t*, Buffer, Buffer*);
  int32_t (*write_db)(db_t*, Buffer, Buffer);
  int32_t (*remove_db)(db_t*, Buffer);
  int32_t (*scan_db)(db_t*, Buffer, Buffer, int32_t, GoIter*);
} DB_vtable;

typedef struct DB {
  db_t *state;
  DB_vtable vtable;
} DB;

typedef struct api_t {
  uint8_t _private[0];
} api_t;

typedef struct GoApi_vtable {
  int32_t (*humanize_address)(const api_t*, Buffer, Buffer*);
  int32_t (*canonicalize_address)(const api_t*, Buffer, Buffer*);
} GoApi_vtable;

typedef struct GoApi {
  const api_t *state;
  GoApi_vtable vtable;
} GoApi;

typedef struct querier_t {
  uint8_t _private[0];
} querier_t;

typedef struct Querier_vtable {
  int32_t (*query_external)(const querier_t*, Buffer, Buffer*);
} Querier_vtable;

typedef struct GoQuerier {
  const querier_t *state;
  Querier_vtable vtable;
} GoQuerier;

Buffer allocate_rust(const uint8_t *ptr, uintptr_t length);

Buffer create(cache_t *cache, Buffer wasm, Buffer *err);

void free_rust(Buffer buf);

Buffer get_code(cache_t *cache, Buffer id, Buffer *err);

Buffer handle(cache_t *cache,
              Buffer code_id,
              Buffer params,
              Buffer msg,
              DB db,
              GoApi api,
              GoQuerier querier,
              uint64_t gas_limit,
              uint64_t *gas_used,
              Buffer *err);

cache_t *init_cache(Buffer data_dir, Buffer supported_features, uintptr_t cache_size, Buffer *err);

Buffer instantiate(cache_t *cache,
                   Buffer contract_id,
                   Buffer params,
                   Buffer msg,
                   DB db,
                   GoApi api,
                   GoQuerier querier,
                   uint64_t gas_limit,
                   uint64_t *gas_used,
                   Buffer *err);

Buffer query(cache_t *cache,
             Buffer code_id,
             Buffer msg,
             DB db,
             GoApi api,
             GoQuerier querier,
             uint64_t gas_limit,
             uint64_t *gas_used,
             Buffer *err);

/**
 * frees a cache reference
 *
 * # Safety
 *
 * This must be called exactly once for any `*cache_t` returned by `init_cache`
 * and cannot be called on any other pointer.
 */
void release_cache(cache_t *cache);
