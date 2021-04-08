#pragma once

#include <ArduinoJson.h>

struct Config {
    char mode[4];
    char ssid[33];
    char password[65];
    char hostname[65];
    char ip[16];
    char authUsername[33];
    char authPassword[33];
    char defaultPage[32];
    char configPage[32];
    char otaAuthHash[33];
    bool isFactoryConfig;
};

extern Config defaultValues;
extern const int JSON_OBJECT_SIZE;


class ConfigManager {
    public:
        static void loadConfig(Config &config, bool loadFactoryConfig = false);
        static void saveConfig(Config &config);
        static void convertToStruct(JsonDocument &doc, Config &config);
        static void convertFromStruct(JsonDocument &doc, Config &config);
};

