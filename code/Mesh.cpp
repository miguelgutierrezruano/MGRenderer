
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
    Mesh::Mesh(Model* meshModel, vector<Vertex> meshVertices, vector<unsigned int> meshIndices, vector<shared_ptr<Texture>> textures)
		: vbo(meshVertices.data(), (unsigned int)meshVertices.size() * sizeof(Vertex)),
		ibo(meshIndices.data(), (unsigned int)meshIndices.size()),
        textures(std::move(textures))
    {
		owner = meshModel;

        VertexBufferLayout vbLayout;
        vbLayout.push<float>(3);
        vbLayout.push<float>(3);
        vbLayout.push<float>(2);

        vao.addBuffer(vbo, vbLayout);
    }

	void Mesh::render(shared_ptr< Shader > shader)
	{
        vao.bind();
        ibo.bind();
        shader.get()->bind();

        mat4 modelMatrix = owner->transform.get_matrix();
        shader.get()->setUniformMat4f("model", modelMatrix);

        // Texture uniforms        
        for (unsigned int i = 0; i < textures.size(); i++)
        {
            textures[i].get()->bind(i);

            // Active slot
            if (textures[i].get()->type == "texture_diffuse")
                shader.get()->setUniform1i("material.diffuse", i);
            else if(textures[i].get()->type == "texture_specular")
                shader.get()->setUniform1i("material.specular", i);
        }

		GLClearError();
        glDrawElements(GL_TRIANGLES, ibo.GetCount(), GL_UNSIGNED_INT, nullptr);
		GLLogCall();
	}
}