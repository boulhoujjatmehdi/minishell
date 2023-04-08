/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 14:30:48 by eboulhou          #+#    #+#             */
/*   Updated: 2023/04/08 19:39:20 by eboulhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

#include "../ft_minishell.h"


int main_function_exec(t_cmd *comms);


//gets
int get_comm_lenght(t_cmd *comms);
int get_nb_of_pipes(t_cmd *comms);
t_cmd *get_right_comm(t_minishell *msh, int idx);

    
#endif