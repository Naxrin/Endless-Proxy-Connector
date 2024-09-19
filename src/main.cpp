#include <Geode/modify/CCHttpClient.hpp>

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