//
// Created by clemenre on 4/10/17.
//

#include "../include/PenguinLightedRenderable.hpp"
#include <glm/gtx/quaternion.hpp>
#include "../include/SnowballRenderable.hpp"
#include "glm/ext.hpp"

PenguinLightedRenderable::PenguinLightedRenderable(ShaderProgramPtr texShader,DynamicSystemPtr dynamicSystem) :
        HierarchicalRenderable(texShader){

    //Loading the differents parts of the penguin
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

    // placing the different parts together
    Body->setMaterial(pearl);

    setParentTransform(GeometricTransformation(glm::vec3(0, 4.5, 2.35), quatAxisAngle(float(M_PI_2), glm::vec3(1,0,0)) * quatAxisAngle(float(M_PI_2), glm::vec3(0,1,0)), glm::vec3(2,2,2)));
    Body->setParentTransform(GeometricTransformation());

    RF->setMaterial(pearl);
    parentTransformation = glm::translate( glm::mat4(1.0), glm::vec3(-0.1, -0.68, 0.35));
    RF->setParentTransform( parentTransformation );

    LF->setMaterial(pearl);
    parentTransformation = glm::translate( glm::mat4(1.0), glm::vec3(-0.12, -0.68, -0.34));
    LF->setParentTransform( parentTransformation );

    LH->setMaterial(pearl);
    parentTransformation = glm::translate( glm::mat4(1.0), glm::vec3(-0.29,-0.1 ,-0.51));
    LH->setParentTransform( parentTransformation );

    RH->setMaterial(pearl);
    parentTransformation = glm::translate( glm::mat4(1.0), glm::vec3(-0.29,-0.1 ,0.56));
    RH->setParentTransform( parentTransformation );

    //link the parts
    HierarchicalRenderable::addChild(Body, RH);
    HierarchicalRenderable::addChild(Body, LH);
    HierarchicalRenderable::addChild(Body, RF);
    HierarchicalRenderable::addChild(Body, LF);

    //physics initializing
    m_status = PENGUIN_STATUS_STARTING;
    m_particle = std::make_shared<Particle>(glm::vec3(0, 0, 0), glm::vec3(0), 5, 0.7);
    m_particle->setFixed(true);
    dynamicSystem->addParticle(m_particle);

    std::vector<ParticlePtr> particleList;
    particleList.push_back(m_particle);
    m_force = std::make_shared<ConstantForceField>(particleList, glm::vec3(0,0,-10));
    dynamicSystem->addForceField(m_force);

    m_forceController = std::make_shared<ControlledForceField>(texShader, m_force);

    scheduleStatusChange = -1;
}

