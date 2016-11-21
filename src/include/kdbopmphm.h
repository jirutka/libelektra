#ifndef OPMPHM_H
#define OPMPHM_H

/* Hash function
 * By Bob Jenkins, May 2006
 * http://burtleburtle.net/bob/c/lookup3.c
 */

#define rot(x, k) (((x) << (k)) | ((x) >> (32 - (k))))

#define final(a, b, c)                                                                                                                     \
	{                                                                                                                                  \
		c ^= b;                                                                                                                    \
		c -= rot (b, 14);                                                                                                          \
		a ^= c;                                                                                                                    \
		a -= rot (c, 11);                                                                                                          \
		b ^= a;                                                                                                                    \
		b -= rot (a, 25);                                                                                                          \
		c ^= b;                                                                                                                    \
		c -= rot (b, 16);                                                                                                          \
		a ^= c;                                                                                                                    \
		a -= rot (c, 4);                                                                                                           \
		b ^= a;                                                                                                                    \
		b -= rot (a, 14);                                                                                                          \
		c ^= b;                                                                                                                    \
		c -= rot (b, 24);                                                                                                          \
	}

#define mix(a, b, c)                                                                                                                       \
	{                                                                                                                                  \
		a -= c;                                                                                                                    \
		a ^= rot (c, 4);                                                                                                           \
		c += b;                                                                                                                    \
		b -= a;                                                                                                                    \
		b ^= rot (a, 6);                                                                                                           \
		a += c;                                                                                                                    \
		c -= b;                                                                                                                    \
		c ^= rot (b, 8);                                                                                                           \
		b += a;                                                                                                                    \
		a -= c;                                                                                                                    \
		a ^= rot (c, 16);                                                                                                          \
		c += b;                                                                                                                    \
		b -= a;                                                                                                                    \
		b ^= rot (a, 19);                                                                                                          \
		a += c;                                                                                                                    \
		c -= b;                                                                                                                    \
		c ^= rot (b, 4);                                                                                                           \
		b += a;                                                                                                                    \
	}

uint32_t opmphmHashfunction (const uint32_t * key, size_t length, uint32_t initval);

/**
 * The requirements are described in doc/help/elektra-data-structures.md.
 */

/**
 * @defgroup vstack Vstack
 * @ingroup internaldatastructs
 *
 * The Vstack structure.
 *
 * A stack implementation with dynamical memory allocation.
 * The space gets doubled if full and reduced by half if used only a quarter of it,
 * but not less than minSize.
 */

typedef struct
{
	size_t minSize; /*!< the minimal size of the stack > */
	size_t size;    /*!< The maximal size of the stack */
	void ** data;   /*!< The data array */
	void ** head;   /*!< The stack pointer, which gets incremented or decremented after each push or pop. */
} Vstack;

Vstack * elektraVstackInit (size_t minSize);
int elektraVstackPush (Vstack * stack, void * data);
void * elektraVstackPop (Vstack * stack);
int elektraVstackIsEmpty (const Vstack * stack);
void elektraVstackDel (Vstack * stack);
int elektraVstackClear (Vstack * stack);


typedef int (*VheapComp) (void *, void *);
/**
 * @defgroup vheap Vheap
 * @ingroup internaldatastructs
 *
 * The Vheap structure.
 *
 * A heap is a Data structure which keeps the data ordered.
 * Elements can only be retrieved in this order! Insertions and retrieves need log (n).
 *
 * This implementation allocates memory dynamically.
 * The space gets doubled if full and reduced by half if used only a quarter of it,
 * but not less than minSize.
 *
 * To construct a max heap the comparison function VheapComp (a, b), must return
 * 1 on a > b and 0 otherwise. For a min heap 1 on a < b and 0 otherwise.
 */
typedef struct
{
	size_t minSize; /*!< the minimal size of the heap > */
	size_t size;    /*!< The size of the heap */
	size_t count;   /*!< The current number of elements in the heap */
	VheapComp comp; /*!< The comparison function */
	void ** data;   /*!< The data array */
} Vheap;

Vheap * elektraVheapInit (int (*comp) (void *, void *), size_t minSize);
void elektraVheapDel (Vheap * vheap);
int elektraVheapClear (Vheap * vheap);
int elektraVheapIsEmpty (const Vheap * vheap);
int elektraVheapInsert (Vheap * vheap, void * data);
void * elektraVheapRemove (Vheap * vheap);

#endif
