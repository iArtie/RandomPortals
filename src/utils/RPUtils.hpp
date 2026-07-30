#pragma once

// calling getSettingValue inside update() is expensive, so we use this instead
template <geode::utils::string::ConstexprString S, typename T>
T const& getSettingFast() {
    static T value = (
        geode::listenForSettingChanges<T>(S.data(), [](T val) {
            value = std::move(val);
        }),
        geode::getMod()->getSettingValue<T>(S.data())
    );
    return value;
}

class RPUtils {
  public:
    static bool isPortalObject(int objectID);
    static bool isBackObject(cocos2d::CCSize size);

    static void updatePortalParticle(GameObject* object, bool disableBlending);
    static void updateBackSprite(GameObject* object, cocos2d::CCSpriteFrameCache* frames, int texIndex);
    static void updateFrontSprite(GameObject* object, cocos2d::CCSpriteFrameCache* frames, int texIndex);
};