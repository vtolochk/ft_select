/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtolochk <vtolochk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 15:05:00 by vtolochk          #+#    #+#             */
/*   Updated: 2018/04/20 15:05:00 by vtolochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

#include "../libft/includes/libft.h"
#include <termios.h>
#include <term.h>
#include <sys/ioctl.h>
#include <termcap.h>

#define UP 0
#define DOWN 1

#define EXIT 0
#define CONTINUE 1

#define ESC 32539
#define SPACE 32544
#define BACKSPACE 32639
#define DELETE_KEY 2117294875
#define ARROW_UP 4283163
#define ARROW_DOWN 4348699
#define ARROW_LEFT
#define ARROW_RIGHT


typedef struct s_select
{
	int list_len;
	struct winsize size;
	struct termios tty;
	struct termios old_tty;
}               t_select;

typedef struct s_files
{
	char *name;
	char underline;
	char selected;
	struct s_files *next;
	struct s_files *prev;
}               t_files;

int exit_error(char *error);
int print_command(int sign);
void set_raw_mode(t_select *data);
void set_canonical_mode(t_select *data);
void get_files(t_files **list, char **argv, int argc, int *list_len);
void print_files(t_select data, t_files *head);
void remove_item(t_files **head, t_select *data);
void free_list(t_files **head, int len);
int print_colons(t_select data, t_files *head);
size_t get_biggest_len(t_files *head, int lst_len);
void underline_and_selected(char *string);
void selected(char *string);
void underline(char *string);
void		signals(void);
int display_files(t_select *data, t_files **files);

#endif
