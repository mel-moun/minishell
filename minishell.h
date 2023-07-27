/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 18:15:33 by mel-moun          #+#    #+#             */
/*   Updated: 2023/07/26 16:27:08 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include "libft/libft.h"
# include <limits.h>

# define WRIT 1
# define READ 0

enum e_tokens
{
	FILEE,
	CMD,
	ARG,
	S_ARG,
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
	APPEND_ERROR,
	HEREDOC_ERROR,
};

typedef struct s_env
{
	char			*env;
	struct s_env	*next;
}	t_env;

typedef struct s_token
{
	char			*token;
	int				type;
	struct s_token	*next;
}	t_token;

typedef struct s_struct
{
	int			exitstatus;
	int			i;
	int			j;
	int			doubleq;
	int			k;
	int			len;
	char		*line;
	char		*expanded;	
	char		*before;
	char		*to_expand;
	char		*str;
	char		*tmp;
	char		*node;
	t_env		*env;
	t_token		*test;
	t_token		*curr;
}	t_struct;

typedef struct s_final
{
	int				*file_types;
	char			**cmds;
	char			**file_names;
	int				fd;
	char			*path;
	int				pip[2];
	pid_t			pid;
	int				prev_pip;
	struct s_final	*next;
}	t_all;

typedef struct s_export_var
{
	char		*variable;
	char		*var;
}	t_export_var;

extern t_struct	g_glo;

///////////parsing
//prompt function
int		prompt(t_token **all, t_all **glo, char **envp);
char	*change_the_line(char *s);
void	handle_characters(char *s);
void	handle_single_quotes(char *s);
void	handle_dollar_signs(char *s);
void	handle_double_quotes(char *s);
void	handle_heredoc(char *s);

int		found_error_one(t_token **all);
int		found_error_two(t_token **all);
void	error_message(int err, t_token **all);
int		parsing_part_one(t_token **all, char *expanded);
void	parsing_part_two(t_token **all, t_all **glo);

// parsing utils
void	creating_linked(t_token **all, char *s);
void	delete_first_node(t_token **head);
void	setup_exact_type(t_token **all);
void	remove_for(t_token **all);
void	final_thing(t_token **all, t_all **gb);
t_all	*ft_lst_final(t_token **all);
void	count_redirections(t_token **all, int *count);
int		*take_file_types(t_token **all);
void	count_cmds_args(t_token **all, int *count);
char	**take_cmds(t_token **all);
void	count_files(t_token **all, int *count);
char	**take_file_names(t_token **all);
void	initialization_of_vars(void);
void	take_the_whole_node(char *s, t_token **all);
void	take_arg_heredoc(char *s, t_token **all);
void	take_pipe(t_token **all);
void	take_append(char *s, t_token **all);
void	take_heredoc(t_token **all, char *s);
void	take_the_word(char *s);
char	*change_heredoc(char *s);
void	found_expand(char *s, t_token **all);
void	take_node(t_token **all);
void	treatment(char *s, t_token **all);
void	take_a_lot_expanded(char *s);
void	found_expand(char *s, t_token **all);
void	take_expanded(char *s);
void	take_one_expanded(void);
void	delete_empty_nodes(t_token **head);
void	free_tmp_str(void);
void	setup_redirections(t_token **curr);
void	final_thing(t_token **all, t_all **gb);
void	handle_pipe_case(t_token **all, t_all **gb);
// expand
// which is searching the value of a variable in the environment
char	*dollars_money_money(char *s, int *i, int sp);
int		count_dollar_char(char *s);
int		alphabetic(char c);
char	*expand_exit_status(int count);
void	add_dollar_char(int count);
char	*expand_exit_status(int count);
int		is_digit(char c);
char	*expand_the_var(int count);
char	*expand_normal(int count, int *i);
char	*dollar_then_quotes(int count, char *s);
char	*dollar_then_digit(int count);
char	*expand_arobase(int count, int len, char *s);
char	*expanded_value(char *s);
int		take_alot_expanded_count(char *s);
//some string management
char	**mer_split(char *s);
int		ft_strcmp(char *s1, char *s2);
int		empty(char *s);
int		mer_strncmp(char *ss1, char *ss2, int n);
int		check_single_double(char *s);
char	*single_double_quotes(char *s, char c, int *i);
char	*take_word(char *s, int *i);
char	*f_join(char *s1, char *s2);
char	*remove_quotes(char *s);
char	*take_everything(char *s, int *i);
char	*mini_strjoin(char *s, char c);
int		closed_double_quotes(char *s);
char	*arg_heredoc(char *s, int *i);
int		check( char *s);
int		char_belongs_to(char c);
int		char_dont_belong_to(char c);
char	*arg_heredoc_support(char *s, int *j, char *arg);
//linked list management
t_token	*ft_lstlast(t_token *lst);
void	lstaddback_token(t_token **lst, t_token *new);
t_token	*lstnew_token(char *content, int value);
void	dollar_lhgar(t_token **all, char *s);
void	deallocating(t_token **ptr);
void	clear_all(t_all **ptr);
int		whats_next(int check);
int		syntax_error_first(t_token **all);
void	join_linked_list(t_token **all, t_token **otherall);
void	ft_lstaddback_final(t_all **lst, t_all *new);
void	free_file_names(t_all *pk);
void	free_cmds(t_all *pk);
void	deallocating_env(t_env **ptr);
//environment
void	take_env(char **arr);
void	ft_lstadd_back(t_env *new);
t_env	*ft_lstnew(char *content);
/**************************************************/
/**************************************************/
/**************************************************/
//execution file
void	pipe_fnct(t_all *all);
int		compare(char *s1, char *s2);
void	use_builtins(t_all *all);
void	execution_fnct_sequel(t_all *all, char **env);
void	execution_fnct(t_all *glo, char **env);
//chdir file
void	change_pwd(void);
int		chdir_norm(t_all *all);
void	chdir_fnct(t_all *all, int flag);
//exit file
int		compare(char *s1, char *s2);
int		is_num(char *ptr);
void	exit_norm(t_all *all);
int		exit_fnct(t_all *all);
//export file
void	export_fnct_norm(void);
void	export_fnct(t_all *all, int flag);
int		export_norm(t_export_var *var, t_all *all, int n);
int		export_while(t_export_var *var, int n, t_all *all, char	*temp);
void	export_fnct_sequel(t_all *all, int n);
//export sequel file
void	export_norm_two(char **env, t_export_var *var, t_all *all, int n);
void	export_norm_three(t_all *all, int n, t_export_var *var);
char	*adrs_substr(char *s, int start, char *t);
//in_redrct file
int		check_redirct(t_all *tmp, int flag);
int		last_input(t_all *tmp);
void	in_redirection_norm(t_all *tmp, int last_in);
void	in_redirect(t_all *all);
//out_redctn file
void	out_redirect(t_all *all);
void	dup_last_out(t_all *tmp, int n);
void	creat_outfil_norm(t_all *all, int *last, int i);
void	creat_outfile_sequel(t_all *all, int *last, int i);
int		creat_outfile(t_all *all);
//path file
char	*path_with_slash(char *cmd);
void	check_path_norm(t_all *all);
void	check_path(t_all *all);
char	**normal_path_sequel(char *str, char *path);
char	*normal_path(char *cmd, char *path);
//print file
int		check_empty_cmd(char *str);
void	print_env(int flag);
int		only_n_alpha(char *str);
void	echo_fnct(t_all *all, int flag);
//redirection file
void	use_execve(t_all *all, char **env);
void	close_heredoc(t_all *all);
//unset_execution file
int		valid_identifier(char *str);
void	unset_fnct(t_all *all, int flag);
void	unset_fnct_sequel(char *str);
void	unset_norm_two(t_env *temp, t_env *prev);
void	unset_norm(char *str);
//use_builtins file
int		use_builtins_sequel(t_all *all);
void	use_builtins(t_all *all);
//waiting_execution file
void	waiting_fnct(t_all *glo);
void	waiting_norm(t_all *glo);
void	free_double_ptr(char **ptr);
void	close_pipes(t_all *all);
void	handler_fnct(int sig);
//heredoc file
void	heredoc_fnction(t_all *all);
int		search_quotes(char *s);
char	*read_norm(char **input, t_all *glo, int i, int del);
void	read_fnct(t_all *glo, int *pip, int i);
void	heredoc_fnct_sequel(t_all *all, int *prev, int i);
#endif