void PenguinLightedRenderable::walkTux(Viewer& viewer, const ShaderProgramPtr& texShader,float time, float duration){
    //Keyframes on parent transformation: pairs of (time, transformation)

    float timeStep = duration / 4;
    glm::vec3 position = m_particle->getPosition();
    Body->addParentTransformKeyframe(0.0+time, GeometricTransformation(position ,
                                                                       glm::normalize(glm::angleAxis(0.0f, glm::vec3(0.0,0.0,0.0)))) );
    position += glm::vec3(0.5,0.0,0.0);
    Body->addParentTransformKeyframe(1*timeStep+time, GeometricTransformation(position,
                                                                              glm::normalize(glm::angleAxis(float(M_PI)/16, glm::vec3(0.0,1.0,0.2)))) );
    position += glm::vec3(0.5,0.0,0.0);
    Body->addParentTransformKeyframe(2*timeStep+time, GeometricTransformation(position,
                                                                              glm::normalize(glm::angleAxis(0.0f, glm::vec3(0.0,1.0,0.2)))) );
    position += glm::vec3(0.5,0.0,0.0);
    Body->addParentTransformKeyframe(3*timeStep+time, GeometricTransformation(position,
                                                                              glm::normalize(glm::angleAxis(-float(M_PI)/16, glm::vec3(0.0,1.0,0.2)))) );
    position += glm::vec3(0.5,0.0,0.0);
    Body->addParentTransformKeyframe(4*timeStep+time, GeometricTransformation(position,
                                                                              glm::normalize(glm::angleAxis(0.0f, glm::vec3(0.0,1.0,0.2)))) );


    glm::vec3 z(0.0,0.0,1.0);
    //Movement of feet and hands
    LF->addLocalTransformKeyframe(0*timeStep+time, GeometricTransformation(glm::vec3(0.0,0.0,0.0), glm::normalize(glm::angleAxis(0.0f, z))));
    LF->addLocalTransformKeyframe(1*timeStep+time, GeometricTransformation(glm::vec3(0.0,0.0,0.0), glm::normalize(glm::angleAxis(float(M_PI)/8, z))));
    LF->addLocalTransformKeyframe(2*timeStep+time, GeometricTransformation(glm::vec3(0.0,0.0,0.0), glm::normalize(glm::angleAxis(0.0f, z))));
    LF->addLocalTransformKeyframe(3*timeStep+time, GeometricTransformation(glm::vec3(0.0,0.0,0.0), glm::normalize(glm::angleAxis(-float(M_PI)/8, z))));
    LF->addLocalTransformKeyframe(4*timeStep+time, GeometricTransformation(glm::vec3(0.0,0.0,0.0), glm::normalize(glm::angleAxis(0.0f, z))));
    RF->addLocalTransformKeyframe(0*timeStep+time, GeometricTransformation(glm::vec3(0.0,0.0,0.0), glm::normalize(glm::angleAxis(0.0f, z))));
    RF->addLocalTransformKeyframe(1*timeStep+time, GeometricTransformation(glm::vec3(0.0,0.0,0.0), glm::normalize(glm::angleAxis(-float(M_PI)/8, z))));
    RF->addLocalTransformKeyframe(2*timeStep+time, GeometricTransformation(glm::vec3(0.0,0.0,0.0), glm::normalize(glm::angleAxis(0.0f, z))));
    RF->addLocalTransformKeyframe(3*timeStep+time, GeometricTransformation(glm::vec3(0.0,0.0,0.0), glm::normalize(glm::angleAxis(float(M_PI)/8, z))));
    RF->addLocalTransformKeyframe(4*timeStep+time, GeometricTransformation(glm::vec3(0.0,0.0,0.0), glm::normalize(glm::angleAxis(0.0f, z))));
    LH->addLocalTransformKeyframe(0*timeStep+time, GeometricTransformation(glm::vec3(0.0,0.0,0.0), glm::normalize(glm::angleAxis(0.0f, z))));
    LH->addLocalTransformKeyframe(1*timeStep+time, GeometricTransformation(glm::vec3(0.0,0.0,0.0), glm::normalize(glm::angleAxis(-float(M_PI)/8, z))));
    LH->addLocalTransformKeyframe(2*timeStep+time, GeometricTransformation(glm::vec3(0.0,0.0,0.0), glm::normalize(glm::angleAxis(0.0f, z))));
    LH->addLocalTransformKeyframe(3*timeStep+time, GeometricTransformation(glm::vec3(0.0,0.0,0.0), glm::normalize(glm::angleAxis(float(M_PI)/8,z))));
    LH->addLocalTransformKeyframe(4*timeStep+time, GeometricTransformation(glm::vec3(0.0,0.0,0.0), glm::normalize(glm::angleAxis(0.0f, z))));
    RH->addLocalTransformKeyframe(0*timeStep+time, GeometricTransformation(glm::vec3(0.0,0.0,0.0), glm::normalize(glm::angleAxis(0.0f,z))));
    RH->addLocalTransformKeyframe(1*timeStep+time, GeometricTransformation(glm::vec3(0.0,0.0,0.0), glm::normalize(glm::angleAxis(float(M_PI)/8,z))));
    RH->addLocalTransformKeyframe(2*timeStep+time, GeometricTransformation(glm::vec3(0.0,0.0,0.0), glm::normalize(glm::angleAxis(0.0f, z))));
    RH->addLocalTransformKeyframe(3*timeStep+time, GeometricTransformation(glm::vec3(0.0,0.0,0.0), glm::normalize(glm::angleAxis(-float(M_PI)/8, z))));
    RH->addLocalTransformKeyframe(4*timeStep+time, GeometricTransformation(glm::vec3(0.0,0.0,0.0), glm::normalize(glm::angleAxis(0.0f, z))));

    m_particle->setPosition(position);
}

