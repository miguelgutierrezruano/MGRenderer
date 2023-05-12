
// Distributed under MIT License
// @miguelgutierrezruano
// 2023

#include "VertexBufferLayout.h"
#include "Mesh.h"
#include "Model.h"

#include "OpenGLDebugger.h"

using namespace std;

namespace mg
{
    Mesh::Mesh(Model* meshModel, vector<Vertex> meshVertices, vector<unsigned int> meshIndices)
		: vbo(meshVertices.data(), (unsigned int)meshVertices.size() * sizeof(Vertex)),
		ibo(meshIndices.data(), (unsigned int)meshIndices.size())
    {
		owner = meshModel;

        VertexBufferLayout vbLayout;
        vbLayout.push<float>(3);
        vbLayout.push<float>(3);
        vbLayout.push<float>(3);

        vao.addBuffer(vbo, vbLayout);
    }

	void Mesh::render(shared_ptr< Shader > shader)
	{
        vao.bind();
        ibo.bind();
        shader.get()->bind();

        mat4 modelMatrix = owner->transform.get_matrix();
        shader.get()->setUniformMat4f("model", modelMatrix);

		GLClearError();
        glDrawElements(GL_TRIANGLES, ibo.GetCount(), GL_UNSIGNED_INT, nullptr);
		GLLogCall();
	}
}