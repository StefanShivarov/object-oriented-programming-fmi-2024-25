#pragma once

#include <string>
#include <iostream>

class URL {

private:
    std::string protocol;
    std::string subdomain;
    std::string domain;
   //optional
    std::string path;
    std::string country;

    // Nested Builder
    struct Builder {
        // Required
        std::string protocol;
        std::string subdomain;
        std::string domain;

        // Optional (default-initialized)
        std::string path = "";
        std::string country = "";
        
        Builder(std::string proto, std::string sub, std::string dom)
            : protocol(std::move(proto)),
            subdomain(std::move(sub)),
            domain(std::move(dom)) {
        }

        Builder& setPath(std::string p) {
            path = std::move(p);
            return *this;
        }
        Builder& setCountry(std::string c) {
            country = c;
            return *this;
        }

        URL build() const {
            return URL(*this);
        }
    };

    // Only Builder can construct
    explicit URL(const Builder& b)
        : protocol(b.protocol),
        subdomain(b.subdomain),
        domain(b.domain),
        path(b.path),
        country(b.country) {
    }
public:
    // Static factory for discoverability and encapsulation
    static Builder builder(const std::string& protocol,
        const std::string& subdomain,
        const std::string& domain) {
        return Builder(protocol, subdomain, domain);
    }

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

};

int main() {
    URL url = URL::builder("https", "www", "example.com")
        .setPath("/index.html")
        .setCountry("BGN")
        .build();
    std::cout << url.toString() << std::endl;
    return 0;
}
