#include "Model.h"
#include "Types.h"

#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <filesystem>  

Model::Model(const std::string& path) {
    LoadModel(path);
}

void Model::Draw(Shader& shader) {
    for (auto& mesh : meshes)
        mesh.Draw(shader);
}

void Model::LoadModel(const std::string& path) {
    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(path,
        aiProcess_Triangulate |
        aiProcess_FlipUVs |
        aiProcess_CalcTangentSpace);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }

    directory = path.substr(0, path.find_last_of("/\\"));
    std::cout << "[Model] Loaded: " << path << "\n";
    std::cout << "[Model] Embedded textures count: " << scene->mNumTextures << "\n";
    std::cout << "[Model] Processing nodes...\n";
    ProcessNode(scene->mRootNode, scene);
    std::cout << "[Model] Total Meshes: " << meshes.size() << "\n";
}

void Model::ProcessNode(aiNode* node, const aiScene* scene) {
    for (unsigned int i = 0; i < node->mNumMeshes; ++i) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(ProcessMesh(mesh, scene));
    }

    for (unsigned int i = 0; i < node->mNumChildren; ++i) {
        ProcessNode(node->mChildren[i], scene);
    }
}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    
    for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
        Vertex vertex;

        vertex.position = glm::vec3(
            mesh->mVertices[i].x,
            mesh->mVertices[i].y,
            mesh->mVertices[i].z
        );

        vertex.normal = mesh->HasNormals()
            ? glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z)
            : glm::vec3(0.0f);

        vertex.texCoords = mesh->mTextureCoords[0]
            ? glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y)
            : glm::vec2(0.0f);

        vertices.push_back(vertex);
    }

    
    for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
        const aiFace& face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; ++j)
            indices.push_back(face.mIndices[j]);
    }

    
    if (mesh->mMaterialIndex >= 0) {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

        
        auto diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

        if (diffuseMaps.empty()) {
            
            std::string manualTexturePath = directory + "ak.png";

            
            if (std::filesystem::exists(manualTexturePath)) {
                std::cout << "[Texture] No diffuse textures found, loading manual texture: " << manualTexturePath << "\n";
                Texture texture;
                texture.id = TextureFromFile("ak.png", directory + "/../Textures", false);
                texture.type = "texture_diffuse";
                texture.path = "ak.png";

                textures.push_back(texture);
            }
            else {
                std::cout << "[Texture] Manual texture 'ak.png' not found at: " << manualTexturePath << "\n";
            }
        }
    }

    std::cout << "[Mesh] Vertices: " << vertices.size()
        << ", Indices: " << indices.size()
        << ", Textures: " << textures.size() << "\n";

    return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName) {
    std::vector<Texture> textures;

    for (unsigned int i = 0; i < mat->GetTextureCount(type); ++i) {
        aiString str;
        mat->GetTexture(type, i, &str);

        std::string texPath = str.C_Str();
        std::string fullPath = directory + "/" + texPath;

        std::cout << "[Texture] Loading texture: " << fullPath << "\n";

        Texture texture;
        texture.id = TextureFromFile(texPath.c_str(), directory, false);
        texture.type = typeName;
        texture.path = texPath;

        textures.push_back(texture);
    }

    if (textures.empty()) {
        std::cout << "[Texture] No textures of type '" << typeName << "' found.\n";
    }

    return textures;
}
