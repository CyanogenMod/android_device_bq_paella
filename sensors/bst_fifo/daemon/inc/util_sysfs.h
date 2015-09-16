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
 * @file         util_sysfs.h
 * @date         "Wed Dec 31 15:33:20 2014 +0800"
 * @commit       "7b2e44c"
 *
 * @brief
 *
 * @detail
 *
 */

#ifndef __UTIL_SYSFS_H
#define __UTIL_SYSFS_H
#include <stdio.h>

int sysfs_get_input_dev_num(const char *pname);
int sysfs_read_int(const char *path, int *value);
int sysfs_write_int(const char *path, int value);
int sysfs_open_input_dev_node(int input_dev_num, const char *name, int mode);
FILE *sysfs_fopen_input_dev_node(int input_dev_num, const char *name, char *mode);

/*!
 *
 * @brief this function attempts to open a file to read up to 'size' bytes from
 * that file into 'buf'
 *
 * @param[i]   filename   filename to be read
 * @param[o]  buf           out put data buffer
 * @param[i]   size          input size to be read, size must be less than
 *                                   'buf' size
 *
 * @return     >= 0 success. or -1 failed
 * @retval      >=0 the count of true read size
 * @retval      -1    failed to open or read file
 */
int util_fs_read_file(const char *filename, void *buf, int size);

/*!
 *
 * @brief this function attempts to open a file to write up to 'size' bytes to
 * that file from 'buf'
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
int util_fs_write_file(const char *filename, void *buf, int size);

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
int util_fs_get_filesize(const char *filename);

/*!
 * @brief This function detects whether a file is existing or not
 *
 * @param[i]   filename     input file name
 *
 * @return 0 file exist, or -1 file does not exist
 */
int util_fs_is_file_exist(const char *filename);


#endif
