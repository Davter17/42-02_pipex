/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 00:35:02 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/09/30 22:00:00 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

extern char	**environ;

void	free_array2(char **array);

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
pid_t	create_child(const char *cmd, int in_fd, int out_fd, int close_fd);

int		open_files(char *input, char *output, int *fd_in, int *fd_out);
int		wait_end(pid_t pid1, pid_t pid2);
int		init_pipe(int *pipe_fd, int fd_in, int fd_out);

void	error_exit(char *msg);
int		open_file(char *file, int mode);
void	handle_here_doc(char *limiter);

int		**create_pipes(int count);
void	close_pipes(int **pipes, int count);
void	setup_pipes(t_pipex *data, int **pipes, int i);

void	fork_processes(t_pipex *data, int **pipes);
void	wait_processes(int count);
void	free_pipes(int **pipes, int count);

#endif
