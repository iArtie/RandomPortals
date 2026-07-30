#include <Geode/modify/PlayLayer.hpp>
#include <Geode/utils/random.hpp>
#include "../utils/RPUtils.hpp"

using namespace geode::prelude;

static const std::vector<std::tuple<int, int, int>> portalTypes = {
    {12, 6, 3}, // I'm mentioning this so no one here misses it: Portal object ID: 12,
                // GameObjectType::CubePortal: 6, portal texture ID: 3
    {13, 5, 4},
    {47, 16, 7},
    {111, 19, 10},
    {660, 26, 13},
    {745, 27, 14},
    {1331, 33, 17},
    {1933, 41, 18}};

static const std::unordered_map<std::string, int> nameToId = {{"Cube", 12},
                                                              {"Ship", 13},
                                                              {"Ball", 47},
                                                              {"Ufo", 111},
                                                              {"Wave", 660},
                                                              {"Robot", 745},
                                                              {"Spider", 1331},
                                                              {"Swing", 1933}};

class $modify(PlayLayer) {
    void addObject(GameObject* obj) {
        PlayLayer::addObject(obj);

        if (Mod::get()->getSettingValue<bool>("freeMode")) {
            auto effect = typeinfo_cast<EffectGameObject*>(obj);

            if (effect) {
                effect->m_cameraIsFreeMode = true;
            }
        }
    }

    void togglePracticeMode(bool practiceMode) {
        if (!Mod::get()->getSettingValue<bool>("easyMode")) {
            PlayLayer::togglePracticeMode(practiceMode);
        }
    }

    void resetLevel() {
        auto easyMode = Mod::get()->getSettingValue<bool>("easyMode");
        auto disableBlending = Mod::get()->getSettingValue<bool>("disableBlending");
        bool skipAll = easyMode && geode::utils::random::chance(0.5);

        if (m_objects && !skipAll) {
            std::unordered_set<int> excludedIDs;

            for (auto key : {"wildcard1", "wildcard2", "wildcard3", "wildcard4"}) {
                auto name = Mod::get()->getSettingValue<std::string>(key);
                if (auto it = nameToId.find(name); it != nameToId.end())
                    excludedIDs.insert(it->second);
            }

            for (auto obj : m_objects->asExt<GameObject>()) {
                if (!obj || excludedIDs.count(obj->m_objectID))
                    continue;

                std::vector<std::tuple<int, int, int>> candidates;
                bool isPortal = false;

                for (auto& portal : portalTypes) {
                    int portalID = std::get<0>(portal);

                    if (portalID == obj->m_objectID) {
                        isPortal = true;
                    } else if (!excludedIDs.count(portalID)) {
                        candidates.push_back(portal);
                    }
                }

                if (!isPortal || candidates.empty())
                    continue;

                int chosenIndex = -1;

                if (easyMode) {
                    if (geode::utils::random::chance(0.5))
                        continue;

                    chosenIndex =
                        geode::utils::random::generate<int>(0, static_cast<int>(candidates.size() - 1));
                } else {
                    chosenIndex =
                        geode::utils::random::generate<int>(0, static_cast<int>(candidates.size() - 1));
                }

                auto newPortal = candidates[chosenIndex];
                obj->m_objectID = std::get<0>(newPortal);
                obj->m_objectType = static_cast<GameObjectType>(std::get<1>(newPortal));
                obj->m_savedObjectType = static_cast<GameObjectType>(std::get<1>(newPortal));

                RPUtils::updatePortalParticle(obj, disableBlending);
            }
        }

        PlayLayer::resetLevel();
    }
};