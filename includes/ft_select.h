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

#define EXIT 0
#define CONTINUE 1
#define SEND 2

#define ESC 27
#define SPACE 32
#define ENTER 10
#define BACKSPACE 127
#define SIG_KILL 255
# define PLUS 43
# define MINUS 45

#define ESC_1 32539
#define SIG_KILL_1 32767
#define SPACE_1 32544
#define ENTER_1 32522
#define BACKSPACE_1 32639

#define DELETE_KEY 2117294875
#define ARROW_UP 4283163
#define ARROW_DOWN 4348699
#define ARROW_LEFT 4479771
#define ARROW_RIGHT 4414235

# define EOC "\e[0m"
# define BLUE "\e[38;5;69m"
# define UNDERLINE "\e[38;5;75m"
# define SELECTED "\e[38;5;180m"
# define WARNING "\e[38;5;197m"

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
	int row;
	struct s_files *next;
	struct s_files *prev;
}               t_files;

int exit_error(char *error);
int print_command(int sign);
void set_raw_mode(t_select *data);
void set_canonical_mode(t_select *data);
void get_files(t_files **list, char **argv, int argc, int *list_len);
void print_files(t_select data, t_files *head, int x, int y);
void remove_item(t_files **head, t_select *data);
void free_list(t_files **head, int len);
int get_biggest_len(t_files *head, int lst_len);
int get_rows(t_select data, t_files *head);
void get_screen_size(struct winsize *size);
void		signals(void);
int display_files(t_select *data, t_files **files);
void clr_screen(t_select data);
void print_file(t_files *lst);
void stop_handler(t_select *data);
void continue_handler(t_select *data);
void print_selected_files(t_files *files, int len);
t_select *data_keeper(t_select *dt);
void move_underline(t_files **files, t_select data, int direction);
void select_file(t_files **files, int len);
void select_all(t_files **files, int list_len);
void unselect_all(t_files **files, int list_len);

#endif
