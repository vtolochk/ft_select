/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtolochk <vtolochk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 19:13:00 by vtolochk          #+#    #+#             */
/*   Updated: 2018/05/04 11:21:25 by vtolochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

t_files		*new_node(void)
{
	t_files *new_node;

	new_node = (t_files*)malloc(sizeof(t_files) * 1);
	new_node->name = NULL;
	new_node->underline = 0;
	new_node->selected = 0;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

void		remove_item(t_files **head, t_select *data, int i)
{
	t_files		*lst;

	lst = *head;
	while (i < data->list_len)
	{
		if (lst->underline == 1)
		{
			data->list_len--;
			lst->next->underline = 1;
			lst->next->prev = lst->prev;
			lst->prev->next = lst->next;
			if (i == 0)
				*head = lst->next;
			ft_strdel(&lst->name);
			free(lst);
			if (data->list_len == 0)
			{
				set_canonical_mode(data);
				exit(0);
			}
			break ;
		}
		i++;
		lst = lst->next;
	}
}

void		free_list(t_files **head, int len)
{
	int			i;
	t_files		*temp;

	i = 0;
	while (i++ < len)
	{
		temp = *head;
		*head = (*head)->next;
		ft_strdel(&temp->name);
		free(temp);
	}
}

void		get_files(t_files **head, char **argv, int argc, int *len)
{
	t_files *lst;

	*head = new_node();
	lst = *head;
	lst->underline = 1;
	argv++;
	*len = argc - 1;
	while (argc-- > 1)
	{
		lst->name = ft_strdup(*argv);
		if (argc == 1)
			break ;
		lst->next = new_node();
		lst->next->prev = lst;
		argv++;
		lst = lst->next;
	}
	(*head)->prev = lst;
	lst->next = *head;
}
