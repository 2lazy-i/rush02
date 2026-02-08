/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   triad.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: 2lazy <2lazy@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/07 14:33:44 by 2lazy         #+#    #+#                 */
/*   Updated: 2026/02/08 14:20:48 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rush02.h"

// TODO:
// - Convert 0-999 triad to words
// - Handle hundreds, 10-19 special case, tens, units
// - Avoid extra spaces or unnecessary "zero"
void	char_to_string(char *str, char c)
{

	str[0] = c;
	str[1] = '\0';
}

char	*append_with_space(char *s1, char *s2)
{
	strcat(s1, " ");
	strcat(s1, s2);
	return  (s1);
}

char *convert_triad(char *triad, t_dict *dict)
{
	char	buf[200];
	char	*result;
    char	charstr[3];

	result = buf;
	if (triad[0] != '0')
	{
		char_to_string(charstr, triad[0]);
		result = append_with_space(lookup(dict, charstr), lookup(dict, "100"));
		result = strcat(result, " ");
	}
	if (triad[1] == '1')
		return (strcat(result, lookup(dict, triad + 1)));
	if (triad[1] == '0' && triad[2] == '0')
		return (result);
	if (triad[1] == '0')
		return (strcat(result, lookup(dict, triad + 2)));
	char_to_string(charstr, triad[1]);
	strcat(charstr, "0");
	result =  strcat(result, lookup(dict, charstr));
	result = strcat(result, " ");
	if (triad[2] == '0')
		return (result);
	char_to_string(charstr, triad[2]);
	result =  strcat(result, lookup(dict, charstr));
    return (result);
}
