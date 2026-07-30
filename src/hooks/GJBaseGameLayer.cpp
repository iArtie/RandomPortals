#include <Geode/modify/GJBaseGameLayer.hpp>
#include "../utils/RPUtils.hpp"

using namespace geode::prelude;

class $modify(GJBaseGameLayer) {
    struct Fields {
        int currentTextureIndex = 1;
        float timeSinceLastTextureUpdate = 0.f;
    };

    void update(float dt) {
        GJBaseGameLayer::update(dt);

        auto fields = m_fields.self();

        if (m_isEditor && !getSettingFast<"enable-in-editor", bool>())
            return;

        auto playLayer = PlayLayer::get();

        if (playLayer && getSettingFast<"easyMode", bool>() && playLayer->m_isPracticeMode) {
            playLayer->onQuit();
        }

        fields->timeSinceLastTextureUpdate += dt;

        if (fields->timeSinceLastTextureUpdate >= 0.05f) {
            fields->timeSinceLastTextureUpdate = 0.f;
            fields->currentTextureIndex = fields->currentTextureIndex % 15 + 1;
        }

        if (!m_objects)
            return;

        auto frames = CCSpriteFrameCache::sharedSpriteFrameCache();
        auto texIndex = fields->currentTextureIndex;
        auto disableBlending = getSettingFast<"disableBlending", bool>();

        for (auto* objects : m_objects->asExt<GameObject>()) {
            if (objects->getZOrder() == -89 ||
                objects->getZOrder() == -90) { // Yeah, the only way to get the back object for the
                                               // portal is only with Z order, sadly, yes
                RPUtils::updateBackSprite(objects, frames, texIndex);
            }

            if (RPUtils::isPortalObject(objects->m_objectID)) {
                RPUtils::updateFrontSprite(objects, frames, texIndex);
                RPUtils::updatePortalParticle(objects, disableBlending);
            }
        }
    }
};
