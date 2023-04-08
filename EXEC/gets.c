/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gets.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 18:35:07 by eboulhou          #+#    #+#             */
/*   Updated: 2023/04/08 18:38:22 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int get_comm_lenght(t_cmd *comms)
{
	int i;

	i = 0;
	while(comms)
	{
		comms = comms->next;
		i++;
	}
	return i;
}

int get_nb_of_pipes(t_cmd *comms)
{
	int i;
	
	i = 0;
	while(comms)
	{
		if(comms->infile > 0 || comms->infile == -2)
			i++;

		i++;
		comms = comms->next;
	}
	return i;
	
}