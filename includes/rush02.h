/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush02.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 2lazy <2lazy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 14:30:58 by 2lazy             #+#    #+#             */
/*   Updated: 2026/02/07 14:52:47 by 2lazy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUSH02_H
# define RUSH02_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

/* Dictionary node */
typedef struct s_dict
{
    char *key;              // number as string, e.g., "42"
    char *value;            // word representation, e.g., "forty-two"
    struct s_dict *next;
} t_dict;

/* Main program */
int     validate_args(int argc, char **argv);
char    *clean_number(char *str);

/* Dictionary handling */
t_dict  *parse_dictionary(char *filename);  // implemented
void    free_dictionary(t_dict *dict);      // implemented

/* Number conversion */
char    *convert_number(char *num, t_dict *dict);   // TODO: implement full number conversion
char    *convert_triad(char *triad, t_dict *dict);  // TODO: implement 0-999 conversion

/* Utilities */
int     ft_strlen(char *str);
int     ft_isdigit(char c);
char    *ft_strdup(char *src);
void    ft_putstr(char *str);

#endif