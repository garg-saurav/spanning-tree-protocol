#include "bridge.h"

using namespace std;

Bridge::Bridge(int id, vector<char> lans_list):id(id){
	for(auto i:lans_list){
		this->lans[i]=DP;
	}
	this->root_id=id;
	this->root_port='-';
	this->root_distance=0;
	this->bridge_to_root_id=INT_MAX;
}

bool Bridge::setRootId(int id){
	if(this->root_id==id){
		return false;
	}else{
		this->root_id=id;
		return true;
	}
}

bool Bridge::setRootDistance(int distance){
	if(this->root_distance==distance){
		return false;
	}else{
		this->root_distance=distance;
		return true;
	}
}

bool Bridge::setRootPort(char newPort){
	if(this->root_port==newPort){
		return false;
	}else{
		this->root_port=newPort;
		return true;
	}
}

bool Bridge::setBridgeToRootId(int bridge_id){
	if(this->bridge_to_root_id==bridge_id){
		return false;
	}else{
		this->bridge_to_root_id=bridge_id;
		return true;
	}
}

bool Bridge::setPortType(char port, port_type type){
	if(this->lans[port]==type){
		return false;
	}else{
		this->lans[port]=type;
		// cout<<type<<";;;;;;;;;";
		return true;
	}
}

bool Bridge::receive(int new_root_id, int distance, int bridge_id, char port){ // return if change occured or not

	bool updated = false;

	port_type newPortType=this->lans[port];
	int newRootId=this->root_id;
	int newRootDistance=this->root_distance;
	int newBridgeToRootId=this->bridge_to_root_id;
	char newPort=this->root_port;

	if(new_root_id<(this->root_id)){
		newPortType=RP;
		// cout<<"RP"<<endl;
		newPort=port;
		newRootId=new_root_id;
		newRootDistance=distance+1;
		newBridgeToRootId=bridge_id;
	}else if(new_root_id==this->root_id){
		if(distance<this->root_distance){
			if(distance+1<this->root_distance){
				newRootDistance=distance+1;
				newPort=port;
				newPortType=RP;
				newBridgeToRootId=bridge_id;
			}else{
				if(bridge_id<this->bridge_to_root_id){
					newPort=port;
					newPortType=RP;
					newBridgeToRootId=bridge_id;
				}else if(bridge_id==this->bridge_to_root_id){
					if(port<this->root_port){
						newPort=port;
						newPortType=RP;
					}else if(port>this->root_port){
						newPortType=NP;
					}else{}
				}else{
					newPortType=NP;
				}
			}
		}else if(distance==this->root_distance){
			if(bridge_id<this->id){
				if(port!=this->root_port){
					newPortType=NP;
				}
			}else if(bridge_id>this->id){ // either this->port is NP or DP
				// if NP then no change as some else node is DP for this lan
				// if DP then too no change
				// if RP then too no change
			}else{}
		}else{ // distance > this->root_distance
			// if NP then no change as some else node is DP for this lan
			// if DP then too no change
			// if RP then too no change
		}
	}else{ // new_root_id > this->root_id
		// if NP then no change as some else node is DP for this lan
		// if DP then too no change
		// if RP then too no change
	}

	// do the required updates

	updated = setRootId(newRootId) or updated; // ensure the order for confirm update
	// cout<<this->lans['B']<<" ";
	updated = setRootPort(newPort) or updated;
	updated = setPortType(port,newPortType) or updated;
	// cout<<port<<" "<<newPortType<<"\n";
	// cout<<this->lans['B']<<" ";
	updated = setRootDistance(newRootDistance) or updated;
	updated = setBridgeToRootId(newBridgeToRootId) or updated;

	if(newRootId!=this->root_id){
		for(auto it=this->lans.begin(); it!=this->lans.end(); it++){
			if(it->second==NP){ // if root is changed a previous null port may become designated port
				it->second=DP;	// it will be changed to null in further steps if not required
			}
		}
	}

	return updated;
}

void Bridge::get(vector<int>& conf_message){
	conf_message[0]=this->root_id;
	conf_message[1]=this->root_distance;
	conf_message[2]=this->id;
}

vector<char> Bridge::transfer(string host_src, string host_dst, char port){ // assume spanning tree formed
	// returns list of the ports at which to forward
	
	this->forwarding_table[host_src]=port;
	if(this->forwarding_table.find(host_dst)!=this->forwarding_table.end()){
		return vector<char>(1,this->forwarding_table[host_dst]);
	}else{
		vector<char> res;
		for(auto& i:lans){
			if(i.second!=NP && i.first!=port){
				res.push_back(i.first);
			}
		}
		return res;
	}
}