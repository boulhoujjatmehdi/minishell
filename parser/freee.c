/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freee.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhihi <fhihi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:24:53 by fhihi             #+#    #+#             */
/*   Updated: 2023/05/17 16:34:23 by fhihi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parse.h"

//free 2d array in c?

void	free_2darrary(char **arr)
{
	int i;
	
	i = 0;
	while(arr && arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	if (arr)
		free(arr);
}

void	free_lincked_list(t_list *head)
{
	while(head)
	{
		ft_lstdelone(head, &free);
		head = head->next;		
	}
}
