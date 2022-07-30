#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

/*
	NOT IMPLEMENTED YET
*/

#include "renderer.h"

namespace graphics
{
	class VertexBuffer
	{
	private:
		unsigned int m_RendererID;
	public:
		VertexBuffer(const void* data, unsigned int size);
		~VertexBuffer();

		void bind();
		void unbind();
	};
}
#endif
