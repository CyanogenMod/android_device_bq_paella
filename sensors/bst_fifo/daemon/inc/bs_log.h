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
 * @file         bs_log.h
 * @date         "Wed Dec 31 15:33:20 2014 +0800"
 * @commit       "7b2e44c"
 *
 * @brief
 *
 * @detail
 *
 */

#ifndef __BS_LOG_H
#define __BS_LOG_H

#include <stdio.h>
#include <string.h>
#include <errno.h>

#ifdef CFG_LOG_WITH_TIME
#include "util_misc.h"
#include "util_time.h"
#define GET_TIME_TICK() (get_current_timestamp())
#else
#define GET_TIME_TICK() (0)
#endif

#define LOG_LEVEL_Q 0	/* quiet */
#define LOG_LEVEL_E 3
#define LOG_LEVEL_W 4
#define LOG_LEVEL_N 5
#define LOG_LEVEL_I 6
#define LOG_LEVEL_D 7

#ifndef CFG_LOG_LEVEL
#define CFG_LOG_LEVEL LOG_LEVEL_I
#endif

#ifndef LOG_TAG_MODULE
#define LOG_TAG_MODULE
#endif

#if (defined CFG_LOG_TO_LOGCAT && defined CFG_LOG_TO_TERM) ||\
	(defined CFG_LOG_TO_LOGCAT && defined CFG_LOG_TO_FILE) || \
	(defined CFG_LOG_TO_FILE && defined CFG_LOG_TO_TERM)
#error "Conflicting options!"
#endif

#ifdef CFG_LOG_TO_LOGCAT
#include<android/log.h>

/* here use android api instead of cutils to make compatibility
	with ndk build */
#define LOG_TAG    "sensord"
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define LOGF(...)  __android_log_print(ANDROID_LOG_FATAL,LOG_TAG,__VA_ARGS__)
#ifndef LOGE_IF
#define LOGE_IF(cond, ...) \
    ( (cond) \
    ? ((void)__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)) \
    : (void)0 )
#endif

#define BS_LOG LOGD
#define OUT_CHANNEL

#else

#include <stdio.h>
#include "trace.h"
#define BS_LOG trace_log
extern int g_fd_trace;

#define OUT_CHANNEL g_fd_trace,
#endif


#if (CFG_LOG_LEVEL >= LOG_LEVEL_E)
#define PERR(fmt, args...) BS_LOG(OUT_CHANNEL "\n" "[%u]" "[E]" "BS_ERR" LOG_TAG_MODULE "<%s><%d>" fmt "<reason> %s" "\n", GET_TIME_TICK(), __FUNCTION__, __LINE__, ##args, (char *)strerror(errno))
#else
#define PERR(fmt, args...)
#endif

#if (CFG_LOG_LEVEL >= LOG_LEVEL_W)
#define PWARN(fmt, args...) BS_LOG(OUT_CHANNEL "\n" "[%u]" "[W]" "BS_WARN" LOG_TAG_MODULE "<%s><%d>" fmt "\n", GET_TIME_TICK(), __FUNCTION__, __LINE__, ##args)
#else
#define PWARN(fmt, args...)
#endif


#if (CFG_LOG_LEVEL >= LOG_LEVEL_N)
#define PNOTICE(fmt, args...) BS_LOG(OUT_CHANNEL "\n" "[%u]" "[N]" "BS_NOTICE" LOG_TAG_MODULE "<%s><%d>" fmt "\n", GET_TIME_TICK(), __FUNCTION__, __LINE__, ##args)
#else
#define PNOTICE(fmt, args...)
#endif

#if (CFG_LOG_LEVEL >= LOG_LEVEL_I)
#define PINFO(fmt, args...) BS_LOG(OUT_CHANNEL "\n" "[%u]" "[I]" "BS_INFO" LOG_TAG_MODULE "<%s><%d>" fmt "\n", GET_TIME_TICK(), __FUNCTION__, __LINE__, ##args)
#else
#define PINFO(fmt, args...)
#endif

#if (CFG_LOG_LEVEL >= LOG_LEVEL_D)
#define PDEBUG(fmt, args...) BS_LOG(OUT_CHANNEL "\n" "[%u]" "[D]" "BS_DBG" LOG_TAG_MODULE "<%s><%d>" fmt "\n", GET_TIME_TICK(), __FUNCTION__, __LINE__, ##args)
#else
#define PDEBUG(fmt, args...)
#endif

#endif
