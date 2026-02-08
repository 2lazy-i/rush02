/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush02.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myapaten <myapaten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 17:59:40 by 2lazy             #+#    #+#             */
/*   Updated: 2026/02/08 18:29:18 by myapaten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUSH02_H
# define RUSH02_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

/* Dictionary node */
typedef struct s_dict
{
	char			*key;
	char			*value;
	struct s_dict	*next;
}					t_dict;

/* Dictionary functions */
t_dict				*parse_dictionary(char *filename);
void				free_dictionary(t_dict *dict);
t_dict				*parse_line(char *line);
t_dict				*create_node(char *key, char *value);
char				*ft_substr(char *str, int start, int len);
int					skip_spaces(char *line, int i);

/* Parser functions */
int					validate_args(int argc, char **argv);
char				*clean_number(char *str);

/* Conversion functions */
char				*convert_number(char *num, t_dict *dict);
char				*convert_triad(char *triad, t_dict *dict);

/* Utilities */
int					ft_strlen(char *str);
int					ft_isdigit(char c);
char				*ft_strdup(char *src);
void				ft_putstr(char *str);
char				*lookup(t_dict *dict, char *key);
char				*ft_strjoin(char *s1, char *s2);
char				*ft_strjoin_free(char *s1, char *s2, int free_s1);

#endif