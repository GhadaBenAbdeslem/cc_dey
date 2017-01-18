/*
 * Copyright (c) 2017 Digi International Inc.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 *
 * Digi International Inc. 11001 Bren Road East, Minnetonka, MN 55343
 * =======================================================================
 */

#ifndef DATA_POINT_H_
#define DATA_POINT_H_

#include <cloudconnector.h>

#define DATA_POINTS_BATCH_SIZE 10

ccapi_dp_error_t init_sample_data_stream(ccapi_dp_collection_handle_t *dp_collection);
ccapi_dp_error_t add_sample_data_point(ccapi_dp_collection_handle_t dp_collection);
ccapi_dp_error_t send_sample_data_stream(ccapi_dp_collection_handle_t dp_collection);
ccapi_dp_error_t destroy_sample_data_stream(ccapi_dp_collection_handle_t dp_collection);

#endif /* DATA_POINT_H_ */
