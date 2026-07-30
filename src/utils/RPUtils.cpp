#include "RPUtils.hpp"

using namespace geode::prelude;

bool RPUtils::isPortalObject(int objectID) {
    return objectID == 12 || objectID == 13 || objectID == 47 || objectID == 111 ||
           objectID == 660 || objectID == 745 || objectID == 1331 || objectID == 1933;
}
bool RPUtils::isBackObject(CCSize size) {
    return size == CCSize(49.f, 77.5f) || size == CCSize(48.75f, 77.5f) ||
           size == CCSize(46.f, 74.5f) || size == CCSize(25.25f, 78.f);
}

void RPUtils::updatePortalParticle(GameObject* object, bool disableBlending) {
    if (!object->m_particle)
        return;

    if (disableBlending) {
        object->m_particle->setBlendFunc({GL_ONE, GL_ZERO});
    } else {
        object->m_particle->setBlendFunc({GL_SRC_ALPHA, GL_ONE});
    }

    switch (object->m_objectID) { // Portal colors remade bc it the original color of the UFO
                               // blends in with the ball and the swing, lol
    case 12:
        object->m_particle->setStartColor({0.f, 1.f, 0.f, 1.f});
        object->m_particle->setEndColor({0.f, 0.85f, 0.f, 1.f});
        break;
    case 13:
        object->m_particle->setStartColor({1.f, 0.f, 1.f, 1.f});
        object->m_particle->setEndColor({0.85f, 0.f, 0.85f, 1.f});
        break;
    case 47:
        object->m_particle->setStartColor({0.85f, 0.05f, 0.05f, 1.f});
        object->m_particle->setEndColor({0.65f, 0.f, 0.f, 1.f});
        break;
    case 111:
        object->m_particle->setStartColor({1.f, 0.55f, 0.f, 1.f});
        object->m_particle->setEndColor({1.f, 0.4f, 0.f, 1.f});
        break;
    case 660:
        object->m_particle->setStartColor({0.f, 0.45f, 1.f, 1.f});
        object->m_particle->setEndColor({0.f, 0.3f, 0.9f, 1.f});
        break;
    case 745:
        object->m_particle->setStartColor({1.f, 1.f, 1.f, 1.f});
        object->m_particle->setEndColor({0.9f, 0.9f, 0.9f, 1.f});
        break;
    case 1331:
        object->m_particle->setStartColor({0.65f, 0.f, 1.f, 1.f});
        object->m_particle->setEndColor({0.5f, 0.f, 0.85f, 1.f});
        break;
    case 1933:
        object->m_particle->setStartColor({1.f, 0.85f, 0.f, 1.f});
        object->m_particle->setEndColor({0.9f, 0.7f, 0.f, 1.f});
        break;
    }
}

void RPUtils::updateBackSprite(GameObject* object, CCSpriteFrameCache* frames, int texIndex) {
    if (!RPUtils::isBackObject(object->getContentSize()))
        return;

    auto name = fmt::format("back_{:02d}.png", texIndex);
    auto frame = frames->spriteFrameByName(name.c_str());

    if (frame) {
        object->setDisplayFrame(frame);
        object->setAnchorPoint({0.960f, 0.495f});
    }
}

void RPUtils::updateFrontSprite(GameObject* object, CCSpriteFrameCache* frames, int texIndex) {
    auto frontName = fmt::format("front_{:02d}.png", texIndex);
    auto frontFrame = frames->spriteFrameByName(frontName.c_str());

    if (!frontFrame)
        return;

    auto tabName = fmt::format("tab_{:02d}.png", texIndex);
    auto guideFrame = frames->spriteFrameByName(tabName.c_str());

    if (object->getChildrenCount() >= 1) {
        auto children = object->getChildrenExt();

        auto* child0 = typeinfo_cast<CCSprite*>(children[0]);
        if (child0) {
            if (children.size() >= 2) {
                Ref<CCSprite> child1 = typeinfo_cast<CCSprite*>(children[1]);
                if (child1 && child1->getParent() == object) {
                    auto worldPos = object->convertToWorldSpace(child1->getPosition());
                    auto worldRotation = object->getRotation() + child1->getRotation();

                    object->removeChild(child1, false);
                    child0->addChild(child1);

                    child1->setPosition(child0->convertToNodeSpace(worldPos));
                    child1->setRotation(worldRotation - child0->getRotation());
                    child1->setAnchorPoint({0.65f, 0.5f});
                    child1->setDisplayFrame(frames->spriteFrameByName("randomPortalIcon.png"));
                }
            }

            child0->setAnchorPoint({1.25f, 0.5f});
            child0->setDisplayFrame(guideFrame);
        }
    }

    object->setDisplayFrame(frontFrame);
    object->setAnchorPoint({0.32f, 0.5f});
}