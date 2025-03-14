#include "mini.h"

/*static void print_token_flags(t_flag *flag)
{
    printf("Flags:\n");
    printf("  Single Quotes: %s\n", flag->singol_quotes ? "true" : "false");
    printf("  Double Quotes: %s\n", flag->double_quotes ? "true" : "false");
    printf("  Dollar: %s\n", flag->dollar ? "true" : "false");
    printf("  Redirect Input: %s\n", flag->redirect_input ? "true" : "false");
    printf("  Redirect Output: %s\n", flag->redirect_output ? "true" : "false");
    printf("  Append Mode: %s\n", flag->append_mode ? "true" : "false");
    printf("  Pipe: %s\n", flag->pipe ? "true" : "false");
    printf("  Delimiter: %s\n", flag->delimiter ? "true" : "false");
}

void print_cmds(t_cmd *cmds, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("Comando %d:\n", i + 1);
        printf("  cmd: %s\n", cmds[i].cmd ? cmds[i].cmd : "NULL");

        printf("  arg: ");
        if (cmds[i].arg)
        {
            for (int j = 0; cmds[i].arg[j]; j++)
                printf("\"%s\" ", cmds[i].arg[j]);
        }
        else
            printf("NULL");
        printf("\n");

        printf("  redirect: %s\n", cmds[i].redirect ? cmds[i].redirect : "NULL");
        printf("  file: %s\n", cmds[i].file ? cmds[i].file : "NULL");
        printf("  flag_cmd: %s\n", cmds[i].flag_cmd ? "true" : "false");
        printf("--------------------------------\n");
    }
}

void print_tokens(t_token *token)
{
    char    *s = "WORD";
    char    *s_one = "OPERATORS";
    while (token)
    {
        printf("Token:\n");
        if (token->type_token == 0)
            printf("  Type: %s\n", s);
        else if (token->type_token == 1)
            printf("  Type: %s\n", s_one);
        printf("  Argument: %s\n", token->arg ? token->arg : "(null)");
        print_token_flags(token->flag);
        if(token->next)
            printf("token->next : %p",(void *)token->next);
        else
            printf("token->next : (NULL)");

        printf("---------------------\n");
        token = token->next;
    }
}*/

static int red_heredoc(t_mini *mini)
{
    int fd;
    char *line;

    fd = open("/tmp/heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
    {
        printf("redirection error: fd invalid\n");
        return (-1);
    }
    printf("Heredoc (type '%s' to stop):\n", mini->cmd->file);
    while (1)
    {
        line = readline("> ");
        if (!line || strcmp(line, mini->cmd->file) == 0) // Stop when delimiter is entered
        {
            free(line);
            break;
        }
        write(fd, line, strlen(line));
        write(fd, "\n", 1);
        free(line);
    }
    close(fd);
    // Open heredoc file for reading and redirect stdin
    fd = open("/tmp/heredoc_tmp", O_RDONLY);
    if (fd < 0)
    {
        printf("redirection error: unable to open heredoc file\n");
        return (-1);
    }
    if (dup2(fd, STDIN_FILENO) < 0)
    {
        printf("dup2 error: fd invalid\n");
        return (-1);
    }
    close(fd);
    return (0);
}