void PenguinLightedRenderable::jumpTux(Viewer& viewer, const ShaderProgramPtr& texShader,float time, float duration){
    //Keyframes on parent transformation: pairs of (time, transformation)
    float timeStep = duration / 3;
    glm::vec3 position = m_particle->getPosition();
    Body->addParentTransformKeyframe(0*timeStep+time, GeometricTransformation(position ,
                                                                              glm::normalize(glm::angleAxis(-float(M_PI)/16, glm::vec3(0.0,0.0,1.0)))) );
    position += glm::vec3(0.5,0.25,0.0);
    Body->addParentTransformKeyframe(1*timeStep+time, GeometricTransformation(position,
                                                                              glm::normalize(glm::angleAxis(-float(M_PI)/8, glm::vec3(0.0,0.0,1.0)))) );
    position += glm::vec3(0.5,0.25,0.0);
    Body->addParentTransformKeyframe(2*timeStep+time, GeometricTransformation(position,
                                                                              glm::normalize(glm::angleAxis(-float(M_PI)/4, glm::vec3(0.0,0.0,1.0)))) );
    position += glm::vec3(0.5,0.0,0.0);
    Body->addParentTransformKeyframe(3*timeStep+time, GeometricTransformation(position,
                                                                              glm::normalize(glm::angleAxis(-float(M_PI)/2, glm::vec3(0.0,0.0,1.0)))) );

    glm::vec3 z(0.0,0.0,1.0);
    //Movement of feet and hands
    LF->addLocalTransformKeyframe(0.0+time, GeometricTransformation(glm::vec3(0.0,0.0,0.0), glm::normalize(glm::angleAxis(0.0f, z))));
    LF->addLocalTransformKeyframe(2*timeStep+time, GeometricTransformation(glm::vec3(0.0,0.0,0.0), glm::normalize(glm::angleAxis(-float(M_PI)/4, z))));
    RF->addLocalTransformKeyframe(0.0+time, GeometricTransformation(glm::vec3(0.0,0.0,0.0), glm::normalize(glm::angleAxis(0.0f, z))));
    RF->addLocalTransformKeyframe(2*timeStep+time, GeometricTransformation(glm::vec3(0.0,0.0,0.0), glm::normalize(glm::angleAxis(-float(M_PI)/4, z))));

    // update position
    m_particle->setPosition(position);
    m_particle->setVelocity(glm::vec3(0, 1, 0)); //could be oriented...
    scheduleStatusChange = time+duration;

}

void PenguinLightedRenderable::collisionTux(Viewer &viewer, const ShaderProgramPtr &texShader, float time,
                                            float duration, glm::vec3 dirProjection) {
    float timeStep = duration / 3;
    glm::vec3 position = m_particle->getPosition();

    glm::vec3 velocityDirection, yAxis(0, 1, 0), zAxis(0, 0, 1);
    glm::vec3 newRightSide;
    glm::quat rot;

    velocityDirection = glm::normalize(m_particle->getVelocity());

    rot = glm::rotation(yAxis, velocityDirection);
    newRightSide = rot * zAxis;
    rot = glm::rotation(newRightSide, glm::cross(velocityDirection, -zAxis)) * rot;

//    setParentTransform(GeometricTransformation(m_particle->getPosition(),
//                                               rot, getParentStaticTransform().getScale()));

    //Here tux should be aligned with its original velocity, facing the sun and praising it like a good sun knight should

    //We will make a crushed look on our poor tux

    Body->addParentTransformKeyframe(0*timeStep+time, GeometricTransformation(position ,
                                                                              glm::normalize(glm::angleAxis(-float(M_PI)/2, zAxis))) );


    //Below Tux should spread its foot a bit because he is goddamn stuck !
    Body->addParentTransformKeyframe(1*timeStep+time, GeometricTransformation(position,
                                                                              glm::normalize(glm::angleAxis(-float(M_PI)/2, zAxis)), glm::vec3(0.9,1.0,1.1)) );

    Body->addParentTransformKeyframe(2*timeStep+time, GeometricTransformation(position,
                                                                              glm::normalize(glm::angleAxis(-float(M_PI)/2, zAxis))) );

    //Here tux will jump out of the snow
    Body->addParentTransformKeyframe(3*timeStep+time, GeometricTransformation(position + glm::vec3(0.0,1.0,0.0),
                                                                              glm::normalize(glm::angleAxis(float(M_PI)/2, zAxis))) );

    //Here Tux should spread its feet and hands a bit because he is goddamn stuck !
    LF->addLocalTransformKeyframe(1.0*timeStep+time, GeometricTransformation(glm::vec3(0), glm::normalize(glm::angleAxis(float(M_PI)/6, yAxis))));
    LF->addLocalTransformKeyframe(2.0*timeStep+time, GeometricTransformation(glm::vec3(0), glm::normalize(glm::angleAxis(0.0f, glm::vec3(0.0)))));
    RF->addLocalTransformKeyframe(1.0*timeStep+time, GeometricTransformation(glm::vec3(0), glm::normalize(glm::angleAxis(float(M_PI)/6, -yAxis))));
    RF->addLocalTransformKeyframe(2.0*timeStep+time, GeometricTransformation(glm::vec3(0), glm::normalize(glm::angleAxis(0.0f, glm::vec3(0.0)))));
    RH->addLocalTransformKeyframe(1.0*timeStep+time, GeometricTransformation(glm::vec3(0), glm::normalize(glm::angleAxis(float(M_PI)/8,zAxis))));
    RH->addLocalTransformKeyframe(2.0*timeStep+time, GeometricTransformation(glm::vec3(0), glm::normalize(glm::angleAxis(0.0f, zAxis))));
    LH->addLocalTransformKeyframe(1.0*timeStep+time, GeometricTransformation(glm::vec3(0), glm::normalize(glm::angleAxis(float(M_PI)/8,zAxis))));
    LH->addLocalTransformKeyframe(2.0*timeStep+time, GeometricTransformation(glm::vec3(0), glm::normalize(glm::angleAxis(0.0f, zAxis))));




}


