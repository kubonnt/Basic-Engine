#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

/*
	NOT IMPLEMENTED YET
*/

#include "renderer.h"

namespace graphics
{
	class IndexBuffer
	{
	private:
		unsigned int m_RendererID;
		unsigned int m_Count;
	public:
		IndexBuffer(const unsigned int* data, unsigned int count);
		~IndexBuffer();

		void bind();
		void unbind();
	};
}
#endif
