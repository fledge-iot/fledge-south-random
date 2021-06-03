/*
 * Fledge south service plugin
 *
 * Copyright (c) 2018 Dianomic Systems
 *
 * Released under the Apache 2.0 Licence
 *
 * Author: Massimiliano Pinto
 */
#include <random.h>
#include <reading.h>
#include <plugin_api.h>
#include <logger.h>

/**
 * Constructor for the random "sensor"
 */
Random::Random()
{
	srand(time(0));
	m_lastValue = rand() % 100;
}

/**
 * Destructor for the random "sensor"
 */
Random::~Random()
{
}

/**
 * Take a reading from the random "sensor"
 */
Reading	Random::takeReading()
{
	m_lastValue += ((rand() % 100) > 50 ? 1 : -1) *
		((rand() % 100) / 20);
	DatapointValue value(m_lastValue);
	return Reading(m_asset_name,new Datapoint("random", value));
}

/**
 * Setpoint write operation
 */
bool Random::write(const std::string& name, const std::string value)
{
	Logger::getLogger()->error("Random plugin does not support write operations");
	return false;
}

/**
 * SetPoint operation. We support reseeding the random number generator
 */
bool Random::operation(const std::string& operation, int count, PLUGIN_PARAMETER **params)
{
	if (operation.compare("seed") == 0)
	{
		if (count)
		{
			if (params[0]->name.compare("seed"))
			{
				long seed = strtol(params[0]->value.c_str(), NULL, 10);
				srand(seed);
			}
			else
			{
				return false;
			}
		}
		else
		{
			srand(time(0));
		}
		Logger::getLogger()->info("Reseeded random number generator");
		return true;
	}
	Logger::getLogger()->error("Unrecognised operation %s", operation.c_str());
	return false;
}
