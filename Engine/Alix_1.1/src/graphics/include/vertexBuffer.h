#pragma once

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
