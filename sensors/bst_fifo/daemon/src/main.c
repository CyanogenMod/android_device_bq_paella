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
 * @file         main.c
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
#include <sys/ioctl.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>
#include <linux/fs.h>

#define LOG_TAG_MODULE "<main>"
#include "sensord.h"

#ifdef __DEBUG_SIGALT_STACK_SUPPORT__
extern void early_ev_init();
#endif
extern void early_trace_init();
extern void misc_init();
extern void dump_ver();

void parse_cmd_line(int argc, char* argv[])
{
	int i;

	PINFO("argc: %d", argc);

	for (i = 0; i < argc; i++) {
		PINFO("argv[%d]: %s", i, argv[i]);
		if (0 == strcmp("-v", argv[i])) {
			dump_ver();
			exit(0);
		}
	}
}


extern void early_ev_init();
extern void early_trace_init();
extern void misc_init();

int main(int argc, char *argv[])
{
	int err = 0;

	early_trace_init();

#ifdef __DEBUG_SIGALT_STACK_SUPPORT__
	/* handle exceptions as early as possible */
	early_ev_init();
#endif

	/* this might exit the whole process if needed */
	parse_cmd_line(argc, argv);

	misc_init();

	sensor_cfg_init();

	err = hw_cntl_init();
	if (err) {
		PWARN("fail to init hw");
		goto exit_clean;
	}

	err = channel_cntl_init();
	if (err) {
		PWARN("fail to init channels");
		goto exit_clean;
	}

	/* event handler register */
	err = ev_init();
	if (err) {
		PWARN("fail to init channels");
		goto exit_clean;
	}

	ev_loop_check_cmd();

	//sensord_process();
exit_clean:
	return err;
}
