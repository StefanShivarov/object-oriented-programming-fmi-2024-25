### Builder
Представете си, че имате клас с 15 полета, от които само няколко са задължителни.
Ако се опитате да съберете всичко в един конструктор с 15 аргумента – успех на този, който ще се опита да разбере какво се случва

Вместо това можем да направим следното:
 - да отделим задължителните параметри в конструктора
 - да задаваме незадължителните стойности чрез ясно именовани методи
 - и накрая да създадем обекта по по-четим и контролиран начин

Това води до по-разбираем, гъвкав и поддържан код, особено когато се налага да създаваме обекти с много конфигурации

Нека да разгледаме пример с HTTP заяка. Тя има:
 - задължителни части: метод (GET, POST), URL
 - незадължителни части: headers, body, timeout, cookies и т.н

**Пример**
`HttpRequest.hpp`
```c++
#pragma once

#include <string>
#include <map>

class HttpRequest {
private:
    std::string method;
    std::string url;
    std::map<std::string, std::string> headers;
    std::string body;

    // Частен конструктор
    HttpRequest(const std::string& method, const std::string& url)
        : method(method), url(url) {}

public:
    class Builder {
    private:
        std::string method;
        std::string url;
        std::map<std::string, std::string> headers;
        std::string body;

    public:
        Builder(const std::string& method, const std::string& url)
            : method(method), url(url) {}

        Builder& setHeader(const std::string& key, const std::string& value) {
            headers[key] = value;
            return *this;
        }

        Builder& setBody(const std::string& data) {
            body = data;
            return *this;
        }

        HttpRequest build() {
            HttpRequest request(method, url);
            request.headers = headers;
            request.body = body;
            return request;
        }
    };

    void send() const {
        std::cout << "=== Sending HTTP " << method << " request ===\n";
        std::cout << "URL: " << url << "\n";
        if (!headers.empty()) {
            std::cout << "Headers:\n";
            for (const auto& h : headers) {
                std::cout << "  " << h.first << ": " << h.second << "\n";
            }
        }
        if (!body.empty()) {
            std::cout << "Body: " << body << "\n";
        }
    }
};
```

`main.cpp`
```c++
#include "HttpRequest.h"
#include <iostream>

int main() {
    HttpRequest request = HttpRequest::Builder("POST", "https://api.example.com/data")
        .setHeader("Content-Type", "application/json")
        .setHeader("Authorization", "Bearer token123")
        .setBody(R"({"name": "John", "age": 30})")
        .build();

    request.send();

    return 0;
}
```