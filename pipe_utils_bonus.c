/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 00:00:00 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/05/12 00:00:00 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	close_pipes(int **pipes, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

int	**create_pipes(int count)
{
	int	**pipes;
	int	i;

	pipes = malloc(sizeof(int *) * count);
	i = 0;
	while (i < count)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		pipe(pipes[i]);
		i++;
	}
	return (pipes);
}

void	get_fds(t_pipex *data, int **pipes, int i, int *fds)
{
	if (i == 0)
		fds[0] = data->infile;
	else
		fds[0] = pipes[i - 1][0];
	if (i == data->cmd_count - 1)
		fds[1] = data->outfile;
	else
		fds[1] = pipes[i][1];
}

void	close_unused_pipes(int **pipes, int count, int i)
{
	int	j;

	j = 0;
	while (j < count)
	{
		if (j != i - 1)
			close(pipes[j][0]);
		if (j != i)
			close(pipes[j][1]);
		j++;
	}
}

void	setup_pipes(t_pipex *data, int **pipes, int i)
{
	int	fds[2];

	get_fds(data, pipes, i, fds);
	close_unused_pipes(pipes, data->cmd_count - 1, i);
	execute_child(data->cmd_args[i], fds[0], fds[1]);
}
