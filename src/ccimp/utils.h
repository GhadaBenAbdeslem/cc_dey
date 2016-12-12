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

#ifndef UTILS_H_
#define UTILS_H_

#include "ccapi/ccapi.h"
#include "load_config.h"

/*------------------------------------------------------------------------------
                    F U N C T I O N  D E C L A R A T I O N S
------------------------------------------------------------------------------*/
ccapi_start_t *create_ccapi_start_struct(const cc_cfg_t *const cc_cfg);
ccapi_tcp_info_t *create_ccapi_tcp_start_info_struct(const cc_cfg_t *const cc_cfg);
void free_ccapi_start_struct(ccapi_start_t *ccapi_start);
void free_ccapi_tcp_start_info_struct(ccapi_tcp_info_t *const tcp_info);
void add_virtual_directories(const vdir_t *const vdirs, int n_vdirs);
int start_system_monitor(const cc_cfg_t *const cc_cfg);
void stop_system_monitor(void);

#endif /* UTILS_H_ */
