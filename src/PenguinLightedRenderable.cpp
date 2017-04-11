//
// Created by clemenre on 4/10/17.
//

#include "../include/PenguinLightedRenderable.hpp"

static glm::mat4 parentTransformationBody;


PenguinLightedRenderable::PenguinLightedRenderable(ShaderProgramPtr texShader,Viewer &viewer) :
    HierarchicalRenderable(texShader){

    glm::mat4 parentTransformation, localTransformation;

    MaterialPtr pearl = Material::Pearl();

    Body = std::make_shared<KeyframedMeshRenderable>(
                    texShader, "../tux/TuxBody.obj", "../tux/TuxBody.png");

    RF = std::make_shared<KeyframedMeshRenderable>(
                    texShader, "../tux/RightFoot.obj", "../tux/RightFoot.png");

    LF = std::make_shared<KeyframedMeshRenderable>(
                    texShader, "../tux/LeftFoot.obj", "../tux/leftFoot.png");

    LH = std::make_shared<KeyframedMeshRenderable>(
                    texShader, "../tux/LeftHand.obj", "../tux/LeftHand.png");

    RH = std::make_shared<KeyframedMeshRenderable>(
                    texShader, "../tux/RightHand.obj", "../tux/RightHand.png");

    Body->setMaterial(pearl);
    parentTransformationBody = glm::translate( glm::mat4(1.0), glm::vec3(0, 4.5, 2.35));
    parentTransformationBody = glm::rotate( parentTransformationBody, float(M_PI_2), glm::vec3(1,0,0));
    parentTransformationBody = glm::rotate( parentTransformationBody, float(M_PI_2), glm::vec3(0,1,0));
    parentTransformationBody = glm::scale( parentTransformationBody, glm::vec3(2,2,2));
    Body->setParentTransform( parentTransformationBody );
    viewer.addRenderable(Body);


    RF->setMaterial(pearl);
    parentTransformation = glm::translate( glm::mat4(1.0), glm::vec3(-0.1, -0.68, 0.35));
    RF->setParentTransform( parentTransformation );
    viewer.addRenderable(RF);


    LF->setMaterial(pearl);
    parentTransformation = glm::translate( glm::mat4(1.0), glm::vec3(-0.12, -0.68, -0.34));
    LF->setParentTransform( parentTransformation );
    viewer.addRenderable(LF);


    LH->setMaterial(pearl);
    parentTransformation = glm::translate( glm::mat4(1.0), glm::vec3(-0.29,-0.1 ,-0.51));
    LH->setParentTransform( parentTransformation );
    viewer.addRenderable(LH);


    RH->setMaterial(pearl);
    parentTransformation = glm::translate( glm::mat4(1.0), glm::vec3(-0.29,-0.1 ,0.56));
    RH->setParentTransform( parentTransformation );
    viewer.addRenderable(RH);

    HierarchicalRenderable::addChild(Body, RH);
    HierarchicalRenderable::addChild(Body, LH);
    HierarchicalRenderable::addChild(Body, RF);
    HierarchicalRenderable::addChild(Body, LF);


}

