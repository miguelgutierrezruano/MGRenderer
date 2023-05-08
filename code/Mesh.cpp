
// Distributed under MIT License
// @miguelgutierrezruano
// 2023

#include "VertexBufferLayout.h"
#include "Mesh.h"

using namespace std;

namespace mg
{
    // vec3 position vec3 rgb color
    const Vertex Mesh::vertexAttributes[] =
    {
        { vec3(-1,-1,+1), vec3(0, 0, 1) },
        { vec3(+1,-1,+1), vec3(1, 0, 1) },
        { vec3(+1,+1,+1), vec3(1, 1, 1) },
        { vec3(-1,+1,+1), vec3(0, 1, 1) },
        { vec3(-1,-1,-1), vec3(0, 0, 0) },
        { vec3(+1,-1,-1), vec3(1, 0, 0) },
        { vec3(+1,+1,-1), vec3(1, 1, 0) },
        { vec3(-1,+1,-1), vec3(0, 1, 0) }
    };

    const GLuint Mesh::indices[] =
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
        : ibo(indices, 3 * 12),
          shader(meshShader),
          vbo(vertexAttributes, 6 * 8 * sizeof(float))
	{
        VertexBufferLayout vbLayout;
        vbLayout.push<float>(3);
        vbLayout.push<float>(3);

        vao.addBuffer(vbo, vbLayout);
	}

	void Mesh::render()
	{
        vao.bind();
        ibo.bind();
        shader->bind();

        mat4 modelMatrix = transform.get_matrix();
        shader->setUniformMat4f("model", modelMatrix);

        glDrawElements(GL_TRIANGLES, ibo.GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}