/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouzafo <ybouzafo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 05:04:22 by ybouzafo          #+#    #+#             */
/*   Updated: 2023/06/13 09:34:35 by ybouzafo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 6
# endif

int					g_exit_status;
extern void			rl_replace_line(const char *str, int n);

// une seule globale.
typedef struct s_pars
{
	char			**s;
	char			*dr;
	char			*herdoc;
	char			*cmd;
	char			*dupcmd;
	char			**envr;
	int				id;
	int				od;
	int				hd;
	int				herdoc_fd[2];
	char			**cmds;
	int				state;
	struct s_pars	*next;
}					t_pars;

typedef struct s_exp
{
	char			*key;
	char			*value;
	struct s_exp	*next;
}					t_exp;

/*-------------------------------------------aide.c----------------------------------------------*/
int					ft_strncmp(const char *s1, const char *s2, size_t l);
char				*ft_strjoina(char const *s1, char const *s2);
/*-------------------------------------------expand.c----------------------------------------------*/
char				*check_env(char *str);
char				*egal_egal(t_exp *data, char *ent);
char				*ft_expand(char *str, t_exp *data);
char				*ft_expanda(char *str, t_exp *data);
char				*expand(char *str, t_exp *data);
/*----------------------------------------putendl.c-----------------------------------------------*/
void				ft_putendl_fd(char *s, int fd);
/*----------------------------------------handl_quotes.c-----------------------------------------------*/
int					nmbr_quotes(char *str);
/*----------------------------------------handl_redir.c-----------------------------------------------*/
void				ft_add_cmds(char *s, char ***cmds);
void				handl_redirec(t_pars *pars, t_exp *data);
/*----------------------------------------handl_sp.c-----------------------------------------------*/
int					is_alphanum(char c);
char				*add_sp(char *s);
void				check_symbole(t_pars *pars);
void				supprimer_espaces(char *texte);
void				should_add_sp(char *s, char **d, int i, int count);
/*----------------------------------------herdoc.c-----------------------------------------------*/
int					create_herdoc(t_pars *pars, char *str, t_exp *data);

/*----------------------------------------my_split.c-----------------------------------------------*/
size_t				ft_strlen(const char *str);
char				**ft_split(char *s, char c);
int					compter_mots(char const *s, char c);

/*----------------------------------------my_libft.c-----------------------------------------------*/
char				*ft_strchr(const char *string, int r);
char				*ft_strjoin(char *s1, char *s2);
char				*ft_strttcpy(char *dest, char *src);
char				*ft_strdup(const char *src);
char				*ft_substr(char const *s, unsigned int start, size_t len);
/*----------------------------------------parsing_add.c-----------------------------------------------*/
char				*extr_path(char **env);
void				add_char(char **s, char c);
/*----------------------------------------parsing.c-----------------------------------------------*/
void				parsing(t_pars *pars, t_exp *data);
void				ft_add_to_pars(t_pars **a, t_pars *new);
//void				min_parsing(t_pars *pars);
/*----------------------------------------print.c-----------------------------------------------*/
void				print(char *line);
void				print_noeud(t_pars *pars);
void				print_herdoc(t_pars *pars);
void				print_pars(t_pars *pars);
int					check_if_builtin(t_pars *pars, t_exp *data, int x);

/*----------------------------------------syntax_error.c-----------------------------------------------*/
int					is_all_space(char *s);
int					check_pipe(char *s);
int					check_error(char *str);
int					ft_perror(void);
/*----------------------------------------utils.c-----------------------------------------------*/
char				**fill_string(char const *s, char c, char **strings,
						int start);
void				func_free(char **s);
char				**ft_splita(char const *s, char c);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
/*---------------------------------------echo.c-----------------------------------------------*/
void				ft_echo(char **cmds, t_exp *data);
// int					type_quot(char *str);
// char				*skip_quotes(char *str);
char				*skip_double(char *str);
char				*skip_single(char *str);
int					type_quot(char *str);
int					var_quotes(char *str);
char				*skip_quotes(char *str);
int					nmbr_qu(char *str);
int					check_n(char *str);
/*---------------------------------------pwd.c-----------------------------------------------*/

void				extr_pwd(t_exp *data);
void				pwd_env(t_pars *pars, t_exp *data);
/*---------------------------------------cd_rep.c-----------------------------------------------*/

// void				cd_rep(t_pars *pars, char **env);
int					cd_repa(t_pars *pars, t_exp *data);
void				mod_envr(t_exp *data, char *str);
int					cd_repa_dort(char *str, t_exp *data, int t);
int					cd_repa_iki(char *str, t_exp *data, int t);
int					cd_continu(t_exp *data, char *str, int t);
void				path_absolu(t_exp *data, char *str);
void				change_envir(t_exp *data);
void				mod_point(t_exp *data);
void				change_pwd(char *str, t_exp *data);

void				get_cd(char *old, char *pwd, t_exp *data);
void				sauf_cd(t_exp *data);
void				cd_dash(t_exp *data);
void				cd_dollar(t_exp *data, char *str);
void				cd_point(t_exp *data);
void				cd_deux_point(t_exp *data);
void				add_old(t_exp *data, char *ptr);

