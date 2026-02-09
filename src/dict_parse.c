/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 2lazy <2lazy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 18:30:00 by 2lazy             #+#    #+#             */
/*   Updated: 2026/02/09 20:22:32 by 2lazy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rush02.h"

/*
** read_file - Reads entire file content into a single string
** @fd: File descriptor of opened file
** 
** Strategy: Read byte-by-byte and concatenate into growing string.
** This approach is simple but not the most efficient for large files.
** For dictionary files (typically small), this is acceptable.
** 
** Why byte-by-byte:
** - Simplifies buffer management
** - No need to handle partial reads
** - Dictionary files are small enough that performance isn't critical
** 
** Alternative: Could read in larger chunks for better performance,
** but would require more complex buffer management.
*/
static char	*read_file(int fd)
{
    char	*content;
    char	*temp;
    char	buf[2];
    int		bytes;

    content = ft_strdup("");
    if (!content)
        return (NULL);
    bytes = read(fd, buf, 1);
    while (bytes > 0)
    {
        buf[1] = '\0';
        temp = ft_strjoin(content, buf);
        free(content);
        if (!temp)
            return (NULL);
        content = temp;
        bytes = read(fd, buf, 1);
    }
    return (content);
}

/*
** add_node - Appends a node to the end of dictionary linked list
** @head: Pointer to head pointer (allows modifying head)
** @node: Node to add
** 
** Using linked list because:
** - Simple to implement without knowing file size upfront
** - Easy insertion without resizing
** - Dictionary lookups are O(n) but file is small (~35 entries)
** 
** Appends to end to preserve dictionary order (not strictly necessary
** for functionality, but makes debugging easier).
*/
static void	add_node(t_dict **head, t_dict *node)
{
    t_dict	*current;

    if (!node)
        return ;
    if (!*head)
    {
        *head = node;
        return ;
    }
    current = *head;
    while (current->next)
        current = current->next;
    current->next = node;
}

/*
** parse_content - Parses file content string into dictionary nodes
** @content: Full file content as single string
** 
** Algorithm:
** 1. Scan for newline characters to identify line boundaries
** 2. Extract each line using ft_substr
** 3. Parse line into key:value pair via parse_line
** 4. Add valid nodes to linked list (invalid lines silently skipped)
** 
** Line format expected: "key: value" (handled by parse_line)
** Empty lines and invalid formats are ignored, allowing flexible dict files.
*/
static t_dict	*parse_content(char *content)
{
    t_dict	*head;
    int		i;
    int		line_start;
    char	*line;
    t_dict	*node;

    head = NULL;
    i = 0;
    while (content[i])
    {
        line_start = i;
        /* Find end of current line */
        while (content[i] && content[i] != '\n')
            i++;
        /* Extract line as separate string for parsing */
        line = ft_substr(content, line_start, i - line_start);
        node = parse_line(line);
        free(line);
        add_node(&head, node);
        /* Skip the newline character */
        if (content[i] == '\n')
            i++;
    }
    return (head);
}

/*
** parse_dictionary - Main entry point for dictionary file parsing
** @filename: Path to dictionary file
** 
** Flow:
** 1. Open file (return NULL on failure - file not found, no permissions)
** 2. Read entire content into string
** 3. Parse content into linked list of key-value pairs
** 4. Clean up and return dictionary
** 
** Returns NULL on any error, allowing caller to handle appropriately.
** File descriptor is always closed to prevent resource leaks.
*/
t_dict	*parse_dictionary(char *filename)
{
    int		fd;
    char	*content;
    t_dict	*dict;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return (NULL);
    content = read_file(fd);
    close(fd);
    if (!content)
        return (NULL);
    dict = parse_content(content);
    free(content);
    return (dict);
}
