
#include "core.h"

void		create_buffers(t_core *c)
{
	glGenVertexArrays(1, &c->otest.vao_id);
	glBindVertexArray(c->otest.vao_id);
	glGenBuffers(2, &c->otest.vbo_ids[0]);
	glBindBuffer(GL_ARRAY_BUFFER, c->otest.vbo_ids[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * c->otest.vertices_size * 6, c->otest.vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(c->position_loc);
	glVertexAttribPointer(c->position_loc, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *)0);
	glEnableVertexAttribArray(c->color_loc);
	glVertexAttribPointer(c->color_loc, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat)));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, c->otest.vbo_ids[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * c->otest.indices_size * 3, c->otest.indices, GL_STATIC_DRAW);
	check_gl_error(__LINE__);
}
