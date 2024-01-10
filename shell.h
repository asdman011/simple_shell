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

/* Buffer sizes for read and write operations */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* Constants for command chaining */
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

/* Flags for convert_number() function */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/* Flags for system features */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE ".history_shell"
#define HIST_MAX 4096

extern char **environ;

/**
 * struct liststr - Node structure for a singly linked list
 * @num: the numerical field
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
 * struct passinfo - Structure containing pseudo-arguments for function calls.
 *
 * @arg: String generated from getline containing command-line arguments.
 * @argv: Array of strings generated from arg.
 * @path: String path for the current command.
 * @argc: Argument count.
 * @line_count: Count of errors encountered.
 * @err_num: Error code for exit() calls.
 * @linecount_flag: Flag indicating whether to count this line of input.
 * @fname: Program filename.
 * @env: Linked list local copy of the environment variables.
 * @history: History node.
 * @alias: Alias node.
 * @environ: Custom modified copy of environ from linked list env.
 * @env_changed: Flag indicating if the environment was changed.
 * @status: Return status of the last executed command.
 * @cmd_buf: Address of the pointer to the command buffer; used if chaining commands.
 * @cmd_buf_type: Type of command chaining (CMD_type ||, &&, ;).
 * @readfd: File descriptor from which to read line input.
 * @histcount: History line number count.
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

    char **cmd_buf; /* Pointer to cmd ; chain buffer, for memory management */
    int cmd_buf_type; /* CMD_type ||, &&, ; */
    int readfd;
    int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/* Function prototypes for shell functionality */

/* Shell loop functions */
int hsh(info_t *, char **);
int find_builtin_command(info_t *);
void locate_cmd(info_t *);
void execute_command(info_t *);

/* Parser functions */
int is_command(info_t *, char *);
char *duplicate_chars(char *, int, int);
char *find_executable_path(info_t *, char *, char *);

/* Shell main loop function */
int shell_loop(char **);

/* Error handling functions */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* String manipulation functions */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* Additional string functions */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* Memory-related functions */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* Tokenizer functions */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* Memory management functions */
char *set_memory(char *, char, unsigned int);
void free_memory(char **);
void *_relloc(void *, unsigned int, unsigned int);

/* Bulk memory freeing function */
int bulk_free(void **);

/* Functions for handling interactive mode */
int interactive_mode(info_t *);
int is_delimiter(char, char *);
int _isalpha(int);
int _atoi(char *);

/* Additional error handling functions */
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* Builtin command functions */
int exit_shell(info_t *);
int change_directory(info_t *);
int display_help(info_t *);

/* Additional builtin functions */
int display_history(info_t *);
int manage_alias(info_t *);

/* Input reading and handling functions */
ssize_t read_input(info_t *);
int get_line(info_t *, char **, size_t *);
void handle_interrupt_signal(int);

/* Shell information management functions */
void clear_sh_info(info_t *);
void set_sh_info(info_t *, char **);
void free_sh_info(info_t *, int);

/* Environment-related functions */
char *get_environment_variable(info_t *, const char *);
int display_environment(info_t *);
int set_environment_variable(info_t *);
int unset_environment_variable(info_t *);
int populate_env_ls(info_t *);

/* Additional environment functions */
char **get_environment_variables(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* History management functions */
char *get_shell_history_file(info_t *info);
int save_shell_history(info_t *info);
int load_shell_history(info_t *info);
int build_shell_history_list(info_t *info, char *buf, int linecount);
int renumber_shell_history(info_t *info);

/* Linked list manipulation functions */
list_t *create_node(list_t **, const char *, int);
list_t *append_node(list_t **, const char *, int);
size_t print_string_list(const list_t *);
int remove_node_at_index(list_t **, unsigned int);
void release_string_list(list_t **);

/* Additional linked list functions */
size_t count_list_elements(const list_t *);
char **convert_list_to_strings(list_t *);
size_t print_generic_list(const list_t *);
list_t *find_node_with_prefix(list_t *, char *, char);
ssize_t find_node_index(list_t *, list_t *);

/* Variable substitution functions */
int is_var_chain(info_t *, char *, size_t *);
void inspect_var_chain(info_t *, char *, size_t *, size_t, size_t);
int substitute_alias(info_t *);
int substitute_variables(info_t *);
int substitute_string(char **, char *);

#endif
