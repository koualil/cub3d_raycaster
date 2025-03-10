#include "../include/cub3D.h"


void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab == NULL)
		return ;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_lst(t_lst *lst)
{
	t_lst	*tmp;

	tmp = lst;
	while (tmp->next != NULL)
	{
		free(tmp->content);
		tmp = tmp->next;
		free(tmp->prev);
		tmp->prev = NULL;
	}
	free(tmp->content);
	free(tmp);
}

void	free_tokens(t_token *tokens, t_lst *content)
{
	free_lst(content);
	free(tokens);
}

static void	free_map(t_map *map)
{
	free_tab(map->map);
	free(map);
}

void	free_param(t_param *param)
{
	free(param->east_texture);
	free(param->west_texture);
	free(param->north_texture);
	free(param->south_texture);
	free_map(param->map_data);
	free(param);
}
