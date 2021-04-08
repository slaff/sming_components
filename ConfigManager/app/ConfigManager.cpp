#include "ConfigManager.h"

void ConfigManager::loadConfig(Config &config, bool loadFactoryConf) {
  String file;
  bool isFactoryConfig = false;
  if (!loadFactoryConf && fileExist("config")) {
    file = "config";
  } else if (fileExist("factoryConfig")) {
    file = "factoryConfig";
    isFactoryConfig = true;
  } else {
    return;
  }

  // StaticJsonDocument<512> doc;
  DynamicJsonDocument doc(JSON_OBJECT_SIZE);
  if (Json::loadFromFile(doc, file)) {
    convertToStruct(doc, config);
    doc.clear();
    config.isFactoryConfig = isFactoryConfig;
  } else {
    Serial.println(F("Failed to parse configuration!"));
  }
}

void ConfigManager::saveConfig(Config &config) {
  DynamicJsonDocument doc(JSON_OBJECT_SIZE);
  convertFromStruct(doc, config);

  if (fileExist("config")) {
    fileDelete("config");
  }

  // Serialize JSON to file
  Json::saveToFile(doc, "config");
  doc.clear();
}

void ConfigManager::convertToStruct(JsonDocument &doc, Config &config) {
  sprintf(config.mode, "%.*s", sizeof(config.mode) - 1, doc["mode"] | defaultValues.mode);
  sprintf(config.ssid, "%.*s", sizeof(config.ssid) - 1, doc["ssid"] | defaultValues.ssid);
  sprintf(config.password, "%.*s", sizeof(config.password) - 1, doc["password"] | defaultValues.password);
  sprintf(config.hostname, "%.*s", sizeof(config.hostname) - 1, doc["hostname"] | defaultValues.hostname);
  sprintf(config.ip, "%.*s", sizeof(config.ip) - 1, doc["ip"] | defaultValues.ip);
  sprintf(config.authUsername, "%.*s", sizeof(config.authUsername) - 1, doc["authUsername"] | defaultValues.authUsername);
  sprintf(config.authPassword, "%.*s", sizeof(config.authPassword) - 1, doc["authPassword"] | defaultValues.authPassword);
  sprintf(config.defaultPage, "%.*s", sizeof(config.defaultPage) - 1, doc["defaultPage"] | defaultValues.defaultPage);
  sprintf(config.configPage, "%.*s", sizeof(config.configPage) - 1, doc["configPage"] | defaultValues.configPage);
  sprintf(config.otaAuthHash, "%.*s", sizeof(config.otaAuthHash) - 1, doc["otaAuthHash"] | defaultValues.otaAuthHash);
}

void ConfigManager::convertFromStruct(JsonDocument &doc, Config &config) {
  doc["mode"] = config.mode;
  doc["ssid"] = config.ssid;
  doc["password"] = config.password;
  doc["hostname"] = config.hostname;
  doc["ip"] = config.ip;
  doc["authUsername"] = config.authUsername;
  doc["authPassword"] = config.authPassword;
  doc["defaultPage"] = config.defaultPage;
  doc["configPage"] = config.configPage;
  doc["otaAuthHash"] = config.otaAuthHash;
}
