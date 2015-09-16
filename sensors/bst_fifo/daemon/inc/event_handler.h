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
 * @file         event_handler.h
 * @date         "Fri Jan 9 17:45:01 2015 +0800"
 * @commit       "7c424a4"
 *
 * @brief
 *
 * @detail
 *
 */

#ifndef __EVENT_HANDLER_H
#define __EVENT_HANDLER_H
#include <signal.h>

#include "configure.h"
#include "options.h"

#include <asm/sigcontext.h>

#ifdef CFG_CHECK_DISPLAY_STATE
typedef struct {
	int (*on_display_state_change)(int state);
} display_event_handler_t;
#endif

#ifdef __SIGALT_STACK_SUPPORT__
typedef struct ucontext_generic {
	unsigned long	  uc_flags;
	struct ucontext_generic  *uc_link;
	stack_t		  uc_stack;
	struct sigcontext uc_mcontext;
	sigset_t	  uc_sigmask;	/* mask last for extensibility */
} ucontext_generic_t;
#endif

#ifdef CFG_CHECK_DISPLAY_STATE
void register_display_event_handler(display_event_handler_t *phandler);
void unregister_display_event_handler(display_event_handler_t *phandler);
#endif

int ev_init();
void ev_loop_check_cmd();
int fifo_write(void *data, int size);
#if __HAL_VER__ >= __SENSORS_DEVICE_API_VERSION_1_1__
int fifo_write_flush_finish_event(int handle);
#endif

#endif
