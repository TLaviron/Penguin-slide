//
// Created by sebastien on 03/04/17.
//

#include "../include/SlopeRenderable.hpp"

SlopeRenderable::SlopeRenderable(ShaderProgramPtr shaderProgram , double inclinaison, BasicTerrainGenerator terrain) :
        HierarchicalRenderable(shaderProgram)
{

//    // 8 vertices
//    m_positions.push_back(glm::vec3(-0.5, -0.5, -0.5));
//    m_positions.push_back(glm::vec3(0.5, -0.5, -0.5));
//    m_positions.push_back(glm::vec3(0.5, 0.5, -0.5));
//    m_positions.push_back(glm::vec3(-0.5, 0.5, -0.5));
//    m_positions.push_back(glm::vec3(-0.5, -0.5, 0.5));
//    m_positions.push_back(glm::vec3(-0.5, 0.5, 0.5));
//    m_positions.push_back(glm::vec3(0.5, 0.5, 0.5));
//    m_positions.push_back(glm::vec3(0.5, -0.5, 0.5));
//
//    // 8 normals (== vertex coordinates, since the cube is centered)
//    for(const glm::vec3& x : m_positions) {
//        m_normals.push_back(glm::normalize(x));
//    }
//
//    // 12 triangles, 3 index each
//    m_index.push_back(glm::ivec3(0, 2, 1));
//    m_index.push_back(glm::ivec3(0, 3, 2));
//    m_index.push_back(glm::ivec3(1, 6, 7));
//    m_index.push_back(glm::ivec3(1, 2, 6));
//    m_index.push_back(glm::ivec3(5, 4, 7));
//    m_index.push_back(glm::ivec3(5, 7, 6));
//    m_index.push_back(glm::ivec3(4, 3, 0));
//    m_index.push_back(glm::ivec3(4, 5, 3));
//    m_index.push_back(glm::ivec3(3, 6, 2));
//    m_index.push_back(glm::ivec3(3, 5, 6));
//    m_index.push_back(glm::ivec3(4, 0, 1));
//    m_index.push_back(glm::ivec3(4, 1, 7));
//
//    //Assign one color to each of the 12 triangles
//    m_colors.push_back(glm::vec4(1,0,0,1));
//    m_colors.push_back(glm::vec4(0,1,0,1));
//    m_colors.push_back(glm::vec4(0,0,1,1));
//    m_colors.push_back(glm::vec4(0,1,1,1));
//    m_colors.push_back(glm::vec4(1,0,0,1));
//    m_colors.push_back(glm::vec4(0,1,0,1));
//    m_colors.push_back(glm::vec4(0,0,1,1));
//    m_colors.push_back(glm::vec4(0,1,1,1));



    int x = 8;
    int y = 8;
    int n = 2; // discretisation
    std::vector<glm::vec3> spline1(x);
    std::vector<glm::vec3> spline2(y);
    std::vector<glm::vec3> herm1((x-1)*n + 1);
    std::vector<glm::vec3> herm2((y-1)*n + 1);
    // points de controle du spline
    for (int k = 0; k < x; ++k) {
        spline1[k] = glm::vec3(0,k,random(-terrain.getVariation(), terrain.getVariation()));
    }
    for (int k = 0; k < y; ++k) {
        spline2[k] = glm::vec3(k,0,random(-terrain.getVariation(), terrain.getVariation()));
    }
    // calcul de l'interpolation des points de la spline
    for (int k = 0; k < (x-1)*n + 1; ++k) {
        if(k>n && k<(x-2)*n + 1 ){
            herm1[k] = hermiteInterp(spline1, ((float) k) / n);
        }else if(k<=n){
            herm1[k] = glm::vec3(0,((float) k)/n,spline1[1][2] + (spline1[1][2] - spline1[0][2])* ((float) (k%n))/n);
        }else {
            herm1[k] = glm::vec3(0,((float) k)/n,spline1[x-2][2]+ (spline1[x-1][2] - spline1[x-2][2])* ((float) (k%n))/n);
        }
    }
    for (int k = 0; k < (y-1)*n + 1; ++k) {
        if(k>n && k<(y-2)*n+1 ){
            herm2[k] = hermiteInterp(spline2, ((float) k) / n);
        } else if(k<=n) {
            herm2[k] = glm::vec3(((float) k)/n,0,spline2[0][2] + (spline2[1][2] - spline2[0][2])* ((float) (k%n))/n);
        } else {
            herm2[k] = glm::vec3((((float) k)/n),0,spline2[y-2][2] + (spline2[y-1][2] - spline2[y-2][2])* ((float) (k%n))/n);
        }
    }

    //création des faces
    m_positions.resize(n*n*x*y/2);
    m_colors.resize(n*n*x*y/2);
    m_index.resize(n*n*x*y);
    m_normals.resize(n*n*x*y);
    int debut = 0;
    for (int i = 0; i < n*x; ++i) {
        for (int j = debut; j < n*y ; j+=2) {
            m_positions.push_back(herm1[i] + herm2[j]);
            m_colors.push_back(randomColor());

        }
        debut = 1 - debut;
    }
    debut = 0;
    for (int i = 0; i < n*x; ++i) {
        for (int j = debut; j < (n*y-debut)/2; j++) {
            if (i!=0){
                m_index.push_back(glm::vec3(i*n*y +j,i*n*y +j+1,(i-1)*n*y -debut +j ));
            }
            if (i != n*x -1){
                m_index.push_back(glm::vec3(i*n*y +j,i*n*y +j+1,(i+1)*n*y -debut +j ));

            }
        }
        debut = 1 - debut;
    }
    m_model = glm::mat4(1.0);
    glGenBuffers(1, &m_pBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_pBuffer);
    glBufferData(GL_ARRAY_BUFFER, m_positions.size()*sizeof(glm::vec3), m_positions.data(), GL_STATIC_DRAW);
    glGenBuffers(1, &m_cBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_cBuffer);
    glBufferData(GL_ARRAY_BUFFER, m_colors.size()*sizeof(glm::vec4), m_colors.data(), GL_STATIC_DRAW);
    glcheck(glGenBuffers(1, &m_nBuffer));
    glcheck(glBindBuffer(GL_ARRAY_BUFFER, m_nBuffer));
    glcheck(glBufferData(GL_ARRAY_BUFFER, m_normals.size()*sizeof(glm::vec3), m_normals.data(), GL_STATIC_DRAW));
    glcheck(glGenBuffers(1, &m_iBuffer));
    glcheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iBuffer));
    glcheck(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_index.size()*sizeof(glm::ivec3), m_index.data(), GL_STATIC_DRAW));
}

