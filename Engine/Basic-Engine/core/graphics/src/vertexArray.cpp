#include "../include/vertexArray.h"

namespace graphics
{
	VertexArray::VertexArray(const unsigned int* data, unsigned int size, unsigned int index, unsigned int offset, unsigned int position)
		: m_Count(size)
	{
		// It needs some refactoring. Right now everything is fixed but must be flexible, movable, adjustable
		glGenVertexArrays(1, &m_RendererID); // We can generate multiple VAOs or buffers at the same time glGenVertexArrays(1, VAOs);
		glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, offset, (void*)0);
		glEnableVertexAttribArray(position);
	}
	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}
	void VertexArray::bind()
	{
		glBindVertexArray(m_RendererID);
	}
	void VertexArray::unbind()
	{
		glBindVertexArray(0);
	}
}