#include "shell.h"

/**
 * Placeholder Comment
*/
ssize_t input_buffer(info_t *info, char **buffer, size_t *length)
{
	ssize_t read_size = 0;
	size_t len_pos = 0;

	if (!*length) {
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, sigintHandler);
		read_size = getline(buffer, &len_pos, stdin);
		if (read_size > 0) {
			if ((*buffer)[read_size - 1] == '\n') {
				(*buffer)[read_size - 1] = '\0';
				read_size--;
			}
			info->line_count_flag = 1;
			remove_comments(*buffer);
			build_history_list(info, *buffer, info->history_count++);
			{
				*length = read_size;
				info->cmd_buffer = buffer;
			}
		}
	}
	return (read_size);
}

/**
 * Placeholder comment
*/
ssize_t retrieve_input(info_t *details) {
	static char *chain_buf;
	static size_t iterator, end, length;
	ssize_t read_count = 0;
	char **command_buf_p = &(details->arguments), *pointer;

	_putchar(BUF_FLUSH);
	read_count = input_buffer(details, &chain_buf, &length);
	if (read_count == -1) /* EOF */
		return (-1);
	if (length) {
		end = iterator;
		pointer = chain_buf + iterator;

		verify_chain(details, chain_buf, &end, iterator, length);
		while (end < length) {
			if (is_chain(details, chain_buf, &end))
				break;
			end++;
		}

		iterator = end + 1;
		if (iterator >= length) {
			iterator = length = 0;
			details->command_buffer_type = CMD_NORM;
		}

		*command_buf_p = pointer;
		return (_strlen(pointer));
	}

	*command_buf_p = chain_buf;
	return (read_count);
}

/**
 * Placeholder comment
*/
ssize_t custom_read(info_t *details, char *buffer, size_t *pos) {
	ssize_t bytes_read = 0;

	if (*pos)
		return (0);
	bytes_read = read(details->read_file_descriptor, buffer, READ_BUFFER_SIZE);
	if (bytes_read >= 0)
		*pos = bytes_read;

	return (bytes_read);
}

/**
 * Placeholder comment
*/

int read_input(info_t *details, char **pointer, size_t *len)
{
	static char buffer[READ_BUF_SIZE];
	static size_t idx, length;
	size_t chars;
	ssize_t read_bytes = 0, stored_bytes = 0;
	char *ptr = NULL, *new_ptr = NULL, *cursor;

	ptr = *pointer;
	if (ptr && len)
		stored_bytes = *len;
	if (idx == length)
		idx = length = 0;

	read_bytes = read_buf(details, buffer, &length);
	if (read_bytes == -1 || (read_bytes == 0 && length == 0))
		return (-1);

	cursor = _strchr(buffer + idx, '\n');
	chars = cursor ? 1 + (unsigned int)(cursor - buffer) : length;
	new_ptr = _realloc(ptr, stored_bytes, stored_bytes ? stored_bytes + chars : chars + 1);
	if (!new_ptr)
		return (ptr ? free(ptr), -1 : -1);

	if (stored_bytes)
		_strncat(new_ptr, buffer + idx, chars - idx);
	else
		_strncpy(new_ptr, buffer + idx, chars - idx + 1);

	stored_bytes += chars - idx;
	idx = chars;
	ptr = new_ptr;

	if (len)
		*len = stored_bytes;
	*pointer = ptr;
	return (stored_bytes);
}

/**
 * Placeholder comment
*/

void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
