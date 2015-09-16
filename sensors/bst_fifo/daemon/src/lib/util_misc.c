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

#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

#include <stdio.h>

#define LOG_TAG_MODULE "<util_misc>"
#include "sensord.h"



void get_token_pairs(const char *psz_line, char seperator, char *ptoken_l, char *ptoken_r)
{
	char ch;
	int i;
	int pos = -1;

	i = 0;
	while ('\0' != (ch = psz_line[i])) {
		if (ch == seperator) {
			pos = i;
			break;
		} else {
			ptoken_l[i] = psz_line[i];
		}
		i++;
	}
	ptoken_l[i] = '\0';

	if (-1 != pos) {
		i = pos + 1;
		while ('\0' != psz_line[i]) {
			ptoken_r[i - pos - 1] = psz_line[i];
			i++;
		}
		ptoken_r[i - pos - 1] = '\0';
	} else {
		ptoken_r[0] = '\0';
	}
}

int txt_file_read_int(int fd, int *pvalue, int rewind)
{
	int err = 0;
	char buf[16] = "";	/* FIXME */
	int tmp;

	if (rewind) {
		lseek(fd, 0, SEEK_SET);
	}

	tmp = read(fd, buf, sizeof(buf) - 1);
	if (0 < tmp) {
		buf[tmp] = 0;
		tmp = sscanf(buf, "%11d", pvalue);
		if (1 != tmp) {
			err = -EINVAL;
		}
	} else {
		PERR("error reading from file");
		err = -EIO;
	}

	return err;
}


int txt_file_write_int(int fd, int value, short rewind, short nl)
{
	int err = 0;
	char buf[16] = "";	/* FIXME */
	int tmp;

	if (rewind) {
		lseek(fd, 0, SEEK_SET);
	}

	tmp = sprintf(buf, "%d%s", value, nl ? "\n" : "");

	if (tmp > 0) {
		tmp = write(fd, buf, tmp + 1);
		if (tmp <= 0) {
			err = -1;
			PERR("err writing to %d %d: %d", value, fd, tmp);
		}
	} else {
		err = -1;
	}

	return err;
}


void list_init(struct list_node *head)
{
	head->next = NULL;
}


void list_add_head(struct list_node *head, struct list_node *new)
{
	new->next = head;
}


void list_add_rear(struct list_node *head, struct list_node *new)
{
	struct list_node *cur = head;

	while (NULL != cur->next) {
		cur = cur->next;
	}

	cur->next = new;
	new->next = NULL;
}


/*
 * @description: try to find the nod with the address
 * @return
 * NULL if the nod is not found, otherwise the nod itself is returned
 */
struct list_node * list_find_node(struct list_node *head, struct list_node *nod)
{
	struct list_node *cur = head;

	while (NULL != cur) {
		if (cur == nod) {
			break;
		}

		cur = cur->next;
	}

	return cur;
}


/*
 * @return
 * the new head of the list
 */
struct list_node * list_del_node(struct list_node *head, struct list_node *nod)
{
	struct list_node *cur = head;
	struct list_node *prev = NULL;
	struct list_node *new_head = head;

	while (NULL != cur) {
		if (cur == nod) {
			if (cur == head) {
				new_head = head->next;
			}

			if (NULL != prev) {
				prev->next = cur->next;
			}

			break;
		} else {
			prev = cur;
			cur = cur->next;
		}
	}

	return new_head;
}

/*! get greatest common dividor
 */
int get_gcd(int a, int b)
{
	if (0 == b)
		return a;
	return get_gcd(b, a % b);
}


int32_t get_nearest_divisible_int(uint32_t a, uint32_t b)
{
	int32_t ret;

	if (0 == b) {
		/* error */
		return -1;
	}

	if (0 == a) {
		return (int32_t)b;
	}

	if (a <= b) {
		return (int32_t)a;
	}

	for (ret = b; ret > 0; ret--) {
		if (0 == (a % ret)) {
			break;
		}
	}

	return ret;
}


int get_num_set_bits_u32(uint32_t n)
{
	unsigned int i;
	int ret;

	ret = 0;
	for (i = 0; i < sizeof(n) * 8; i++) {
		if ((1<<i) & n) {
			ret++;
		}
	}

	return ret;
}