void SlopeRenderable::do_draw()
{
    int modelLocation = m_shaderProgram->getUniformLocation("modelMat");
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(m_model));
    int positionLocation = m_shaderProgram->getAttributeLocation("vPosition");
    int colorLocation  = m_shaderProgram->getAttributeLocation("vColor");
    int normalLocation = m_shaderProgram->getAttributeLocation("vNormal");

    if (modelLocation != ShaderProgram::null_location) {
        glcheck(glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(getModelMatrix())));
    }


    glEnableVertexAttribArray(positionLocation);
    glBindBuffer(GL_ARRAY_BUFFER, m_pBuffer);
    glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glEnableVertexAttribArray(colorLocation);
    glBindBuffer(GL_ARRAY_BUFFER, m_cBuffer);
    glVertexAttribPointer(colorLocation, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glcheck(glEnableVertexAttribArray(normalLocation));
    glcheck(glBindBuffer(GL_ARRAY_BUFFER, m_nBuffer));
    glcheck(glVertexAttribPointer(normalLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)0));

    glcheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iBuffer));
    glcheck(glDrawElements(GL_TRIANGLES, m_index.size()*3, GL_UNSIGNED_INT, (void*)0));
//release
    glDisableVertexAttribArray(positionLocation);
    glDisableVertexAttribArray(colorLocation);
    glcheck(glDisableVertexAttribArray(normalLocation));

}

void SlopeRenderable::do_animate(float time) {}

SlopeRenderable::~SlopeRenderable()
{
    glDeleteBuffers(1, &m_pBuffer);
    glDeleteBuffers(1, &m_cBuffer);
    glDeleteBuffers(1, &m_iBuffer);
    glcheck(glDeleteBuffers(1, &m_nBuffer));

}

