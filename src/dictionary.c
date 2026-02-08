/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 2lazy <2lazy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 14:32:17 by 2lazy             #+#    #+#             */
/*   Updated: 2026/02/08 17:16:53 by 2lazy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rush02.h"

static char	*ft_substr(char *str, int start, int len)
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

static int	skip_spaces(char *line, int i)
{
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    return (i);
}

static t_dict	*create_node(char *key, char *value)
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

static t_dict	*parse_line(char *line)
{
    int		i;
    int		key_start;
    int		key_end;
    int		val_start;
    int		val_end;

    i = skip_spaces(line, 0);
    key_start = i;
    while (line[i] && line[i] != ' ' && line[i] != '\t' && line[i] != ':')
        i++;
    key_end = i;
    i = skip_spaces(line, i);
    if (line[i] != ':')
        return (NULL);
    i++;
    i = skip_spaces(line, i);
    val_start = i;
    while (line[i] && line[i] != '\n')
        i++;
    val_end = i;
    while (val_end > val_start && (line[val_end - 1] == ' '
            || line[val_end - 1] == '\t'))
        val_end--;
    return (create_node(ft_substr(line, key_start, key_end - key_start),
            ft_substr(line, val_start, val_end - val_start)));
}

static char	*read_file(int fd)
{
    char	*content;
    char	*temp;
    char	buf[2];
    int		bytes;

    content = ft_strdup("");
    bytes = read(fd, buf, 1);
    while (bytes > 0)
    {
        buf[1] = '\0';
        temp = ft_strjoin(content, buf);
        free(content);
        content = temp;
        bytes = read(fd, buf, 1);
    }
    return (content);
}

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
        while (content[i] && content[i] != '\n')
            i++;
        line = ft_substr(content, line_start, i - line_start);
        node = parse_line(line);
        free(line);
        add_node(&head, node);
        if (content[i] == '\n')
            i++;
    }
    return (head);
}

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
