#include <Geode/modify/LoadingLayer.hpp>

using namespace geode::prelude;

class $modify(LoadingLayer) {
    bool init(bool refresh) {
        if (!LoadingLayer::init(refresh))
            return false;

        std::filesystem::path zipFilePath = Mod::get()->getResourcesDir() / "RandomPortals.zip";
        std::filesystem::path unzipDir = Mod::get()->getResourcesDir() / "RandomPortals";

        if (!std::filesystem::exists(unzipDir)) {
            auto unzipRes = utils::file::Unzip::intoDir(zipFilePath, unzipDir);
            if (unzipRes.isErr()) {
                log::error("Failed to extract random portal textures: {}", unzipRes.unwrapErr());
                return true;
            }
        }

        auto unzipDirStr = utils::string::pathToString(unzipDir);

        CCFileUtils::get()->addTexturePack(
            CCTexturePack{.m_id = this->getID(), .m_paths = {unzipDirStr}});

        auto GM = GameManager::sharedState();

        if (!GM->getUGV("30")) {
            GM->setUGV("30", true);
        }

        return true;
    }
};
