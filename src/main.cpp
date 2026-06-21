#include <Geode/Geode.hpp>
#include <Geode/modify/GManager.hpp>

using namespace geode::prelude;

class $modify(GManager) { // I create a separate manager to avoid bans, and also disable user logins to prevent any issues, people won't understand sometimes, sadly
    void setup() {
        std::string fileName = m_fileName;
        auto pos = fileName.find(".dat");

        if (pos != std::string::npos) {
            fileName.insert(pos, "randomportals");
        }

        m_fileName = fileName;
        GManager::setup();
    }
};