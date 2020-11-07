#ifndef BRIDGESIM_H
#define BRIDGESIM_H

#include "bridge.h"
#include<queue>
#include<map>

void simulate(std::vector<Bridge>& bridges, std::map<char, std::vector<int> >& lan_to_bridgeIds, int trace);
void transfer_simulate(std::vector<Bridge>& bridges, std::map<char, std::vector<int> >& lan_to_bridgeIds, std::map<std::string,char>& host_to_lan, std::string host_src, std::string host_dst, int trace);

#endif