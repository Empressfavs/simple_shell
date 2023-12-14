#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains arguements to pass into a function,
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;
	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* loop.c */
int hsh(info_t *info, char **arv);
int find_builtin(info_t *info);
void find_cmd(info_t *info);
void fork_cmd(info_t *info);

/* parser.c */
int is_command(info_t *data, char *path);
char *duplicate_char(char *pathstr, int start, int stop);
char *find_path(info_t *data, char *pathstr, char *cmd);

/* loophsh.c */
int loophsh(char **);

/* err.c */
void _eputs(char *str);
int _eputchar(char c);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* 0-string.c */
int _str_len(char *s);
int _str_cmp(char *str1, char *str2);
char *starts_with(const char *haystack, const char *needle);
char *_str_cat(char *dest, char *src);

/* 1-string.c */
char *_str_cpy(char *dest, char *src);
char *_strdupli(const char *str);
void _puts(char *str);
int _putchar(char c);

/* ext.c */
char *_strncpy(char *dest, char *src, int n);
char *_strncat(char *dest, char *src, int n);
char *_strchr(char *s, char c);

/* token.c */
char **strtow(char *str, char *d);
char **strtow2(char *str, char d);

/* reallocate.c */
char *_memset(char *s, char b, unsigned int n);
void _free(char **ss);
void *_reallocate(void *ptr, unsigned int prev_size, unsigned int new_size);

/* mem.c */
int mfree(void **ptr);

/* trum.c */
int interact(info_t *info);
int is_del(char c, char *del);
int _isalpha(int c);
int _trum(char *d);

/* err.c */
int err_atoi(char *s);
void display_err(info_t *inf, char *errstr);
int display_p(int input, int f);
char *convert_num(long int num, int base, int flags);
void rem_comments(char *buf);

/* built_in.c */
int _ourexit(info_t *info);
int _ourcd(info_t *info);
int _chcur(info_t *info);

/* 1_builtin.c */
int _myhistory(info_t *info);
int set_alias(info_t *info, char *str);
int unset_alias(info_t *info, char *str);
int _alias(info_t *info);
int print_alias(list_t *node);

/* line.c */
ssize_t input_buff(info_t *info, char **buff, size_t *len);
ssize_t _input(info_t *info);
ssize_t read_buf(info_t *info, char *buff, size_t *i);
int _line(info_t *info, char **ptr, size_t *length);
void sigintHandler(__attribute__((unused))int sig_num);

/* info.c */
void clear_inf(info_t *info);
void set_inf(info_t *info, char **arv);
void free_info(info_t *info, int eve);

/* environment.c */
int _environment(info_t *info);
char *_getenviron(info_t *info, const char *name);
int _setenviron(info_t *info);
int _unsetenviron(info_t *info);
int pop_env_list(info_t *info);

/* env.c */
char **get_env(info_t *info);
int _unsetenv(info_t *info, char *var);
int _setenv(info_t *info, char *var, char *value);

/* history.c */
char *history_file(info_t *info);
int create_history(info_t *info);
int read_history(info_t *info);
int history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* node.c */
list_t *add_node(list_t **head, const char *str, int num);
list_t *end_node(list_t **head, const char *str, int num);
size_t print_str(const list_t *l);
int delete_node(list_t **head, unsigned int ind);
void free_node(list_t **head_ptr);

/* node2.c */
size_t list_len(const list_t *n);
char **list_str(list_t *head);
size_t print_list(const list_t *n);
list_t *node_starts_with(list_t *node, char *pre, char c);
ssize_t node_index(list_t *head, list_t *node);

/* chain.c */
int is_chain(info_t *info, char *buf, size_t *p);
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len);
int rep_alias(info_t *info);
int rep_vars(info_t *info);
int rep_string(char **prev, char *ne);

#endif
