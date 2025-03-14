/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrento <ltrento@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 07:12:03 by ltrento           #+#    #+#             */
/*   Updated: 2025/03/14 07:16:32 by ltrento          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	case_sigint_heredoc(int sig)
{
	(void)sig;
    
	unlink("/tmp/heredoc_tmp");
	exit(1);
}


static int red_heredoc(t_mini *mini)
{
    int fd;
    char *line;
    struct sigaction signal;

    signal.sa_handler = case_sigint_heredoc;
    sigemptyset(&signal.sa_mask);
    signal.sa_flags = 0;
    sigaction(SIGINT, &signal, NULL);
    fd = open("/tmp/heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
        return (-1);
    while (1)
    {
        line = readline("> ");
        if (!line || strcmp(line, mini->cmd->file) == 0)
        {
            free(line);
            break;
        }
        write(fd, line, ft_strlen(line));
        write(fd, "\n", 1);
        free(line);
    }
    close(fd);
    setup_signal();
    fd = open("/tmp/heredoc_tmp", O_RDONLY);
    if (fd < 0)
        return (-1);
    if (dup2(fd, STDIN_FILENO) < 0)
        return (-1);
    close(fd);
    return (0);
}
