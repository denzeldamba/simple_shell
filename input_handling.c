#include "shell.h"

ssize_t input_buf(shell_info *info, char **buffer, size_t *buffer_length) {
    ssize_t return_value = 0;
    size_t input_length = 0;

    if (!*buffer_length) {
        free(*buffer);
        *buffer = NULL;
        signal(SIGINT, sigintHandler);

#if USE_GETLINE
        return_value = getline(buffer, &input_length, stdin);
#else
        return_value = _getline(info, buffer, &input_length);
#endif

        if (return_value > 0) {
            if ((*buffer)[return_value - 1] == '\n') {
                (*buffer)[return_value - 1] = '\0'; // Remove trailing newline
                return_value--;
            }
            info->linecount_flag = 1;
            remove_comments(*buffer);
            build_history_list(info, *buffer, info->histcount++);
        }
    }
    return return_value;
}

ssize_t get_input(shell_info *info) {
    static char *buffer;
    static size_t index_i = 0, index_j = 0, buffer_length = 0;
    ssize_t return_value = 0;
    char **buffer_p = &(info->arg), *pointer;

    _putchar(BUF_FLUSH);
    return_value = input_buf(info, &buffer, &buffer_length);

    if (return_value == -1) {
        return -1;
    }

    // Rest of the function implementation
}

ssize_t read_buf(shell_info *info, char *buffer, size_t *index_i) {
    ssize_t return_value = 0;

    if (*index_i) {
        return 0;
    }

    return_value = read(info->readfd, buffer, READ_BUF_SIZE);

    if (return_value >= 0) {
        *index_i = return_value;
    }
    return return_value;
}

int _getline(shell_info *info, char **ptr, size_t *length) {
    static char buffer[READ_BUF_SIZE];
    static size_t index_i = 0, buffer_length = 0;
    size_t k;
    ssize_t return_value = 0, s = 0;
    char *pointer = NULL, *new_pointer = NULL, *c;

    pointer = *ptr;

    if (pointer && length) {
        s = *length;
    }

    if (index_i == buffer_length) {
        index_i = buffer_length = 0;
    }

    return_value = read_buf(info, buffer, &buffer_length);

    if (return_value == -1 || (return_value == 0 && buffer_length == 0)) {
        return -1;
    }

    c = _strchr(buffer + index_i, '\n');
    k = c ? 1 + (unsigned int)(c - buffer) : buffer_length;
    new_pointer = _realloc(pointer, s, s ? s + k : k + 1);

    if (!new_pointer) {
        return (pointer ? free(pointer), -1 : -1);
    }

    if (s) {
        _strncat(new_pointer, buffer + index_i, k - index_i);
    } else {
        _strncpy(new_pointer, buffer + index_i, k - index_i + 1);
    }

    s += k - index_i;
    index_i = k;
    pointer = new_pointer;

    if (length) {
        *length = s;
    }

    *ptr = pointer;
    return s;
}

void sigintHandler(__attribute__((unused)) int sig_num) {
    _puts("\n$ ");
    _putchar(BUF_FLUSH);
}
