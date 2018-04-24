/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtolochk <vtolochk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 19:13:00 by vtolochk          #+#    #+#             */
/*   Updated: 2018/04/24 19:13:00 by vtolochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void print_files(t_files *head, int list_len)
{
	t_files *lst;

	lst = head;
	while (list_len > 0)
	{
		write(1, lst->name, ft_strlen(lst->name));
		write(1, "\n", 1);
		list_len--;
		lst = lst->next;
	}
}

t_files *new_node(void)
{
	t_files *new_node;

	new_node = (t_files*)malloc(sizeof(t_files) * 1);
	new_node->name = NULL;
	new_node->next= NULL;
	new_node->prev = NULL;
	return (new_node);
}

void get_files(t_files **head, char **argv, int argc, int *list_len)
{
	t_files *lst;

	*head = new_node();
	lst = *head;
	argv++;
	while (argc > 1)
	{
		lst->name = ft_strdup(*argv);
		lst->next = new_node();
		lst->next->prev = lst;
		argv++;
		argc--;
		(*list_len)++;
		lst = lst->next;
	}
	lst->next = *head;
	(*head)->prev = lst;
}
