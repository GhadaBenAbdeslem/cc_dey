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

#include <stdio.h>
#include "ccapi/ccapi.h"
#include "ccapi_rci_functions.h"
#include "cc_logging.h"

ccapi_global_error_id_t rci_session_start_cb(ccapi_rci_info_t * const info)
{
	UNUSED_PARAMETER(info);
	log_debug("    Called '%s'", __func__);

	return CCAPI_GLOBAL_ERROR_NONE;
}

ccapi_global_error_id_t rci_session_end_cb(ccapi_rci_info_t * const info)
{
	UNUSED_PARAMETER(info);
	log_debug("    Called '%s'", __func__);

	return CCAPI_GLOBAL_ERROR_NONE;
}

ccapi_global_error_id_t rci_action_start_cb(ccapi_rci_info_t * const info)
{
	UNUSED_PARAMETER(info);
	log_debug("    Called '%s'", __func__);

	return CCAPI_GLOBAL_ERROR_NONE;
}

ccapi_global_error_id_t rci_action_end_cb(ccapi_rci_info_t * const info)
{
	UNUSED_PARAMETER(info);
	log_debug("    Called '%s'", __func__);

	return CCAPI_GLOBAL_ERROR_NONE;
}

ccapi_global_error_id_t rci_do_command_cb(ccapi_rci_info_t * const info)
{
	UNUSED_PARAMETER(info);
	log_debug("    Called '%s'", __func__);

	log_error("%s", "RCI request for do_command not implemented.");
	return CCAPI_GLOBAL_ERROR_NOT_IMPLEMENTED;
}

ccapi_global_error_id_t rci_set_factory_defaults_cb(ccapi_rci_info_t * const info)
{
	UNUSED_PARAMETER(info);
	log_debug("    Called '%s'", __func__);

	log_error("%s", "RCI request for factory_defaults not implemented.");
	return CCAPI_GLOBAL_ERROR_NOT_IMPLEMENTED;
}

ccapi_global_error_id_t rci_reboot_cb(ccapi_rci_info_t * const info)
{
	UNUSED_PARAMETER(info);
	log_debug("    Called '%s'", __func__);

	log_error("%s", "RCI request for reboot not implemented.");
	return CCAPI_GLOBAL_ERROR_NOT_IMPLEMENTED;
}

