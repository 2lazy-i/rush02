/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 2lazy <2lazy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 18:30:00 by 2lazy             #+#    #+#             */
/*   Updated: 2026/02/08 21:26:01 by 2lazy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rush02.h"

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
