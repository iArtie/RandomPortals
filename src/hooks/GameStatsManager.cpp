#include <Geode/modify/GameStatsManager.hpp>

using namespace geode::prelude;

class $modify(GameStatsManager) {
    bool isItemUnlocked(UnlockType type, int id) {
        if (Mod::get()->getSettingValue<bool>("practice-music")) {
            if (type == UnlockType::GJItem && id == 17) {
                return true;
            }
        }
        return true;
    }
};