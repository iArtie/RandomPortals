#include <Geode/modify/GameManager.hpp>

using namespace geode::prelude;

class $modify(GameManager) {
    bool isIconUnlocked(int id, IconType type) {
        if (Mod::get()->getSettingValue<bool>("unlock-all") == true) {
            return true;
        } else {
            return GameManager::isIconUnlocked(id, type);
        }
    }

    bool isColorUnlocked(int id, UnlockType type) {
        if (Mod::get()->getSettingValue<bool>("unlock-all") == true) {
            return true;
        } else {
            return GameManager::isColorUnlocked(id, type);
        }
    }
};