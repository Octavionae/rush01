/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dim4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkapreli <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 20:09:32 by lkapreli          #+#    #+#             */
/*   Updated: 2022/06/19 20:09:36 by lkapreli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

//void	ft_check_col(int n)

//void	ft_check_raw(int n)

void	ft_get_constr(int constraint_col[4][2], int constraint_raw[4][2])
{
	constraint_col[0][0] = 3;
	constraint_col[0][1] = 2;
	constraint_col[1][0] = 2;
	constraint_col[1][1] = 3;
	constraint_col[2][0] = 3;
	constraint_col[2][1] = 2;
	constraint_col[3][0] = 3;
	constraint_col[3][1] = 2;
	constraint_raw[0][0] = 4;
	constraint_raw[0][1] = 1;
	constraint_raw[1][0] = 2;
	constraint_raw[1][1] = 2;
	constraint_raw[2][0] = 4;
	constraint_raw[2][1] = 4;
	constraint_raw[3][0] = 2;
	constraint_raw[3][1] = 2;
}

int	ft_check_constr(int tab[4][2])
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if ((tab[i][0] == 1) && (tab[i][1] == 1))
			return (1);
		else if ((tab[i][0] == 2) && (tab[i][1] == 4))
			return (1);
		else if ((tab[i][0] == 3) && (tab[i][1] == 3))
			return (1);
		else if ((tab[i][0] == 3) && (tab[i][1] == 4))
			return (1);
		else if ((tab[i][0] == 4) && (tab[i][1] == 2))
			return (1);
		else if ((tab[i][0] == 4) && (tab[i][1] == 3))
			return (1);
		else if ((tab[i][0] == 4) && (tab[i][1] == 4))
			return (1);
	i++;
	}
	return (0);
}

void	ft_print_array(int tab[4][4])
{
	int		i;
	int		j;
	char	number_to_char;
	char	space;

	i = 0;
	j = 0;
	space = 32;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			number_to_char = tab[i][j] + 48;
			write(1, &number_to_char, 1);
			if (j != 3)
				write(1, &space, 1);
			if (j == 3)
				write(1, "\n", 1);
			j++;
		}
		i++;
	}
}

void	ft_set_board_value(int tab[4][4], int i, int j, int val, int remain[4])
{
	if ((tab[i][j] == 0) && (remain[val - 1] > 0))
	{
		tab[i][j] = val;
		remain[val - 1]--;
	}
	else if (tab[i][j] != val)
	{	
		printf("error pas de solution");
		exit(1);
	}
}

int	ft_check_end(int tab[4])
{
	int	n;
	int	i;

	n = tab[0];
	i = 0;
	if (n < tab[1])
		n = tab[1];
	if (n < tab[2])
		n = tab[2];
	if (n < tab[3])
		n = tab[3];
	return (n);
}

void	ft_clear_board(int tab[4][4])
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			tab[i][j] = 0;
			j++;
		}
		i++;
	}
}

void	ft_init_remain(int remain[4])
{
	int	i;

	i = 0;
	while (i < 4)
	{
		remain[i] = 4;
		i++;
	}
}

void	print_remain(int remain[4])
{
	int		i;
	char	c;

	i = 0;
	while (i < 4)
	{
		c = remain[i] + 48;
		write(1, &c, 1);
		printf("%c", '\n');
		i++;
	}
}

void	ft_init_col1(int tab[4][4], int constr_col[4][2], int remain[4])
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		if ((constr_col[i][0] == 1) && (constr_col[i][1] == 2))
		{
			ft_set_board_value(tab, 0, i, 4, remain);
			ft_set_board_value(tab, 3, i, 3, remain);
		}
		if ((constr_col[i][0] == 1) && (constr_col[i][1] == 3))
			ft_set_board_value(tab, 0, i, 4, remain);
		if ((constr_col[i][0] == 1) && (constr_col[i][1] == 4))
		{
			j = 0;
			while (j < 4)
			{
				ft_set_board_value(tab, j, i, 4 - j, remain);
				j++;
			}
		}
		i++;
	}
}

void	ft_init_col2(int tab[4][4], int constr_col[4][2], int remain[4])
{
	int	i;

	i = 0;
	while (i < 4)
	{	
		if ((constr_col[i][0] == 2) && (constr_col[i][1] == 1))
		{
			ft_set_board_value(tab, 0, i, 3, remain);
			ft_set_board_value(tab, 3, i, 4, remain);
		}
		if ((constr_col[i][0] == 2) && (constr_col[i][1] == 3))
		{
			ft_set_board_value(tab, 1, i, 4, remain);
		}
		i++;
	}	
}

void	ft_init_col3(int tab[4][4], int constr_col[4][2], int remain[4])
{
	int	i;

	i = 0;
	while (i < 4)
	{	
		if ((constr_col[i][0] == 3) && (constr_col[i][1] == 1))
			ft_set_board_value(tab, 3, i, 4, remain);
		if ((constr_col[i][0] == 3) && (constr_col[i][1] == 2))
			ft_set_board_value(tab, 2, i, 4, remain);
		i++;
	}	
}

void	ft_init_col4(int tab[4][4], int constr_col[4][2], int remain[4])
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		if ((constr_col[i][0] == 4) && (constr_col[i][1] == 1))
		{	
			j = 0;
			while (j < 4)
			{
				ft_set_board_value(tab, j, i, j + 1, remain);
				j++;
			}
		}
		i++;
	}
}

void	ft_init_raw1(int tab[4][4], int constr_raw[4][2], int remain[4])
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{	
		if ((constr_raw[i][0] == 1) && (constr_raw[i][1] == 2))
		{
			ft_set_board_value(tab, i, 0, 4, remain);
			ft_set_board_value(tab, i, 3, 3, remain);
		}
		if ((constr_raw[i][0] == 1) && (constr_raw[i][1] == 3))
			ft_set_board_value(tab, i, 0, 4, remain);
		if ((constr_raw[i][0] == 1) && (constr_raw[i][1] == 4))
		{
			j = 0;
			while (j < 4)
			{
				ft_set_board_value(tab, i, j, 4 - j, remain);
				j++;
			}
		}
		i++;
	}
}

void	ft_init_raw2(int tab[4][4], int constr_raw[4][2], int remain[4])
{
	int	i;

	i = 0;
	while (i < 4)
	{	
		if ((constr_raw[i][0] == 2) && (constr_raw[i][1] == 1))
		{
			ft_set_board_value(tab, i, 0, 3, remain);
			ft_set_board_value(tab, i, 3, 4, remain);
		}
		if ((constr_raw[i][0] == 2) && (constr_raw[i][1] == 3))
		{
			ft_set_board_value(tab, i, 1, 4, remain);
		}
		i++;
	}	
}

void	ft_init_raw3(int tab[4][4], int constr_raw[4][2], int remain[4])
{
	int	i;

	i = 0;
	while (i < 4)
	{	
		if ((constr_raw[i][0] == 3) && (constr_raw[i][1] == 1))
			ft_set_board_value(tab, i, 3, 4, remain);
		if ((constr_raw[i][0] == 3) && (constr_raw[i][1] == 2))
			ft_set_board_value(tab, i, 2, 4, remain);
		i++;
	}	
}

void	ft_init_raw4(int tab[4][4], int constr_raw[4][2], int remain[4])
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		if ((constr_raw[i][0] == 4) && (constr_raw[i][1] == 1))
		{	
			j = 0;
			while (j < 4)
			{
				ft_set_board_value(tab, i, j, j + 1, remain);
				j++;
			}
		}
		i++;
	}
}

void	ft_init_col(int tab[4][4], int constr_col[4][2], int remain[4])
{
	ft_init_col1(tab, constr_col, remain);
	ft_init_col2(tab, constr_col, remain);
	ft_init_col3(tab, constr_col, remain);
	ft_init_col4(tab, constr_col, remain);
}

void	ft_init_raw(int tab[4][4], int constr_raw[4][2], int remain[4])
{
	ft_init_raw1(tab, constr_raw, remain);
	ft_init_raw2(tab, constr_raw, remain);
	ft_init_raw3(tab, constr_raw, remain);
	ft_init_raw4(tab, constr_raw, remain);
}

int	ft_check_single0_raw(int tab[4][4], int i)
{
	int	j;
	int	card0;

	j = 0;
	card0 = 0;
	while (j < 4)
	{
		if (tab[i][j] == 0)
			card0++;
			j++;
	}	
	return (card0);
}

int	ft_check_single0_col(int tab[4][4], int j)
{	
	int	i;
	int	card0;

	i = 0;
	card0 = 0;
	while (i < 4)
	{
		if (tab[i][j] == 0)
			card0++;
			i++;
	}
	return (card0);
}

void	ft_fill_col(int tab[4][4], int remain[4])
{
	int	i;
	int	j;
	int	var;

	j = 0;
	var = 10;
	while (j < 4)
	{
		if (ft_check_single0_col(tab, j) == 1)
		{
			i = 0;
			while (i < 4)
			{
				var = var - tab[0][j] - tab[1][j] - tab[2][j] - tab[3][j];
				if (tab[i][j] == 0)
					ft_set_board_value(tab, i, j, var, remain);
				i++;
			}
		}
		j++;
	}
}

void	ft_fill_raw(int tab[4][4], int remain[4])
{
	int	i;
	int	j;
	int	var;

	i = 0;
	var = 10;
	while (i < 4)
	{
		if (ft_check_single0_raw(tab, i) == 1)
		{
			j = 0;
			while (j < 4)
			{
				var = var - tab[i][0] - tab[i][1] - tab[i][2] - tab[i][3];
				if (tab[i][j] == 0)
					ft_set_board_value(tab, i, j, var, remain);
				j++;
			}
		}
		i++;
	}
}

int	main(void)
{
	int	board[4][4];
	int	constr_col[4][2];
	int	constr_raw[4][2];
	int	remain[4];
	int	n_end;

	n_end = 4;
	ft_get_constr(constr_col, constr_raw);
	if (ft_check_constr(constr_col) == 1 || ft_check_constr(constr_raw) == 1)
	{
		write(1, "grille impossible", 17);
		exit(1);
	}
	ft_clear_board(board);
	ft_init_remain(remain);
	ft_init_col(board, constr_col, remain);
	ft_init_raw(board, constr_raw, remain);
	while (n_end > 0)
	{
		ft_fill_col(board, remain);
		ft_fill_raw(board, remain);
		n_end = ft_check_end(remain);
	}	
	ft_print_array(board);
}
