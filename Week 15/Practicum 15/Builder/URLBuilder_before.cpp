//#pragma once

#include <string>
#include <iostream>
using namespace std;
class URL {

public:

    // Convert to string
    std::string toString() const {
        std::string url = protocol + "://" + subdomain + "." + domain;
        if (!path.empty()) url += path;
        if (!country.empty()) {
            url += "?country=";
            url += country;
        }
        return url;
    }
    URL(const string& _protocol, const string& _subdomain, const string& _domain,
        const string& _path = "",const string& _country = "") :
        protocol(_protocol),
        subdomain(_subdomain),
        domain(_domain),
        path(_path),
        country(_country)
    {

    }

private:
    std::string protocol;
    std::string subdomain;
    std::string domain;
//optional
    std::string path;
    std::string country;

};

int main() {
   /* URL url = URL::builder("https", "www", "example.com")
        .setPath("/index.html")
        .setCountry("BGN")
                   .build();*/
    URL url("https", "www", "example.com", "/index.html");
     std::cout << url.toString() << std::endl;
     return 0;
 }
