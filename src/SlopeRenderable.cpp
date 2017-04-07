//
// Created by sebastien on 03/04/17.
//

#include "../include/SlopeRenderable.hpp"

SlopeRenderable::SlopeRenderable(ShaderProgramPtr shaderProgram, BasicTerrainGenerator terrain) :
        HierarchicalRenderable(shaderProgram)
{
    int initx=20;
    int inity=100;
    int x = 2*initx;
    int y = 2*inity;
    int n = 20; // discretisation nécessairement pair
    std::vector<glm::vec3> spline1(x+2);
    std::vector<glm::vec3> spline2(y+2);
    std::vector<glm::vec3> herm1((x-1)*n + 1);
    std::vector<glm::vec3> herm2((y-1)*n + 1);
    std::vector<glm::vec3> hermtan1((x-1)*n + 1);
    std::vector<glm::vec3> hermtan2((y-1)*n + 1);
    // points de controle du spline
    for (int k = 0; k < x+2; ++k) {
        spline1[k] = glm::vec3(k-initx,0,random(-terrain.getVariation(), terrain.getVariation()));
    }
    for (int k = 0; k < y+2; ++k) {
        spline2[k] = glm::vec3(0,k,random(-terrain.getVariation(), terrain.getVariation()));
    }
    // calcul de l'interpolation des points de la spline
    for (int k = 0; k < (x-1)*n + 1; ++k) {
        herm1[k] = hermiteInterp(spline1, ((float) k) / n );
    }
    for (int k = 0; k < (y-1)*n + 1; ++k) {
        herm2[k] = hermiteInterp(spline2, ((float) k) / n );
    }
    for (int k = 0; k < (x-1)*n + 1; ++k) {
        hermtan1[k] = hermiteTangent(spline1, ((float) k) / n );
    }
    for (int k = 0; k < (y-1)*n + 1; ++k) {
        hermtan2[k] = hermiteTangent(spline2, ((float) k) / n );
    }

    //création des faces
    int debut = 0;
    int current_vertex = 0;
    for (int i = 0; i < n*(x-1)+1; ++i) {
        for (int j = debut; j < (y-1)*n + 1 ; j+=2) {
            glm::vec3 tmp(herm1[i][0] + herm2[j][0],herm1[i][1] + herm2[j][1],herm1[i][2] * herm2[j][2]);
            tmp[2] +=terrain.getX(tmp[0])+terrain.getY(tmp[1]);
            m_positions.push_back(tmp);
            glm::vec3 tan1(hermtan1[i][0],hermtan1[i][1],hermtan1[i][2]*herm2[j][2]);
            glm::vec3 tan2(hermtan2[j][0],hermtan2[j][1],hermtan1[j][2]*herm2[i][2]);
            glm::vec3 tanx(terrain.getX(tmp[0]+1) - terrain.getX(tmp[0]),0,0);
            glm::vec3 tany(0,terrain.getY(tmp[1]+1) - terrain.getY(tmp[1]),0);
            glm::vec3 tan(glm::normalize(tanx + tany + glm::cross(tan1,tan2)));
            m_normals.push_back(tan);
//            m_colors.push_back(glm::vec4(tan[0],tan[1],tan[2],1.0));
            m_colors.push_back(glm::vec4(1.0,1.0,1.0,0.0));
//            m_colors.push_back(randomColor());
            if (i!=0 && i != n*(x-1)){
                if (debut ||(j != 0 && j != (y-1)*n) ) {
                    m_index.push_back(glm::ivec3(current_vertex, current_vertex - ((y-1) * (n / 2) +1),
                                                 current_vertex + ((y-1) * (n / 2)+1) - 1));
                    m_index.push_back(glm::ivec3(current_vertex, (current_vertex - ((y-1) * (n / 2)+1)) + 1,
                                                 current_vertex + ((y-1) * (n / 2)+1)));
                }else if (j == 0){
                    m_index.push_back(glm::ivec3(current_vertex,(current_vertex-((y-1)*(n/2)+1)) + 1,current_vertex + ((y-1)*(n/2)+1) ));
                }else{
                    m_index.push_back(glm::ivec3(current_vertex,current_vertex-((y-1)*(n/2)+1),current_vertex+((y-1)*(n/2)+1) -1 ));
                }
            }
            current_vertex++;
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
    //Location
    int modelLocation = m_shaderProgram->getUniformLocation("modelMat");
    int positionLocation = m_shaderProgram->getAttributeLocation("vPosition");
    int colorLocation = m_shaderProgram->getAttributeLocation("vColor");
    int normalLocation = m_shaderProgram->getAttributeLocation("vNormal");

    //Send data to GPU
    if (modelLocation != ShaderProgram::null_location) {
        glcheck(glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(getModelMatrix())));
    }

    if (positionLocation != ShaderProgram::null_location) {
        //Activate location
        glcheck(glEnableVertexAttribArray(positionLocation));
        //Bind buffer
        glcheck(glBindBuffer(GL_ARRAY_BUFFER, m_pBuffer));
        //Specify internal format
        glcheck(glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)0));
    }
    if (colorLocation != ShaderProgram::null_location) {
        glcheck(glEnableVertexAttribArray(colorLocation));
        glcheck(glBindBuffer(GL_ARRAY_BUFFER, m_cBuffer));
        glcheck(glVertexAttribPointer(colorLocation, 4, GL_FLOAT, GL_FALSE, 0, (void*)0));
    }
    if (normalLocation != ShaderProgram::null_location) {
        glcheck(glEnableVertexAttribArray(normalLocation));
        glcheck(glBindBuffer(GL_ARRAY_BUFFER, m_nBuffer));
        glcheck(glVertexAttribPointer(normalLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)0));
    }

    glcheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iBuffer));
    glcheck(glDrawElements(GL_TRIANGLES, m_index.size()*3, GL_UNSIGNED_INT, (void*)0));

    if (positionLocation != ShaderProgram::null_location) {
        glcheck(glDisableVertexAttribArray(positionLocation));
    }
    if (colorLocation != ShaderProgram::null_location) {
        glcheck(glDisableVertexAttribArray(colorLocation));
    }
    if (normalLocation != ShaderProgram::null_location) {
        glcheck(glDisableVertexAttribArray(normalLocation));
    }
}

void SlopeRenderable::do_animate(float time) {}

SlopeRenderable::~SlopeRenderable()
{
    glDeleteBuffers(1, &m_pBuffer);
    glDeleteBuffers(1, &m_cBuffer);
    glDeleteBuffers(1, &m_iBuffer);
    glcheck(glDeleteBuffers(1, &m_nBuffer));

}

