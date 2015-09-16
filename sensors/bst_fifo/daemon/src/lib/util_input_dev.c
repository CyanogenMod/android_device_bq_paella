/*!
 * @section LICENSE
 * $license$
 *
 * @file         $filename$
 * @date         $date$
 * @commit       $id$
 *
 * @brief
 *
 * @detail
 *
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/input.h>

#define LOG_TAG_MODULE "<util_input_dev>"
#include "sensord.h"

int input_get_event_num(const char *pname)
{
	int num = -1;
	int i;
	char filename[64];
	int err;
	char ev_name[64];
	int fd;

	for (i = 0; i < MAX_INPUT_DEV_NUM; i++) {
		sprintf(filename, "/dev/input/event%d", i);
		fd = open(filename, O_RDONLY);
		if (fd >= 0) {
			err = ioctl(fd, EVIOCGNAME(sizeof(ev_name) - 1), &ev_name);
			PINFO("err: %d ev_name: %s", err, ev_name);
			if (err < 1) {
				ev_name[0] = '\0';
			}

			if (0 == strcmp(ev_name, pname)) {
				num = i;
				close(fd);
				break;
			}

			close(fd);
		}
	}

	if (-1 == num) {
		PWARN("cannot find input event for: %s", pname);
	}
	
	return num;
}


int input_open_ev_fd(int num)
{
	int fd_ev;
	char sysfs_node_path[64] = "";

	sprintf(sysfs_node_path, "/dev/input/event%d", 
			num);
	fd_ev = open(sysfs_node_path, O_RDONLY);
	if (-1 == fd_ev) {
		PERR("error openning input event: %s", sysfs_node_path);
	}

	return fd_ev;
}
