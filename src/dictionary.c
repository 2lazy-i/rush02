/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 2lazy <2lazy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 14:32:17 by 2lazy             #+#    #+#             */
/*   Updated: 2026/02/07 15:02:57 by 2lazy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rush02.h"

// helper: check space
static int ft_isspace(char c)
{
    return (c == ' ' || c == '\t');
}

// trim spaces from both ends
static char *trim_spaces(char *str)
{
    int start = 0;
    int end = 0;
    int len;
    char *res;

    while (str[start] && ft_isspace(str[start]))
        start++;

    end = start;
    while (str[end])
        end++;
    end--;
    while (end >= start && ft_isspace(str[end]))
        end--;

    len = end - start + 1;
    res = malloc(len + 1);
    if (!res)
        return NULL;

    for (int i = 0; i < len; i++)
        res[i] = str[start + i];
    res[len] = '\0';
    return res;
}

// read entire file into buffer
static char *read_file(int fd)
{
    char buffer[4096];
    char *content;
    int bytes;

    content = malloc(1);
    if (!content)
        return NULL;
    content[0] = '\0';

    while ((bytes = read(fd, buffer, 4095)) > 0)
    {
        buffer[bytes] = '\0';
        char *tmp = malloc(ft_strlen(content) + bytes + 1);
        if (!tmp)
        {
            free(content);
            return NULL;
        }
        int i = 0;
        while (content[i])
        {
            tmp[i] = content[i];
            i++;
        }
        for (int j = 0; j < bytes; j++)
            tmp[i + j] = buffer[j];
        tmp[i + bytes] = '\0';
        free(content);
        content = tmp;
    }
    if (bytes < 0)
    {
        free(content);
        return NULL;
    }
    return content;
}

// parse dictionary file into linked list
t_dict *parse_dictionary(char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd < 0)
        return NULL;

    char *content = read_file(fd);
    close(fd);
    if (!content)
        return NULL;

    t_dict *head = NULL;
    t_dict *new = NULL;
    int i = 0;
    int line_start = 0;

    while (content[i])
    {
        if (content[i] == '\n' || content[i + 1] == '\0')
        {
            int line_end = (content[i] == '\n') ? i : i + 1;
            int len = line_end - line_start;
            if (len > 0)
            {
                char tmp[len + 1];
                int k;
                for (k = 0; k < len; k++)
                    tmp[k] = content[line_start + k];
                tmp[k] = '\0';

                // find colon
                int colon = 0;
                while (tmp[colon] && tmp[colon] != ':')
                    colon++;

                if (tmp[colon] == ':')
                {
                    tmp[colon] = '\0';
                    char *key = trim_spaces(tmp);
                    char *value = trim_spaces(tmp + colon + 1);
                    if (key && value)
                    {
                        new = malloc(sizeof(t_dict));
                        if (new)
                        {
                            new->key = key;
                            new->value = value;
                            new->next = head;
                            head = new;
                        }
                    }
                }
            }
            line_start = i + 1;
        }
        i++;
    }

    free(content);
    return head;
}

// free dictionary memory
void free_dictionary(t_dict *dict)
{
    t_dict *tmp;
    while (dict)
    {
        tmp = dict->next;
        free(dict->key);
        free(dict->value);
        free(dict);
        dict = tmp;
    }
}
