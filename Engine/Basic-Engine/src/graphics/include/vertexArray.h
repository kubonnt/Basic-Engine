#pragma once

#include "renderer.h"

namespace graphics
{
	class VertexArray
	{
	private:
		unsigned int m_RendererID;
		unsigned int m_Count;
	public:
		VertexArray(const unsigned int* data, unsigned int size, unsigned int index, unsigned int offset, unsigned int position);
		~VertexArray();

		void bind();
		void unbind();
	};
}