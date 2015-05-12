/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/12 09:54:32 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/12 09:54:32 by rdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int			loop_hook(t_core *c)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	c->cam_pos = create_vec(5.0f + c->translate.x, c->translate.y,
							c->translate.z);
	c->cam_look_at = create_vec(c->translate.x, c->translate.y,
							c->translate.z);
	glBindTexture(GL_TEXTURE_2D, c->textures[c->current_texture]);
	set_camera(c->view_matrix, c->cam_pos, c->cam_look_at);
	glUseProgram(c->program);
	glUniformMatrix4fv(c->proj_loc, 1, GL_FALSE, c->proj_matrix);
	glUniformMatrix4fv(c->view_loc, 1, GL_FALSE, c->view_matrix);
	glUniform1f(c->y_deg_loc, c->y_deg);
	glUniform1f(c->anim_loc, c->anim);
	glUniform1f(c->tex_enabled_loc, c->tex_enabled);
	glUniform1f(c->tex_scale_loc, c->tex_scale);
	glUniform3f(c->rotations_loc, c->rotations.x,
				c->rotations.y, c->rotations.z);
	glDrawElements(GL_TRIANGLES, c->otest.indices_size * 3,
					GL_UNSIGNED_SHORT, 0);
	check_gl_error(__LINE__);
	c->y_deg++;
	if (c->y_deg == 360)
		c->y_deg = 0;
	mlx_opengl_swap_buffers(c->window.init);
	return (1);
}
