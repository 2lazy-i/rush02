/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 2lazy <2lazy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 14:33:28 by 2lazy             #+#    #+#             */
/*   Updated: 2026/02/07 15:32:14 by 2lazy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rush02.h"

// TODO:
// 1. Split number into triads (groups of 3 digits)
// 2. Skip "000" triads
// 3. Call convert_triad() for each triad
// 4. Append thousand/million/billion if needed
// 5. Join triads into final string
char *convert_number(char *num, t_dict *dict)
{
    (void)num;
    (void)dict;
    return ft_strdup("zero"); // placeholder
}
