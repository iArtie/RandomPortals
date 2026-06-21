#include <Geode/modify/OptionsLayer.hpp>

using namespace geode::prelude;

class $modify(OptionsLayer) {
    void onAccount(CCObject*) {
        auto array = CCArray::create();

        array->addObject(DialogObject::create(
            "RobTop",
            "Nuh uh! You can't login your <cy>account</c> here! you will be <cr>BANNED</c>",
            28, 1, false, { 255, 255, 255 }
        ));

        auto dialog = DialogLayer::createDialogLayer(nullptr, array, 2);
        dialog->animateInRandomSide();
        CCScene::get()->addChild(dialog);
    }
};