#ifndef BRIDGE_H
#define BRIDGE_H

#include<iostream>
#include<map>
#include<string>
#include<vector>
#include<climits>

enum port_type
{
	RP,
	DP,
	NP,
};

class Bridge{
public:
	const int id;
	std::map<char,port_type> lans;
	int root_id;
	int root_distance;
	int bridge_to_root_id;
	char root_port;
	std::map<std::string, char> forwarding_table;

	Bridge(int id, std::vector<char> lans_list); // constructor
	bool setRootId(int id);
	bool setRootPort(char port);
	bool setRootDistance(int distance);
	bool setBridgeToRootId(int bridge_id);
	bool setPortType(char port, port_type type);

	bool receive(int new_root_id, int distance, int bridge_id, char port);

	void get(std::vector<int>& conf_message);
	std::vector<char> transfer(std::string host_src, std::string host_dst, char port);

};

#endif

