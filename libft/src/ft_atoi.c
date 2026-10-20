/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzinchuk <kzinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:19:59 by kzinchuk          #+#    #+#             */
/*   Updated: 2024/10/30 12:50:24 by kzinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	result;

	sign = 1;
	result = 0;
	while ((*nptr >= '\t' && *nptr <= '\r') || *nptr == ' ')
	{
		nptr++;
	}
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
		{
			sign = -1;
		}
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = (result * 10 + (*nptr - '0'));
		nptr++;
	}
	return (result * sign);
}

// # include <stdlib.h>
// # include <stdio.h>
// int main() {
//     // Simple test case
//     char *test_input = "-99999999999999999999912";
//     int result = ft_atoi(test_input);
// 	int result2 = atoi(test_input);

//     printf(" ===> %d \n", result);
// 	printf(" ===> %d \n", result2);
//     return 0;
// }
