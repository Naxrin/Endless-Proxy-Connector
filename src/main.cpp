using namespace geode::prelude;

void proxy(CCHttpClient* self, CCHttpRequest* req) {
	auto old_url = req->getUrl();
	auto new_url = std::string(old_url);

	auto old_server = std::string("www.boomlings.com/database");
	auto new_server = std::string("dl.geometrydashchinese.com");

	auto final_url = new_url.replace(new_url.find(old_server), old_server.length(), new_server).c_str();

	req->setUrl(final_url);

	self->send(req);
}

$execute {
    Mod::get()->hook(
        reinterpret_cast<void*>(
			geode::addresser::getNonVirtual(&cocos2d::extension::CCHttpClient::send)
        ),
        &proxy,
        "cocos2d::extension::CCHttpClient::send",
        tulip::hook::TulipConvention::Thiscall
    );
}

// https://github.com/relativemodder/tiny-gdps-switcher