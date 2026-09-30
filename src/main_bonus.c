/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 20:39:42 by event             #+#    #+#             */
/*   Updated: 2025/04/06 23:50:06 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_pipex(t_pipex *data, int argc, char **argv)
{
	if (!ft_strncmp(argv[1], "here_doc", 9))
	{
		data->here_doc = 1;
		data->limiter = argv[2];
		data->cmd_args = &argv[3];
		data->cmd_count = argc - 4;
		data->outfile = open_file(argv[argc - 1], 2);
		handle_here_doc(data->limiter);
		data->infile = STDIN_FILENO;
	}
	else
	{
		data->here_doc = 0;
		data->cmd_args = &argv[2];
		data->cmd_count = argc - 3;
		data->infile = open_file(argv[1], 0);
		data->outfile = open_file(argv[argc - 1], 1);
	}
}

void	execute_pipeline(t_pipex *data)
{
	int	**pipes;

	pipes = create_pipes(data->cmd_count - 1);
	if (!pipes)
		error_exit("Error: pipes creation failed\n");
	fork_processes(data, pipes);
	close_pipes(pipes, data->cmd_count - 1);
	wait_processes(data->cmd_count);
	free_pipes(pipes, data->cmd_count - 1);
}

int	main(int argc, char **argv)
{
	t_pipex	data;

	if (argc < 5)
		error_exit("Error: Invalid number of arguments\n");
	init_pipex(&data, argc, argv);
	if (data.infile < 0 || data.outfile < 0)
		error_exit("Error: Could not open file\n");
	if (data.cmd_count < 2)
		error_exit("Error: At least two commands required\n");
	execute_pipeline(&data);
	close(data.infile);
	close(data.outfile);
	return (0);
}
