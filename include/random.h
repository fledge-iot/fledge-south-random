#ifndef _RANDOM_H
#define _RANDOM_H
/*
 * Fledge south service plugin
 *
 * Copyright (c) 2018 Dianomic Systems
 *
 * Released under the Apache 2.0 Licence
 *
 * Author: Mark Riddoch, Massimiliano Pinto
 */
#include <reading.h>
#include <plugin_api.h>

class Random {
	public:
		Random();
		~Random();
		Reading		takeReading();
	void	setAssetName(const std::string& assetName)
		{
			m_asset_name = assetName;
		}
	bool	write(const std::string& name, const std::string value);
	bool	operation(const std::string& operaiton, int count, PLUGIN_PARAMETER **params);

	private:
		long		m_lastValue;
		std::string	m_asset_name;
};
#endif
