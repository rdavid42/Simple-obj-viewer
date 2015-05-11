/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/04 17:26:44 by rdavid            #+#    #+#             */
/*   Updated: 2015/04/04 17:26:44 by rdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "bmp_loader.h"

int			main(int argc, char **argv)
{
	t_core			core;

	if (argc < 2)
		return (print_error("Please give me an obj file !\n", 0));
	if (!parse_object(argv[1], &core.otest))
		return (print_error("Failed to parse object !\n", 0));
	if (!initialize_core(&core))
		return (0);
	mlx_loop(core.mlx_init);
	(void)argc;
	(void)argv;
	return (0);
}
