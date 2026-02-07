/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 2lazy <2lazy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 14:31:53 by 2lazy             #+#    #+#             */
/*   Updated: 2026/02/07 14:53:08 by 2lazy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rush02.h"

#include "../includes/rush02.h"

int main(int argc, char **argv)
{
    char    *number;
    t_dict  *dict;
    char    *result;

    // 1️⃣ Validate input arguments (digits only)
    if (!validate_args(argc, argv))
    {
        write(1, "Error\n", 6);
        return (1);
    }

    // 2️⃣ Remove leading zeros
    number = clean_number(argv[1]);

    // 3️⃣ Load dictionary
    if (argc == 3)
        dict = parse_dictionary(argv[2]);  // custom dictionary
    else
        dict = parse_dictionary("numbers.dict");  // default dictionary

    if (!dict)
    {
        write(1, "Dict Error\n", 11);  // dictionary failed to load
        return (1);
    }

    // 4️⃣ Convert number to words (TODO: implement logic)
    result = convert_number(number, dict); // placeholder

    // 5️⃣ Print result
    if (result)
    {
        ft_putstr(result);
        write(1, "\n", 1);
        free(result);
    }

    // 6️⃣ Free memory
    free(number);
    free_dictionary(dict);
    return (0);
}