void PenguinLightedRenderable::walkTux(Viewer& viewer, const ShaderProgramPtr& texShader,float time, glm::vec3 position,glm::vec3 orientation, float distance){
    //Keyframes on parent transformation: pairs of (time, transformation)

    Body->addParentTransformKeyframe(0.0+time, GeometricTransformation(glm::vec3(0.0,0.0,1.5) + position , glm::normalize(glm::angleAxis(float(M_PI)/4, glm::vec3(2.5, 2.5,2.5)))) );
    Body->addParentTransformKeyframe(1.0+time, GeometricTransformation(glm::vec3(0.0,0.0,1.5) + position+(distance*0.25f*glm::normalize(orientation)),
            glm::normalize(glm::angleAxis(float(M_PI)/4, glm::vec3(2.5, 2.5,2.2)))) );
    Body->addParentTransformKeyframe(2.0+time, GeometricTransformation(glm::vec3(0.0,0.0,1.5) + position+(distance*0.5f*glm::normalize(orientation)),
                                                                       glm::normalize(glm::angleAxis(float(M_PI)/4, glm::vec3(2.5, 2.5,2.5)))) );
    Body->addParentTransformKeyframe(3.0+time, GeometricTransformation(glm::vec3(0.0,0.0,1.5) + position+(distance*0.75f*glm::normalize(orientation)),
                                                                       glm::normalize(glm::angleAxis(float(M_PI)/4, glm::vec3(2.5, 2.5,2.8)))) );
    Body->addParentTransformKeyframe(4.0+time, GeometricTransformation(glm::vec3(0.0,0.0,1.5) + position+(distance*glm::normalize(orientation)),
                                                                       glm::normalize(glm::angleAxis(float(M_PI)/4, glm::vec3(2.5, 2.5,2.5)))) );
    LF->addLocalTransformKeyframe(0.0 + time, GeometricTransformation(glm::vec3(0.0,0.0,0.0), glm::normalize(glm::angleAxis(0.0f, glm::vec3(1.0,0.0,0.0)))) );
    LF->addLocalTransformKeyframe(1.0+ time, GeometricTransformation(glm::vec3(0.0,0.0,0.0), glm::normalize(glm::angleAxis(float(M_PI)/8, glm::vec3(0.0,0.0,1.0)))) );
    LF->addLocalTransformKeyframe(2.0+ time, GeometricTransformation(glm::vec3(0.0,0.0,0.0), glm::normalize(glm::angleAxis(0.0f, glm::vec3(0.0,0.0,1.0)))) );
    LF->addLocalTransformKeyframe(3.0+ time, GeometricTransformation(glm::vec3(0.0,0.0,0.0), glm::normalize(glm::angleAxis(-float(M_PI)/8, glm::vec3(0.0,0.0,1.0)))) );
    LF->addLocalTransformKeyframe(4.0+ time, GeometricTransformation(glm::vec3(0.0,0.0,0.0), glm::normalize(glm::angleAxis(0.0f, glm::vec3(0.0,0.0,1.0)))) );
    RF->addLocalTransformKeyframe(0.0+ time, GeometricTransformation(glm::vec3(0.0,0.0,0.0), glm::normalize(glm::angleAxis(0.0f, glm::vec3(1.0,0.0,0.0)))) );
    RF->addLocalTransformKeyframe(1.0+ time, GeometricTransformation(glm::vec3(0.0,0.0,0.0), glm::normalize(glm::angleAxis(-float(M_PI)/8, glm::vec3(0.0,0.0,1.0)))) );
    RF->addLocalTransformKeyframe(2.0+ time, GeometricTransformation(glm::vec3(0.0,0.0,0.0), glm::normalize(glm::angleAxis(0.0f, glm::vec3(0.0,0.0,1.0)))) );
    RF->addLocalTransformKeyframe(3.0+ time, GeometricTransformation(glm::vec3(0.0,0.0,0.0), glm::normalize(glm::angleAxis(float(M_PI)/8, glm::vec3(0.0,0.0,1.0)))) );
    RF->addLocalTransformKeyframe(4.0+ time, GeometricTransformation(glm::vec3(0.0,0.0,0.0), glm::normalize(glm::angleAxis(0.0f, glm::vec3(0.0,0.0,1.0)))) );
    LH->addLocalTransformKeyframe(0.0+ time, GeometricTransformation(glm::vec3(0.0,0.0,0.0), glm::normalize(glm::angleAxis(0.0f, glm::vec3(1.0,0.0,0.0)))) );
    LH->addLocalTransformKeyframe(1.0+ time, GeometricTransformation(glm::vec3(0.0,0.0,0.0), glm::normalize(glm::angleAxis(-float(M_PI)/8, glm::vec3(0.0,0.0,1.0)))) );
    LH->addLocalTransformKeyframe(2.0+ time, GeometricTransformation(glm::vec3(0.0,0.0,0.0), glm::normalize(glm::angleAxis(0.0f, glm::vec3(0.0,0.0,1.0)))) );
    LH->addLocalTransformKeyframe(3.0+ time, GeometricTransformation(glm::vec3(0.0,0.0,0.0), glm::normalize(glm::angleAxis(float(M_PI)/8, glm::vec3(0.0,0.0,1.0)))) );
    LH->addLocalTransformKeyframe(4.0+ time, GeometricTransformation(glm::vec3(0.0,0.0,0.0), glm::normalize(glm::angleAxis(0.0f, glm::vec3(0.0,0.0,1.0)))) );
    RH->addLocalTransformKeyframe(0.0+ time, GeometricTransformation(glm::vec3(0.0,0.0,0.0), glm::normalize(glm::angleAxis(0.0f, glm::vec3(1.0,0.0,0.0)))) );
    RH->addLocalTransformKeyframe(1.0+ time, GeometricTransformation(glm::vec3(0.0,0.0,0.0), glm::normalize(glm::angleAxis(float(M_PI)/8, glm::vec3(0.0,0.0,1.0)))) );
    RH->addLocalTransformKeyframe(2.0+ time, GeometricTransformation(glm::vec3(0.0,0.0,0.0), glm::normalize(glm::angleAxis(0.0f, glm::vec3(0.0,0.0,1.0)))) );
    RH->addLocalTransformKeyframe(3.0+ time, GeometricTransformation(glm::vec3(0.0,0.0,0.0), glm::normalize(glm::angleAxis(-float(M_PI)/8, glm::vec3(0.0,0.0,1.0)))) );
    RH->addLocalTransformKeyframe(4.0+ time, GeometricTransformation(glm::vec3(0.0,0.0,0.0), glm::normalize(glm::angleAxis(0.0f, glm::vec3(0.0,0.0,1.0)))) );
}

void PenguinLightedRenderable::do_animate(float time){

}

void PenguinLightedRenderable::do_draw(){

}

PenguinLightedRenderable::~PenguinLightedRenderable(){

}

KeyframedMeshRenderablePtr PenguinLightedRenderable::getLF(){
    return LF;
}

KeyframedMeshRenderablePtr PenguinLightedRenderable::getRF(){
    return RF;
}

KeyframedMeshRenderablePtr PenguinLightedRenderable::getLH(){
    return LH;
}

KeyframedMeshRenderablePtr PenguinLightedRenderable::getRH(){
    return RH;
}

KeyframedMeshRenderablePtr PenguinLightedRenderable::getBody(){
    return Body;
}

void PenguinLightedRenderable::bindMembers(PenguinLightedRenderablePtr thisPenguin){
    HierarchicalRenderable::addChild(thisPenguin,Body);
}
