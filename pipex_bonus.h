/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 00:00:00 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/05/12 00:00:00 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <fcntl.h>
# include <sys/wait.h>
# include "libft/libft.h"
# include "libft/ft_printf.h"

extern char	**environ;

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	int		here_doc;
	int		cmd_count;
	char	**cmd_args;
	char	*limiter;
}	t_pipex;

char	*get_path_env(void);
char	*join_path(const char *dir, const char *command);
char	*find_executable(char *command);

char	**split_command(const char *command);
void	execute_child(const char *cmd, int input_fd, int output_fd);

void	handle_here_doc(char *limiter);
int		open_file(char *file, int mode);
void	error_exit(char *msg);
void	free_pipex(t_pipex *data);

int		**create_pipes(int count);
void	close_pipes(int **pipes, int count);
void	setup_pipes(t_pipex *data, int **pipes, int i);

void	fork_processes(t_pipex *data, int **pipes);
void	wait_processes(int count);
void	free_pipes(int **pipes, int count);

#endif
