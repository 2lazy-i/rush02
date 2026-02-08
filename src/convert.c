/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convert.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: 2lazy <2lazy@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/07 14:33:28 by 2lazy         #+#    #+#                 */
/*   Updated: 2026/02/08 14:17:03 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rush02.h"
// TODO:
// 1. Split number into triads (groups of 3 digits)
// 2. Skip "000" triads
// 3. Call convert_triad() for each triad
// 4. Append thousand/million/billion if needed
// 5. Join triads into final string

char *numb_gen(int amount)
{
	char	*number;
	int		n;

	number = malloc(amount + 2);
	n = 0;
	number[n++] = '1';
	while (n <= amount)
		number[n++] = '0';
	number[n] = '\0';
	return (number);
}

void	fill_triad(char triad[4], char *num)
{
	triad[0] = num[0];
	triad[1] = num[1];
	triad[2] = num[2];
	triad[3] = '\0';
}

void	partial_triad(char triad[4], char *num, int lacking_numbers)
{
	int n;

	triad[0] = '0';
	if (lacking_numbers == 1)
		triad[1] = num[0];
		triad[2] = num[1];
	if (lacking_numbers == 2)
		triad[1] = '0';
		triad[2] = num[0];
	triad[3] = '\0';
}


char *convert_number(char *num, t_dict *dict)
{
	char	buf[1000];
    char	*result;
	char	triad[4];
	//char 	*number_zero;
	int		length;
	int		n;

	result = buf;
	length = ft_strlen2(num);
	n = 0;
	if (length % 3 != 0)
	{
		partial_triad(triad, num, length % 3);
		printf("partial triad>%s\n", convert_triad(triad, dict));
		n += length % 3;
	}
	while (n < length / 3)
	{
		fill_triad(triad, num + n * 3);
		printf("triad>%s ", convert_triad(triad, dict));
		if (length - n * 3 - 3 >= 3)
			printf("(%d)>%s\n", length - n * 3 - 3, lookup(dict, numb_gen(length - n * 3 - 3)));
		n++;
	}
	//printf("\ntest>%s ", convert_triad("400", dict));
    return (NULL);
    //return ft_strdup("zero"); // placeholder
}
