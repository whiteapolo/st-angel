#ifndef ANGEL_H
#define ANGEL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dict.h"

#define ASSERT(con, msg) if (con) { printf("ERROR: %s\n", msg); return 1; }
#define READ_TOKEN_TILL(curr, dest, till)      \
		dest = curr;                   \
		curr = strchr(curr, till);     \
		if (!curr) {                   \
			puts("Syntax Error");  \
			return;                \
		}                              \
		*curr = '\0';                  \
		curr++;                        \

char *buf;
Dict dict;

int agl_init(const char *file_name);
void agl_destory();
void *agl_get(char *key);
int *agl_get_int(char *key);
bool *agl_get_bool(char *key);
const char *agl_get_string(char *key);
float *agl_get_float(char *key);

void *mk_token(char *val);
int _get_file_size(FILE *f);
int _read_whole_file(FILE *f, int size);
void _dict_it();

bool *booldup(bool b);
int *intdup(int b);
float *floatdup(float b);

int agl_init(const char *file_name)
{
	FILE *f;
	ASSERT(!(f = fopen(file_name, "r")), "could not read file");
	int size = _get_file_size(f);
	_read_whole_file(f, size);
	fclose(f);
	dict_init(&dict, size / 10);
	_dict_it();
	return 0;
}

void agl_destory()
{
	free(buf);
	dict_destroy(&dict);
}

void *agl_get(char *key)
{
	return dict_find(&dict, key);
}

void _dict_it()
{
	char *curr = buf;
	char *key;
	char *val;
	while (*curr) {
		if (*curr != '#') {
			READ_TOKEN_TILL(curr, key, ' ');
			READ_TOKEN_TILL(curr, val, '\n');
			/* printf("Tokized: %s, %s\n", key, val); */
			dict_insert(&dict, key, mk_token(val));
		} else {
			curr = strchr(curr, '\n');
			curr++;
		}
	}
}


void *mk_token(char *val)
{
	void *t;
	if (*val == '"') {
		*strchr(++val, '"') = '\0';
		t = strdup(val);
	} else if (*val == 'y' || *val == 'n') {
		t = booldup(*val - 'n');
	} else if (strchr(val, '.')) {
		t = floatdup(atof(val));
	} else {
		t = intdup(atoi(val));
	}
	return t;
}

int *agl_get_int(char *key)
{
	int *tmp = dict_find(&dict, key);
	return tmp;
}

float *agl_get_float(char *key)
{
	float *tmp = dict_find(&dict, key);
	return tmp;
}

bool *agl_get_bool(char *key)
{
	bool *tmp = dict_find(&dict, key);
	return tmp;
}

const char *agl_get_string(char *key)
{
	char *tmp = dict_find(&dict, key);
	return tmp;
}
int _read_whole_file(FILE *f, int size)
{
	buf = malloc(sizeof(char) * (size + 1));
	ASSERT(!fread(buf, sizeof(char), size, f), "Problem reading file");
	buf[size-1] = '\n';
	buf[size] = '\0';
	return 0;
}

int _get_file_size(FILE *f)
{
	fseek(f, 0, SEEK_END);
	int size = ftell(f);
	rewind(f);
	return size;
}

//dup values
bool *booldup(bool b)
{
	bool *n = malloc(sizeof(bool));
	*n = b;
	return n;
}

float *floatdup(float b)
{
	float *n = malloc(sizeof(float));
	*n = b;
	return n;
}

int *intdup(int b)
{
	int *n = malloc(sizeof(int));
	*n = b;
	return n;
}

#endif
