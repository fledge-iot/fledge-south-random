/*
 * Fledge south plugin.
 *
 * Copyright (c) 2018 Dianomic Systems
 *
 * Released under the Apache 2.0 Licence
 *
 * Author: Massimiliano Pinto
 */
#include <random.h>
#include <plugin_api.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string>
#include <logger.h>
#include <plugin_exception.h>
#include <config_category.h>
#include <version.h>

using namespace std;

#define PLUGIN_NAME "Random"
#define CONFIG	"{\"plugin\" : { \"description\" : \"" PLUGIN_NAME " data generation plugin\", " \
			"\"type\" : \"string\", \"default\" : \"" PLUGIN_NAME "\", \"readonly\" : \"true\"}, " \
		"\"asset\" : { \"description\" : \"Asset name\", " \
			"\"type\" : \"string\", \"default\" : \"Random\", \"displayName\": \"Asset Name\", \"mandatory\": \"true\" } } "
		  
/**
 * The Random plugin interface
 */
extern "C" {

/**
 * The plugin information structure
 */
static PLUGIN_INFORMATION info = {
	PLUGIN_NAME,              // Name
	VERSION,                  // Version
	SP_CONTROL,   		  // Flags
	PLUGIN_TYPE_SOUTH,        // Type
	"1.0.0",                  // Interface version
	CONFIG                    // Default configuration
};

/**
 * Return the information about this plugin
 */
PLUGIN_INFORMATION *plugin_info()
{
	return &info;
}

/**
 * Initialise the plugin, called to get the plugin handle
 */
PLUGIN_HANDLE plugin_init(ConfigCategory *config)
{
	Random *random = new Random();

	if (config->itemExists("asset"))
	{
		random->setAssetName(config->getValue("asset"));
	}
	else
	{
		random->setAssetName("Random");
	}

	return (PLUGIN_HANDLE)random;
}

/**
 * Start the Async handling for the plugin
 */
void plugin_start(PLUGIN_HANDLE handle)
{
}

/**
 * Poll for a plugin reading
 */
Reading plugin_poll(PLUGIN_HANDLE handle)
{
	Random *random = static_cast<Random *>(handle);

	return random->takeReading();
}

/**
 * Reconfigure the plugin
 */
void plugin_reconfigure(PLUGIN_HANDLE *handle, string& newConfig)
{
	ConfigCategory  config("random", newConfig);
	Random          *random = static_cast<Random *>(*handle);

	if (config.itemExists("asset"))
	{
		random->setAssetName(config.getValue("asset"));
	}
}

/**
 * Shutdown the plugin
 */
void plugin_shutdown(PLUGIN_HANDLE handle)
{
	Random *random = static_cast<Random *>(handle);

	delete random;
}

bool plugin_write(PLUGIN_HANDLE handle, string& name, string& value)
{
	Random *random = static_cast<Random *>(handle);

	return random->write(name, value);
}

bool plugin_operation(PLUGIN_HANDLE handle, string& operation, int count, PLUGIN_PARAMETER **params)
{
	Random *random = static_cast<Random *>(handle);

	return random->operation(operation, count, params);
}
};
