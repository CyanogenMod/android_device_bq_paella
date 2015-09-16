/*!
 * @section LICENSE
 *
 * (C) Copyright 2011~2015 Bosch Sensortec GmbH All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *
 * @file         trace.c
 * @date         "Wed Dec 31 15:33:20 2014 +0800"
 * @commit       "7b2e44c"
 *
 * @brief
 *
 * @detail
 *
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <linux/ioctl.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <stdarg.h>

#define LOG_TAG_MODULE "<trace>"
#include "sensord.h"

#define SENSORD_TRACE_FILE (PATH_DIR_SENSOR_STORAGE "/sensord.log")
#define SENSORD_EARLY_TRACE_FILE (PATH_DIR_DATA "/sensor.log")

extern void dump_ver();

#ifdef CFG_LOG_TO_FILE
int g_fd_trace = -1;
#endif

void early_trace_init()
{
#ifdef CFG_LOG_TO_FILE
	char *path = SENSORD_EARLY_TRACE_FILE;
	int fd = -1;

	fd = open(path,
			O_CREAT | O_TRUNC | O_WRONLY | O_SYNC,
			S_IRUSR | S_IWUSR |
			S_IRGRP | S_IWGRP |
			S_IROTH | S_IWOTH);
	if (-1 != fd) {
		fchmod(fd, 0666);
	}

	g_fd_trace = fd;

	PINFO("pid: %d", getpid());
#endif
}


void trace_init()
{
#ifdef CFG_LOG_TO_FILE
	char *path = SENSORD_EARLY_TRACE_FILE;

	if (-1 != g_fd_trace) {
		close(g_fd_trace);
		unlink(path);
	}

	g_fd_trace = open(SENSORD_TRACE_FILE,
			O_CREAT | O_TRUNC | O_WRONLY | O_SYNC,
			S_IRUSR | S_IWUSR |
			S_IRGRP | S_IWGRP |
			S_IROTH | S_IWOTH);

	if (-1 != g_fd_trace) {
		fchmod(g_fd_trace, 0666);
		write_version(g_fd_trace);
	}
#endif
}


void trace_log(int fd, const char *fmt, ...)
{
	int ret;
	va_list ap;
	char buf[512];

	va_start(ap, fmt);
	ret = vsnprintf(buf, sizeof(buf), fmt, ap);
	va_end(ap);

	if (ret > 0) {
		ret = write(fd, buf, ret);
	}

	fsync(fd);
}


void trace_flush(int fd)
{
	fsync(fd);
}
