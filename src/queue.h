/* queue.h
 *
 *   Copyright (C) 2010       Henrik Hautakoski <henrik@fiktivkod.org>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   You should have received a copy of the GNU General Public License along
 *   with this program; if not, write to the Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef __QUEUE_H
#define __QUEUE_H

#include <stddef.h>

typedef struct __queue* queue_t;

queue_t queue_init(void);

void queue_enqueue(queue_t q, void *obj);

void* queue_dequeue(queue_t q);

int queue_isempty(queue_t q);

size_t queue_num_items(queue_t q);

void queue_destroy(queue_t q);

#endif /* __QUEUE_H */
