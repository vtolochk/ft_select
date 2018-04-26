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
		if (lst->underline && lst->selected)
		{
			tputs(tgetstr("so", NULL), 1, &print_command);
			tputs(tgetstr("us", NULL), 1, &print_command);
			write(1, lst->name, ft_strlen(lst->name));
			write(1, "\n", 1);
			tputs(tgetstr("ue", NULL), 1, &print_command);
			tputs(tgetstr("se", NULL), 1, &print_command);
		}
		else if (lst->selected)
		{
			tputs(tgetstr("so", NULL), 1, &print_command);
			write(1, lst->name, ft_strlen(lst->name));
			write(1, "\n", 1);
			tputs(tgetstr("se", NULL), 1, &print_command);
		}
		else if (lst->underline)
		{
			tputs(tgetstr("us", NULL), 1, &print_command);
			write(1, lst->name, ft_strlen(lst->name));
			write(1, "\n", 1);
			tputs(tgetstr("ue", NULL), 1, &print_command);
		}
		else
		{
			write(1, lst->name, ft_strlen(lst->name));
			write(1, "\n", 1);
		}
		list_len--;
		lst = lst->next;
	}
}

t_files *new_node(void)
{
	t_files *new_node;

	new_node = (t_files*)malloc(sizeof(t_files) * 1);
	new_node->name = NULL;
	new_node->underline = 0;
	new_node->selected= 0;
	new_node->next= NULL;
	new_node->prev = NULL;
	return (new_node);
}

void get_files(t_files **head, char **argv, int argc, int *list_len)
{
	t_files *lst;

	*head = new_node();
	lst = *head;
	lst->underline = 1;
	argv++;
	while (argc-- > 1)
	{
		lst->name = ft_strdup(*argv);
		if (argc == 1)
		{
			(*list_len)++;
			break ;
		}
		lst->next = new_node();
		lst->next->prev = lst;
		argv++;
		(*list_len)++;
		lst = lst->next;
	}
	lst->next = *head;
	(*head)->prev = lst;
}
