/***************************************************************************
      kdb.h  -  Exported methods of the Library
                             -------------------
    begin                : Mon Dec 29 2003
    copyright            : (C) 2003 by Avi Alkalay
    copyright            : (C) 2008 by Markus Raab
    email                : avi@unix.sh, elektra@markus-raab.org
 ***************************************************************************/

@DISCLAMER@

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the BSD License (revised).                      *
 *                                                                         *
 ***************************************************************************/

#ifndef KDB_H
#define KDB_H

#include <kdbos.h>

#define KDB_VERSION "@KDB_VERSION@"
#define KDB_VERSION_MAJOR @KDB_VERSION_MAJOR@
#define KDB_VERSION_MINOR @KDB_VERSION_MINOR@
#define KDB_VERSION_MICRO @KDB_VERSION_MICRO@

#define KS_END ((Key*)0)

enum {
	KEY_END=0,
	KEY_NAME=1,
	KEY_VALUE=1<<1,
	KEY_OWNER=1<<2,
	KEY_COMMENT=1<<3,
	KEY_BINARY=1<<4,
	KEY_UID=1<<5,
	KEY_GID=1<<6,
	KEY_MODE=1<<7,
	KEY_ATIME=1<<8,
	KEY_MTIME=1<<9,
	KEY_CTIME=1<<10,
	KEY_SIZE=1<<11,
	KEY_DIR=1<<14,
	KEY_META=1<<15
};

enum {
	KDB_O_NONE=0,
	KDB_O_DEL=1,
	KDB_O_POP=1<<1,
	KDB_O_NODIR=1<<2,
	KDB_O_DIRONLY=1<<3,
	KDB_O_NOSTAT=1<<4,
	KDB_O_STATONLY=1<<5,
	KDB_O_NOREMOVE=1<<6,
	KDB_O_REMOVEONLY=1<<7,
	KDB_O_INACTIVE=1<<8,
	KDB_O_SYNC=1<<9,
	KDB_O_SORT=1<<10,
	KDB_O_NORECURSIVE=1<<11,
	KDB_O_NOCASE=1<<12,
	KDB_O_WITHOWNER=1<<13,
	KDB_O_NOALL=1<<14
};


#ifdef __cplusplus
namespace ckdb {
extern "C" {
#endif


typedef struct _KDB	KDB;
typedef struct _Key	Key;
typedef struct _KeySet	KeySet;


/**************************************
 *
 * KDB methods
 *
 **************************************/

KDB * kdbOpen(void);
int kdbClose(KDB *handle);

ssize_t kdbGet(KDB *handle, KeySet *returned,
	Key * parentKey, option_t options);
ssize_t kdbSet(KDB *handle, KeySet *returned,
	Key * parentKey, option_t options);

ssize_t kdbGetByName(KDB *handle, KeySet *returned,
	const char *parentName, option_t options);

int kdbGetKey(KDB *handle, Key *key);
int kdbSetKey(KDB *handle, const Key *key);

int kdbGetString(KDB *handle, const char *keyname, char *returned,
	size_t maxSize);
int kdbSetString(KDB *handle, const char *keyname, const char *value);
int kdbRemove(KDB *handle, const char *keyname);


/**************************************
 *
 * Key methods
 *
 **************************************/

/* Basic Methods */
Key *keyNew(const char *keyname, ...);
Key *keyVNew(const char *keyname, va_list ap);

Key *keyDup(const Key *source);
int keyCopy(Key *dest, const Key *source);

int keyClear(Key *key);
int keyDel(Key *key);

ssize_t keyIncRef(Key *key);
ssize_t keyDecRef(Key *key);
ssize_t keyGetRef(const Key *key);

/* Meta Info */
int keyRewindMeta(Key *key);
const Key *keyNextMeta(Key *key);
const Key *keyCurrentMeta(const Key *key);

int keyCopyMeta(Key *dest, const Key *source, const char *metaName);

const Key *keyGetMeta(const Key *key, const char* metaName);
ssize_t    keySetMeta(Key *key, const char* metaName,
	const char *newMetaString);

int keyStat(Key *key);
int keyRemove(Key *key);

/* Methods for Making Tests */
int keyCmp(const Key *k1, const Key *k2);

int keyNeedStat(const Key *key);
int keyNeedSync(const Key *key);
int keyNeedRemove(const Key *key);

int keyIsBelow(const Key *key, const Key *check);
int keyIsDirectBelow(const Key *key, const Key *check);

int keyIsInactive(const Key *key);

int keyIsBinary(const Key *key);
int keyIsString(const Key *key);

/* Name Manipulation Methods */
const char *keyName(const Key *key);
ssize_t keyGetNameSize(const Key *key);
ssize_t keyGetName(const Key *key, char *returnedName, size_t maxSize);
ssize_t keySetName(Key *key, const char *newname);

ssize_t keyGetFullNameSize(const Key *key);
ssize_t keyGetFullName(const Key *key, char *returnedName, size_t maxSize);

const char *keyBaseName(const Key *key);
ssize_t keyGetBaseNameSize(const Key *key);
ssize_t keyGetBaseName(const Key *key, char *returned, size_t maxSize);
ssize_t keyAddBaseName(Key *key,const char *baseName);
ssize_t keySetBaseName(Key *key,const char *baseName);

/* Value Manipulation Methods */
const void *keyValue(const Key *key);
ssize_t keyGetValueSize(const Key *key);

ssize_t keyGetString(const Key *key, char *returnedString, size_t maxSize);
ssize_t keySetString(Key *key, const char *newString);

ssize_t keyGetBinary(const Key *key, void *returnedBinary, size_t maxSize);
ssize_t keySetBinary(Key *key, const void *newBinary, size_t dataSize);



/**************************************
 *
 * KeySet methods
 *
 **************************************/

KeySet *ksNew(size_t alloc, ...);
KeySet *ksVNew(size_t alloc, va_list ap);

KeySet *ksDup(const KeySet * source);
int ksCopy(KeySet *dest, const KeySet *source);

int ksClear(KeySet *ks);
int ksDel(KeySet *ks);

void ksSort(KeySet *ks);

ssize_t ksGetSize(const KeySet *ks);

ssize_t ksAppendKey(KeySet *ks, Key *toAppend);
ssize_t ksAppend(KeySet *ks, const KeySet *toAppend);

Key *ksPop(KeySet *ks);

int ksRewind(KeySet *ks);
Key *ksNext(KeySet *ks);
Key *ksCurrent(const KeySet *ks);

Key *ksHead(const KeySet *ks);
Key *ksTail(const KeySet *ks);

cursor_t ksGetCursor(const KeySet *ks);
int ksSetCursor(KeySet *ks, cursor_t cursor);

Key *ksLookup(KeySet *ks, Key *k, option_t options);
Key *ksLookupByName(KeySet *ks, const char *name, option_t options);

#ifdef __cplusplus
}
}
#endif


#endif /* KDB_H */