/*---------------------------------------get_env.c-----------------------------------------------*/

void				get_env(t_pars *pars, char **env);
/*---------------------------------------export-------------------------------------------------*/
void				get_my_export(t_pars *pars, t_exp *data);
int					ft_strcmp(char *p1, char *p2);
void				get_export(t_pars *pars, t_exp **data, char *ptr);
char				*get_value(t_pars *pars, char *s);
char				*get_key(t_pars *pars, char *s);
int					srch_egal(char *s);
int					srch_plus(char *s);
void				ft_add_back(t_exp **a, t_exp *new);
char				*min_key(char *s, int k);
void				min_get_export(t_pars *pars, t_exp **data, char *ptr);
void				min_get_exp(t_exp *tmp, t_pars *pars, char *ptr);
/*-------------------------------------check_export--------------------------------------*/
int					min_check(t_exp *new_tmp, char *s);
int					min_check2(t_exp *new_tmp, char *s);
int					check_export(t_exp **data, t_pars *pars, char *ptr);
char				*trim_egal(char *p);
int					check_er_syntax(char *s);
int					err_exp(char *s);
void				perror_exp(void);
int					is_alph_digit(char c);

/*-------------------------------------env-------------------------------------------------------*/
t_exp				*my_export(t_pars *pars, char **env);
char				*copy_value(char *s, int k);
char				*copy_key(char *s, int k);
void				min_env_null(t_exp *data, t_exp *new, t_exp *current,
						t_exp *tmp);
t_exp				*env_null(t_exp *new_data, t_exp *data);
void				srch_oldpwd(t_exp *data, char *s, int k);
void				check_pwd_env(char **env, t_exp *data, t_exp *new_data);
/*-------------------------------------unset.c--------------------------------------------------------*/
void				unset_env(char **cmds, t_exp *data);
/*----------------------------execution---------------------------------------------------------------*/
void				execution(t_pars *pars, t_exp *data);
char				*ext_path(t_exp *data);
int					ft_access(char **ptr, t_pars *pars, t_exp *data,
						char **arr);
/*----------------------------env-- -------------------------------------------------------------*/
void				extr_envir(t_pars *pars, t_exp *data);
/*----------------------------exit-- -------------------------------------------------------------*/
void				ft_exit(t_pars *pars);
int					check_nb(char *v);
int					exit_atoi(char *v);

/*-------------------------------------env-------------------------------------------------------*/
char				**pr_envr(t_exp *data);
int					old_var(t_exp *data);
int					y_a_quotes(char *str);
char				*egal(t_exp *data, char *comp);
int					builtin(t_pars *pars, t_exp *data, int x);
/*-------------------------------------exec.norm-------------------------------------------------------*/
void				cd_fonction(t_pars *pars, t_exp *data, int x);
void				fonction(t_exp *data, t_pars *pars);
void				ajout_oldpwd(t_exp *data, char *st);
int					echo_exec(t_pars *pars, t_exp *data);
void				echo_n(char **cmds, t_exp *data, int t, int i);
void				echo_sans_n(char **cmds, t_exp *data, int t);
int					func_echo(char *cmds, char *cmdplus, t_exp *data);
int					func_sans_n(char *cmds, t_exp *data);
char				*trim_quotes(char *s, int *j, char c);
char				*min_skip(char *s, int *i, char c, char *str);
char				*skip_quot_exp(char *s);
/*-------------------------------------redirec_norm-------------------------------------------------------*/
int					handle_output_redirect_conditions(t_exp *data, t_pars *pars,
						int s, int i);
void				handle_output_redirect(t_pars *pars, t_exp *data, int i);
void				handle_redirect_output(t_pars *pars, t_exp *data);
void				handle_input_redirect(t_pars *pars, int i);
void				handle_redirect_input(t_pars *pars);
void				handle_heredoc(t_pars *pars, t_exp *data, int i);
void				handle_append_output_redirect(t_pars *pars, t_exp *data,
						int i);
//int					red_continue(t_pars *pars, t_exp *data, int i);
/************************************builtins********************************/
int					exp_builtins(t_pars *pars, t_exp *data);
int					export_built(t_pars *pars, t_exp *data);
int					exit_built(t_pars *pars);
int					pwd_unset(t_pars *pars, t_exp *data, int x);
int					env_built(t_pars *pars, t_exp *data);
int					cd_built(t_pars *pars, t_exp *data);
int					cd_builtin(t_pars *pars, t_exp *data, int x);
/*---------------------------------expand before split --------------------------------*/
int					find_redir(char *p, int j);
char				*expand_str(char *p, t_exp *data);
int					is_alph_num(char c);
char				*expand_func(char *s, int *j, t_exp *data);
char				**func_expand(char **a, t_exp *data);
int					ft_ls_size(t_exp *p);
void				squipe(char c, char *s, int *i);
void				add_many_chars(char **s, char *st);
void				add_filename(char **s, char *a, int *i);
int					ft_isspace(char c);
void				squipe_pro(char *s, char **st, int *i, t_exp *data);
char				*expand_file(char *a, t_exp *data);
int					check_ambiguous(char *s);
char				*ft_itoa(int n);

#endif
