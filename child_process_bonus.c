/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 00:00:00 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/05/12 00:00:00 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	**split_command(const char *command)
{
	char	**args;

	args = ft_split(command, ' ');
	if (!args)
	{
		perror("malloc");
		exit(1);
	}
	return (args);
}

void	exec_command(char **args, char *executable)
{
	execve(executable, args, environ);
	perror("execve");
	free(executable);
	free_array2(args);
	exit(127);
}

void	execute_child(const char *cmd, int input_fd, int output_fd)
{
	char	**args;
	char	*executable;

	if (input_fd != STDIN_FILENO)
	{
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
	}
	if (output_fd != STDOUT_FILENO)
	{
		dup2(output_fd, STDOUT_FILENO);
		close(output_fd);
	}
	args = split_command(cmd);
	if (!args || !args[0])
		exit(1);
	executable = find_executable(args[0]);
	if (!executable)
	{
		write(STDERR_FILENO, "command not found\n", 18);
		free_array2(args);
		exit(127);
	}
	exec_command(args, executable);
}
