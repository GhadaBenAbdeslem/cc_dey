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

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "file_utils.h"
#include "cc_logging.h"

/**
 * file_exists() - Check that the file with the given name exists
 *
 * @filename:	Full path of the file to check if it exists.
 *
 * Return: 1 if the file exits, 0 if it does not exist.
 */
int file_exists(const char * const filename)
{
	return access(filename, F_OK) == 0;
}

/**
 * file_readable() - Check that the file with the given name can be read
 *
 * @filename:	Full path of the file to check if it is readable.
 *
 * Return: 1 if the file is readable, 0 if it cannot be read.
 */
int file_readable(const char * const filename)
{
	return access(filename, R_OK) == 0;
}

/**
 * file_writable() - Check that the file with the given name can be written
 *
 * @filename:	Full path of the file to check if it is writable.
 *
 * Return: 1 if the file is writable, 0 if it cannot be written.
 */
int file_writable(const char * const filename)
{
	return access(filename, W_OK) == 0;
}

/**
 * read_file_line() - Read the first line of the file and return its contents
 *
 * @path:			Absolute path of the file to read.
 * @buffer:			Buffer to store the contents of the file.
 * @bytes_to_read:	The number of bytes to read.
 *
 * Return: 0 on success, -1 on error.
 */
int read_file_line(const char * const path, char *buffer, int bytes_to_read)
{
	FILE *fd = NULL;
	int error = 0;

	if (!file_readable(path)) {
		log_error("%s: file is not readable: %s", __func__, path);
		return -1;
	}
	if ((fd = fopen(path, "rb")) == NULL) {
		log_error("%s: fopen error: %s", __func__, path);
		return -1;
	}
	if (fgets(buffer, bytes_to_read, fd) == NULL) {
		log_error("%s: fgets error: %s", __func__, path);
		error = -1;
	}
	fclose(fd);

	return error;
}

/**
 * write_to_file() - Write data to a file
 *
 * @path:		Absolute path of the file to be written.
 * @format:		String that contains the text to be written to the file.
 *
 * Return: 0 if the file was written successfully, -1 otherwise.
 */
int write_to_file(const char * const path, const char * const format, ...)
{
	va_list args;
	FILE *f = NULL;
	int len, error = 0;

	if (!file_writable(path)) {
		log_error("%s: file cannot be written: %s", __func__, path);
		return -1;
	}
	va_start(args, format);
	f = fopen(path, "w");
	if (f == NULL) {
		log_error("%s: fopen error: %s", __func__, path);
		error = -1;
		goto done;
	}
	len = vfprintf(f, format, args);
	if (len < 0) {
		log_error("%s: vfprintf error: %s", __func__, path);
		error = -1;
	}
	fsync(fileno(f));
	fclose(f);

done:
	va_end(args);

	return error;
}