void PenguinLightedRenderable::generateSnow(Viewer &viewer, ShaderProgramPtr shader,
                                            DynamicSystemPtr systemSnow, DynamicSystemRenderablePtr systemSnowRenderable)
{

    SnowballRenderablePtr SF;
    ParticlePtr particle;
    glm::vec3 pv(0.0);
    glm::vec3 px(0.0);
    float pm = 0.1, pr = 0.15;

    for (int i = -5; i < 5; ++i) {
        for (int j = 0; j < 10; ++j) {
            px = glm::vec3(2*i, 2*j, random(5.0f, 20.0f));
            particle = std::make_shared<Particle>(px, pv, pm, pr);
            SF = std::make_shared<SnowballRenderable>(shader, particle);
            systemSnow->addParticle(particle);
            HierarchicalRenderable::addChild(systemSnowRenderable, SF);
        }
    }
}


void PenguinLightedRenderable::do_animate(float time){

}

void PenguinLightedRenderable::do_draw(){

}

void PenguinLightedRenderable::beforeAnimate(float time){
    if (scheduleStatusChange > 0 && time > scheduleStatusChange){
        m_particle->setFixed(false);
        scheduleStatusChange = -1;
        m_status = PENGUIN_STATUS_SLIDING;
        // remove all keyframes to get the animation right
        Body->clear();
        RF->clear();
        LF->clear();
        RH->clear();
        LH->clear();
    }
    glm::vec3 velocityDirection, yAxis(0, 1, 0), zAxis(0, 0, 1);
    glm::vec3 newRightSide;
    glm::quat rot;

    switch(m_status){
        case PENGUIN_STATUS_STARTING:
        case PENGUIN_STATUS_RECOVERING:
            break;// fully keyframed, nothing to do
        case PENGUIN_STATUS_SLIDING:
            velocityDirection = glm::normalize(m_particle->getVelocity());

            // compute quaternion to align penguin yAxis (head) with velocityDirection
            // we also need nose facing downward, which means the penguin's right side (+z)
            // has to be aligned with cross(velocityDirection, z)
            rot = glm::rotation(yAxis, velocityDirection);
            newRightSide = rot * zAxis;
            rot = glm::rotation(newRightSide, glm::cross(velocityDirection, zAxis)) * rot;
            setParentTransform(GeometricTransformation(m_particle->getPosition(),
                                                       rot, getParentStaticTransform().getScale()));

            m_forceController->updateForce(velocityDirection);
            break;
        case PENGUIN_STATUS_COLIDING:
            break;
        default:
            break;
    }
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

void PenguinLightedRenderable::bindForceController(DynamicSystemRenderablePtr systemRenderable){
    HierarchicalRenderable::addChild(systemRenderable, m_forceController);
}

void PenguinLightedRenderable::setStatus(PenguinStatus status){
    m_status = status;
}

PenguinStatus PenguinLightedRenderable::getStatus(){
    return m_status;
}

const ParticlePtr & PenguinLightedRenderable::getParticle(){
    return m_particle;
}
