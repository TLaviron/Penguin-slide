//
// Created by clemenre on 4/10/17.
//

#include "../include/PenguinLightedRenderable.hpp"
#include "../include/Utils.hpp"
#include "../include/lighting/Material.hpp"

PenguinRenderable::PenguinRenderable(ShaderProgramPtr shaderProgram) :
    TexturedMeshRenderable(shaderProgram, "../tux/TuxBody.obj", "../tux/TuxBody.png" ) {

    glm::vec3 translate(0, 4.5, 2.35);
    glm::quat BodyRota1 = quatAxisAngle(float(M_PI_2), glm::vec3(0, 0, 1));
    glm::quat BodyRota2 = quatAxisAngle(float(M_PI_2), glm::vec3(0, 1, 0));
    glm::vec3 scale(2, 2, 2);
    MaterialPtr pearl = Material::Pearl();
    this->setMaterial(pearl);
    this->setParentTransform(GeometricTransformation::makeTranslation(translate));
    this->setParentTransform(GeometricTransformation::makeRotation(BodyRota1));
    this->setParentTransform(GeometricTransformation::makeRotation(BodyRota2));
    this->setParentTransform(GeometricTransformation::makeScale(scale));

    translate = glm::vec3(0.8, 4.2, 1.0);
    glm::quat Rota1 = quatAxisAngle(float(M_PI_2), glm::vec3(1,0,0));
    glm::quat Rota2 = quatAxisAngle(float(M_PI_2), glm::vec3(0,1,0));

    RF =std::make_shared<TexturedMeshRenderable>(texShader, "../tux/RightFoot.obj", "../tux/RightFoot.png");
    RF->setMaterial(pearl);
    RF->setParentTransform(GeometricTransformation::makeTranslation(translate));
    RF->setParentTransform(GeometricTransformation::makeRotation(Rota1));
    RF->setParentTransform(GeometricTransformation::makeRotation(Rota2));
    RF->setParentTransform(GeometricTransformation::makeScale(scale));

    translate = glm::vec3(-0.7, 4.2, 1.0);

    TexturedMeshRenderablePtr TuxLF =
            std::make_shared<TexturedMeshRenderable>(
                    texShader, "../tux/LeftFoot.obj", "../tux/leftFoot.png");
    TuxLF->setMaterial(pearl);
    TuxLF->setParentTransform(GeometricTransformation::makeTranslation(translate));
    TuxLF->setParentTransform(GeometricTransformation::makeRotation(Rota1));
    TuxLF->setParentTransform(GeometricTransformation::makeRotation(Rota2));
    TuxLF->setParentTransform(GeometricTransformation::makeScale(scale));

    translate = glm::vec3(-1.03, 4, 2.3);

    TexturedMeshRenderablePtr TuxLH =
            std::make_shared<TexturedMeshRenderable>(
                    texShader, "../tux/LeftHand.obj", "../tux/LeftHand.png");
    TuxLH->setMaterial(pearl);
    TuxLH->setParentTransform(GeometricTransformation::makeTranslation(translate));
    TuxLH->setParentTransform(GeometricTransformation::makeRotation(Rota1));
    TuxLH->setParentTransform(GeometricTransformation::makeRotation(Rota2));
    TuxLH->setParentTransform(GeometricTransformation::makeScale(scale));

    translate = glm::vec3(1.09, 4, 2.3);

    TexturedMeshRenderablePtr TuxRH =
            std::make_shared<TexturedMeshRenderable>(
                    texShader, "../tux/RightHand.obj", "../tux/RightHand.png");
    TuxRH->setMaterial(pearl);
    TuxRH->setParentTransform(GeometricTransformation::makeTranslation(translate));
    TuxRH->setParentTransform(GeometricTransformation::makeRotation(Rota1));
    TuxRH->setParentTransform(GeometricTransformation::makeRotation(Rota2));
    TuxRH->setParentTransform(GeometricTransformation::makeScale(scale));

}

