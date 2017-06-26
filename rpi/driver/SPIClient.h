/*
 * SPIClient.h
 *
 *  Created on: 20 Feb 2017
 *      Author: pi
 */

#ifndef SPICLIENT_H_
#define SPICLIENT_H_

#include "NavXSPIMessage.h"

class SPIClient {

private:
	bool pigpio_initialized;
	int spi_handle;

public:
	SPIClient();

	bool is_open() { return pigpio_initialized; }

	virtual bool transmit(uint8_t *p_data, uint8_t len);
	virtual bool transmit_and_receive(uint8_t *p_tx_data, uint8_t tx_len, uint8_t *p_rx_data, uint8_t rx_len);

	bool write(NavXSPIMessage& write);
	bool read(NavXSPIMessage& request, uint8_t *p_response, uint8_t response_len);

	template<typename T> bool read(uint8_t bank, uint8_t offset, T& value)
	{
		NavXSPIMessage msg(bank,
				offset,
				sizeof(T));
		uint8_t response_packet[sizeof(T) + 1];
		if(read(msg, response_packet, sizeof(response_packet))){
			value = (T)*((T*)(&response_packet[0]));
			return true;
		}
		return false;
	}

	template<typename T> bool write(uint8_t bank, uint8_t offset, T value)
	{
		NavXSPIMessage msg(bank,
				offset,
				sizeof(T),
				(uint8_t *)&value);
		return write(msg);
	}

	virtual ~SPIClient();
};

#endif /* SPICLIENT_H_ */