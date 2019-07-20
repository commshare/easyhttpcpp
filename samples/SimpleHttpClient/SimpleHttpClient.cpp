/*
 * Copyright 2017 Sony Corporation
 */

#include <iostream>
#include <stdexcept>

#include "easyhttpcpp/EasyHttp.h"

void displayUsage(char** argv)
{
    std::cout << "Usage: " << argv[0] << " <url>" << std::endl;
    std::cout << "       Fetches the resource identified by <url> and prints it to the standard output"
              << std::endl;
}

void dumpResponse(easyhttpcpp::Response::Ptr pResponse)
{
    std::cout << "Http status code: " << pResponse->getCode() << std::endl;
    std::cout << "Http status message: " << pResponse->getMessage() << std::endl;
    std::cout << "Http response headers:\n" << pResponse->getHeaders()->toString() << std::endl;

    // dump response body if text
    const std::string contentType = pResponse->getHeaderValue("Content-Type", "");
    if (Poco::isubstr<std::string>(contentType, "text/html") != std::string::npos) {
        std::cout << "Http response body:\n" << pResponse->getBody()->toString() << std::endl;
    }
}
/*
怎么支持ssl
Usage: G:\NNNNET\myeasyhttp\win32\Release\sync_client.exe <url>
	   Fetches the resource identified by <url> and prints it to the standard output
HTTP GET url: https://github.com/commshare/poco1.7.9
Error occurred: EASYHTTPCPP-ERR-100704: SSL error occurred in sendRequest.
[scheme=https, host=github.com] message=[Error during handshake: The function requested is not supported]
*/
int main(int argc, char** argv)
{
    // need a url to execute easyhttpcpp http client
    if (argc < 2) {
        displayUsage(argv);
       // return 1;
    }
    std::string url// = argv[1];
	= "https://github.com/commshare/poco1.7.9";
    // HTTP GET the url
    std::cout << "HTTP GET url: " << url << std::endl;

    try {
        // cache dir = current working dir; cache size = 100 KB
        easyhttpcpp::HttpCache::Ptr pCache = easyhttpcpp::HttpCache::createCache(Poco::Path::current(), 1024 * 100);

        // a default http connection pool
        easyhttpcpp::ConnectionPool::Ptr pConnectionPool = easyhttpcpp::ConnectionPool::createConnectionPool();

        // configure http cache and connection pool instance (optional but recommended)
        easyhttpcpp::EasyHttp::Builder httpClientBuilder;
        httpClientBuilder.setCache(pCache)
                .setConnectionPool(pConnectionPool);

        // create http client
        easyhttpcpp::EasyHttp::Ptr pHttpClient = httpClientBuilder.build();

        // create a new request and execute synchronously
        easyhttpcpp::Request::Builder requestBuilder;
        easyhttpcpp::Request::Ptr pRequest = requestBuilder.setUrl(url).build();
        easyhttpcpp::Call::Ptr pCall = pHttpClient->newCall(pRequest);
        easyhttpcpp::Response::Ptr pResponse = pCall->execute();

        if (!pResponse->isSuccessful()) {
            std::cout << "HTTP GET Error: (" << pResponse->getCode() << ")" << std::endl;
        } else {
            std::cout << "HTTP GET Success!" << std::endl;
        }

        // dump response
        dumpResponse(pResponse);
    } catch (const std::exception& e) {
        std::cout << "Error occurred: " << e.what() << std::endl;
    }

    return 0;
}

/*去掉NDEBUG
Usage: G:\NNNNET\myeasyhttp\win32\Release\sync_client.exe <url>
	   Fetches the resource identified by <url> and prints it to the standard output
HTTP GET url: https://github.com/commshare/poco1.7.9
2019/07/21 03:45:56 [23764:0] EASYHTTPCPP_ConnectionPoolInternal LogLv=D line=29 create. this=[01515FD0]
2019/07/21 03:45:56 [23764:0] EASYHTTPCPP_HttpEngine LogLv=D line=216 request is available to cache.
2019/07/21 03:45:56 [23764:0] EASYHTTPCPP_HttpFileCache LogLv=D line=56 getMetadata key=06c7c77b7269d0981ff097eea889025c6baa4bc7
2019/07/21 03:45:56 [23764:0] EASYHTTPCPP_LruCacheByDataSizeStrategy LogLv=D line=102 get: not found key. [06c7c77b7269d0981ff097eea889025c6baa4bc7]
2019/07/21 03:45:56 [23764:0] EASYHTTPCPP_HttpFileCache LogLv=D line=59 getMetadata : [06c7c77b7269d0981ff097eea889025c6baa4bc7] not found in cache.
2019/07/21 03:45:56 [23764:0] EASYHTTPCPP_CacheManager LogLv=D line=38 Cache[1] getMetadata : not found.
2019/07/21 03:45:56 [23764:0] EASYHTTPCPP_HttpCacheInternal LogLv=D line=121 cache not found.
2019/07/21 03:45:56 [23764:0] EASYHTTPCPP_ConnectionPoolInternal LogLv=D line=104 create HTTPSClientSession.
2019/07/21 03:45:56 [23764:0] EASYHTTPCPP_ConnectionInternal LogLv=D line=32 create this=[015AE938] url=[https://github.com/commshare/poco1.7.9]
2019/07/21 03:45:56 [23764:0] EASYHTTPCPP_ConnectionPoolInternal LogLv=D line=139 createConnection: insert connection=[015AE938]
2019/07/21 03:45:56 [23764:0] EASYHTTPCPP_HttpEngine LogLv=D line=419 Poco HTTPRequest:
2019/07/21 03:45:56 [23764:0] EASYHTTPCPP_HttpEngine LogLv=D line=420 method=GET
2019/07/21 03:45:56 [23764:0] EASYHTTPCPP_HttpEngine LogLv=D line=446 sendRequest: SSL exception. [scheme=https, host=github.com] message=[Error during handshake: The function requested is not supported]
2019/07/21 03:45:56 [23764:0] EASYHTTPCPP_HttpEngine LogLv=D line=297 sendRequestAndReceiveResponseWithRetryByConnection: other HttpException. [EASYHTTPCPP-ERR-100704: SSL error occurred in sendRequest. [scheme=https, host=github.com] message=[Error during handshake: The function requested is not supported]]
2019/07/21 03:45:56 [23764:0] EASYHTTPCPP_ConnectionPoolInternal LogLv=D line=162 removeConnectionWithoutLock: removed Connection from ConnectionPool. connection=[015AE938]
2019/07/21 03:45:56 [23764:0] EASYHTTPCPP_QueuedThreadPool LogLv=D line=131 shutdown was executed
2019/07/21 03:45:56 [23764:0] EASYHTTPCPP_QueuedThreadPool LogLv=D line=152 shutdownAndJoinAll was executed
Error occurred: EASYHTTPCPP-ERR-100704: SSL error occurred in sendRequest. [scheme=https, host=github.com] message=[Error during handshake: The function requested is not supported]

G:\NNNNET\myeasyhttp\win32\Release\sync_client.exe (进程 23764)已退出，返回代码为: 0。
若要在调试停止时自动关闭控制台，请启用“工具”->“选项”->“调试”->“调试停止时自动关闭控制台”。
按任意键关闭此窗口...


*/