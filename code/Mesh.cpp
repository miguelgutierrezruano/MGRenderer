
// Distributed under MIT License
// @miguelgutierrezruano
// 2023

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Mesh.h"

using namespace std;

namespace mg
{
    // vec3 position vec3 rgb color
    const GLfloat Mesh::vertexAttributes[] =
    {
       -1,-1,+1, 0, 0, 1,
       +1,-1,+1, 1, 0, 1,
       +1,+1,+1, 1, 1, 1,
       -1,+1,+1, 0, 1, 1,
       -1,-1,-1, 0, 0, 0,
       +1,-1,-1, 1, 0, 0,
       +1,+1,-1, 1, 1, 0,
       -1,+1,-1, 0, 1, 0
    };

    const GLuint  Mesh::indices[] =
    {
        0, 1, 2,            // front
        0, 2, 3,
        4, 0, 3,            // left
        4, 3, 7,
        7, 5, 4,            // back
        7, 6, 5,
        1, 5, 6,            // right
        1, 6, 2,
        3, 2, 6,            // top
        3, 6, 7,
        5, 0, 4,            // bottom
        5, 1, 0
    };

	Mesh::Mesh(Shader* meshShader)
        : ibo(indices, 3 * 12)
	{
        VertexBuffer vertexBuffer(vertexAttributes, 6 * 8 * sizeof(float));
        VertexBufferLayout vbLayout;
        vbLayout.push<float>(3);
        vbLayout.push<float>(3);

        vao.addBuffer(vertexBuffer, vbLayout);

        shader = make_shared<Shader>(meshShader);
	}

	void Mesh::render()
	{
        vao.bind();
        ibo.bind();
        shader.get()->bind();

        glDrawElements(GL_TRIANGLES, ibo.GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}