/**
 *  HomeNetwork.c
 *  Runs commands to tweak the radio communication according to settings in config.h
 */

#include "HomeNetwork.h"

HomeNetwork::HomeNetwork(int pin1, int pin2, int nodeID) 
{
	RF24 radio(8, 9); // CE & CSN pins
	RF24Network network(radio)
;}

void HomeNetwork::config(void) 
{
	radio.setRetries(retryDelay, retryTimes);
	radio.setPALevel(powerAmplifierLevel);
	radio.setDataRate(dataRate);
}