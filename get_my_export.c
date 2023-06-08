/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_my_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmouto <kelmouto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:08:09 by kelmouto          #+#    #+#             */
/*   Updated: 2023/06/05 13:56:16 by kelmouto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    get_my_export(t_pars *pars, t_exp *data)
{
    (void)pars;
    while(data)
    {
        printf("declare -x ");
       
        if (srch_egal(data->key))
        {
            if(data->value)
            {
                printf("%s",data->key);
                printf("\"");
                printf("%s",data->value);
                printf("\"\n");
            }
            else 
            {
               printf("%s\n",trim_egal(data->key));
            }
        }
        else
            printf("%s\n",data->key);
        data = data->next;   
    }
}