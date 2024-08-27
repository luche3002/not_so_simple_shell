#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>


#define TOKEN_DELIM " \t\r\n\a"

extern char **environ;

/*for read/write buffers*/
#define READ_BUF_SIZE 1024
#define write_buf_size 1024
#define BUF_FLUSH -1

/*for command chaining*/
#define CMD_NORM0
#define CMD_OR1
#define CMD_AND2
#define CMD_CHAIN3

/*for convert_number()*/
#define CONVERT_LOWERCASE1
#define CONVERT_UNSIGNED2

/*1 if using system getline()*/
#define USE_GETLINE0
#define USE_STRTOK0

#define HIST_FILE ".simple_shell_history"
#define HIST_MAX4096

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
 * struct passinfo - enables uniform function prototype
 *with argument placeholders
 * @arg: string gotten from getline which conatains arguments
 * @argv: array of strings or commands gotten from getline
 * @path: string path for the current command
 * @argc: argument count
 * @line_count: count number of lines processed
 * @err_num: error status code for exit function
 * @linecount_flag: count this line of input if set
 * @fname: program file name used in compilation of the program
 * @env: linked list for a local copy of environ
 * @environ: custom modified copy of environ from linked list env
 * @history: history node
 * @alias: alias node
 * @env_changed: if environ is changed, set
 * @status: return status of the previously executed command
 * @cmd_buf: address of pointer to cmd_buf, set if chaining commands
 * @cmd_buf_type: CMD_type (||, &&, ;)
 * @readfd: file descriptor from which line input is read
 * @histcount: history line number count
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
	{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, \
			NULL, NULL, 0, 0, NULL, 0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * @type: builtin command flag
 * @func: the function
 */

typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/*strings function prototype*/
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);
char **strtow(char *, char *);
char **strtow2(char *, char);
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/*builtin function prototypes*/
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);
int _myalias(info_t *);
int _myhistory(info_t *);
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/*memory and its allocation prototypes*/
int bfree(void **);
void *_realloc(void *, unsigned int, unsigned int);
void ffree(char **);
char *_memset(char *, char, unsigned int);

/*functions used with / for performing builtin functions*/
char *_igetenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

/*function prototype to read line and get input*/
void sigintHandler(int);
int _getline(info_t *, char **, size_t *);
ssize_t get_input(info_t *);

/*function prototypes to handle the shell history*/
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/*function prototypes to handle singly linked list*/
void free_list(list_t **);
int delete_node_at_index(list_t **, unsigned int);
size_t print_list_str(const list_t *);
list_t *add_node_end(list_t **, const char *, int);
list_t *add_node(list_t **, const char *, int);

/*function prototypes to operate on singly linked list*/
char **list_to_strings(list_t *);
list_t *node_starts_with(list_t *, char *, char);
size_t list_len(const list_t *);
size_t print_list(const list_t *);
ssize_t get_node_index(list_t *, list_t *);

/*function prototypes that finds builtins and commands*/
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/*function prototypes that prints error*/
char *convert_number(long int, int, int);
int _erratoi(char *);
int print_d(int, int);
void print_error(info_t *, char *);
void remove_comments(char *);

/*function prototypes that replaces aliases, variables and so on*/
int is_chain(info_t *, char *, size_t *);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);

/*function prototype to handle the interactivity of the shell*/
int _atoi(char *);
int _isalpha(int);
int interactive(info_t *);
int is_delim(char, char *);

/*function prototypes to check if an input is a command*/
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/*function prototype for shell loop*/
int loophsh(char **);

/*function prototypes to handle clear*/
void clear_info(info_t *);
void free_info(info_t *, int);
void set_info(info_t *, char **);



/*Just Included prototypes*/

/* Function prototypes*/
char *read_line(void);
char **split_line(char *line);
int execute(char **args);
int launch(char **args);

/*Builtins*/
int shell_cd(char **args);
int shell_exit(char **args);
int shell_env(char **args);

/*Helper function*/
char *_getenv(const char *name);
char *find_command(char *command);

#endif
