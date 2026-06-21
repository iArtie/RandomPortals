
#include <Geode/modify/PauseLayer.hpp>
#include <Geode/ui/GeodeUI.hpp>

using namespace geode::prelude;

class $modify(RPPauseLayer, PauseLayer) {
    void customSetup() {
        PauseLayer::customSetup();

        auto menu = getChildByID("right-button-menu");
        if (!menu) return;

        auto sprite = CircleButtonSprite::createWithSpriteFrameName(
            "randomPortalIcon.png", 0.8f,
            CircleBaseColor::Green, CircleBaseSize::MediumAlt
        );
        sprite->setScale(0.6f);

        auto button = CCMenuItemSpriteExtra::create(
            sprite, this, menu_selector(RPPauseLayer::onModSettings)
        );
        button->setID("mod-button"_spr);
        menu->addChild(button);
        menu->updateLayout();
    }

    void onModSettings(CCObject*) {
        geode::openSettingsPopup(Mod::get());
    }

    void onPracticeMode(CCObject * sender) {
        if (Mod::get()->getSettingValue<bool>("easyMode")) {
            FLAlertLayer::create(
                "Practice Mode\n  Disabled",
                "\nYou can't use practice mode with <cy>easy mode</c> option enabled",
                "Ok"
            )->show();
            return;
        }

        PauseLayer::onPracticeMode(sender);
    }
};