
#include <Geode/modify/PauseLayer.hpp>
#include <Geode/ui/GeodeUI.hpp>

using namespace geode::prelude;

class $modify(RPPauseLayer, PauseLayer) {
    void customSetup() {
        PauseLayer::customSetup();

        auto menu = getChildByID("right-button-menu");
        if (!menu)
            return;

        auto sprite = CircleButtonSprite::createWithSpriteFrameName(
            "randomPortalIcon.png", 0.8f, CircleBaseColor::Green, CircleBaseSize::MediumAlt);
        sprite->setScale(0.6f);

        auto button = CCMenuItemExt::createSpriteExtra(sprite, [this](auto) {
            openSettingsPopup(Mod::get());
        });
        button->setID("mod-button"_spr);
        menu->addChild(button);
        menu->updateLayout();
    }

    void onPracticeMode(CCObject* sender) {
        if (Mod::get()->getSettingValue<bool>("easyMode")) {
            FLAlertLayer::create(
                "Info", "You can't use practice mode with <cy>easy mode</c> option enabled", "Ok")
                ->show();
            return;
        }

        PauseLayer::onPracticeMode(sender);
    }
};