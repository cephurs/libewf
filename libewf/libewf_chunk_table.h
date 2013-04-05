/*
 * Chunk table functions
 *
 * Copyright (c) 2006-2013, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#if !defined( _LIBEWF_CHUNK_TABLE_H )
#define _LIBEWF_CHUNK_TABLE_H

#include <common.h>
#include <types.h>

#include "libewf_io_handle.h"
#include "libewf_libbfio.h"
#include "libewf_libcerror.h"
#include "libewf_libfcache.h"
#include "libewf_libfdata.h"
#include "libewf_section.h"

#include "ewf_table.h"

/* TODO refactor */
#include "libewf_libmfdata.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libewf_chunk_table libewf_chunk_table_t;

struct libewf_chunk_table
{
	/* The IO handle
	 */
	libewf_io_handle_t *io_handle;

	/* The chunk size
	 */
	uint32_t chunk_size;

	/* The format version
	 */
	uint8_t format_version;

	/* The previous last chunk that was filled
	 */
	int previous_last_chunk_filled;

	/* The last chunk that was filled
	 */
	int last_chunk_filled;

	/* The last chunk that was compared
	 */
	int last_chunk_compared;

	/* The sectors with checksum errors
	 */
	libcdata_range_list_t *checksum_errors;
};

int libewf_chunk_table_initialize(
     libewf_chunk_table_t **chunk_table,
     libewf_io_handle_t *io_handle,
     libcerror_error_t **error );

int libewf_chunk_table_free(
     libewf_chunk_table_t **chunk_table,
     libcerror_error_t **error );

int libewf_chunk_table_clone(
     libewf_chunk_table_t **destination_chunk_table,
     libewf_chunk_table_t *source_chunk_table,
     libcerror_error_t **error );

int libewf_chunk_table_get_number_of_checksum_errors(
     libewf_chunk_table_t *chunk_table,
     uint32_t *number_of_errors,
     libcerror_error_t **error );

int libewf_chunk_table_get_checksum_error(
     libewf_chunk_table_t *chunk_table,
     uint32_t index,
     uint64_t *start_sector,
     uint64_t *number_of_sectors,
     libcerror_error_t **error );

int libewf_chunk_table_append_checksum_error(
     libewf_chunk_table_t *chunk_table,
     uint64_t start_sector,
     uint64_t number_of_sectors,
     libcerror_error_t **error );

int libewf_chunk_table_read_chunk(
     intptr_t *io_handle,
     libbfio_pool_t *file_io_pool,
     libmfdata_list_element_t *list_element,
     libfcache_cache_t *cache,
     int file_io_pool_entry,
     off64_t element_data_offset,
     size64_t element_data_size,
     uint32_t element_data_range_flags,
     uint8_t read_flags,
     libcerror_error_t **error );

int libewf_chunk_table_read_offsets(
     intptr_t *io_handle,
     libbfio_pool_t *file_io_pool,
     libmfdata_list_t *chunk_table_list,
     int element_index,
     int number_of_elements,
     libfcache_cache_t *cache,
     int file_io_pool_entry,
     off64_t element_group_offset,
     size64_t element_group_size,
     uint32_t element_group_flags,
     uint8_t read_flags,
     libcerror_error_t **error );

int libewf_chunk_table_fill_v1(
     libewf_chunk_table_t *chunk_table,
     libmfdata_list_t *chunk_table_list,
     int chunk_index,
     int file_io_pool_entry,
     libewf_section_t *table_section,
     off64_t base_chunk,
     uint32_t number_of_offsets,
     const uint8_t *table_entries_data,
     size_t table_entries_data_size,
     uint8_t tainted,
     libcerror_error_t **error );

int libewf_chunk_table_fill_v2(
     libewf_chunk_table_t *chunk_table,
     libmfdata_list_t *chunk_table_list,
     int chunk_index,
     int file_io_pool_entry,
     libewf_section_t *table_section,
     uint32_t number_of_offsets,
     const uint8_t *table_entries_data,
     size_t table_entries_data_size,
     uint8_t tainted,
     libcerror_error_t **error );

int libewf_chunk_table_correct_v1(
     libewf_chunk_table_t *chunk_table,
     libmfdata_list_t *chunk_table_list,
     int chunk_index,
     int file_io_pool_entry,
     libewf_section_t *table_section,
     off64_t base_chunk,
     uint32_t number_of_offsets,
     const uint8_t *table_entries_data,
     size_t table_entries_data_size,
     uint8_t tainted,
     libcerror_error_t **error );

int libewf_chunk_table_generate_table_entries_data(
     libmfdata_list_t *chunk_table_list,
     int chunk_index,
     uint8_t format_version,
     uint8_t *table_entries_data,
     size_t table_entries_data_size,
     uint32_t number_of_entries,
     off64_t base_offset,
     libcerror_error_t **error );

/* TODO */

/* TODO fix cyclic dependency with segment file
int libewf_chunk_table_get_segment_file_chunk_group_by_offset(
     libewf_chunk_table_t *chunk_table,
     libbfio_pool_t *file_io_pool,
     libfdata_list_t *segment_files_list,
     libfcache_cache_t *segment_files_cache,
     off64_t offset,
     int *segment_files_list_index,
     off64_t *segment_file_data_offset,
     libewf_segment_file_t **segment_file,
     int *chunk_groups_list_index,
     off64_t *chunk_group_data_offset,
     libfdata_list_t **chunks_list,
     libcerror_error_t **error );
*/

int libewf_chunk_table_chunk_exists_for_offset(
     libewf_chunk_table_t *chunk_table,
     uint64_t chunk_index,
     libbfio_pool_t *file_io_pool,
     libfdata_list_t *segment_files_list,
     libfcache_cache_t *segment_files_cache,
     off64_t offset,
     libcerror_error_t **error );

int libewf_chunk_table_get_chunk_data_by_offset(
     libewf_chunk_table_t *chunk_table,
     uint64_t chunk_index,
     libewf_io_handle_t *io_handle,
     libbfio_pool_t *file_io_pool,
     libewf_media_values_t *media_values,
     libfdata_list_t *segment_files_list,
     libfcache_cache_t *segment_files_cache,
     libfcache_cache_t *chunks_list_cache,
     off64_t offset,
     libewf_chunk_data_t **chunk_data,
     off64_t *chunk_data_offset,
     libcerror_error_t **error );

int libewf_chunk_table_set_chunk_data_by_offset(
     libewf_chunk_table_t *chunk_table,
     uint64_t chunk_index,
     libbfio_pool_t *file_io_pool,
     libfdata_list_t *segment_files_list,
     libfcache_cache_t *segment_files_cache,
     libfcache_cache_t *chunks_list_cache,
     off64_t offset,
     libewf_chunk_data_t *chunk_data,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif

