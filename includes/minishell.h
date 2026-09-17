/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 19:24:13 by tlebon            #+#    #+#             */
/*   Updated: 2024/12/11 17:52:21 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <unistd.h>		// chdir, getcwd, fork
# include <stdio.h>			// printf
# include <stdlib.h>		// getenv
# include <fcntl.h>			// open
# include <stdbool.h>		// booleans
# include <errno.h>			// duh
# include <sys/wait.h>		// Wait duh

# include <limits.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

# define R_IN			1 		// "< redirect input"
# define HEREDOC		2		// "<< redirect input until specified delimiter"
# define R_OUT			3 		// "> redirect output"
# define R_OUT_APPEND	4		// ">> redirect output in append mode"
# define PIPE			5		// "| use left part as an arg for right part"
# define CMD			6		// "command"
# define ARG			7		// "argument of a command"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

extern bool	g_heredoc_stop;

typedef struct s_token // contient l'element de la commande + son type
{
	char			*str;
	int				type;
	bool			hello_there;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

typedef struct s_env
{
	char			*name;
	char			*str;
	long long int	ret;
	bool			printed;
	struct s_env	*next;
	struct s_env	*prev;
}				t_env;

typedef struct s_data
{
	t_token			*tokens;
	t_env			*env_lst;
	char			*line;
	char			**env_cpy;
	long long int	ret;
	bool			loop;
}				t_data;

typedef struct s_exec
{
	t_token	*cmd_block;
	char	**env_tab;
}				t_exec;

typedef struct s_manager
{
	t_exec	*s_exec;
	int		*pipefd;
	int		*prev_pipe;
	int		**hd_tab;
}				t_manager;

///// BUILTIN /////////////////////////////////////////////////////////////////

// BIN_UTILS.C      5   VC
t_env	*find_variable(char *name, t_env *s_env);
t_env	*copy_s_env(t_env *s_env);
int		already_exists(t_env *s_env, char *name);
char	*get_env_str(t_env *s_env, char *name);
int		set_env_str(t_env **s_env, char *name, char *str);

// CD.C				4	V
int		exec_cd(char **cmd_tab, t_env **s_env, char ***env_pt);

// ECHO.C			2	V
int		exec_echo(char **cmd_tab);

// ENV.C			1	VC
int		exec_env(t_env *s_env);

// EXEC_BIN.C       4   XC
int		exec_builtin(t_manager *s_manager, t_data *s_data);

// EXIT.C			5	V
int		exec_exit(char **cmd_tab, t_data *s_data);

// EXPORT.C			5	X
int		exec_export(char **args, t_env **s_env, char ***env_pt);

// PWD.C			1	VC
int		exec_pwd(void);

// UNSET.C			2	VC
int		exec_unset(char **cmd_tab, t_env **s_env, char ***env_pt);
void	free_env_node(t_env *node, t_env **s_env);

// UPDATE_ENV.C     5   V
int		update_env_tab(t_env *s_env, char ***env_pt, int do_free);
int		update_env(t_env **env_lst, char *name, char *value, char ***env_pt);

///////////////////////////////////////////////////////////////////////////////

// BOOL.C			2	V
int		is_builtin(t_token *cmd_block);
int		is_type(t_token *s_token, int type);

// COMMAND.C		4	V
char	**prepare_cmd_tab(t_token *s_token);
char	*get_cmd_path(t_env *s_env, char *cmd);

// EXEC_CMD.C		3	X
int		exec_cmd(t_manager *s_manager, t_data *s_data);
void	continue_exec(t_token **s_token, t_manager *s_manager);

// FREE.C           2   X
void	clean_up(t_data *s_data, t_manager *s_manager, char **cmd_tab,
			char *path);
void	close_child(t_manager *s_manager);
void	clean_child(t_data *s_data, t_manager *s_manager);
int		close_hd_tab_fd(int	**tab);
void	free_s_manager(t_manager *s_manager, bool error);

// HERE_DOC_NORM.C	1	X
int		allocate_hd_tab(t_token *s_token, int ***hd_pipes_tab);
int		chose_hd_fd(int **hd_pipes_tab);
int		update_hd_tab(t_token *s_token, int ***hd_tab);
void	close_remain_hd(int **hd_pipes_tab);

// HERE_DOC.C       2   X
int		**new_hd_tab(t_token *s_token);

// IN_OUT_FILES.C	5   VC
int		set_fd_in_out(int *fdin, int *fdout, t_manager *s_manager);
int		redirect_input(int fdin, int fdout);

// MANAGER.C		5	VC
int		launch_exec(t_data *s_data);

// PIPE.C			2	VC
int		create_pipe(t_manager *s_manager, t_token *s_token);
void	clean_close(int fd);

// UTILS.C			5	VC
int		tab_size(char **tab);
t_token	*search_next_cmd(t_token *s_token);
t_token	*search_next_token(t_token *s_token, int type);
int		open_infile(char *file_path);
int		open_outfile(char *file_path, int append);

////////////////////////////////////////////////////////////////////////////////

// INIT.C
void	init_minishell(t_data *data, int ac);
void	heredoc_sigint_handler(int sig);
void	handle_sigint(int sig);

// PARSING.C
int		handle_special_token(char *ingr, int *start, char *temp);
int		handle_normal_token(char *ingr, int *start, char *temp);
int		chopper(t_token **res, char *ingr, int *start);
int		let_me_cook(t_data *data);

// TOKENS.C
int		token_len(char *token, t_env *env_lst);
t_token	*create_token(const char *str, int type);
void	append_token(t_token **head, t_token *new_token);

// ENV.C
char	*env_extractor(char *name, t_env *env_lst);
char	*get_env(char *token, int start, t_env *env_lst);
t_env	*create_env(char *name, char *str, bool printed);
void	append_env_lst(t_env **head, t_env *new_env);
int		create_env_lst(char **v_env, t_data *data);

// TYPE_READERS.C
int		read_type(char	*chunk);
int		physio(t_token *fruit_salad);

// FINISHES.C
int		handle_dollars(char *str, char *new_str, int start, t_data data);
int		handle_quotes(char *str, char *new_str, int start, t_data data);
int		handle_clean(char *str, char *new_str, int start, t_data data);
int		finishes(t_token *tokens, t_data data);

// FINISHES_NORMER.C
bool	solo_dollar(char *str, int start);
void	handle_dollar_question_mark(char *new_str, t_data data);
int		get_endof_envname(char *str, int start);

// FREE.C
void	ft_reset(t_data *data);
void	free_tokens(t_token *head);
void	free_env_lst(t_env *head);
void	free_all(t_data	*data);

// ERRORS.c
bool	empty_line(char *line);
bool	quote_error(char *input);
bool	error_check(t_data *data);
int		syntax_error(t_token *tokens);

// UTILS.C & UTILS_2.C
bool	is_special(const char *c, int char_len);
bool	is_quote(const char *c, int char_len);
bool	is_wspace(const char *c, int char_len);
bool	match(char *s1, char *s2);
void	ft_cat(char *dest, const char *src, const char c_src);
int		utf8_char_len(unsigned char c);
char	*iterate_shlvl(char *str);
char	*handle_copy_env(char *env, char *name);

//	DEBUG.C
char	*bip_boup(int type);
void	print_tokens(t_token *head);
void	display_env_lst(t_env *head);

#endif