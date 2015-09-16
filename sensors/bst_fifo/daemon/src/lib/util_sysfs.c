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
#include <errno.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define LOG_TAG_MODULE "<util_sysfs>"
#include "sensord.h"

int sysfs_get_input_dev_num(const char *pname)
{
	int num = -1;

	int fd = -1;
	char sysfs_node_path[128] = "";
	char dev_name[128] = "";        /* NOTE: limitation */
	int i;
	int len = strlen(pname);

	for (i = 0; i < MAX_INPUT_DEV_NUM; i++) {
		sprintf(sysfs_node_path, "%s/input%d/name",
				SYSFS_PATH_INPUT_DEV, i);
		fd = open(sysfs_node_path, O_RDONLY);
		if (-1 != fd) {
			memset(dev_name, 0, sizeof(dev_name));
			read(fd, dev_name, sizeof(dev_name) - 1);
			PDEBUG("dev name: %s len_dev_name: %d pname: %s len: %d",
					dev_name, strlen(dev_name), pname, len);
			close(fd);

			if (0 == strncmp(dev_name, pname, len)) {
				num = i;
				break;
			}
		}
	}

	if (-1 == num) {
		PWARN("cannot find input syspath with name: %s", pname);
	}

	return num;
}


int sysfs_read_int(const char *path, int *value)
{
	int fd;
	size_t count;
	char buf[32] = "";
	int err = 0;

	fd = open(path, O_RDONLY);
	if(fd < 0) {
		PERR("error openning file: %s", path);
		close(fd);
		return -EIO;
	}

	count = read(fd, buf, sizeof(buf) - 1);
	if (count > 0) {
		buf[count] = 0;
		sscanf(buf, "%11d", value);
	} else {
		PERR("error reading from file: %s", path);
		err = -EIO;
	}

	close(fd);

	return err;
}


int sysfs_write_int(const char *path, int value)
{
    int fd;
    int tmp;
    int err = 0;
    char buffer[16] = "";

    fd = open(path, O_WRONLY);
    if (-1 != fd) {
        tmp = sprintf(buffer, "%d\n", value);
        err = write(fd, buffer, tmp);
        if (err < tmp) {
            PERR("err writing to file: %s result: %d", path, err);
            err = -EIO;
        } else {
            err = 0;
        }
        close(fd);
    } else {
        PERR("failed to open %s", path);
        err = -EIO;
    }

    return err;
}


int sysfs_open_input_dev_node(int input_dev_num, const char *name, int mode)
{
	int fd;
	char sysfs_node_path[64] = "";

	sprintf(sysfs_node_path, "%s/input%d/%s",
			SYSFS_PATH_INPUT_DEV, input_dev_num, name);
	fd = open(sysfs_node_path, mode);

	if (-1 == fd) {
		PERR("error openning file: %s", sysfs_node_path);
	}

	return fd;
}


FILE *sysfs_fopen_input_dev_node(int input_dev_num, const char *name, char *mode)
{
	FILE *fp = NULL;
	char sysfs_node_path[64] = "";

	sprintf(sysfs_node_path, "%s/input%d/%s",
			SYSFS_PATH_INPUT_DEV, input_dev_num, name);
	fp = fopen(sysfs_node_path, mode);

	return fp;
}

/*!
 *
 * @brief this function attempts to open a file to read up to 'size' bytes from
 * that file into 'buf'
 *
 * @param[i]   filename   filename to be read
 * @param[o]  buf           out put data buffer
 * @param[i]   size          input size to be read, size must be less or
 *                                   equal than 'buf' size
 *
 * @return     >= 0 success. or -1 failed
 * @retval      >=0 the count of true read size
 * @retval      -1    failed to open or read file
 */
int util_fs_read_file(const char *filename, void *buf, int size)
{
	int fd;
	int len;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		PERR("file: %s does not exist", filename);
		close(fd);
		return -1;
	}

	len = read(fd, buf, size);

	if (len == -1)
	{
		PERR("file :%s, failed to read", filename);
	}
	
	close(fd);
	return len;
}

/*!
 *
 * @brief this function attempts to open a file to write up to 'size' bytes to
 * that file from 'buf'
 *
 * @detail If file exists, content will be replaced with new.
 *            If file does not exist, new file will be created
 *
 * @param[i]   filename   filename to be read
 * @param[i]  buf            input data buffer
 * @param[i]   size          input size to be writen, size must be less or
 *                                   equal than 'buf' size
 *
 * @return     >= 0 success. or -1 failed
 * @retval      >=0 the count of true read size
 * @retval      -1    failed to open or read file
 */
int util_fs_write_file(const char *filename, void *buf, int size)
{
	int fd;
	int len;

	fd = open(filename, O_RDWR | O_TRUNC | O_CREAT,
			(S_IRWXU | S_IRWXG | S_IRWXO));
	if (fd < 0)
	{
		PERR("file: %s does not exist", filename);
		close(fd);
		return -1;
	}

	len = write(fd, buf, size);
	if (len == -1)
	{
		PERR("file:%s, failed to write!", filename);
	}
	close(fd);
	return len;
}

/*!
 * @brief This function atempts to get the size of the file
 *
 * @param[i]  filename   target filename
 *
 * @return >= 0 success, return the file size, or -1 failed.
 *
 * @retval >=0, file size
 * @retval -1,    failed to get file size
 *
 */
int util_fs_get_filesize(const char *filename)
{
	int fd;
	int len;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		close(fd);
		return -1;
	}

	len = lseek(fd, 0, SEEK_END);
	close(fd);
	return len;
}

/*!
 * @brief This function detects whether a file is existing or not
 *
 * @param[i]   filename     input file name
 *
 * @return 0 file exist, or -1 file does not exist
 */
int util_fs_is_file_exist(const char *filename)
{
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		close(fd);
		return -1;
	}
	close(fd);
	return 0;
}
