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
 * @file         util_misc.h
 * @date         "Wed Dec 31 15:33:20 2014 +0800"
 * @commit       "7b2e44c"
 *
 * @brief
 *
 * @detail
 *
 */

#ifndef __UTIL_MISC_H
#define __UTIL_MISC_H


#define ABS(x) ((x) > 0 ? (x) : -(x))

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(arr) ((int)(sizeof(arr) / sizeof((arr)[0])))
#endif

#ifndef OFFSET_OF
#define OFFSET_OF(type, member)\
	((size_t) &((type *)0)->member)
#endif

#ifndef CONTAINER_OF
#define CONTAINER_OF(ptr, type, member)\
	(type *)((char *)(ptr) - OFFSET_OF(type, member))
#endif


#define FLOAT_EQU(x, y)\
	((x > y) ? ((x - y) < 0.000001) : ((y - x) < 0.000001))

#define EMIT_BUG() \
	do {\
		fprintf(stderr, "bug at file: %s line: %d\n", __FILE__, __LINE__);\
		*((unsigned char *)0) = 0;\
	} while (0);

#define SET_VALUE_BITS(x,val,start,bits)\
	(((x) & ~(((1 << (bits)) - 1) << (start))) | ((val) << (start)))


#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

#define SWAP(type, a, b)\
	do {\
		type t;\
		t = a;\
		a = b;\
		b = t;\
	} while (0);


#define UNUSED_PARAM(param) ((void)(param))
#define __unused__ __attribute__((unused))

struct list_node {
	struct list_node *next;
	long data;
};

struct dlist_node {
	struct dlist_node *prev;
	struct dlist_node *next;
	long data;
};

void util_misc_init();

void get_token_pairs(const char *psz_line, char seperator,
		char *ptoken_l, char *ptoken_r);

int txt_file_read_int(int fd, int *pvalue, int rewind);
int txt_file_write_int(int fd, int value, short rewind, short nl);


void list_init(struct list_node *head);
void list_add_head(struct list_node *head, struct list_node *new);
void list_add_rear(struct list_node *head, struct list_node *new);
struct list_node * list_find_node(struct list_node *head, struct list_node *nod);
struct list_node * list_del_node(struct list_node *head, struct list_node *nod);


int get_gcd(int a, int b);
int32_t get_nearest_divisible_int(uint32_t a, uint32_t b);
/* get number of 1s (set bits) in a u32 integer */
int get_num_set_bits_u32(uint32_t n);
#endif
