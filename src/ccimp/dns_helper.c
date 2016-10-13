/*
 * dns_helper.c
 *
 * Copyright (C) 2016 Digi International Inc., All Rights Reserved
 *
 * This software contains proprietary and confidential information of Digi.
 * International Inc. By accepting transfer of this copy, Recipient agrees
 * to retain this software in confidence, to prevent disclosure to others,
 * and to make no use of this software other than that for which it was
 * delivered. This is an unpublished copyrighted work of Digi International
 * Inc. Except as permitted by federal law, 17 USC 117, copying is strictly
 * prohibited.
 *
 * Restricted Rights Legend
 *
 * Use, duplication, or disclosure by the Government is subject to restrictions
 * set forth in sub-paragraph (c)(1)(ii) of The Rights in Technical Data and
 * Computer Software clause at DFARS 252.227-7031 or subparagraphs (c)(1) and
 * (2) of the Commercial Computer Software - Restricted Rights at 48 CFR
 * 52.227-19, as applicable.
 *
 * Digi International Inc. 11001 Bren Road East, Minnetonka, MN 55343
 *
 * Description: DNS helper.
 *
 */

#include "ccimp/ccimp_network.h"
#include "ccimp/ccimp_os.h"

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <errno.h>

#include "dns_helper.h"
#include "utils.h"

/*------------------------------------------------------------------------------
                             D E F I N I T I O N S
------------------------------------------------------------------------------*/
#define APP_DNS_CACHE_TIMEOUT	(24 * 3600)
#define APP_MAX_HOST_NAME		64

#define cast_for_alignment(cast, ptr)	((cast) ((void *) (ptr)))

/*------------------------------------------------------------------------------
                 D A T A    T Y P E S    D E F I N I T I O N S
------------------------------------------------------------------------------*/
typedef struct
{
	char name[APP_MAX_HOST_NAME];
	in_addr_t ip_addr;
	unsigned long sys_time;
	int is_redirected;
} dns_cache_t;

/*------------------------------------------------------------------------------
                    F U N C T I O N  D E C L A R A T I O N S
------------------------------------------------------------------------------*/
static int dns_cache_is_valid(char const * const device_cloud_url, in_addr_t * const ip_addr);
static int dns_resolve_name(char const * const domain_name, in_addr_t * const ip_addr);
static void dns_cache_update(char const * const device_cloud_url, in_addr_t const ip_addr);

/*------------------------------------------------------------------------------
                         G L O B A L  V A R I A B L E S
------------------------------------------------------------------------------*/
static dns_cache_t dns_cache = {"", INADDR_NONE, 0, 0};

/*------------------------------------------------------------------------------
                     F U N C T I O N  D E F I N I T I O N S
------------------------------------------------------------------------------*/
void dns_set_redirected(int const state)
{
	dns_cache.is_redirected = state;
}

void dns_cache_invalidate(void)
{
	dns_cache.ip_addr = INADDR_NONE;
}

int dns_resolve(char const * const device_cloud_url, in_addr_t * const ip_addr)
{
	int status = -1;

	if (device_cloud_url == NULL || ip_addr == NULL)
		goto done;

	*ip_addr = inet_addr(device_cloud_url);

	if (*ip_addr == INADDR_NONE) {
		if (!dns_cache_is_valid(device_cloud_url, ip_addr)) {
			if (dns_resolve_name(device_cloud_url, ip_addr) == 0) {
				dns_cache_update(device_cloud_url, *ip_addr);
			} else {
				log_error("dns_resolve(): Can't resolve DNS for %s", device_cloud_url);
				goto done;
			}
		}
	}
	status = 0;

done:
	return status;
}

static int dns_cache_is_valid(char const * const device_cloud_url, in_addr_t * const ip_addr)
{
	int valid = 0;

	if (!dns_cache.is_redirected) {
		if ((dns_cache.ip_addr != INADDR_NONE)
				&& (strncmp(dns_cache.name, device_cloud_url, APP_MAX_HOST_NAME) == 0)) {
			ccimp_os_system_up_time_t elapsed_time;

			ccimp_os_get_system_time(&elapsed_time);
			if ((elapsed_time.sys_uptime - dns_cache.sys_time) < APP_DNS_CACHE_TIMEOUT) {
				*ip_addr = dns_cache.ip_addr;
				valid = 1;
			}
		}
	}

	return valid;
}

static int dns_resolve_name(char const * const domain_name, in_addr_t * const ip_addr)
{
	int ret = -1;
	struct addrinfo *res_list;
	struct addrinfo *res;

	{
		struct addrinfo hint = { 0 };
		int error;

		hint.ai_socktype = SOCK_STREAM;
		hint.ai_family = AF_INET;
		error = getaddrinfo(domain_name, NULL, &hint, &res_list);
		if (error != 0) {
			log_error("dns_resolve_name(): DNS resolution failed for [%s]", domain_name);
			goto done;
		}
	}

	/* loop over all returned results and look for a IPv4 address */
	for (res = res_list; res; res = res->ai_next) {
		if (res->ai_family == PF_INET) {
			struct sockaddr_in * const sa = cast_for_alignment(struct sockaddr_in *, res->ai_addr);
			struct in_addr const ipv4_addr = sa->sin_addr;

			*ip_addr = ipv4_addr.s_addr;
			log_debug("dns_resolve_name(): ip address = [%s]", inet_ntoa(ipv4_addr));
			ret = 0;
			break;
		}
	}
	freeaddrinfo(res_list);

done:
	return ret;
}

static void dns_cache_update(char const * const device_cloud_url, in_addr_t const ip_addr)
{
	if (!dns_cache.is_redirected) {
		strncpy(dns_cache.name, device_cloud_url, APP_MAX_HOST_NAME - 1);
		dns_cache.name[APP_MAX_HOST_NAME - 1] = '\0';
		dns_cache.ip_addr = ip_addr;
		{
			ccimp_os_system_up_time_t system_up_time;

			ccimp_os_get_system_time(&system_up_time);
			dns_cache.sys_time = system_up_time.sys_uptime;
		}
	}
}

