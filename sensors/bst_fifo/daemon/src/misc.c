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
 * @file         misc.c
 * @date         "Thu Jan 8 18:20:01 2015 +0800"
 * @commit       "4b0860f"
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
#include "version.h"

#define LOG_TAG_MODULE "<init>"
#include "sensord.h"

extern void trace_init();

void dump_ver()
{
	ts_version version;

	(void)bsx_get_version(&version);

	PINFO("algorithm version: %d.%d.%d.%d",
			version.major, version.minor,
			version.majorbugFix, version.minorbugFix);
	PINFO("daemon version: %s", get_daemon_version());
	PINFO("build date: %s", get_build_date());

}

void write_version(int fd)
{
	char buf[128];
	ts_version version;

	sprintf(buf, "========\nsensord: %s\n", get_daemon_version());
	write(fd, buf, strlen(buf));
	sprintf(buf, "build_date: %s\n", get_build_date());
	write(fd, buf, strlen(buf));
	(void)bsx_get_version(&version);
	sprintf(buf, "algo_version: %d.%d.%d.%d\n========\n\n", version.major,
				version.minor,
				version.majorbugFix,
				version.minorbugFix);
	write(fd, buf, strlen(buf));
}

/*
 * @Description: this function will make a landmark
 *
 */
static void mark_land_owner()
{
	int fd;

	fd = open(PROCESS_LANDMARK, O_RDWR | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR |
			S_IRGRP | S_IWGRP |
			S_IROTH | S_IWOTH);
	if (-1 != fd) {
		fchmod(fd, 0644);
		txt_file_write_int(fd, getpid(), 1, 1);
		close(fd);
	}
}


void storage_init()
{
	char *path = NULL;
	int err = 0;
	struct stat st;

	path = PATH_DIR_SENSOR_STORAGE;

	err = access(path, F_OK);
	if (!err) {
		st.st_mode = ~S_IFDIR;
		err = stat(path, &st);
		if (!S_ISDIR(st.st_mode)) {
			PWARN("a file of the same name exists");
			/* mark error explicitly for creating the dir */
			err = -ENOTDIR;
		}
	}

	if (err) {
		PINFO("create path of storage");
		unlink(path);
		err = mkdir(path, 0777);
		if (err) {
			PERR("error creating storage dir");
		}
	}

	err = chmod(path, 0777);
	if (err) {
		PERR("error chmod on %s", path);
	}
}

int misc_init()
{
	int err = 0;

	storage_init();
	mark_land_owner();
	trace_init();

	PINFO("<<------sensord <%d> started------>>", getpid());

	dump_ver();
	time_init();

	return err;
}
