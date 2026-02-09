/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 2lazy <2lazy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 14:32:17 by 2lazy             #+#    #+#             */
/*   Updated: 2026/02/09 20:22:45 by 2lazy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rush02.h"

/*
** ft_substr - Extracts a substring from a string
** @str: Source string
** @start: Starting index in source
** @len: Number of characters to extract
** 
** Standard substring function needed for line extraction.
** Allocates exactly len+1 bytes (for null terminator).
** 
** Note: Does not check bounds - caller must ensure valid indices.
** This is acceptable for internal use where we control the inputs.
*/
char	*ft_substr(char *str, int start, int len)
{
    char	*res;
    int		i;

    res = malloc(len + 1);
    if (!res)
        return (NULL);
    i = 0;
    while (i < len)
    {
        res[i] = str[start + i];
        i++;
    }
    res[len] = '\0';
    return (res);
}

/*
** create_node - Allocates and initializes a dictionary node
** @key: Number string (e.g., "100")
** @value: Word string (e.g., "hundred")
** 
** Takes ownership of key and value strings (caller should not free them).
** Initializes next pointer to NULL for safe list operations.
** 
** Returns NULL on allocation failure, key/value will be leaked
** in this case - caller should handle cleanup if needed.
*/
t_dict	*create_node(char *key, char *value)
{
    t_dict	*node;

    node = malloc(sizeof(t_dict));
    if (!node)
        return (NULL);
    node->key = key;
    node->value = value;
    node->next = NULL;
    return (node);
}

/*
** parse_line - Parses a single dictionary line into key-value node
** @line: Single line from dictionary file
** 
** Expected format: "key: value" with optional whitespace
** Examples:
**   "0: zero"
**   "100:hundred"
**   "  1000  :  thousand  "
** 
** Algorithm:
** 1. Skip leading whitespace
** 2. Extract key (until whitespace or colon)
** 3. Skip whitespace and verify colon separator
** 4. Skip whitespace after colon
** 5. Extract value (until end, trimming trailing whitespace)
** 
** Returns NULL for invalid lines (missing key, colon, or value).
** This allows malformed lines to be silently ignored.
** 
** pos array usage: [key_start, key_end, value_start, value_end]
** Using array to reduce local variable count (norm compliance).
*/
t_dict	*parse_line(char *line)
{
    int		i;
    int		pos[4];
    char	*key;
    char	*value;

    i = skip_spaces(line, 0);
    pos[0] = i;                              /* key_start */
    pos[1] = find_key_end(line, i);          /* key_end */
    if (pos[1] == pos[0])                    /* empty key - invalid */
        return (NULL);
    i = skip_spaces(line, pos[1]);
    if (line[i] != ':')                      /* missing colon - invalid */
        return (NULL);
    i = skip_spaces(line, i + 1);
    pos[2] = i;                              /* value_start */
    pos[3] = find_value_end(line, pos[2]);   /* value_end */
    if (pos[3] == pos[2])                    /* empty value - invalid */
        return (NULL);
    key = ft_substr(line, pos[0], pos[1] - pos[0]);
    value = ft_substr(line, pos[2], pos[3] - pos[2]);
    return (create_node(key, value));
}

/*
** free_dictionary - Frees all memory used by dictionary linked list
** @dict: Head of dictionary list
** 
** Must free three allocations per node:
** 1. key string
** 2. value string
** 3. node struct itself
** 
** Traverses list and frees each node, using temp pointer
** to safely access next before freeing current node.
*/
void	free_dictionary(t_dict *dict)
{
    t_dict	*temp;

    while (dict)
    {
        temp = dict->next;
        free(dict->key);
        free(dict->value);
        free(dict);
        dict = temp;
    }
}
