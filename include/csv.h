#ifndef _CSV_H
#define _CSV_H
/*
 * Fledge south service plugin
 *
 * Copyright (c) 2018 Dianomic Systems
 *
 * Released under the Apache 2.0 Licence
 *
 * Author: Mark Riddoch
 */
#include <reading.h>
#include <config_category.h>
#include <thread>


class Csv {
	public:
		Csv();
		~Csv();
		Reading		nextValue();
	void	setAssetName(const std::string& assetName)
		{
			m_asset = assetName;
		}
	void	setFile(const std::string& file)
		{
			m_file = file;
		}
	void	configure(ConfigCategory *config);
	void	start();
	void	pollThread();
	void	registerIngest(void *data, void (*cb)(void *, Reading))
		{
			m_ingest = cb;
			m_data = data;
		}

	private:
		std::string	m_asset;
		std::string	m_file;
		FILE		*m_fp;
		std::thread	*m_thread;
		unsigned int	m_sleepInterval;
		bool		m_running;
		void		*m_data;
		void		(*m_ingest)(void *, Reading);
};
#endif
