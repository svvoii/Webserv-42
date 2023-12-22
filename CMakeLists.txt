cmake_minimum_required(VERSION 3.24)
project(webserv)
project(webserv_lib)

add_compile_options(-gdwarf-4 -O1 -fno-limit-debug-info  -Wall -Wextra -Werror)
set(CMAKE_CXX_STANDARD 98)

add_executable(webserv src/main.cpp
        src/Server/Sockets/src/ConnectingSocket.cpp
        src/Server/Sockets/src/SimpleSocket.cpp
        src/Server/Sockets/src/ListeningSocket.cpp
        src/Server/Sockets/src/BindingSocket.cpp
#        src/Server/old/response/ServerResponse.cpp
#        src/Server/old/ServerInit.cpp
#        src/Server/old/ServerExceptions.cpp
#        src/Server/old/Server.cpp
#        src/Server/old/location_synth/SynthFoundExact.cpp
#        src/Server/old/location_synth/LocationSynth.cpp
#        src/Server/old/location_synth/SynthNotFound.cpp
        src/Server/ServerManager/src/ServersManager.cpp
        src/Server/ServerManager/src/Server.cpp
        src/Server/ServerManager/src/HttpRequest.cpp
        src/Server/ServerManager/src/HttpResponse.cpp
        src/Server/request/ClientRequest.cpp
        src/Server/request/ClientRequestURLHandlers.cpp
        src/Server/request/ClientRequestRequestHandlers.cpp
        src/Server/request/ClientRequestURLParamsHandlers.cpp
        src/Server/request/RequestExceptions.cpp
        src/Config/config/ConfigCreate.cpp
        src/Config/config/Config.cpp
        src/Config/config/ConfigParse.cpp
        src/Config/Node.cpp
        src/Config/server_configuration/ServerConfiguration.cpp
        src/Config/server_configuration/ServerConfigurationLocationSearch.cpp
        src/Config/server_configuration/ServerConfigurationLocationHandler.cpp
        src/Config/location/ErrPage.cpp
        src/Config/location/Location.cpp
        src/Config/location/LocationHandleReturn.cpp
        src/Config/location/LimitExcept.cpp


#        src/Server/old/response/ServerResponse.h
#        src/Server/old/Server.h
#        src/Server/old/ServerExceptions.h
        src/Server/request/RequestExceptions.h
        src/Server/request/ClientRequest.h
        src/Config/config/ConfigExceptions.h
        src/Config/config/Config.h
        src/Config/server_configuration/ServerConfiguration.h
        src/Config/Node.h
        src/Config/location/Location.h
        src/Config/location/ErrPage.h
        src/Config/location/LimitExcept.h

        src/Server/Sockets/includes/ListeningSocket.hpp
        src/Server/Sockets/includes/SimpleSocket.hpp
        src/Server/Sockets/includes/BindingSocket.hpp
        src/Server/Sockets/includes/ConnectingSocket.hpp
        src/Server/Sockets/HeaderSockets.hpp
        src/Server/ServerManager/includes/HttpResponse.hpp
        src/Server/ServerManager/includes/HttpRequest.hpp
        src/Server/ServerManager/includes/Server.hpp
        src/Server/ServerManager/includes/ServersManager.hpp
)
add_library(webserv_lib
        src/Server/Sockets/src/ConnectingSocket.cpp
        src/Server/Sockets/src/SimpleSocket.cpp
        src/Server/Sockets/src/ListeningSocket.cpp
        src/Server/Sockets/src/BindingSocket.cpp
#        src/Server/old/response/ServerResponse.cpp
#        src/Server/old/ServerInit.cpp
#        src/Server/old/ServerExceptions.cpp
#        src/Server/old/Server.cpp
#        src/Server/old/location_synth/SynthFoundExact.cpp
#        src/Server/old/location_synth/LocationSynth.cpp
#        src/Server/old/location_synth/SynthNotFound.cpp
        src/Server/ServerManager/src/ServersManager.cpp
        src/Server/ServerManager/src/Server.cpp
        src/Server/ServerManager/src/HttpRequest.cpp
        src/Server/ServerManager/src/HttpResponse.cpp
        src/Server/request/ClientRequest.cpp
        src/Server/request/ClientRequestURLHandlers.cpp
        src/Server/request/ClientRequestRequestHandlers.cpp
        src/Server/request/ClientRequestURLParamsHandlers.cpp
        src/Server/request/RequestExceptions.cpp
        src/Config/config/ConfigCreate.cpp
        src/Config/config/Config.cpp
        src/Config/config/ConfigParse.cpp
        src/Config/Node.cpp
        src/Config/server_configuration/ServerConfiguration.cpp
        src/Config/server_configuration/ServerConfigurationLocationSearch.cpp
        src/Config/server_configuration/ServerConfigurationLocationHandler.cpp
        src/Config/location/ErrPage.cpp
        src/Config/location/Location.cpp
        src/Config/location/LocationHandleReturn.cpp
        src/Config/location/LimitExcept.cpp


#        src/Server/old/response/ServerResponse.h
#        src/Server/old/Server.h
#        src/Server/old/ServerExceptions.h
        src/Server/request/RequestExceptions.h
        src/Server/request/ClientRequest.h
        src/Config/config/ConfigExceptions.h
        src/Config/config/Config.h
        src/Config/server_configuration/ServerConfiguration.h
        src/Config/Node.h
        src/Config/location/Location.h
        src/Config/location/ErrPage.h
        src/Config/location/LimitExcept.h

        src/Server/Sockets/includes/ListeningSocket.hpp
        src/Server/Sockets/includes/SimpleSocket.hpp
        src/Server/Sockets/includes/BindingSocket.hpp
        src/Server/Sockets/includes/ConnectingSocket.hpp
        src/Server/Sockets/HeaderSockets.hpp
        src/Server/ServerManager/includes/HttpResponse.hpp
        src/Server/ServerManager/includes/HttpRequest.hpp
        src/Server/ServerManager/includes/Server.hpp
        src/Server/ServerManager/includes/ServersManager.hpp)

add_subdirectory(test)