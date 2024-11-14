#include <Geode/modify/CCHttpClient.hpp>
#include <Geode/modify/SongInfoLayer.hpp>

using namespace geode::prelude;

std::string replace(std::string haystack, std::string needle, std::string replacement) {
    auto index = haystack.find(needle);

    if (std::string::npos != index) {
        return haystack.replace(index, needle.length(), replacement);
    }

    return haystack;
}

class $modify(_, CCHttpClient) {
	void send(CCHttpRequest* req)
    {
		std::string url = req->getUrl();

        std::string old_server_host = "www.boomlings.com/database";
        std::string new_server = "https://endless-services.zhazha120.cn/api/EndlessProxy/GeometryDash";

        if (Mod::get()->getSettingValue<bool>("Enabled")){
            url = replace(url, "http://" + old_server_host, new_server);
            url = replace(url, "https://" + old_server_host, new_server);
	    }

        auto final_url = url.c_str();
	    req->setUrl(final_url);

        CCHttpClient::send(req);
    }
};

#ifndef GEODE_IS_MACOS
class $modify(MySongInfoLayer, SongInfoLayer) {
    bool init(gd::string p0, gd::string p1, gd::string p2, gd::string p3, gd::string p4, gd::string p5, int p6, gd::string p7, int p8) {
        if (!SongInfoLayer::init(p0, p1, p2, p3, p4, p5, p6, p7, p8))
            return false;
        
        auto layer = static_cast<CCNode*>(getChildren()->objectAtIndex(0));
        auto menu = static_cast<CCMenu*>(layer->getChildren()->objectAtIndex(3));

        auto dldBtn = static_cast<CCNode*>(menu->getChildren()->objectAtIndex(2));
        auto pos = dldBtn->getPosition();
        dldBtn->setPosition(CCPoint(pos.x, pos.y+10.f));

        auto proxySpr = ButtonSprite::create("Download from Endless Proxy", "bigFont.fnt", "GJ_button_01.png");
        proxySpr->setScale(0.6);
        auto proxyBtn = CCMenuItemSpriteExtra::create(proxySpr, this, menu_selector(MySongInfoLayer::onProxyWebPage));
        proxyBtn->setPosition(CCPoint(pos.x, pos.y-30.f));

        menu->addChild(proxyBtn);
        return true;
    }

    void onProxyWebPage(CCObject*) {

        std::string link = "start https://endless-services.zhazha120.cn/#/endless-proxy/newgrounds/audios/" + std::to_string(m_songID);
        system(link.c_str());
    }
};
#endif
