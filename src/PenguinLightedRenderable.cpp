//
// Created by clemenre on 4/10/17.
//

#include "../include/PenguinLightedRenderable.hpp"
#include <glm/gtx/quaternion.hpp>


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

    HierarchicalRenderable::addChild(Body, RH);
    HierarchicalRenderable::addChild(Body, LH);
    HierarchicalRenderable::addChild(Body, RF);
    HierarchicalRenderable::addChild(Body, LF);

    m_status = PENGUIN_STATUS_STARTING;
    m_particle = std::make_shared<Particle>(glm::vec3(0, 0, 0), glm::vec3(0), 5, 0.7);

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
    m_particle->setPosition(position);
}
void PenguinLightedRenderable::do_animate(float time){

}

void PenguinLightedRenderable::do_draw(){

}

void PenguinLightedRenderable::beforeAnimate(float time){
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

void PenguinLightedRenderable::setStatus(PenguinStatus status){
    m_status = status;
}

PenguinStatus PenguinLightedRenderable::getStatus(){
    return m_status;
}

const ParticlePtr & PenguinLightedRenderable::getParticle(){
    return m_particle;
}
